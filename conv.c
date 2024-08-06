// ==============================================================================================
// Unit and Currency Conversion CLI
// ----------------------------------------------------------------------------------------------
// Author: github.com/lfknudsen
// ----------------------------------------------------------------------------------------------
// Compile:
// gcc conv.c parse.c curr.c temperature.c length.c -o conv -lcurl
//
// Usage:
// ./conv [<Value>] <From> [to] <To>
// Mostly case insensitive.
//
// Examples:
// ./conv 10 DKK JPY
// ./conv 10 GBP to EUR
// ./conv usd dkk
// ./conv usd to DKK
// ./conv 10 C K
// ./conv 10 Kelvin Rankine
// ./conv 700 m yd
// ./conv 30 furlong to nmi
// ==============================================================================================

#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "conv.h"
#include "parse.h"
#include "curr.h"
#include "temperature.h"
#include "length.h"
#include "units_length.h"

// ==============================================================================================
// ----------------------------------------------------------------------------------------------
// SETUP:
// Please go to openexchangerates.org and create a free account.
// Then put your app key below, within the double-quotes:
// ----------------------------------------------------------------------------------------------

#define API_KEY "SET API KEY HERE TO USE THIS FEATURE"

// ----------------------------------------------------------------------------------------------
// ==============================================================================================

void dealloc(void* ptr, char* label) {
	printf("Freeing %s.\n", label);
	free(ptr);
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		return error_msg(argv[0]);
	}
	struct parsed_input* input = malloc(sizeof(*input));
	int parse_ret = parse_input(input, argc, argv);
	if (parse_ret == 1) {
		free(input);
		return 1;
	}
	if (parse_ret == 2) {
		printf("Error: Same input and output type.\n");
		free(input);
		return 1;
	}
	double result;
	switch (input->type) {
		case Currency:
			convert_currency(API_KEY, input, &result);
			if (DEBUG) printf("Currency: ");
			printf("%lf\n", result);
			break;
		case Temperature:
			if (convert_temperature(input->from.string[0], input->to.string[0], input->val, &result)) {
				printf("Temperature scale not implemented.\n");
			} else {
				if (DEBUG) printf("Temperature: ");
				printf("%lf\n", result);
			}
			break;
		case Length:
			if (convert_length(input->from.unit, input->to.unit, input->val, &result)) {
				printf("Length scale not implemented.\n");
			} else {
				if (DEBUG) printf("Length: ");
				printf("%lf\n", result);
			}
			break;
		default:
			printf("Unimplemented conversion type.\n");
			break;
	};

	free(input);
	return 0;
}
