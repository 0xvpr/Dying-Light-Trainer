#ifndef _EVENTS_H
#define _EVENTS_H

#include <stdbool.h>

/**
 * Listens for keyboard input and performs various actions.
 *
 * @param: void
 *
 * @return: Returns caller request for shutdown.
**/
bool events_HandleKeyboard(void);

#endif /* _EVENTS_H */
