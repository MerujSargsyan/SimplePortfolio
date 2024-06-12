CFLAGS = gcc -Wall -Wextra -std=gnu99
LIBSRC = lib/raylib/src
LIBS = -L$(LIBSRC) -lraylib -lm -ldl -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
LIBBUILT = 0

all: main

main: src/main.c
	if [$(LIBBUILT) = 0];
		@cd lib/raylib && git submodule update --init && cd ../../\
		LIBBUILT = 1
	$(CFLAGS) -I$(LIBSRC) -o bin/$@ $< $(LIBS)

run: bin/main
	main
	$<
