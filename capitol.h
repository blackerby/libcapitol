#ifndef CAPITOL_H
#define CAPITOL_H

#include <stdbool.h>

#define BASE_URL "https://www.congress.gov"

typedef enum {
	HOUSE,
	SENATE
} chamber_t;

typedef enum {
	BILL,
	RESOLUTION,
	CONCURRENT_RESOLUTION,
	JOINT_RESOLUTION,
	REPORT
} cong_object_t;

typedef struct {
	int congress;
	char *object_type;
	int number;
	char *version;
} cite_token_t;

typedef struct {
	int congress;
	chamber_t chamber;
	cong_object_t object_type;
	int number;
	char *version;
} citation_t;

char *read(char *val, char *input, char start, char end);
cite_token_t tokenize(char *input);
citation_t parse(cite_token_t token);
bool obj_eq(char *obj, char *hcand, char *scand);
void url(citation_t citation, char *out);
char *ordinal(int congress);
void convert_citation(char *input, char *out);

#endif
