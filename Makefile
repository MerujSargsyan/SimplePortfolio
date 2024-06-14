# check if lib already downloaded
LIBFLAG=0

all: | blib
	mkdir -p build
	cd build && cmake ..
	cd build && $(MAKE)

blib:
ifeq ($(LIBFLAG),0)
	@cd lib/raylib/ && git submodule update --init && cd src && make && cd ../../../
	$(eval LIBFLAG := 1)
endif
run:
	bin/main
