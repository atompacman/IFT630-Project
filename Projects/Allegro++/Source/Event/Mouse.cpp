#include <allegro5/mouse.h>

#include <alpp/Core.h>
#include <alpp/Event/Mouse.h>

#include <easylogging++.h>

alpp::event::Mouse::Mouse() :
    Agent(),
    m_PressedButtons(),
    m_PosX          (0),
    m_PosY          (0),
    m_DeltaX        (0),
    m_DeltaY        (0),
    m_DeltaScroll   (0)
{
    CHECK_BOOL_AL_FUNC(al_install_mouse(), m_InitSuccess, "Could not initialize mouse");
}

bool alpp::event::Mouse::handleEvent(ALLEGRO_EVENT i_Event)
{
    switch (i_Event.type)
    {
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        if (i_Event.mouse.button < MAX_NUM_BUTTONS)
        {
            m_PressedButtons[i_Event.mouse.button] = true;
        }
        else
        {
            LOG(WARNING) << "Cannot handle mouse button over " << MAX_NUM_BUTTONS;
        }
        onButtonPressed(i_Event.mouse.button);
        break;

    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        if (i_Event.mouse.button < MAX_NUM_BUTTONS)
        {
            m_PressedButtons[i_Event.mouse.button] = false;
        }
        else
        {
            LOG(WARNING) << "Cannot handle mouse button over " << MAX_NUM_BUTTONS;
        }
        onButtonReleased(i_Event.mouse.button);
        break;

    case ALLEGRO_EVENT_MOUSE_AXES:
        m_PosX        = i_Event.mouse.x;
        m_PosY        = i_Event.mouse.y;
        m_DeltaX      = i_Event.mouse.dx;
        m_DeltaY      = i_Event.mouse.dy;
        m_DeltaScroll = i_Event.mouse.dy;
        onMouseMoved();
        break;
    }

    return true;
}

ALLEGRO_EVENT_SOURCE * alpp::event::Mouse::getEventSource() const
{
    return al_get_mouse_event_source();
}