CFLAGS = gcc -Wall -Wextra -std=gnu99
LIBSRC = lib/raylib/src
LIBS = -L$(LIBSRC) -lraylib -lm -ldl -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
LIBBUILT = 1

all: main

main: src/main.c | build
	$(CFLAGS) -I$(LIBSRC) -o bin/$@ $< $(LIBS)

build:
ifeq ($(LIBBUILT),0)
	@cd lib/raylib && git submodule update --init && cd src/ && make && cd ../../
	$(eval LIBBUILT := 1)
endif   

run: bin/main | main
	$<
