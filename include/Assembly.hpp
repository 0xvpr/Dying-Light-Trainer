#ifndef ASSEMBLY_HPP
#define ASSEMBLY_HPP

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Takes no parameters.
 *
 * @param: void
 *
 * @return: Returns 69
**/
int foo(void);

/**
 * Takes one parameter and returns it.
 *
 * @param:  x    Integer to be returned.
 *
 * @return: Returns x.
**/
int bar(int);

#ifdef __cplusplus
}
#endif

#endif // ASSEMBLY_HPP
