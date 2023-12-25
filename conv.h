#ifndef CONV_H
#define CONV_H

enum conv_type {
	Invalid,		// default case
	Currency,
	Volume,			// unimplemented
	Distance,		// unimplemented
	Weight,			// unimplemented
	Temperature,
	Data_Size		// unimplemented
};

struct parsed_input {
	enum conv_type type;
	double val;
	int from_pos;
	int to_pos;
	char from[4];
	char to[4];
};

#endif
