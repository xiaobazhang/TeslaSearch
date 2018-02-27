ifeq ($(TIALLOY_PATH), )
	export TIALLOY_PATH=/usr/local/
endif


all:
	mkdir -p build;
	cd build;cmake -DCMAKE_INSTALL_PREFIX=${TIALLOY_PATH} ..;make -j8

clean:
	rm -rf build;rm -rf core.*;

install:
	cd build;make install;