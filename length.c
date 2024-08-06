#include <stdio.h>

#include "length.h"
#include "units_length.h"

// Convert 'val' metres to another unit.
// Returns 0 on success. Returns 1 otherwise.
static int from_meter(enum unit to, double val, double* result) {
	if (DEBUG) printf("Converting from metres to %d.\n", to);
	switch (to) {
		case yocto: // yoctometre
			*result = val * 1000000000000000000000000.0;
			return 0;
		case zepto: // zeptometre
			*result = val * 1000000000000000000000.0;
			return 0;
		case atto: // attometre
			*result = val * 1000000000000000000.0;
			return 0;
		case femto: // femtometre
			*result = val * 1000000000000000.0;
			return 0;
		case pico: // picometre
			*result = val * 1000000000000.0;
			return 0;
		case nano: // nanometre
			*result = val * 1000000000.0;
			return 0;
		case micro: // micrometre
			*result = val * 1000000.0;
			return 0;
		case milli: // millimetre
			*result = val * 1000.0;
			return 0;
		case centi: // centimetre
			*result = val * 100.0;
			return 0;
		case deci: // decimetre
			*result = val * 10.0;
			return 0;
		case deca: // decametre
			*result = val / 10.0;
			return 0;
		case hecto: // hectometre
			*result = val / 100.0;
			return 0;
		case kilo: // kilometre
			*result = val / 1000.0;
			return 0;
		case mega: // megametre
			*result = val / 1000000.0;
			return 0;
		case giga: // gigametre
			*result = val / 1000000000.0;
			return 0;
		case tera: // terametre
			*result = val / 1000000000000.0;
			return 0;
		case peta: // petametre
			*result = val / 1000000000000000.0;
			return 0;
		case exa: // exametre
			*result = val / 1000000000000000000.0;
			return 0;
		case zetta: // zettametre
			*result = val / 1000000000000000000000.0;
			return 0;
		case yotta: // yottametre
			*result = val / 1000000000000000000000000.0;
			return 0;
		case ronna: // ronnametre
			*result = val / 1000000000000000000000000000.0;
			return 0;
		case mile: // int. mile
			*result = val / 1609.344;
			return 0;
		case twip: // twip (17.64um)
			*result = (val * 1000000) / 17.64;
			return 0;
		case thou: // mil / thou (25.4um)
			*result = (val * 1000000) / 25.4;
			return 0;
		case point: // point (0.3528mm)
			*result = (val * 1000) / 0.3528;
			return 0;
		case pica: // pica (4.2333mm)
			*result = (val * 1000) / 4.2333;
			return 0;
		case inch: // inch
			*result = val * 39.37;
			return 0;
		case foot: // foot (0.3048m)
			*result = val / 0.3048;
			return 0;
		case yard: // yard
			*result = val * 1.09361;
			return 0;
		case statute: // U.S. survey mile/league
			*result = val / 1609.3472;
			return 0;
		case fathom: // fathom
			*result = val * 0.5468;
			return 0;
		case cable: // U.S. cable
			*result = val / 220;
			return 0;
		case nautical: // nautical mile
			*result = val / 1852;
			return 0;
		case hand: // hand
			*result = val * 9.84252;
			return 0;
		case chain: // chain
			*result = val / 20.1168;
			return 0;
		case furlong: // furlong
			*result = val / 201.168;
			return 0;
		case rod: // rod/pole/perch/lug
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
static int to_meter(enum unit from, double val, double* result) {
	if (DEBUG) printf("Converting from %d to metres.\n", from);
	switch (from) {
		case yocto:
			*result = val / 1000000000000000000000000.0;
			return 0;
		case zepto:
			*result = val / 1000000000000000000000.0;
			return 0;
		case atto:
			*result = val / 1000000000000000000.0;
			return 0;
		case femto:
			*result = val / 1000000000000000.0;
			return 0;
		case pico:
			*result = val / 1000000000000.0;
			return 0;
		case nano:
			*result = val / 1000000000.0;
			return 0;
		case micro:
			*result = val * 0.000001;
			return 0;
		case milli:
			*result = val / 1000.0;
			return 0;
		case centi:
			*result = val / 100.0;
			return 0;
		case deci:
			*result = val / 10.0;
			return 0;
		case deca:
			*result = val * 10.0;
			return 0;
		case hecto:
			*result = val * 100.0;
			return 0;
		case kilo:
			*result = val * 1000.0;
			return 0;
		case mega:
			*result = val * 1000000.0;
			return 0;
		case giga:
			*result = val * 1000000000.0;
			return 0;
		case tera:
			*result = val * 1000000000000.0;
			return 0;
		case peta:
			*result = val * 1000000000000000.0;
			return 0;
		case exa:
			*result = val * 1000000000000000000.0;
			return 0;
		case zetta:
			*result = val * 1000000000000000000000.0;
			return 0;
		case yotta:
			*result = val * 1000000000000000000000000.0;
			return 0;
		case ronna:
			*result = val * 1000000000000000000000000000.0;
			return 0;
		case mile: // int. mile
			*result = val * 1609.344;
			return 0;
		case twip: // twip (17.64um)
			*result = (val * 17.64) / 1000000;
			return 0;
		case thou: // mil / thou (25.4um)
			*result = (val * 25.4) / 1000000;
			return 0;
		case point: // point (0.3528mm)
			*result = (val * 0.3528) / 1000;
			return 0;
		case pica: // pica (4.2333mm)
			*result = (val * 4.2333) / 1000;
			return 0;
		case inch: // inch
			*result = val / 39.37;
			return 0;
		case foot: // foot (0.3048m)
			*result = val * 0.3048;
			return 0;
		case yard: // yard
			*result = val * 0.9144;
			return 0;
		case statute: // U.S. survey mile/league
			*result = val * 1609.3472;
			return 0;
		case fathom: // fathom
			*result = val * 1.8288;
			return 0;
		case cable: // U.S. cable
			*result = val * 220;
			return 0;
		case nautical: // nautical mile
			*result = val * 1852;
			return 0;
		case hand: // hand
			*result = val * 0.1016;
			return 0;
		case chain: // chain
			*result = val * 20.1168;
			return 0;
		case furlong: // furlong
			*result = val * 201.168;
			return 0;
		case rod: // rod/pole/perch/lug
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
int convert_length(enum unit from, enum unit to, double val, double* result) {
	switch (from) {
		case metre:
			return from_meter(to, val, result);
		default:
			to_meter(from, val, result);
			if (DEBUG) printf("%f %d -> %f m\n", val, from, *result);
			if (to == metre)
				return 0;
			return from_meter(to, *result, result);
	}
	return 0;
}
