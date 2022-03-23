PROJECT     = daylight-savings

TOOLCHAIN   = msvc-toolchain.cmake

CMAKE       = cmake.exe
CMAKE_FLAGS = -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)

BUILD       = Build
SOURCE      = Sources

SOURCES     = $(wildcard $(SOURCE)/*.cpp)
OBJECTS     = $(patsubst $(SOURCE)/%.cpp,build/CMakeFiles/$(PROJECT).dir/$(SOURCE)/%.cpp.o,$(SOURCES))

all: $(PROJECT)

$(PROJECT): CMakeLists.txt
	$(CMAKE) --build $(BUILD) --config Release

.PHONY: $(OBJECTS)
CMakeLists.txt: $(OBJECTS)
	$(CMAKE) -B $(BUILD)

clean:
	rm -fr bin/*
	rm -fr $(BUILD)/*

extra-clean:
	rm -fr bin
	rm -fr $(BUILD)
