#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "conv.h"

// Reads validity-checked input and converts between two temperature scales,
// storing the outcome in *result (a pointer).
// Returns:
//		0 on success.
//		1 on failure.
int convert_temperature(char from, char to, double val, double *result);

#endif
