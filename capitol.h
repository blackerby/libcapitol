#ifndef CAPITOL_H
#define CAPITOL_H

#define FIRST_CONGRESS 1789

typedef enum {
	HOUSE,
	SENATE
} chamber_t;

typedef enum {
	HOUSE_BILL,
	SENATE_BILL,
	HOUSE_RESOLUTION,
	SENATE_RESOLUTION,
	HOUSE_CONCURRENT_RESOLUTION,
	SENATE_CONCURRENT_RESOLUTION,
	HOUSE_JOIN_RESOLUTION,
	SENATE_JOINT_RESOLUTION,
	HOUSE_REPORT,
	SENATE_REPORT
} cong_object_t;

typedef struct {
	char *congress;
	char *object_type;
	char *number;
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
/*citation_t parse(cite_token_t token);*/

#endif
