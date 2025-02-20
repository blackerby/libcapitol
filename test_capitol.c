#include "test-framework/unity.h"
#include "capitol.h"
#include <stdlib.h>

void setUp(void)
{
}

void tearDown(void)
{
}

static void check_token(cite_token_t expected, cite_token_t actual)
{
	TEST_ASSERT_EQUAL_STRING(expected.congress, actual.congress);
	TEST_ASSERT_EQUAL_STRING(expected.object_type, actual.object_type);
	TEST_ASSERT_EQUAL_STRING(expected.number, actual.number);
	TEST_ASSERT_EQUAL_STRING(expected.version, actual.version);
}

static void check_citation(citation_t expected, citation_t actual)
{
	TEST_ASSERT_EQUAL(expected.congress, actual.congress);
	TEST_ASSERT_EQUAL(expected.chamber, actual.chamber);
	TEST_ASSERT_EQUAL(expected.object_type, actual.object_type);
	TEST_ASSERT_EQUAL(expected.number, actual.number);
	TEST_ASSERT_EQUAL_STRING(expected.version, actual.version);
}

static void test_tokenize_no_version(void)
{
	cite_token_t expected = (cite_token_t) { "118", "hr", "8070", NULL };
	cite_token_t actual = tokenize("118hr8070");

	check_token(expected, actual);
	free(actual.congress);
	free(actual.object_type);
	free(actual.number);
}

static void test_tokenize_with_version(void)
{
	cite_token_t expected = { "118", "hr", "8070", "ih" };
	cite_token_t actual = tokenize("118hr8070ih");

	check_token(expected, actual);
	free(actual.congress);
	free(actual.object_type);
	free(actual.number);
	free(actual.version);
}

static void test_parse_no_version(void)
{
	cite_token_t token = tokenize("118hr8070");
	citation_t expected = { 118, HOUSE, BILL, 8070, NULL };
	citation_t actual = parse(token);

	check_citation(expected, actual);
	free(token.congress);
	free(token.object_type);
	free(token.number);
	free(token.version);
}

static void test_parse_with_version(void)
{
	cite_token_t token = tokenize("118hr8070ih");
	citation_t expected = { 118, HOUSE, BILL, 8070, "ih" };
	citation_t actual = parse(token);

	check_citation(expected, actual);
	free(token.congress);
	free(token.object_type);
	free(token.number);
	free(token.version);
}

static void test_url_no_version(void)
{
	citation_t token = { 118, HOUSE, BILL, 8070, NULL };
	char *expected = "https://www.congress.gov/bill/118th-congress/house-bill/8070";
	char *actual = url(token);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
	free(actual);
}

static void test_url_with_version(void)
{
	citation_t token = { 118, HOUSE, BILL, 8070, "ih" };
	char *expected = "https://www.congress.gov/bill/118th-congress/house-bill/8070/ih";
	char *actual = url(token);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
	free(actual);
}

static void test_convert_no_version(void)
{
	char *expected = "https://www.congress.gov/bill/118th-congress/house-bill/8070";
	char *actual = convert_citation("118hr8070");

	TEST_ASSERT_EQUAL_STRING(expected, actual);
	free(actual);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_tokenize_no_version);
	RUN_TEST(test_tokenize_with_version);
	RUN_TEST(test_parse_no_version);
	RUN_TEST(test_parse_with_version);
	RUN_TEST(test_url_no_version);
	RUN_TEST(test_url_with_version);
	RUN_TEST(test_convert_no_version);

	return UNITY_END();
}
