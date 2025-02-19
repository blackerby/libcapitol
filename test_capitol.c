#include "test-framework/unity.h"
#include "capitol.h"
#include <string.h>

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

static void test_tokenize_no_version(void)
{
	cite_token_t expected = (cite_token_t) { "118", "hr", "8070", NULL };
	cite_token_t actual = tokenize("118hr8070");

	check_token(expected, actual);
}

static void test_tokenize_with_version(void)
{
	cite_token_t expected = (cite_token_t) { "118", "hr", "8070", "ih" };
	cite_token_t actual = tokenize("118hr8070ih");

	check_token(expected, actual);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_tokenize_no_version);
	RUN_TEST(test_tokenize_with_version);

	return UNITY_END();
}
