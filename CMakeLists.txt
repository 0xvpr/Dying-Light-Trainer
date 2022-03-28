cmake_minimum_required(VERSION 3.2)

# Project name
set(TARGET daylight-savings)
project(${TARGET} C CXX ASM_MASM)

# Set language standards
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD            99)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_INCLUDE_CURRENT_DIR   ON)

# Output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Lib")

# Include directories
include_directories(${TARGET}
    .
    dying-light/Includes
    imgui
    kiero
    kiero/minhook/src
    kiero/minhook/src/hde
    kiero/minhook/include
)

set(KIERO_DIR kiero)
set(KIERO_SOURCES
    # Sources
    ${KIERO_DIR}/kiero.cpp
    ${KIERO_DIR}/minhook/src/buffer.c
    ${KIERO_DIR}/minhook/src/hook.c
    ${KIERO_DIR}/minhook/src/trampoline.c
    ${KIERO_DIR}/minhook/src/hde/hde32.c
    ${KIERO_DIR}/minhook/src/hde/hde64.c

    # Includes
    ${KIERO_DIR}/kiero.h
    ${KIERO_DIR}/minhook/include/MinHook.h
    ${KIERO_DIR}/minhook/src/buffer.h
    ${KIERO_DIR}/minhook/src/hde/hde32.h
    ${KIERO_DIR}/minhook/src/hde/hde64.h
    ${KIERO_DIR}/minhook/src/hde/pstdint.h
    ${KIERO_DIR}/minhook/src/hde/table32.h
    ${KIERO_DIR}/minhook/src/hde/table64.h
    ${KIERO_DIR}/minhook/src/trampoline.h
)

set(IMGUI_DIR imgui)
set(IMGUI_SOURCES
    # Sources
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_impl_dx11.cpp
    ${IMGUI_DIR}/imgui_impl_win32.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    # Includes
    ${IMGUI_DIR}/imgui_impl_dx11.h
    ${IMGUI_DIR}/imgui_impl_win32.h
    ${IMGUI_DIR}/imgui_internal.h
    ${IMGUI_DIR}/imstb_rectpack.h
    ${IMGUI_DIR}/imstb_textedit.h
    ${IMGUI_DIR}/imstb_truetype.h
)

# Source directories
set(SOURCE_DIR dying-light/Sources)
set(INCLUDE_DIR dying-light/Includes)
set(ASM_DIR ${SOURCE_DIR}/Assembly)

# Add sources
set(SOURCES 
    # CXX Sources
    ${SOURCE_DIR}/DllMain.cpp
    ${SOURCE_DIR}/Events.cpp
    ${SOURCE_DIR}/Hacks.cpp
    ${SOURCE_DIR}/Memory.cpp
    ${SOURCE_DIR}/Menu.cpp
    ${SOURCE_DIR}/Render.cpp
    # CXX Includes
    ${INCLUDE_DIR}/Assembly.hpp
    ${INCLUDE_DIR}/Offsets.hpp
    ${INCLUDE_DIR}/Events.hpp
    ${INCLUDE_DIR}/Hacks.hpp
    ${INCLUDE_DIR}/Memory.hpp
    ${INCLUDE_DIR}/Menu.hpp
    ${INCLUDE_DIR}/Render.hpp
    # Assembly Sources
    ${ASM_DIR}/foo.asm
    ${ASM_DIR}/bar.asm
)

# Build dynamic load library
add_library(${TARGET} SHARED ${KIERO_SOURCES} ${MINHOOK_SOURCES} ${IMGUI_SOURCES} ${SOURCES})
set_target_properties(
    ${TARGET}
    PROPERTIES
    OUTPUT_NAME ${TARGET}
    PREFIX ""
    SUFFIX ".dll"
)
