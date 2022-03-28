#ifndef EVENTS_HEADER
#define EVENTS_HEADER

namespace events {

    /**
     * Listens for keyboard input and performs various actions.
     *
     * @param: void
     *
     * @return: Returns caller request for shutdown.
    **/
    bool HandleKeyboard(void);

} // namespace events

#endif // EVENTS_HEADER
