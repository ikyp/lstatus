NAME = dwmstatus

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/include/X11/
# X11LIB = /usr/lib/

# INCS = -I. -I/usr/include -I${X11INC}
INCS = -I${X11INC}
# LIBS = -L/usr/lib -lc -L${X11LIB} -lX11
LIBS = -L/usr/lib -lc -lX11

DEBUG_CFLAGS = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
DEBUG_LDFLAGS = -g ${LIBS}
CFLAGS = -std=c99 -pedantic -Wall -Os ${INCS} ${CPPFLAGS}
LDFLAGS = -s ${LIBS}

# compiler and linker
CC = gcc
