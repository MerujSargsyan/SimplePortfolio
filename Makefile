all: 
	mkdir -p build
	cd build && cmake ..
	cd build && $(MAKE)

run:
	bin/Simple_Portfolio
