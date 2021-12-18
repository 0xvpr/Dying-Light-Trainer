cmake_minimum_required(VERSION 3.8.0)

# Project name
project("Daylight Savings")
set(TARGET daylight-savings)

# Enable languages
enable_language(C)
enable_language(CXX)
enable_language(ASM_MASM)

# Set language standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD   99)

# Output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Include directories
include_directories(${TARGET} include)
set(INCLUDE_DIR include)

# Source directories
set(SOURCE_DIR src)
set(ASM_DIR asm/masm)

# Add sources
set(SOURCES 
    # C Sources
    ${SOURCE_DIR}/main.c
    ${SOURCE_DIR}/drawing.c
    ${SOURCE_DIR}/events.c
    ${SOURCE_DIR}/render.c
    ${SOURCE_DIR}/hacks.c
    ${SOURCE_DIR}/mem.c
    # Includes
    ${INCLUDE_DIR}/assembly.h
    ${INCLUDE_DIR}/offsets.h
    ${INCLUDE_DIR}/drawing.h
    ${INCLUDE_DIR}/events.h
    ${INCLUDE_DIR}/render.h
    ${INCLUDE_DIR}/hacks.h
    ${INCLUDE_DIR}/mem.h
    # Assembly Sources
    ${ASM_DIR}/foo.asm
    ${ASM_DIR}/bar.asm
)

# Build dynamic load library
add_library(${TARGET} SHARED ${SOURCES})
set_target_properties(
    ${TARGET}
    PROPERTIES
    OUTPUT_NAME ${TARGET}
    PREFIX ""
    SUFFIX ".dll"
)
