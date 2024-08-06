#include <stdio.h>

#include "length.h"
#include "units_length.h"

// Note: First dimension of lengths_symbols_si[] and
// lengths_symbols_si_short[] must be equally long.
const char *lengths_symbols_si[] = {
		"ym", "zm", "am", "fm", "pm",
		"nm", "um", "μm", "mm", "cm", "dm",
		"m", "dam", "hm", "km", "Mm",
		"Gm", "Tm", "Pm", "Em", "Zm",
		"Ym", "Rm"};
const char *lengths_symbols_si_short = "yzafpnuuicdmDhkMGTPEZYR";
const int lengths_symbols_si_len = 23;

// Note: First dimension of lengths_si[] and lengths_si_short[]
// must be equally long.
const char *lengths_si[] = {
	"yocto", "zepto", "atto", "femto", "pico",
	"nano", "micro", "milli", "centi", "deci",
	"meter", "metre", "meters", "metres", "deca",
	"hecto", "kilo", "mega", "giga", "tera",
	"peta", "exa", "zetta", "yotta", "ronna"};
const char *lengths_si_short = "yzafpnuicdmmmmDhkMGTPEZYR";
const int lengths_si_len = 25;

// Note: First dimension of lengths_us[] and lengths_us_short[]
// must be equally long.
const char *lengths_us[] = {
	"mile",		"miles",	"mi",	"mi.",		// 4
	"mil",		"mils",		"thou", "thous",	// 4
	"inch",		"inches",	"\"",	"in",		// 4
	"foot",		"feet",		"\'",	"ft",	"f",// 5
	"yard",		"yards",	"yd",				// 3
	"league",	"leagues",	"le",
	"survey mile", "survey miles", "statute mile", "statute miles", // 3+4
	"chain", "chains",							// 2
	"furlong", "furlongs",						// 2
	"rod", "rods", "pole", "poles", "perch", "perches", "lug", "lugs" // 8
};
const char *lengths_us_short = "llllttttIIIIFFFFFrrrsssssssCCUULLLLLLLL";
const int lengths_us_len = 39;

const char* lengths_typo[] = {
	"pica", "picas", "p", "pc", "pcs",
	"point", "points", "P", "pt", "pts",
	"twip", "twips",
};
const char* lengths_typo_short = "AAAAAoooooww";
const int lengths_typo_len = 12;

const char* lengths_symbols_us_naut[] = {"ftm", "cb", "NM", "M", "nmi"};
const char* lengths_symbols_us_naut_short = "ObNNN";
const int lengths_symbols_us_naut_len = 5;

const char* lengths_us_naut[] = {
	"fathom", "fathoms",
	"cable", "cables", "cable length", "cable lengths",
	"nautical mile", "nautical miles", "nmile", "nmiles"
};
const char* lengths_us_naut_short = "OObbbbNNNN";
const int lengths_us_naut_len = 10;

const char* lengths_misc[] = {
	"hand", "hands", "h", "hh"
};
const char* lengths_misc_short = "HHHH";
const int lengths_misc_len = 4;

static double dpow(double quotient, double exponent) {
	if (exponent == 0) { return 1.0; }
	if (exponent == 1) { return quotient; }
	double prod = quotient;
	for (int i = 0; i < exponent; i++) {
		prod *= quotient;
	}
	return prod;
}

// Convert 'val' metres to another unit.
// Returns 0 on success. Returns 1 otherwise.
static int from_meter(char to, double val, double* result) {
	if (DEBUG) printf("Converting from metres to %c.\n", to);
	switch (to) {
		case 'y': // yoctometre
			*result = val * 1000000000000000000000000.0;
			return 0;
		case 'z': // zeptometre
			*result = val * 1000000000000000000000.0;
			return 0;
		case 'a': // attometre
			*result = val * 1000000000000000000.0;
			return 0;
		case 'f': // femtometre
			*result = val * 1000000000000000.0;
			return 0;
		case 'p': // picometre
			*result = val * 1000000000000.0;
			return 0;
		case 'n': // nanometre
			*result = val * 1000000000.0;
			return 0;
		case 'u': // micrometre
			*result = val * 1000000.0;
			return 0;
		case 'i': // millimetre
			*result = val * 1000.0;
			return 0;
		case 'c': // centimetre
			*result = val * 100.0;
			return 0;
		case 'd': // decimetre
			*result = val * 10.0;
			return 0;
		case 'D': // decametre
			*result = val / 10.0;
			return 0;
		case 'h': // hectometre
			*result = val / 100.0;
			return 0;
		case 'k': // kilometre
			*result = val / 1000.0;
			return 0;
		case 'M': // megametre
			*result = val / 1000000.0;
			return 0;
		case 'G': // gigametre
			*result = val / 1000000000.0;
			return 0;
		case 'T': // terametre
			*result = val / 1000000000000.0;
			return 0;
		case 'P': // petametre
			*result = val / 1000000000000000.0;
			return 0;
		case 'E': // exametre
			*result = val / 1000000000000000000.0;
			return 0;
		case 'Z': // zettametre
			*result = val / 1000000000000000000000.0;
			return 0;
		case 'Y': // yottametre
			*result = val / 1000000000000000000000000.0;
			return 0;
		case 'R': // ronnametre
			*result = val / 1000000000000000000000000000.0;
			return 0;
		case 'l': // int. mile
			*result = val / 1609.344;
			return 0;
		case 'w': // twip (17.64um)
			*result = (val * 1000000) / 17.64;
			return 0;
		case 't': // mil / thou (25.4um)
			*result = (val * 1000000) / 25.4;
			return 0;
		case 'o': // point (0.3528mm)
			*result = (val * 1000) / 0.3528;
			return 0;
		case 'A': // pica (4.2333mm)
			*result = (val * 1000) / 4.2333;
			return 0;
		case 'I': // inch
			*result = val * 39.37;
			return 0;
		case 'F': // foot (0.3048m)
			*result = val / 0.3048;
			return 0;
		case 'r': // yard
			*result = val * 1.09361;
			return 0;
		case 's': // U.S. survey mile/league
			*result = val / 1609.3472;
			return 0;
		case 'O': // fathom
			*result = val * 0.5468;
			return 0;
		case 'b': // U.S. cable
			*result = val / 220;
			return 0;
		case 'N': // nautical mile
			*result = val / 1852;
			return 0;
		case 'H': // hand
			*result = val * 9.84252;
			return 0;
		case 'C': // chain
			*result = val / 20.1168;
			return 0;
		case 'U': // furlong
			*result = val / 201.168;
			return 0;
		case 'L': // rod/pole/perch/lug
			*result = val / 5.0292;
			return 0;
		default:
			*result = val;
			return 1;
	}
	return 1;
}

// Convert 'val' units of the unit specified in 'from' to metres.
// Returns 0 on success. Returns 1 otherwise.
static int to_meter(char from, double val, double* result) {
	if (DEBUG) printf("Converting to metres.\n");
	switch (from) {
		case 'y':
			*result = val / 1000000000000000000000000.0;
			return 0;
		case 'z':
			*result = val / 1000000000000000000000.0;
			return 0;
		case 'a':
			*result = val / 1000000000000000000.0;
			return 0;
		case 'f':
			*result = val / 1000000000000000.0;
			return 0;
		case 'p':
			*result = val / 1000000000000.0;
			return 0;
		case 'n':
			*result = val / 1000000000.0;
			return 0;
		case 'u':
			*result = val * 0.000001;
			return 0;
		case 'i':
			*result = val / 1000.0;
			return 0;
		case 'c':
			*result = val / 100.0;
			return 0;
		case 'd':
			*result = val / 10.0;
			return 0;
		case 'D':
			*result = val * 10.0;
			return 0;
		case 'h':
			*result = val * 100.0;
			return 0;
		case 'k':
			*result = val * 1000.0;
			return 0;
		case 'M':
			*result = val * 1000000.0;
			return 0;
		case 'G':
			*result = val * 1000000000.0;
			return 0;
		case 'T':
			*result = val * 1000000000000.0;
			return 0;
		case 'P':
			*result = val * 1000000000000000.0;
			return 0;
		case 'E':
			*result = val * 1000000000000000000.0;
			return 0;
		case 'Z':
			*result = val * 1000000000000000000000.0;
			return 0;
		case 'Y':
			*result = val * 1000000000000000000000000.0;
			return 0;
		case 'R':
			*result = val * 1000000000000000000000000000.0;
			return 0;
		case 'l': // int. mile
			*result = val * 1609.344;
			return 0;
		case 'w': // twip (17.64um)
			*result = (val * 17.64) / 1000000;
			return 0;
		case 't': // mil / thou (25.4um)
			*result = (val * 25.4) / 1000000;
			return 0;
		case 'o': // point (0.3528mm)
			*result = (val * 0.3528) / 1000;
			return 0;
		case 'A': // pica (4.2333mm)
			*result = (val * 4.2333) / 1000;
			return 0;
		case 'I': // inch
			*result = val / 39.37;
			return 0;
		case 'F': // foot (0.3048m)
			*result = val * 0.3048;
			return 0;
		case 'r': // yard
			*result = val * 0.9144;
			return 0;
		case 's': // U.S. survey mile/league
			*result = val * 1609.3472;
			return 0;
		case 'O': // fathom
			*result = val * 1.8288;
			return 0;
		case 'b': // U.S. cable
			*result = val * 220;
			return 0;
		case 'N': // nautical mile
			*result = val * 1852;
			return 0;
		case 'H': // hand
			*result = val * 0.1016;
			return 0;
		case 'C': // chain
			*result = val * 20.1168;
			return 0;
		case 'U': // furlong
			*result = val * 201.168;
			return 0;
		case 'L': // rod/pole/perch/lug
			*result = val * 5.0292;
			return 0;
		default:
			*result = val;
			return 1;
	}
	return 1;
}

// First converts to meters, then from there to the intended output unit.
// Returns 0 on success. Returns 1 otherwise.
int convert_length(char from, char to, double val, double* result) {
	switch (from) {
		case 'm':
			return from_meter(to, val, result);
		default:
			to_meter(from, val, result);
			if (DEBUG) printf("%f %c -> %f m\n", val, from, *result);
			if (to == 'm')
				return 0;
			return from_meter(to, *result, result);
	}
	return 0;
}
