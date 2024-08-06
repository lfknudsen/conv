#ifndef PARSE_H
#define PARSE_H

#include "conv.h"

int error_msg();

int parse_input(struct parsed_input *input, int argc, char *argv[]);

#endif
