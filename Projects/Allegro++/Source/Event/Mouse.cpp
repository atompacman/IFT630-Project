#include <allegro5/mouse.h>

#include <alpp/Core.h>
#include <alpp/Event/Mouse.h>

#include <easylogging++.h>

alpp::event::Mouse::Mouse(float i_MaxDurationForClickMS) :
    Agent(),
    PressedButtons          (),
    Position                (),
    DeltaPos                (),
    DeltaScroll             (0),
    m_MaxDurationForClickSec(i_MaxDurationForClickMS / 1000.),
    m_PressedTimestamps     ()
{
    CHECK_BOOL_AL_FUNC(al_install_mouse(), m_InitSuccess, "Could not initialize mouse");
}

bool alpp::event::Mouse::handleEvent(ALLEGRO_EVENT i_Event)
{
    auto button = Button(i_Event.mouse.button);

    switch (i_Event.type)
    {
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        if (i_Event.mouse.button >= NUM_BUTTONS)
        {
            LOG(WARNING) << "Cannot handle mouse buttons over " << NUM_BUTTONS;
            return true;
        }

        PressedButtons     [i_Event.mouse.button] = true;
        m_PressedTimestamps[i_Event.mouse.button] = i_Event.any.timestamp;

        switch (button)
        {
        case Button::Left  : onLeftPressed();              break;
        case Button::Right : onRightPressed();             break;
        case Button::Middle: onMiddlePressed();            break;
        default:             onOtherButtonPressed(button); break;
        }

        break;

    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        if (i_Event.mouse.button >= NUM_BUTTONS)
        {
            LOG(WARNING) << "Cannot handle mouse buttons over " << NUM_BUTTONS;
            return true;
        }

        PressedButtons[i_Event.mouse.button] = false;

        switch (button)
        {
        case Button::Left  : onLeftReleased();              break;
        case Button::Right : onRightReleased();             break;
        case Button::Middle: onMiddleReleased();            break;
        default:             onOtherButtonReleased(button); break;
        }

        // Handle rapid clicks
        if (i_Event.any.timestamp - m_PressedTimestamps[i_Event.mouse.button] 
                > m_MaxDurationForClickSec)
        {
            return true;
        }

        switch (button)
        {
        case Button::Left:   onLeftClick();              break;
        case Button::Right:  onRightClick();             break;
        case Button::Middle: onMiddleClick();            break;
        default:             onOtherButtonClick(button); break;
        }

        break;

    case ALLEGRO_EVENT_MOUSE_AXES:
        Position    = PixelCoords(i_Event.mouse.x, i_Event.mouse.y);
        DeltaPos    = Vector2D<int16_t>(i_Event.mouse.dx, i_Event.mouse.dy);
        DeltaScroll = i_Event.mouse.dz;
        
        if (DeltaPos != Vector2D<int16_t>(0, 0))
        {
            onMouseMoved();
        }
        if (DeltaScroll != 0)
        {
            onScroll();
        }
        
        break;
    }

    return true;
}

ALLEGRO_EVENT_SOURCE * alpp::event::Mouse::getEventSource() const
{
    return al_get_mouse_event_source();
}