CC?=gcc
CFLAGS?=-std=c11 -Werror -Wextra -pedantic -g
INSTALL_LOC?=\//usr/local/bin/
FILE?=conv

here: conv.c
	${CC} conv.c -o ${FILE} -lcurl

debug: conv.c
	${CC} conv.c -o ${FILE} -lcurl ${CFLAGS}

all: conv.c
	${CC} conv.c -o ${FILE} -lcurl ${CFLAGS} -Wall

path: conv.c
	sudo ${CC} conv.c -o ${INSTALL_LOC}${FILE} -lcurl

pathdebug: conv.c
	sudo ${CC} conv.c -o ${INSTALL_LOC}${FILE} -lcurl ${CFLAGS}

pathall: conv.c
	sudo ${CC} conv.c -o ${INSTALL_LOC}${FILE} -lcurl ${CFLAGS} -Wall
