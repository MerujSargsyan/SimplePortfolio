CFLAGS = gcc -Wall -Wextra -std=gnu99
LIBSRC = lib/raylib/src
LIBS = -L$(LIBSRC) -lraylib -lm -ldl -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL

default: main

main: src/main.c
	$(CFLAGS) -I$(LIBSRC) -o bin/$@ $< $(LIBS)

run: bin/main
	$<
