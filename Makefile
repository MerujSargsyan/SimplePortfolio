all: 
	mkdir -p build
	cd build && cmake ..
	cd build && $(MAKE)

run: all
	bin/Simple_Portfolio
