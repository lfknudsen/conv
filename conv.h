#ifndef CONV_H
#define CONV_H

#define DEBUG 0

enum conv_type {
	Invalid,		// default case
	Currency,
	Volume,			// unimplemented
	Length,
	Weight,			// unimplemented
	Temperature,
	Data_Size		// unimplemented
};

struct parsed_input {
	enum conv_type type;
	double val;
	int from_pos;
	int to_pos;
	char from[15];
	char to[15];
};

#endif
