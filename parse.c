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

// Assumes that 97 <= b <= 122.
// Return 1 if the characters are the same, regardless of case.
// Returns 0 otherwise.
static int ccase(char a, char b) {
	if (a >= 65 && a <= 90)
		return (a + 32 == b);
	return (a == b);
}

static int ccase_or_empty(char a, char b) {
	if (a >= 65 && a <= 90)
		return ((a + 32 == b) || (a == '\0'));
	return ((a == b) || (a == '\0'));
}

// Assumes that for any character c in b, 97 <= c <= 122.
// Check whether any character in 'b' matches (regardless of case)
// with 'a'.
static int anycase(char a, char* b) {
	char c = a;
	if (a >= 65 && a <= 90)
		c += 32;
	for (unsigned int i = 0; i < strlen(b); i++) {
		if (c == b[i]) return 1;
	}
	return 0;
}

// Assumes that for any character c in b, 97 <= c <= 122.
// Check whether any character in 'b' matches (regardless of case)
// with 'a', or if 'a' is a null-terminator.
static int anycase_or_empty(char a, char* b) {
	char c = a;
	if (a >= 65 && a <= 90)
		c += 32;
	for (unsigned int i = 0; i < strlen(b); i++) {
		if (c == b[i]) return 1;
	}
	if (a == '\0') return 1;
	return 0;
}

enum unit map_length(char* str) {
	switch (str[0]) {
		case 'A':
		case 'a':
			if (anycase(str[1],"mt")) // [at]to / am
				return atto;
			return UNKNOWN;
		case 'C':
		case 'c':
			if (anycase_or_empty(str[1],"ab")) // [ca]ble / cb
				return cable;
			if (anycase(str[1],"em")) // [ce]nti / cm
				return centi;
			if (ccase(str[1],'h')) // ch
				return chain;
			return UNKNOWN;
		case 'D':
		case 'd':
			if (ccase(str[1],'e')) {
				if (ccase(str[2],'c')) {
					if (ccase(str[3],'a')) return deca; // deca
					if (ccase(str[3],'i')) return deci; // deci
					return UNKNOWN;
				}
				return UNKNOWN;
			}
			if (ccase(str[1],'m')) return deci; // dm
			if (ccase(str[1],'a')) return deca; // [da]m
			return UNKNOWN;
		case 'E':
		case 'e':
			if (anycase(str[1],"mx")) // [ex]a / em
				return exa;
			return UNKNOWN;
		case 'F':
		case 'f':
			if (ccase(str[1],'a')) // [fa]thom
				return fathom;
			if (ccase(str[1],'e')) {
				if (ccase(str[2],'e')) return foot; // [fee]t
				if (ccase(str[2],'m')) return femto;// [fem]to
				return UNKNOWN;
			}
			if (ccase(str[1],'t')) {
				if (str[2] == '\0' || str[2] == '.') // ft / ft.
					return foot;
				if (ccase(str[2],'m')) // ftm
					return fathom;
				return UNKNOWN;
			}
			if (ccase_or_empty(str[1],'o')) // [fo]ot / f
				return foot;
			if (ccase(str[1],'u')) // [fu]rlong
				return furlong;
			return UNKNOWN;
		case 'G':
		case 'g':
			if (anycase(str[1], "im")) // [gi]ga / gm
				return giga;
			return UNKNOWN;
		case 'H':
		case 'h':
			if (anycase(str[1], "em")) // [he]cto / hm
				return hecto;
			if (anycase_or_empty(str[1], "ah")) // [ha]nd / hh / h
				return hand;
			return UNKNOWN;
		case 'I':
		case 'i':
			if (ccase(str[1],'n')) // in
				return inch;
			return UNKNOWN;
		case '\"':
			if (str[1] == '\0') // "
				return inch;
			return UNKNOWN;
		case 'K':
		case 'k':
			if (anycase(str[1],"im")) // km / [ki]lo
				return kilo;
			return UNKNOWN;
		case 'L':
		case 'l':
			if (ccase(str[1],'e')) return statute; // [le]ague
			if (ccase(str[1],'u')) return rod; // [lu]g
			return UNKNOWN;
		case 'M':
			if (ccase(str[1],'m')) return mega; // Mm
			__attribute__ ((fallthrough));
		case 'm':
			if (str[1] == '\0') // [m]
				return metre;
			if (ccase(str[1],'e')) {
				if (ccase(str[2],'g')) // [meg]a
					return mega;
				if (ccase(str[2],'t')) // [met]re
					return metre;
				return UNKNOWN;
			}
			if (ccase(str[1],'i')) {
				if (ccase(str[2],'c')) // [mic]ro
					return micro;
				if (str[2] == '\0' || ccase(str[2],'.')) // mi.
					return mile;
				if (ccase(str[2],'l')) {
					if (ccase_or_empty(str[3],'s')) // [mils]
						return thou;
					if (ccase(str[3],'e')) // [mile]
						return mile;
					if (ccase(str[3],'l')) // [mill]i
						return milli;
					return UNKNOWN;
				}
				return UNKNOWN;
			}
			if (ccase(str[1],'m')) // mm
				return milli;
			return UNKNOWN;
		case 'N':
			if (ccase(str[1],'M')) // NM
				return nautical;
			__attribute__ ((fallthrough));
		case 'n':
			if (ccase(str[1],'a')) {
				if (ccase(str[2],'n')) // [nan]o
					return nano;
				if (ccase(str[2],'u')) // [nau]tical
					return nautical;
				return UNKNOWN;
			}
			if (ccase(str[1],'m')) {
				if (str[2] == '\0') // nm
					return nano;
				if (ccase(str[2],'i')) // nmi
					return nautical;
				return UNKNOWN;
			}
			return UNKNOWN;
		case 'P':
			if (ccase(str[1],'m')) // [Pm]
				return peta;
			if (str[1] == '\0') // [P]
				return point;
			return UNKNOWN;
		case 'p':
			if (ccase(str[1],'e')) {
				if (ccase(str[2],'t')) // [pet]a
					return peta;
				if (ccase(str[2],'r')) // [per]ch
					return rod;
				return UNKNOWN;
			}
			if (ccase(str[1],'i')) {
				if (ccase(str[2],'c')) {
					if (ccase(str[3],'o')) // [pico]
						return pico;
					if (ccase(str[3],'a')) // [pica]
						return pica;
					return UNKNOWN;
				}
				return UNKNOWN;
			}
			if (ccase(str[1],'o')) {
				if (ccase(str[2],'l')) // [pol]e
					return rod;
				if (ccase(str[2],'i')) // [poi]nt
					return point;
				return UNKNOWN;
			}
			if (ccase(str[1],'t')) // [pt]
				return point;
			if (ccase_or_empty(str[1],'c')) // [pc]
				return pica;
			if (ccase(str[1],'m')) // [pm]
				return pico;
			return UNKNOWN;
		case 'R':
			if (ccase(str[1],'m')) return ronna; // Rm
			__attribute__ ((fallthrough));
		case 'r':
			if (ccase(str[1],'o')) {
				if (ccase(str[2],'d'))
					return rod;
				if (ccase(str[1],'n')) // [ron]na
					return ronna;
				return UNKNOWN;
			}
			if (ccase(str[1],'m')) // rm
				return ronna;
			return UNKNOWN;
		case 'S':
		case 's':
			if (anycase(str[1],"tu")) // [su]rvey / [st]atute
				return statute;
			return UNKNOWN;
		case 'T':
		case 't':
			if (anycase(str[1],"em")) return tera; // [te]ra / tm
			if (ccase(str[1],'h')) return thou; // [th]ou
			if (ccase(str[1],'w')) return twip; // [tw]ip
			return UNKNOWN;
		//case 'μ':
		case 'U':
		case 'u':
			if (ccase(str[1],'m')) // um
				return micro;
			return UNKNOWN;
		case 'Y':
			if (ccase(str[1],'m')) return yotta; // Ym
			__attribute__ ((fallthrough));
		case 'y':
			if (anycase_or_empty(str[1], "ad")) // [ya]rd / yd
				return yard;
			if (ccase(str[1],'m')) return  yocto; // ym
			if (ccase(str[1],'o')) {
				if (ccase(str[2],'c')) return yocto; // [yoc]to
				if (ccase(str[2],'t')) return yotta; // [yot]ta
				return UNKNOWN;
			}
			return UNKNOWN;
		case 'Z':
			if (anycase(str[1],"em")) {
				if (ccase_or_empty(str[2],'t')) // [[Ze]t]ta / Zm
					return zetta;
				if (ccase(str[2],'p')) // [Zep]to
					return zepto;
				return UNKNOWN;
			}
			return UNKNOWN;
		case 'z':
			if (anycase(str[1],"em")) {
				if (ccase_or_empty(str[2],'p')) // [[ze]p]to / zm
					return zepto;
				if (ccase(str[2],'t')) // [zet]ta;
					return zetta;
				return UNKNOWN;
			}
			return UNKNOWN;
		case '\'':
			if (str[1] == '\0') return foot; // '
			return UNKNOWN;
	}
	return UNKNOWN;
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
	strncpy(input->from.string, argv[unit_from_pos], 13);
	input->from.string[14] = '\0';
	strncpy(input->to.string, argv[unit_to_pos], 13);
	input->to.string[14] = '\0';

	// Print help message if
	// * incorrect number of arguments.
	// * there isn't a valid value + two (potentially) valid unit codes.
	//		Potentially valid country codes have length 3,
	//		only have letters from the (English) alphabet,
	//		and are not identical.
	if (argc >= 3 && argc <= 5) {
		if (strcmp(input->from.string, input->to.string) == 0) {
			return 2;
		}
		// Try to parse as currency codes.
		// A currency code is exactly 3 letters, all in English alphabet.
		if (strlen(input->from.string) == 3 && strlen(input->to.string) == 3
		&& strspn(input->from.string, alphabet) == 3
		&& strspn(input->to.string, alphabet) == 3) {
			input->type = Currency;
			return 0;
		}
		else {
			// Try to parse as temperature scales.
			for (int from_i = 0; from_i < temperatures_len; from_i++) {
				if (strcasecmp(input->from.string, temperatures[from_i]) == 0) {
					for (int to_i = 0; to_i < temperatures_len; to_i++) {
						if (strcasecmp(input->to.string, temperatures[to_i]) == 0) {
							input->type = Temperature;
							input->from.string[0] = temperatures_short[from_i];
							input->to.string[0] = temperatures_short[to_i];
							return 0;
						}
					}
					break;
				}
			}
			// Try to parse as length units.
			if (DEBUG) printf("Trying to parse as length units.\n");
			enum unit from_short = map_length(input->from.string);
			enum unit to_short   = map_length(input->to.string);
			if (from_short != UNKNOWN && to_short != UNKNOWN) {
				input->type = Length;
				input->from.unit = from_short;
				input->to.unit = to_short;
				return 0;
			}
		}
	}
	return 1;
}
