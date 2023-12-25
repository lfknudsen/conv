// ==============================================================================================
// Unit and Currency Conversion CLI
// ----------------------------------------------------------------------------------------------
// Author: github.com/lfknudsen
// ----------------------------------------------------------------------------------------------
// Compile:
// gcc conv.c -o conv -lcurl
//
// Usage:
// ./conv [<Value>] <From> [to] <To>
// Case insensitive.
//
// Examples:
// ./conv 10 DKK JPY
// ./conv 10 GBP to EUR
// ./conv usd dkk
// ./conv usd to dkk
// ==============================================================================================

#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "conv.h"
#include "parse.h"
#include "curr.h"
#include "temperature.h"

//#include "strings.h"

#define DEBUG 0

// ==============================================================================================
// ----------------------------------------------------------------------------------------------
// SETUP:
// Please go to openexchangerates.org and create a free account.
// Then put your app key below, within the double-quotes:
// ----------------------------------------------------------------------------------------------

#define API_KEY "SET API KEY HERE TO USE THIS FEATURE"

// ----------------------------------------------------------------------------------------------
// ==============================================================================================

void dealloc(void *ptr, char* label) {
	printf("Freeing %s.\n", label);
	free(ptr);
}

int main(int argc, char *argv[])
{
	char *usage_msg = "Usage:\n./conv <VAL> <FROM> [to] <TO>\n\
./conv <FROM> <TO>\n\
Case insensitive.\n\
Example:\n./conv 100 JPY DKK\n";

	struct parsed_input *input = malloc(sizeof(struct parsed_input));
	if (parse_input(input, argc, argv) == 1) {
		free(input);
		return 1;
	}
	double result;
	switch (input->type) {
		case Currency:
			convert_currency(API_KEY, input, &result);
			printf("%lf\n", result);
			break;
		case Temperature:
			if (convert_temperature(input, &result)) {
				printf("Temperature scale not implemented yet.\n");
			} else {
				printf("%lf\n", result);
			}
			break;
		default:
			printf("No conversion type found.\n");
			break;
	};

	free(input);
	return 0;
}
