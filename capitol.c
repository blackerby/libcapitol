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

bool obj_eq(char *obj, char *hcand, char *scand)
{
	return (strcmp(obj, hcand) == 0)
	       || (strcmp(obj, scand) == 0);
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
	if (obj_eq(type_token, "hr", "s"))
		type = BILL;
	else if (obj_eq(type_token, "hres", "sres"))
		type = RESOLUTION;
	else if (obj_eq(type_token, "hconres", "sconres"))
		type = CONCURRENT_RESOLUTION;
	else if (obj_eq(type_token, "hjres", "sjres"))
		type = JOINT_RESOLUTION;
	else if (obj_eq(type_token, "hrpt", "srpt"))
		type = REPORT;
	// TODO: error
	
	citation_t citation;
	citation.congress = congress;
	citation.chamber = chamber;
	citation.object_type = type;
	citation.number = number;
	citation.version = token.version;

	return citation;
}
