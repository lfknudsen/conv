CC?=gcc
CFLAGS?=-std=c11 -Werror -Wextra -pedantic -g
INSTALL_LOC?=\//usr/local/bin/
FILE?=conv

here: conv.c parse.c curr.c
	${CC} conv.c parse.c curr.c -o ${FILE} -lcurl

debug: conv.c parse.c curr.c
	${CC} conv.c parse.c curr.c -o ${FILE} -lcurl ${CFLAGS}

all: conv.c parse.c curr.c
	${CC} conv.c parse.c curr.c -o ${FILE} -lcurl ${CFLAGS} -Wall

path: conv.c parse.c curr.c
	sudo ${CC} conv.c parse.c curr.c -o ${INSTALL_LOC}${FILE} -lcurl

pathdebug: conv.c parse.c curr.c
	sudo ${CC} conv.c parse.c curr.c -o ${INSTALL_LOC}${FILE} -lcurl ${CFLAGS}

pathall: conv.c parse.c curr.c
	sudo ${CC} conv.c parse.c curr.c -o ${INSTALL_LOC}${FILE} -lcurl ${CFLAGS} -Wall
