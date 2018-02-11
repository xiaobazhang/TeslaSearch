all:
	mkdir -p build;
	cd build;cmake -DCMAKE_INSTALL_PREFIX=../ ..;make -j8

clean:
	rm -rf build;rm -rf core.*;

install:
	cd build;make install;