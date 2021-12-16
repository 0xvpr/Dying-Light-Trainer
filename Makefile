PROJECT     = daylight-savings

#CC         = i686-w64-mingw32-gcc-posix
CC          = x86_64-w64-mingw32-gcc-posix
CFLAGS      = -std=c99 -Wall -Wextra -Werror -Wpedantic -Wshadow

#LD         = i686-w64-mingw32-gcc-posix
LD          = x86_64-w64-mingw32-gcc-posix
LDFLAGS     = -shared

ASM         = nasm
#ASFLAGS    = -f win32
ASFLAGS     = -f win64

BIN         = bin
BUILD       = build
DEBUG       = $(OBJ)/debug
RELEASE     = $(OBJ)/release

SRC         = src
OBJ         = build
SOURCES     = $(wildcard $(SRC)/*.c)
DBG_OBJECTS = $(patsubst $(SRC)/%.c,$(DEBUG)/%.o,$(SOURCES))
REL_OBJECTS = $(patsubst $(SRC)/%.c,$(RELEASE)/%.o,$(SOURCES))

ASM_SRC     = asm
ASM_OBJ     = $(OBJ)/asm
ASM_SOURCES = $(wildcard $(ASM_SRC)/*.asm)
ASM_OBJECTS = $(patsubst $(ASM_SRC)/%.asm,$(ASM_OBJ)/%.o,$(ASM_SOURCES))

INCLUDE     = include 
INCLUDES    = $(addprefix -I,$(INCLUDE))

LIB_FILES   = psapi
LIBS        = $(addprefix -l,$(LIB_FILES))

all: debug release

debug: $(DEBUG)
release: $(RELEASE)

$(DEBUG): CFLAGS += -g -DDEBUG
$(DEBUG): $(OBJ) $(BIN) $(ASM_OBJECTS) $(DBG_OBJECTS) 
	$(LD) $(LDFLAGS) $(ASM_OBJECTS) $(DBG_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT)_d.dll

$(RELEASE): CFLAGS  += -O3 -fno-ident -fvisibility=hidden -DNDEBUG
$(RELEASE): LDFLAGS += -s
$(RELEASE): $(OBJ) $(BIN) $(ASM_OBJECTS) $(REL_OBJECTS)
	$(LD) $(LDFLAGS) $(ASM_OBJECTS) $(REL_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT).dll

$(ASM_OBJECTS): $(ASM_OBJ)/%.o: $(ASM_SRC)/%.asm
	$(ASM) $(ASFLAGS) $^ -o $@

$(DBG_OBJECTS): $(DEBUG)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(REL_OBJECTS): $(RELEASE)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ):
	mkdir -p $@/asm
	mkdir -p $@/debug
	mkdir -p $@/release

$(BIN):
	mkdir -p $@

clean:
	rm -f bin/*
	rm -f build/{asm,debug,release}/*

extra-clean:
	rm -fr bin
	rm -fr build
