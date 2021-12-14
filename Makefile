PROJECT     = Daylight-Savings.dll

CMAKE       = /bin/cmake
CMAKE_FLAGS =

SOURCES     = $(wildcard src/*.cpp)
OBJECTS     = $(patsubst src/%.cpp,build/CMakeFiles/Testing.dir/src/%.cpp.o,$(SOURCES))

all: $(PROJECT)

$(PROJECT): CMakeLists.txt
	$(CMAKE) --build build

.PHONY: $(OBJECTS)
CMakeLists.txt: $(OBJECTS)
	$(CMAKE) -DCMAKE_TOOLCHAIN_FILE="mingw-gcc-toolchain.cmake" -B build

clean:
	rm -fr bin/*
	rm -fr build/*

extra-clean:
	rm -fr bin
	rm -fr build
