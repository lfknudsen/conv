CC?=gcc
CFLAGS?=-std=c11 -Werror -Wextra -pedantic -g

conv: conv.c
	${CC} conv.c -o conv -lcurl

all: conv.c
	${CC} conv.c -o conv -lcurl ${CFLAGS} -Wall

debug: conv.c	
	${CC} conv.c -o conv -lcurl ${CFLAGS}
