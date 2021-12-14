#ifndef _MEM_H
#define _MEM_H

#include <windows.h>
#include <stdbool.h>
#include <stdint.h>

// TODO: remove extraneous functions ie Detour + Hook

/**
 * Find Dynamic Memory Address of an embedded process.
 *
 * @param: uintptr_t ptr, unsigned offsets[], size_t size
 * @return: uintptr_t
**/
uintptr_t FindDynamicAddress(uintptr_t ptr, unsigned offsets[], size_t size);

/**
 * Byte replacement from source to destination.
 *
 * @param: char* destination, char* source, size_t size
 * @return: void
**/
void Patch(char* dst, char* src, size_t size);

/**
 * Hooks into a function and detours the target function to another function
 *
 * @param: void* targetFunc, void* myFunc, size_t size
 * @return: bool
**/
bool Detour(void* targetFunc, void* myFunc, size_t size);

/**
 * Hooks into a function and detours the target function to another function, then jumps back
 *
 * @param: char* src, char* dst, size_t size
 * @return: char*
**/
char* TrampHook(char* src, char* dst, size_t size);

#endif /* _MEM_H */
