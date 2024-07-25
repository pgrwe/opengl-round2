run: build
	cmake --build build
	./build/bin/opengl_round2

clean: 
	rm -rf build

build:
	cmake -B build
	cmake --build build
