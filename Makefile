# See LICENSE file for copyright and license details.

include config.mk

SRC = ${NAME}.c
OBJ = ${SRC:.c=.o}

all: options ${NAME}

options:
	@echo ${NAME} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

${NAME}: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm ${NAME} ${OBJ}

install:
	@echo install ${NAME} to /usr/local/bin/
	@cp ${NAME} /usr/local/bin/

uninstall:
	@echo removing executable file from /usr/local/bin
	@rm /usr/local/bin/${NAME}

.PHONY: all options clean install uninstall
