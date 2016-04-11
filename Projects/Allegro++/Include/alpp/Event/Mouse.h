#ifndef ALPP_EVENT_MOUSE
#define ALPP_EVENT_MOUSE

#include <alpp/Event/Agent.h>

namespace alpp { namespace event {

class Mouse : public Agent
{
public:

    enum class Button
    {
        Left   = 1,
        Right  = 2,
        Middle = 3,
        Other1 = 4,
        Other2 = 5,
        Other3 = 6,
        Other4 = 7,
        Other5 = 8
    };

    static uint32_t const NUM_BUTTONS = static_cast<uint32_t>(Button::Other5);

    explicit Mouse(float i_MaxDurationForClickMS);
    virtual ~Mouse() { };
    
    bool handleEvent(ALLEGRO_EVENT i_Event) override;

    bool PressedButtons[NUM_BUTTONS];

    PixelCoords       Position;
    Vector2D<int16_t> DeltaPos;
    int16_t           DeltaScroll;

protected:

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

    virtual void onMouseMoved() { };

    virtual void onScroll() { };

    virtual void onLeftClick()                             { };
    virtual void onRightClick()                            { };
    virtual void onMiddleClick()                           { };
    virtual void onOtherButtonClick(Button /* i_Button */) { };

    virtual void onLeftPressed()                             { };
    virtual void onRightPressed()                            { };
    virtual void onMiddlePressed()                           { };
    virtual void onOtherButtonPressed(Button /* i_Button */) { };

    virtual void onLeftReleased()                             { };
    virtual void onRightReleased()                            { };
    virtual void onMiddleReleased()                           { };
    virtual void onOtherButtonReleased(Button /* i_Button */) { };

private:

    float  m_MaxDurationForClickSec;
    double m_PressedTimestamps[NUM_BUTTONS];
};

}}

#endif // ALPP_EVENT_MOUSE