#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1

// Return length of input string.
int str_len(char *str)
{
	int i = 0;
	while (str[i] != '\0') { i++; }
	return i;
}

// Return length of a string until (and exclusive of) the first occurrence of a given character.
int str_until(char *str, char end)
{
	int i = 0;
	while (str[i] != end)
	{
		if (str[i] == '\0') return -1;
		i++;
	}
	return i;
}

// Return sub-string up to (and exclusive of) given position in input string.
// Does NOT modify input string.
// Responsibility of caller to free memory.
char *str_prefix(char *str, int stop)
{
	char *prefix = malloc(stop + 1);
	for (int i = 0; i < stop && str[i] != '\0'; i++)
	{
		prefix[i] = str[i];
	}
	prefix[stop] = '\0';
	return prefix;
}

// Return sub-string from a given start position in input string.
// Does NOT modify input string.
// Responsibility of caller to free memory.
char *str_postfix(char *str, int start)
{
	if (start >= str_len(str)) { return ""; }
	char *postfix = malloc(str_len(str) - start);
	for (int i = 0; str[i + start] != '\0'; i++)
	{
		postfix[i] = str[i + start];
	}
	return postfix;
}

// Return s ub-string from a given start position in input string, until (and exclusive of)
// a given stop position.
// Does NOT modify original string.
// Responsibility of caller to free memory.
char *str_range(char* str, unsigned int start, unsigned int stop)
{
	unsigned int len = str_len(str);
	if (start >= len || stop >= len || start >= stop || (stop - start) >= len) { return ""; }
	char *substring = malloc(len - (stop - start));
	for (int i = 0; str[i + start] != '\0'; i++)
	{
		substring[i] = str[i + start];
	}
	return substring;
}

// Case-insensitive comparison of two strings.
// Return:
// 1 if identical.
// 0 if different.
char str_match(char *a, char *b)
{
	if ((a[0] == '\0') ^ (b[0] == '\0'))
	{
		return 0;
	}

	for (int i = 0; a[i] != '\0' && b[i] != '\0'; i++)
	{
		if (a[i] >= 65 && a[i] <= 90)
		{
			if ((b[i] != a[i]) && (b[i] != (a[i] + 32)))
			{
				return 0;
			}
		}
		else if (a[i] >= 97 && a[i] <= 122)
		{
			if ((b[i] != a[i]) && (b[i] != (a[i] - 32)))
			{
				return 0;
			}
		}
		else if (a[i] != b[i])
		{
			return 0;
		}
		if ((a[i] == '\0') ^ (b[i] == '\0'))
		{
			return 0;
		}
	}
	return 1;
}

// case-sensitive string comparison.
char str_comp(char *a, char *b)
{
	if ((a[0] == '\0') ^ (b[0] == '\0'))
	{
		return 0;
	}

	for (int i = 0; a[i] != '\0' && b[i] != '\0'; i++)
	{
		if (a[i] != b[i]) return 0;
	}
	return 1;
}

// Return the position of the first unidentical character in two strings.
// If they are identical, return -1.
int str_diff(char *a, char *b)
{
	if ((a[0] == '\0') ^ (b[0] == '\0'))
	{
		return 0;
	}

	for (int i = 0; a[i] != '\0' && b[i] != '\0'; i++)
	{
		if (a[i] != b[i]) return i;
	}
	return -1;
}

// return start position of sub-string within super-string.
int str_sub(char *super, char *sub)
{
	if (super[0] == '\0') return -1;
	if (  sub[0] == '\0') return  0;

	for (int i = 0; super[i] != '\0' && sub[i] != '\0'; i++)
	{
		int match_count = 0;
		for (int j = i; super[i] == sub[i]; j ++)
		{
			if (sub[match_count] == '\0') { return i - str_len(sub); }
			if (super[j] == sub[match_count]) { match_count ++; }
		}
	}
	return -1;
}
