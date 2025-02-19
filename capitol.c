#include "capitol.h"
#include <stdlib.h>
#include <string.h>

char *read(char *val, char *input, char start, char end)
{
	char *p = val;
	while (*input >= start && *input <= end) {
		*p++ = *input++;
	}
	*p = '\0';

	return input;
}

cite_token_t tokenize(char *input)
{

	char *congress = malloc(sizeof(char) * 3 + 1);
	input = read(congress, input, '0', '9');

	char *object_type = malloc(sizeof(char) * 7 + 1);
	input = read(object_type, input, 'a', 'z');

	char *number = malloc(sizeof(char) * 5 + 1);
	input = read(number, input, '0', '9');

	cite_token_t token;
	token.congress = congress;
	token.object_type = object_type;
	token.number = number;

	if (*input) {
		char *version = malloc(sizeof(char) * 3 + 1);
		input = read(version, input, 'a', 'z');
		token.version = version;
	} else {
		token.version = NULL;
	}
	return token;
}

citation_t parse(cite_token_t token)
{
	int congress = atoi(token.congress);
	int number = atoi(token.number);

	chamber_t chamber;
	switch (token.object_type[0]) {
		case 'h':
			chamber = HOUSE;
			break;
		case 's':
			chamber = SENATE;
			break;
		// TODO: error
	}

	cong_object_t type;
	char *type_token = token.object_type;
	if (strcmp(type_token, "hr") == 0)
		type = HOUSE_BILL;
	else if (strcmp(type_token, "s") == 0)
		type = SENATE_BILL;
	else if (strcmp(type_token, "hres") == 0)
		type = HOUSE_RESOLUTION;
	else if (strcmp(type_token, "sres") == 0)
		type = SENATE_RESOLUTION;
	else if (strcmp(type_token, "hconres") == 0)
		type = HOUSE_CONCURRENT_RESOLUTION;
	else if (strcmp(type_token, "sconres") == 0)
		type = SENATE_CONCURRENT_RESOLUTION;
	else if (strcmp(type_token, "hjres") == 0)
		type = HOUSE_JOINT_RESOLUTION;
	else if (strcmp(type_token, "sjres") == 0)
		type = SENATE_JOINT_RESOLUTION;
	else if (strcmp(type_token, "hrpt") == 0)
		type = HOUSE_REPORT;
	else if (strcmp(type_token, "srpt") == 0)
		type = SENATE_REPORT;
	// TODO: error
	
	citation_t citation;
	citation.congress = congress;
	citation.chamber = chamber;
	citation.object_type = type;
	citation.number = number;
	citation.version = token.version;

	return citation;
}
