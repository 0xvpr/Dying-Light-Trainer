#ifndef _MEM_H
#define _MEM_H

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <stdbool.h>
#include <stdint.h>

/**
 * Finds the Dynamic Memory Access address of an embedded process.
 *
 * @param: uintptr_t ptr
 * @param: unsigned offsets[]
 * @param: size_t size
 *
 * @return: uintptr_t
**/
uintptr_t FindDynamicAddress(uintptr_t ptr, unsigned offsets[], size_t size);

/**
 * Byte replacement from source to destination.
 *
 * @param: char* destination
 * @param: char* source
 * @param: size_t size
 *
 * @return: void
**/
void Patch(char* dst, char* src, size_t size);

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
 * @param:  data          The data to scan within for the given pattern.
 * @param:  baseAddress   The base address of where the scan data is from.
 * @param:  lpPattern     The pattern to scan for.
 * @param:  pszMask       The mask to compare against for wildcards.
 * @param:  offset        The offset to add to the pointer.
 * @param:  resultUsage   The result offset to use when locating signatures that match multiple functions.
 *
 * @return: Pointer of the pattern found, 0 otherwise.
**/
PBYTE FindSignature(PBYTE BaseAddress, DWORD ImageSize, PBYTE Signature);

#endif /* _MEM_H */
