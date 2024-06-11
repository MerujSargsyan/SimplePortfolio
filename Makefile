CFLAGS = gcc -Wall -Wextra

default: main

main: src/main.c
	$(CFLAGS) -o bin/$@ $<
