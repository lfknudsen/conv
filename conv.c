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

#include <curl/curl.h>
#include <stdio.h>
#include <net/if.h>
#include <string.h>
#include <stdlib.h>

#define DIGIT_LIMIT 500
#define DEBUG 0

// ----------------------------------------------------------------------------------------------
// SETUP:
// Please go to openexchangerates.org and create a free account.
// Then put your app key below, within the double-quotes:
// ----------------------------------------------------------------------------------------------

#define API_KEY "SET API KEY HERE TO USE THIS FEATURE"

// ----------------------------------------------------------------------------------------------

// Receives the response string to our HTTP(S) request.
// Extracts relevant data (currency conversion rates), and outputs it as a two-line string. 
static size_t extract_rates(void *input_ptr, size_t elem_size, size_t elem_count, void *output_ptr)
{
	if (DEBUG) printf("Full response:\n%s\n\n", input_ptr);
	char *mark = "\"rates\": {";
	char *input = strstr(input_ptr, mark) + strlen(mark);

	size_t val_length = strcspn(input, "}");
	if (val_length == 0) { printf("Invalid country codes.\n"); return 0; }
	
	input = strpbrk(input, "0123456789."); // start input string from first country's rate
	val_length = strcspn(input, ",\n");    // distance to end of number
	size_t max = DIGIT_LIMIT < val_length ? DIGIT_LIMIT : val_length; // to prevent seg faults
	memcpy(output_ptr, input, val_length);  // copy number to output string ("read_string")
	strcat(output_ptr, "\n");
	input += val_length;

	val_length = strcspn(input, "}");	
	if (val_length == 3) {
		printf("You have one invalid country code. Please double-check your input.\n");
		return 0; }
	
	input = strpbrk(input, "0123456789.");
	val_length = strcspn(input, "\n");
	max = DIGIT_LIMIT < val_length ? DIGIT_LIMIT : val_length;
	strncat(output_ptr, input, max);
	
	if (DEBUG) printf("Re-formatted response data:\n%s\n\n", output_ptr);
	
	return elem_count;
}

int main(int argc, char *argv[])
{
	if (API_KEY == "SET API KEY HERE TO USE THIS FEATURE")
	{
		printf("To convert between currencies, please open conv.c and edit the file\
as indicated at the top, under the SETUP banner.\n");
		return 1;
	}

	char* usage_msg = "Usage:\n./conv <VAL> <FROM> [to] <TO>\n\
./conv <FROM> <TO>\n\
Case insensitive.\n\
Example:\n./conv 100 JPY DKK\n";

	// ------------------------------------------------------------------------------------------
	// Check correctness of input.
	char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int curr_from_pos = 2, curr_to_pos = 3; // which arguments correspond to the currency codes
	double value = 1.0;
	if (argc == 3) { curr_from_pos = 1; curr_to_pos = 2; }
	else if (argc == 5) { curr_from_pos = 2; curr_to_pos = 4; }
	if (argc == 5 || argc == 4) { value = atof(argv[1]); }
	if (argc == 4 && value == 0.0) { value = 1.0; curr_from_pos = 1; curr_to_pos = 3; }
	if (
		   (argc > 5 || argc < 3)
		|| (!
		 	(value != 0.0 && strlen(argv[curr_from_pos]) == 3 && strlen(argv[curr_to_pos]) == 3 
		  	&& strspn(argv[curr_from_pos], alphabet) == 3 
			&& strspn(argv[curr_to_pos], alphabet) == 3
			&& strcmp(argv[curr_from_pos], argv[curr_to_pos]) != 0))
		)
	{
		printf(usage_msg); return 1;
	}
	// ------------------------------------------------------------------------------------------

	// Set currency codes to uppercase.
	// The variables are used to store the currency codes henceforth.
	char *curr_from = malloc(3);
	char *curr_to = malloc(3);
	for (int i = 0; i < 3; i++)
	{
		if (argv[curr_from_pos][i] > 90) { curr_from[i] = argv[curr_from_pos][i] - 32; }
		if (argv[curr_to_pos][i] > 90) { curr_to[i] = argv[curr_to_pos][i] - 32; }
	}

	CURL *curl;
	CURLcode return_code;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl)
	{
		// Assemble request.
		char *base_url = "https://openexchangerates.org/api/latest.json?app_id=";
		int size_of_url =
			strlen(base_url) + strlen(API_KEY) + strlen("&symbols=") + 3 + 3;
		char url[size_of_url];
		sprintf(url,
				"%s%s&symbols=%s,%s",
				base_url, API_KEY, argv[curr_from_pos], argv[curr_to_pos]);
		if (DEBUG) printf("Full request: %s\n", url);

		if (curl_easy_setopt(curl, CURLOPT_URL,	url) != CURLE_OK)
			{ printf("URL error.\n"); return 1; }
		
		if (curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, extract_rates) != CURLE_OK)
			{ printf("Write-function error.\n"); return 1; }
		
		// Read_string contains output of extract_rates() function.
		char *read_string = malloc((DIGIT_LIMIT * 2) + 1); // two numbers plus a newline in between
		if (curl_easy_setopt(curl, CURLOPT_WRITEDATA, read_string) != CURLE_OK)
			{ printf("Write-data error.\n"); return 1; }
	
		// Send HTTP(S) packet and receive response:
		return_code = curl_easy_perform(curl);

		if (return_code != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(return_code));
			return 1;
		}
		
		if (DEBUG) printf("Final string:\n%s\n", read_string);
		
		// Countries are listed alphabetically in API response, so need to know which is which.
		int from_pos = strcmp(curr_from, curr_to);
		char *token = strtok(read_string, "\n");
		double rate_from, rate_to;
		if (from_pos < 0) // true = "from" currency is listed first in API response.
		{
			rate_from = atof(token);
			token = strtok(NULL, "\n");
			rate_to = atof(token);
		}
		else
		{
			rate_to = atof(token);
			token = strtok(NULL, "\n");
			rate_from = atof(token);
		}
		
		double result = value / rate_from; // convert value in rate_from to USD
		result *= rate_to; // convert USD value to rate_to
		printf("%f %s is %f %s\n", value, curr_from, result, curr_to);
		
		curl_easy_cleanup(curl);
		free(read_string);
		free(curr_from);
		free(curr_to);
	}

	return 0;
}
