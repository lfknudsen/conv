/*
* ============================================================================ *
* Parses input strings to determine which sort of conversion needs to happen.  *
* ============================================================================ *
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "conv.h"

#define DEBUG 0 // 0 = false, 1 = print broad help statements, 2 = print granular help statements.

int greedy_substr_exists(char *superstring, char *substring) {
	for (int super_i = 0; super_i < strlen(superstring); super_i++) {
		for (int sub_i = 0; sub_i < strlen(substring); sub_i++) {

		}
	}
}

void upper_case(char* word_a, char* word_b) {
	for (int i = 0; i < strlen(word_a); i++)
	{
		if (word_a[i] > 90) {
			word_a[i] -= 32;
		}
		if (word_b[i] > 90) {
			word_b[i] -= 32;
		}
	}
}

void capitalise(char* word_a, char* word_b) {
	if (DEBUG == 2) printf("Before capitalise(): %s & %s\n", word_a, word_b);
	if (word_a[0] > 90) {
		word_a[0] -= 32;
	}
	if (word_b[0] > 90) {
		word_b[0] -= 32;
	}
	for (int i = 1; i < strlen(word_a); i++)
	{
		if (word_a[i] < 91) {
			word_a[i] += 32;
		}
		if (word_b[i] < 91) {
			word_b[i] += 32;
		}
	}
	if (DEBUG == 2) printf("After capitalise(): %s & %s\n", word_a, word_b);
}

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
	const char *alphabet	= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static int temperatures_len = 11;
	const char *temperatures[] = {"C", "F", "K", "Roe", "Rø", "Ro", "Ré", "Re", "R", "N", "D"};
	const char *temperatures_shorthands = "CFKOOOEERND"; // what each of above convert to internally
	assert(temperatures_len == strlen(temperatures_shorthands)); // fails if above isn't set-up correctly.
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

	// Fill out the input struct.
	input->val		= value;
	input->from_pos = unit_from_pos;
	input->to_pos	= unit_to_pos;
	strcpy(input->from, argv[unit_from_pos]);
	strcpy(input->to, argv[unit_to_pos]);

	// Print help message if
	// * incorrect number of arguments.
	// * there isn't a valid value + two (potentially) valid unit codes.
	//		Potentially valid country codes have length 3,
	//		only have letters from the (English) alphabet,
	//		and are not identical.
	if (argc >= 3 && argc <= 5
	&& strcmp(input->from, input->to) != 0) {
		if (strlen(input->from) == 3 && strlen(input->to) == 3 // We don't have pre-compiled list
		&& strspn(input->from, alphabet) == 3  // of currency codes. So we just check length and
		&& strspn(input->to, alphabet) == 3) { // contents for potential validity.
			input->type = Currency;
			return 0;
		}
		else {
			//capitalise(input->from, input->to);
			for (int from_i = 0; from_i < temperatures_len; from_i++) {
				char *substr = strcasestr(input->from, temperatures[from_i]);
				if (substr == input->from) {
					if (DEBUG == 2) printf("Temperature parsing: %s = %s\n", input->from, temperatures[from_i]);
					for (int to_i = 0; to_i < temperatures_len; to_i++) {
						substr = strcasestr(input->to, temperatures[to_i]);
						if (substr == input->to) {
							if (DEBUG == 2) printf("Temperature parsing: %s = %s\n", input->to, temperatures[to_i]);
							input->type = Temperature;
							strcpy(input->from, temperatures_shorthands + from_i);
							strcpy(input->to, temperatures_shorthands + to_i);
							return 0;
						}
					}
					break;
				}
			}
		}
	}
	return 1;
}
