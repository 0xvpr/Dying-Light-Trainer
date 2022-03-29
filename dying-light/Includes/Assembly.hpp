#ifndef ASSEMBLY_HEADER
#define ASSEMBLY_HEADER

/**
 * Takes no parameters.
 *
 * @param: void
 *
 * @return: Returns 69
**/
extern "C" int foo(void);

/**
 * Takes one parameter and returns it.
 *
 * @param:  x    Integer to be returned.
 *
 * @return: Returns x.
**/
extern "C" int bar(int);

#endif // ASSEMBLY_HEADER
