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

union u_data {
	char string[15];
	int unit;
};

struct parsed_input {
	enum conv_type type;
	double val;
	int from_pos;
	int to_pos;
	union u_data from;
	union u_data to;
	/*
	union u_from {
		char s_from[15];
		int e_from;
	} uf;
	union u_to {
		char s_to[15];
		int e_to;
	} ut;
	*/
	//char from[15];
	//char to[15];
};

#endif
