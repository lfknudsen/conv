#ifndef UNITS_LENGTH_H
#define UNITS_LENGTH_H

// First dimension of the full arrays are equal in length
// to their short-hand version. In other words, each char* in
// char** lengths_symbols_si
// corresponds to a char in
// char* lengths_symbols_si_short.
// And likewise for the others.
extern const char* lengths_symbols_si[];
extern const char* lengths_symbols_si_short;
extern const int   lengths_symbols_si_len;

extern const char* lengths_si[];
extern const char* lengths_si_short;
extern const int   lengths_si_len;

extern const char* lengths_us[];
extern const char* lengths_us_short;
extern const int   lengths_us_len;

extern const char* lengths_symbols_us_naut[];
extern const char* lengths_symbols_us_naut_short;
extern const int   lengths_symbols_us_naut_len;

extern const char* lengths_us_naut[];
extern const char* lengths_us_naut_short;
extern const int   lengths_us_naut_len;

extern const char* lengths_typo[];
extern const char* lengths_typo_short;
extern const int   lengths_typo_len;

extern const char* lengths_misc[];
extern const char* lengths_misc_short;
extern const int   lengths_misc_len;
#endif
