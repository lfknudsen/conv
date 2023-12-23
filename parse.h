#ifndef PARSE_H
#define PARSE_H

#include "conv.h"

void error_msg(char *program_name);

int parse_input(struct parsed_input *input, int argc, char *argv[]);

#endif
