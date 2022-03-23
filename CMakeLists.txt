cmake_minimum_required(VERSION 3.2)

# Project name
set(TARGET daylight-savings)
project(${TARGET} C CXX ASM_MASM)

# Set language standards
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD            99)
set(CMAKE_C_STANDARD_REQUIRED   ON)

# Output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Lib")

# Include directories
include_directories(${TARGET} Includes)
set(INCLUDE_DIR Includes)

# Source directories
set(SOURCE_DIR Sources)
set(ASM_DIR ${SOURCE_DIR}/Assembly)

# Add sources
set(SOURCES 
    # CXX Sources
    ${SOURCE_DIR}/Main.cpp
    ${SOURCE_DIR}/Drawing.cpp
    ${SOURCE_DIR}/Events.cpp
    ${SOURCE_DIR}/Render.cpp
    ${SOURCE_DIR}/Hacks.cpp
    ${SOURCE_DIR}/Memory.cpp
    # CXX Includes
    ${INCLUDE_DIR}/Assembly.hpp
    ${INCLUDE_DIR}/Offsets.hpp
    ${INCLUDE_DIR}/Drawing.hpp
    ${INCLUDE_DIR}/Events.hpp
    ${INCLUDE_DIR}/Render.hpp
    ${INCLUDE_DIR}/Hacks.hpp
    ${INCLUDE_DIR}/Memory.hpp
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