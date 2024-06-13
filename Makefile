CFLAGS = gcc -Wall -Wextra -std=gnu99
LIBSRC = lib/raylib/src
LIBS = -L$(LIBSRC) 
LIBBUILT = 0
SHELLTP := $(shell uname -s)

ifeq ($(SHELLTP), Darwin) 
    #macOS
    LIBS = -L$(LIBSRC) -lraylib -lm -ldl -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
else
    #Linux
    LIBS = -L$(LIBSRC) -lraylib -lm -lpthread -ldl -lX11
endif

all: main

main: src/main.c | build
	$(CFLAGS) -I$(LIBSRC) -o bin/$@ $< $(LIBS)

build:
ifeq ($(LIBBUILT),0)
	@cd lib/raylib && git submodule update --init && cd src/ && make PLATFORM=PLATFORM_DESKTOP && cd ../../
	$(eval LIBBUILT := 1)
endif   

run: bin/main | main
	$<
