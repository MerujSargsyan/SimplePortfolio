CFLAGS = gcc -Wall -Wextra -std=gnu99
LIBSRC = lib/raylib/src

default: main

main: src/main.c
	$(CFLAGS) -I$(LIBSRC) -o bin/$@ $<
