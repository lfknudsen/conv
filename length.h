#ifndef DIST_H
#define DIST_H

#include "conv.h"
#include "units_length.h"

int convert_length(enum unit from, enum unit to, double val, double* result);

#endif
