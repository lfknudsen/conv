CC?=gcc
CFLAGS?=-std=c11 -Wextra -Wall -pedantic -g
INSTALL_LOC?=\//usr/local/bin/
FILE?=conv

here: conv.c parse.c curr.c temperature.c length.c
	${CC} conv.c parse.c curr.c temperature.c length.c -o ${FILE} -lcurl

debug: conv.c parse.c curr.c temperature.c length.c
	${CC} conv.c parse.c curr.c temperature.c length.c -o ${FILE} -lcurl ${CFLAGS}

all: conv.c parse.c curr.c temperature.c length.c
	${CC} conv.c parse.c curr.c temperature.c length.c -o ${FILE} -lcurl ${CFLAGS} -Wall

path: conv.c parse.c curr.c temperature.c length.c
	sudo ${CC} conv.c parse.c curr.c temperature.c length.c -o ${INSTALL_LOC}${FILE} -lcurl

pathdebug: conv.c parse.c curr.c temperature.c length.c
	sudo ${CC} conv.c parse.c curr.c temperature.c length.c -o ${INSTALL_LOC}${FILE} -lcurl ${CFLAGS}

pathall: conv.c parse.c curr.c temperature.c length.c
	sudo ${CC} conv.c parse.c curr.c temperature.c length.c -o ${INSTALL_LOC}${FILE} -lcurl ${CFLAGS} -Wall
