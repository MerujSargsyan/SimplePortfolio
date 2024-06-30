all: 
	mkdir -p build
	cd build && cmake ..
	cd build && $(MAKE)

run: all
	build/bin/Simple_Portfolio

clean:
	rm -rf build/* bin/*
