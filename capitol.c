#include "capitol.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool obj_eq(char *obj, char *hcand, char *scand)
{
	return (strcmp(obj, hcand) == 0)
	       || (strcmp(obj, scand) == 0);
}

char *ordinal(int congress)
{
	int last = congress % 10;

	switch (last) {
		case 1: return "st";
		case 2: return "nd";
		case 3: return "rd";
		default: return "th";
	}
}

cite_token_t tokenize(char *input)
{
	char *congress = malloc(sizeof(char) * 3 + 1);
	char *p = congress;
	while (*input >= '0' && *input <= '9') {
		*p++ = *input++;
	}
	*p = '\0';

	char *object_type = malloc(sizeof(char) * 7 + 1);
	p = object_type;
	while (*input >= 'a' && *input <= 'z') {
		*p++ = *input++;
	}
	*p = '\0';

	char *number = malloc(sizeof(char) * 5 + 1);
	p = number;
	while (*input >= '0' && *input <= '9') {
		*p++ = *input++;
	}
	*p = '\0';

	cite_token_t token;
	token.congress = atoi(congress);
	free(congress);
	token.object_type = malloc(sizeof(char) * strlen(object_type) + 1);
	strcpy(token.object_type, object_type);
	free(object_type);
	token.number = atoi(number);
	free(number);

	if (*input) {
		char *version = malloc(sizeof(char) * 3 + 1);
		p = version;
		while (*input >= 'a' && *input <= 'z') {
			*p++ = *input++;
		}
		*p = '\0';
		token.version = malloc(sizeof(char) * strlen(version) + 1);
		strcpy(token.version, version);
		free(version);
	} else {
		token.version = NULL;
	}
	return token;
}

citation_t parse(cite_token_t token)
{
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
	citation.congress = token.congress;
	citation.chamber = chamber;
	citation.object_type = type;
	citation.number = token.number;
	if (token.version) {
		citation.version = malloc(sizeof(char) * strlen(token.version) + 1);
		strcpy(citation.version, token.version);
	} else {
		citation.version = NULL;
	}
	
	free(token.object_type);
	if (token.version) free(token.version);
	return citation;
}

void url(citation_t citation, char *out)
{
	char *chamber;
	if (citation.chamber == HOUSE)
		chamber = "house";
	else if (citation.chamber == SENATE)
		chamber = "senate";

	char *collection;
	char *type;
	switch (citation.object_type) {
		case BILL:
			collection = "bill";
			type = "bill";
			break;
		case RESOLUTION:
			collection = "bill";
			type = "resolution";
			break;
		case CONCURRENT_RESOLUTION:
			collection = "bill";
			type = "concurrent-resolution";
			break;
		case JOINT_RESOLUTION:
			collection = "bill";
			type = "joint-resolution";
			break;
		case REPORT:
			collection = "congressional-report";
			type = "report";
			break;
	}

	char url[256];
	sprintf(url, "%s/%s/%d%s-congress/%s-%s/%d", BASE_URL, collection, citation.congress, ordinal(citation.congress), chamber, type, citation.number);
	if (citation.version) {
		strcat(url, "/text/");
		strcat(url, citation.version);
	}

	strcpy(out, url);
	out[strlen(url)] = '\0';
}

void convert_citation(char *input, char *out)
{
	cite_token_t token = tokenize(input);
	citation_t citation = parse(token);
	url(citation, out);
	if (citation.version)
		free(citation.version);
}

