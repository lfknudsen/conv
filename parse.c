/*
* ============================================================================ *
* Parses input strings to determine which sort of conversion needs to happen.  *
* ============================================================================ *
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "parse.h"
#include "units_length.h"
#include "units_temp.h"

static int greedy_substr_exists(char *superstring, char *substring) {
	for (unsigned int super_i = 0; super_i < strlen(superstring); super_i++) {
		for (unsigned int sub_i = 0; sub_i < strlen(substring); sub_i++) {
			printf("Not implemented yet.");
			return 1;
		}
	}
	return 0;
}

static void upper_case(char* word_a, char* word_b) {
	for (unsigned int i = 0; i < strlen(word_a); i++)
	{
		if (word_a[i] > 90) {
			word_a[i] -= 32;
		}
		if (word_b[i] > 90) {
			word_b[i] -= 32;
		}
	}
	return;
}

static void capitalise(char* word_a, char* word_b) {
	if (DEBUG == 2) printf("Before capitalise(): %s & %s\n", word_a, word_b);
	if (word_a[0] > 90) {
		word_a[0] -= 32;
	}
	if (word_b[0] > 90) {
		word_b[0] -= 32;
	}
	for (unsigned int i = 1; i < strlen(word_a); i++)
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
int error_msg(char* program_name) {
	fprintf(stderr, "\x1b[31m%s\x1b[m: Could not parse input.\nUsage:\n%s <VAL> <FROM> [to] <TO>\n\
%s <FROM> <TO>\n\
Case insensitive.\n\
Examples:\n%s 100 JPY DKK\n%s 10 m yd\n%s 13 feet to km\n%s 34 C F\n",
		 program_name, program_name, program_name, program_name, program_name, program_name, program_name);
	return 1;
}

// Returns 1 if the argument matches a pre-defined length unit.
// Saves the short-hand to "output" ptr.
static int is_valid_length_unit(char* word, char* output) {
	if (DEBUG) printf("Trying to match %s\n", word);

	for (int i = 0; i < lengths_si_len; i++) { //+3 for alternate spelling + plurals of metre
		if (strcasecmp(word, lengths_si[i]) == 0) {
			*output = lengths_si_short[i];
			if (DEBUG)
				printf("Matched with %s (shorthand %c).\n",
				lengths_si[i], lengths_si_short[i]);
			return 1;
		}
	}
	for (int i = 0; i < lengths_symbols_si_len; i++) {
		if (strcmp(word, lengths_symbols_si[i]) == 0) {
			*output = lengths_symbols_si_short[i];
			if (DEBUG)
				printf("Matched with %s (shorthand %c).\n",
				lengths_symbols_si[i], lengths_symbols_si_short[i]);
			return 1;
		}
	}

	for (int i = 0; i < lengths_us_len; i++) {
		if (strcmp(word, lengths_us[i]) == 0) {
			*output = lengths_us_short[i];
			if (DEBUG)
				printf("Matched with %s (shorthand %c).\n",
				lengths_us[i], lengths_us_short[i]);
			return 1;
		}
	}

	for (int i = 0; i < lengths_symbols_us_naut_len; i++) {
		if (strcmp(word, lengths_symbols_us_naut[i]) == 0) {
			*output = lengths_symbols_us_naut_short[i];
			if (DEBUG)
				printf("Matched with %s (shorthand %c).\n",
				lengths_symbols_us_naut[i], lengths_symbols_us_naut_short[i]);
			return 1;
		}
	}

	for (int i = 0; i < lengths_us_naut_len; i++) {
		if (strcasecmp(word, lengths_us_naut[i]) == 0) {
			*output = lengths_us_naut_short[i];
			if (DEBUG)
				printf("Matched with %s (shorthand %c).\n",
				lengths_us_naut[i], lengths_us_naut_short[i]);
			return 1;
		}
	}

	for (int i = 0; i < lengths_typo_len; i++) {
		if (strcasecmp(word, lengths_typo[i]) == 0) {
			*output = lengths_typo_short[i];
			if (DEBUG)
				printf("Matched with %s (shorthand %c).\n",
				lengths_typo[i], lengths_typo_short[i]);
			return 1;
		}
	}

	for (int i = 0; i < lengths_misc_len; i++) {
		if (strcasecmp(word, lengths_misc[i]) == 0) {
			*output = lengths_misc_short[i];
			if (DEBUG)
				printf("Matched with %s (shorthand %c).\n",
				lengths_misc[i], lengths_misc_short[i]);
			return 1;
		}
	}
	printf("Could not match %s!\n", word);
	return 0;
}

// Parse input so that it can be passed to the correct sub-procedure.
// It is caller's responsibility to allocate and free the input object. Can use free_input to do so.
// Returns 0 on success.
int parse_input(struct parsed_input *input, int argc, char *argv[]) {
	const char* alphabet	= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// Check correctness of input.
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
	// <unit> to <unit>
	if (argc == 4 && value == 0.0 && strcmp(argv[2],"to") == 0)
		{ value = 1.0; unit_from_pos = 1; unit_to_pos = 3; }

	// Fill out the input struct.
	input->val		= value;
	input->from_pos = unit_from_pos;
	input->to_pos	= unit_to_pos;
	strncpy(input->from, argv[unit_from_pos], 13);
	input->from[14] = '\0';
	strncpy(input->to, argv[unit_to_pos], 13);
	input->to[14] = '\0';

	// Print help message if
	// * incorrect number of arguments.
	// * there isn't a valid value + two (potentially) valid unit codes.
	//		Potentially valid country codes have length 3,
	//		only have letters from the (English) alphabet,
	//		and are not identical.
	if (argc >= 3 && argc <= 5) {
		if (strcmp(input->from, input->to) == 0) {
			return 2;
		}
		// Try to parse as currency codes.
		// A currency code is exactly 3 letters, all in English alphabet.
		if (strlen(input->from) == 3 && strlen(input->to) == 3
		&& strspn(input->from, alphabet) == 3
		&& strspn(input->to, alphabet) == 3) {
			input->type = Currency;
			return 0;
		}
		else {
			// Try to parse as temperature scales.
			for (int from_i = 0; from_i < temperatures_len; from_i++) {
				if (strcasecmp(input->from, temperatures[from_i]) == 0) {
					for (int to_i = 0; to_i < temperatures_len; to_i++) {
						if (strcasecmp(input->to, temperatures[to_i]) == 0) {
							input->type = Temperature;
							input->from[0] = temperatures_short[from_i];
							input->to[0] = temperatures_short[to_i];
							return 0;
						}
					}
					break;
				}
			}
			// Try to parse as length units.
			if (DEBUG) printf("Trying to parse as length units.\n");
			char from_short;
			char to_short;
			if (is_valid_length_unit(input->from, &from_short)
					&& is_valid_length_unit(input->to, &to_short)) {
				input->type = Length;
				memcpy(input->from, &from_short, 1);
				memcpy(input->to, &to_short, 1);
				return 0;
			}
		}
	}
	return 1;
}
