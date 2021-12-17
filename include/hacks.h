#ifndef _HACKS_H
#define _HACKS_H

#include <stdbool.h>

bool bGodmode;
bool bOneShot;
bool bStamina;

/**
 * Toggles god mode on if bGodmode is true and off it bGodmode is false.
 *
 * @param:  bGodmode    Boolean value of the hack state.
 *
 * @return: void
**/ 
void hacks_ToggleGodmode(bool bGodmode);

/**
 * Toggles one shot kill on if bOneShot is true and off it bOneShot is false.
 *
 * @param:  bOneShot    Boolean value of the hack state.
 *
 * @return: void
**/ 
void hacks_ToggleOneShot(bool bOneShot);

/**
 * Toggles infinite stamina if bStamina is true and off it bStamina is false.
 *
 * @param:  bStamina    Boolean value of the hack state.
 *
 * @return: void
**/ 
void hacks_ToggleInfiniteStamina(bool bStamina);

#endif /* _HACKS_H */
