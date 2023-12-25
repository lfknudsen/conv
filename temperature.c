#include "conv.h"
#include "temperature.h"

int conversion(char from, char to, double val, double *result) {
	switch (from) {
		case 'C':
			switch (to) {
				case 'K':
					*result = val + 273.15;
					return 0;
				case 'F':
					*result = val * (9.0/5.0) + 32.0;
					return 0;
				case 'R':
					*result = (val + 273.15) * (9.0/5.0);
					return 0;
				case 'N':
					*result = val * (33.0/100.0);
					return 0;
				case 'E':
					*result = val * (4.0/5.0);
					return 0;
				case 'O':
					*result = val * (21.0/40.0) + 7.5;
					return 0;
				case 'D':
					*result = (100.0 - val) * (3.0/2.0);
					return 0;
				default:
					return 1;
			}
		case 'K':
			switch (to) {
				case 'C':
					*result = val - 273.15;
					return 0;
				case 'F':
					*result = val * (9.0/5.0) - 459.67;
					return 0;
				case 'R':
					*result = val * (9.0/5.0);
					return 0;
				case 'N':
					*result = (val - 273.15) * (33.0/100.0);
					return 0;
				case 'E':
					*result = (val - 273.15) * (4.0/5.0);
					return 0;
				case 'O':
					*result = (val - 273.15) * (21.0/40.0) + 7.5;
					return 0;
				case 'D':
					*result = (373.15 - val) * (3.0/2.0);
					return 0;
				default:
					return 1;
			}
		case 'F':
			switch (to) {
				case 'C':
					*result = (val - 32.0) * (5.0/9.0);
					return 0;
				case 'K':
					*result = (val + 459.67) * (5.0/9.0);
					return 0;
				case 'R':
					*result = val + 459.67;
					return 0;
				case 'N':
					*result = (val - 32.0) * (11.0/60.0);
					return 0;
				case 'E':
					*result = (val - 32.0) * (4.0/9.0);
					return 0;
				case 'O':
					*result = (val - 32.0) * (7.0/24.0) + 7.5;
					return 0;
				case 'D':
					*result = (212.0 - val) * (5.0/6.0);
					return 0;
				default:
					return 1;
			}
		case 'R':
			switch (to) {
				case 'C':
					*result = (val - 491.67) * (5.0/9.0);
					return 0;
				case 'K':
					*result = val * (5.0/9.0);
					return 0;
				case 'F':
					*result = val - 491.67;
					return 0;
				case 'N':
					*result = (val - 491.67) * (11.0/60.0);
					return 0;
				case 'E':
					*result = (val - 491.67) * (4.0/9.0);
					return 0;
				case 'O':
					*result = (val - 491.67) * (7.0/24.0) + 7.5;
					return 0;
				case 'D':
					*result = (671.67 - val) * (5.0/6.0);
					return 0;
				default:
					return 1;
			}
		case 'N':
			switch (to) {
				case 'C':
					*result = val * (100.0/33.0);
					return 0;
				case 'K':
					*result = val * (100.0/33.0) + 273.15;
					return 0;
				case 'F':
					*result = val * (60.0/11.0) + 32;
					return 0;
				case 'R':
					*result = val * (60.0/11.0) + 491.67;
					return 0;
				default:
					conversion(from, 'K', val, result);
					*result = conversion('K', to, *result, result);
					return 0;
			}
		case 'E':
			switch (to) {
				case 'C':
					*result = val * (5.0/4.0);
					return 0;
				case 'K':
					*result = val * (5.0/4.0) + 273.15;
					return 0;
				case 'F':
					*result = val * (9.0/4.0) + 32.0;
					return 0;
				case 'R':
					*result = val * (9.0/4.0) + 491.67;
					return 0;
				default:
					conversion(from, 'K', val, result);
					*result = conversion('K', to, *result, result);
					return 0;
			}
		case 'O':
			switch (to) {
				case 'C':
					*result = (val - 7.5) * (40.0/21.0);
					return 0;
				case 'K':
					*result = (val - 7.5) * (40.0/21.0) + 273.15;
					return 0;
				case 'F':
					*result = (val - 7.5) * (24.0/7.0) + 32.0;
					return 0;
				case 'R':
					*result = (val - 7.5) * (24.0/7.0) + 491.67;
					return 0;
				default:
					conversion(from, 'K', val, result);
					*result = conversion('K', to, *result, result);
					return 0;
			}
		case 'D':
			switch (to) {
				case 'C':
					*result = 100.0 - val * (2.0/3.0);
					return 0;
				case 'K':
					*result = 373.15 - val * (2.0/3.0);
					return 0;
				case 'F':
					*result = 212.0 - val * (6.0/5.0);
					return 0;
				case 'R':
					*result = 671.67 - val * (6.0/5.0);
					return 0;
				default:
					conversion(from, 'K', val, result);
					*result = conversion('K', to, *result, result);
					return 0;
		}
		default:
			return 1;
	}
	return 1;
}

// Reads validity-checked input and converts between two temperature scales,
// storing the outcome in *result (a pointer).
// Returns:
//		0 on success.
//		1 on failure.
// C = Celsius, K = Kelvin, F = Fahrenheit, R = Rankine, N = Newton, E = Réaumur, O = Rømer.
int convert_temperature(struct parsed_input *input, double *result) {
	return conversion(input->from[0], input->to[0], input->val, result);
}
