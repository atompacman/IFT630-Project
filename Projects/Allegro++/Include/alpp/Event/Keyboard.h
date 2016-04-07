#ifndef ALPP_EVENT_KEYBOARD
#define ALPP_EVENT_KEYBOARD

#include <allegro5/keycodes.h>

#include <alpp/Event/Agent.h>

namespace alpp { namespace event {

class Keyboard : public Agent
{
public:

    explicit Keyboard();
    virtual ~Keyboard() { };
    
    bool handleEvent(ALLEGRO_EVENT i_Event) override;

    bool PressedKeys[ALLEGRO_KEY_MAX];

protected:

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

    virtual bool onKeyPressed    (uint8_t i_Key) { return true; };
    virtual bool onKeyReleased   (uint8_t i_Key) { return true; };
    virtual bool onCharacterTyped(uint8_t i_Key) { return true; };
};

}}

#endif // ALPP_EVENT_KEYBOARD