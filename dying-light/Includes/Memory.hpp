#ifndef MEMORY_HEADER
#define MEMORY_HEADER

#include <stdint.h>
#include <windows.h>

/**
 * Finds the Dynamic Memory Access address of an embedded process.
 *
 * @param: uintptr_t ptr
 * @param: unsigned* offsets
 * @param: size_t size
 *
 * @return: uintptr_t
**/
uintptr_t FindDynamicAddress(uintptr_t ptr, unsigned* offsets, size_t size);

/**
 * Byte replacement from source to destination.
 *
 * @param: char* destination
 * @param: char* source
 * @param: size_t size
 *
 * @return: void
**/
void Patch(void* dst, void* src, size_t size);

/**
 * Hooks into a function and detours the target function to another function.
 *
 * @param: void* targetFunc
 * @param: void* myFunc
 * @param: size_t size
 *
 * @return: bool
**/
bool Detour(void* targetFunc, void* myFunc, size_t size);

/**
 * Hooks into a function and detours the target function to another function, then jumps back.
 *
 * @param: char* src
 * @param: char* dst
 * @param: size_t size
 *
 * @return: char*
**/
char* TrampHook(char* targetFunc, char* myFunc, size_t size);

/**
 * Scans a given chunk of data for the given pattern and mask.
 *
 * @param:  base_addr       The base address of where the scan data is from.
 * @param:  img_size        The size of the module.
 * @param:  pattern         The pattern to scan for.
 * @param:  pattern_size    The size of the pattern to scan for.
 *
 * @return: Pointer of the pattern found, 0 otherwise.
**/
PBYTE FindPattern(unsigned char* base_addr, size_t img_size, unsigned char* pattern, size_t s);

#endif // MEMORY_HEADER
