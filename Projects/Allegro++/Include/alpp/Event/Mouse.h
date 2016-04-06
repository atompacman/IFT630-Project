#ifndef ALPP_EVENT_MOUSE
#define ALPP_EVENT_MOUSE

#include <alpp/Event/Agent.h>

namespace alpp { namespace event {

class Mouse : public Agent
{
public:

    explicit Mouse();
    virtual ~Mouse() { };

    bool handleEvent(ALLEGRO_EVENT i_Event) override;

    static uint8_t const MAX_NUM_BUTTONS = 16;

    bool m_PressedButtons[MAX_NUM_BUTTONS];

    uint16_t m_PosX;
    uint16_t m_PosY;
    uint16_t m_DeltaX;
    uint16_t m_DeltaY;
    uint16_t m_DeltaScroll;

protected:

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

    virtual void onMouseMoved() = 0;
    virtual void onButtonPressed(uint8_t i_Button) = 0;
    virtual void onButtonReleased(uint8_t i_Button) = 0;
};

}}

#endif // ALPP_EVENT_MOUSE