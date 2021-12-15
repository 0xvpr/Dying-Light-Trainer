cmake_minimum_required(VERSION 3.8.0)

# Project name
project(Daylight-Savings)
set(TARGET Daylight-Savings)

# Enable languages
enable_language(CXX)
if (MSVC)
    enable_language(MASM)
else ()
    enable_language(ASM_NASM)
endif ()

# Set language standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD   99)

# Output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Add include directories
include_directories(${TARGET} include)

# Source directories
set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(ASM_DIR asm)

# Add sources
set( SOURCES 
     ${SOURCE_DIR}/Main.cpp
     ${SOURCE_DIR}/Drawing.cpp
     ${SOURCE_DIR}/Events.cpp
     ${SOURCE_DIR}/Hacks.cpp
     ${SOURCE_DIR}/Mem.cpp
     ${SOURCE_DIR}/Render.cpp
     ${INCLUDE_DIR}/Assembly.hpp
     ${INCLUDE_DIR}/Drawing.hpp
     ${INCLUDE_DIR}/Entity.hpp
     ${INCLUDE_DIR}/Events.hpp
     ${INCLUDE_DIR}/Hacks.hpp
     ${INCLUDE_DIR}/Mem.hpp
     ${INCLUDE_DIR}/Offsets.hpp
     ${INCLUDE_DIR}/Render.hpp
     ${ASM_DIR}/foo.asm 
     ${ASM_DIR}/bar.asm )

# Build dynamic load library
add_library(${TARGET} SHARED ${SOURCES})
set_target_properties(
    ${TARGET}
    PROPERTIES
    OUTPUT_NAME ${TARGET}
    PREFIX ""
    SUFFIX ".dll"
)

if (MSVC)
    set_source_files_properties(
        ${ASM_DIR}/foo.asm
        ${ASM_DIR}/bar.asm
        PROPERTIES
        COMPILE_FLAGS "/safeseh"
    )
endif ()