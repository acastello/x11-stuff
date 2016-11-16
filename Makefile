CFLAGS=-I/usr/include/freetype2 -lXft -lX11 -lXRes

all: *.c

%: %.c
	gcc $^ -o $@ $(CFLAGS)
