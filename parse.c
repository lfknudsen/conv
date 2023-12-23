#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "conv.h"

// TODO: Print custom message based on what user attempted to do.
void error_msg(char *program_name) {
	fprintf(stderr, "%s: Could not parse input.\nUsage:\n./conv <VAL> <FROM> [to] <TO>\n\
./conv <FROM> <TO>\n\
Case insensitive.\n\
Example:\n./conv 100 JPY DKK\n", program_name);
	return;
}

// Parse input so that it can be passed to the correct sub-procedure.
// It is caller's responsibility to free the returned object. Can use free_input to do so.
int parse_input(struct parsed_input *input, int argc, char *argv[]) {
	// Check correctness of input.
	char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int unit_from_pos = 2, unit_to_pos = 3; // which arguments correspond to the unit codes
	double value = 1.0;
	// <unit> <unit>
	if (argc == 3)
		{ unit_from_pos = 1; unit_to_pos = 2; }
	// <num> <unit> to <unit>
	else if (argc == 5)
		{ unit_from_pos = 2; unit_to_pos = 4; }
	// <unit> to <unit> -- or -- <num> <unit> to <unit> -- or -- <num> <unit> <unit>
	if (argc == 5 || argc == 4)
		{ value = atof(argv[1]); }
	// <unit> to <unit> -- or -- <num> <unit> <unit>
	if (argc == 4 && value == 0.0 && strcmp(argv[2],"to") == 0)
		{ value = 1.0; unit_from_pos = 1; unit_to_pos = 3; }

	// Print help message if
	// * incorrect number of arguments.
	// * there isn't a valid value + two (potentially) valid unit codes.
	//		Potentially valid country codes have length 3,
	//		only have letters from the (English) alphabet,
	//		and are not identical.
	if (
		(argc > 5 || argc < 3)
		||
		(!(
			   value != 0.0
			&& strlen(argv[unit_from_pos]) == 3
			&& strlen(argv[unit_to_pos]) == 3
		  	&& strspn(argv[unit_from_pos], alphabet) == 3
			&& strspn(argv[unit_to_pos], alphabet) == 3
			&& strcmp(argv[unit_from_pos], argv[unit_to_pos]) != 0
		))
	) {
		error_msg(argv[0]);
		return 1;
	}
	input->type		= Currency;
	input->val		= value;
	input->from_pos = unit_from_pos;
	input->to_pos	= unit_to_pos;
	strcpy(input->from, argv[unit_from_pos]);
	strcpy(input->to, argv[unit_to_pos]);
	return 0;
}
