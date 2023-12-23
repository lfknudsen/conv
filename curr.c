#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curr.h"
#include "conv.h"

#define DIGIT_LIMIT 500
#define DEBUG 0

// Receives the response string to our HTTP(S) request.
// Extracts relevant data (currency conversion rates), and outputs it as a two-line string.
static size_t extract_rates(void *input_ptr, size_t elem_size, size_t elem_count, void *output_ptr)
{
	if (DEBUG) printf("Full response:\n%s\n\n", input_ptr);
	char *mark = "\"rates\": {";
	char *input = strstr(input_ptr, mark) + strlen(mark);

	size_t val_length = strcspn(input, "}");
	if (val_length == 0) { printf("Invalid country codes.\n"); return 0; }

	input = strpbrk(input, "0123456789."); // start input string from first country's rate.
	val_length = strcspn(input, ",\n");    // distance to end of number.
	size_t max = DIGIT_LIMIT < val_length ? DIGIT_LIMIT : val_length; // to prevent seg faults.
	memcpy(output_ptr, input, val_length);  // copy number to output string ("extracted_rates").
	strcat(output_ptr, "\n");
	input += val_length;

	val_length = strcspn(input, "}");
	if (val_length == 3) {
		printf("You have one invalid country code. Please double-check your input.\n");
		return 0; }

	input = strpbrk(input, "0123456789."); // start string from second countr's rate.
	val_length = strcspn(input, ",\n");
	max = DIGIT_LIMIT < val_length ? DIGIT_LIMIT : val_length;
	strncat(output_ptr, input, max); // memcpy overwrites - this we append instead

	if (DEBUG) printf("Re-formatted response data:\n%s\n\n", output_ptr);

	return elem_count;
}

int connect_with_curl(char *api_key, double *result, struct parsed_input *input) {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL *curl = curl_easy_init();
	CURLcode return_code;
	if (curl)
	{
		// Assemble request.
		char *base_url = "https://openexchangerates.org/api/latest.json?app_id=";
		int size_of_url =
			strlen(base_url) + strlen(api_key) + strlen("&symbols=") + 3 + 3;
		char url[size_of_url];
		sprintf(url,
				"%s%s&symbols=%s,%s",
				base_url, api_key, input->from, input->to);
		if (DEBUG) printf("Full request:\n%s\n", url);

		if (curl_easy_setopt(curl, CURLOPT_URL,	url) != CURLE_OK)
			{ printf("URL error.\n"); return 1; }

		if (curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, extract_rates) != CURLE_OK)
			{ printf("Write-function error.\n"); return 1; }

		// extracted_rates contains output of extract_rates() function.
		char *extracted_rates = malloc((DIGIT_LIMIT * 2) + 1); // two numbers plus a newline in between
		if (curl_easy_setopt(curl, CURLOPT_WRITEDATA, extracted_rates) != CURLE_OK) {
			printf("Write-data error.\n");
			free(extracted_rates);
			return 1;
		}

		// Send HTTP(S) packet and receive response:
		return_code = curl_easy_perform(curl);

		if (return_code != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(return_code));
			return 1;
		}

		if (DEBUG) printf("Final string:\n%s\n", extracted_rates);

		// Countries are listed alphabetically in API response, so need to know which is which.
		int from_pos = strcmp(input->from, input->to);
		char *token = strtok(extracted_rates, "\n");
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

		*result = input->val / rate_from; // convert value in rate_from to USD
		*result *= rate_to; // convert USD value to rate_to
		//printf("%f %s\n", result, input->to);

		free(extracted_rates);
		curl_easy_cleanup(curl);
		return 0;
	}
	curl_easy_cleanup(curl);
}

int get_api_key(char *api_key) {
	// Attempt first to use API key in conv.c, otherwise in settings file.
	char *api_msg = "API key has not been set.\n\
	Please either edit conv.c as indicated at the top of the file,\
	or fill it in in ~/conv.ini:\napi_key=<here>\n";

	if (strcmp(api_key,"SET API KEY HERE TO USE THIS FEATURE") == 0)
	{
		char *filename = "/conv.ini";
		char *user_dir = malloc(100);
		strcpy(user_dir, getenv("HOME"));
		char *full_path = malloc(strlen(user_dir) + strlen(filename) + 1);
		memcpy(full_path, user_dir, strlen(user_dir));
		free(user_dir);
		strcat(full_path, filename);

		FILE *settings_file;
		settings_file = fopen(full_path, "r");
		if (settings_file == NULL)
		{
			settings_file = fopen(full_path, "w");
			if (settings_file != NULL)
			{
				fprintf(settings_file, "api_key=x");
				fclose(settings_file);
			}
			printf(api_msg);
			printf("Could neither find nor create %s.\n", full_path);
			return 1;
		}
		free(full_path);

		fseek(settings_file, strlen("api_key="), SEEK_SET);
		char *fgets_code = fgets(api_key, 100, settings_file);
		if (fgets_code == NULL || strlen(api_key) <= 1)
		{
			printf(api_msg); return 1;
		}
		api_key[strlen(api_key) - 1] = '\0'; // remove new-line
		fclose(settings_file);
	}

	if (DEBUG) printf("API key:\n%s\n", api_key);
	return 0;
}

int convert_currency(char* key, struct parsed_input *input, double *result) {
	char *api_key = malloc(100);
	strcpy(api_key, key);
	get_api_key(api_key);

	// Set currency codes to uppercase.
	// Assumes input has been checked for length and contents.
	// The variables are used to store the currency codes henceforth.
	for (int i = 0; i < 3; i++)
	{
		if (input->from[i] > 90) {
			input->from[i] -= 32;
		}
		if (input->to[i] > 90) {
			input->to[i] -= 32;
		}
	}
	if (DEBUG) printf("Fixed currency-code case:\nFrom: %s\nTo: %s\n", input->from, input->to);

	connect_with_curl(api_key, result, input);
	free(api_key);

	return 0;
}
