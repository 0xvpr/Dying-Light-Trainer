#ifndef HACKS_HEADER
#define HACKS_HEADER

namespace hacks {

    /**
     * Toggles god mode on if bGodmode is true and off it bGodmode is false.
     *
     * @param:  bGodmode    Boolean value of the hack state.
     *
     * @return: void
    **/ 
    void ToggleGodmode(bool bGodmode);

    /**
     * Toggles one shot kill on if bOneShot is true and off it bOneShot is false.
     *
     * @param:  bOneShot    Boolean value of the hack state.
     *
     * @return: void
    **/ 
    void ToggleOneShot(bool bOneShot);

    /**
     * Toggles infinite stamina if bStamina is true and off it bStamina is false.
     *
     * @param:  bStamina    Boolean value of the hack state.
     *
     * @return: void
    **/ 
    void ToggleInfiniteStamina(bool bStamina);

} // namespace hacks

#endif // HACKS_HEADER
