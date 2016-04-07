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

    virtual void onKeyPressed    (uint8_t i_Key) { };
    virtual void onKeyReleased   (uint8_t i_Key) { };
    virtual void onCharacterTyped(uint8_t i_Key) { };
};

}}

#endif // ALPP_EVENT_KEYBOARD