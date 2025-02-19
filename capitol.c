#include "capitol.h"
#include <stdlib.h>

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
