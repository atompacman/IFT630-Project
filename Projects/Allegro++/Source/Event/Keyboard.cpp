#include <allegro5/keyboard.h>

#include <alpp/Core.h>
#include <alpp/Event/Keyboard.h>

#include <easylogging++.h>

alpp::event::Keyboard::Keyboard() :
    Agent(),
    PressedKeys()
{
    CHECK_BOOL_AL_FUNC(al_install_keyboard(), m_InitSuccess, "Could not initialize keyboard");
}

bool alpp::event::Keyboard::handleEvent(ALLEGRO_EVENT i_Event)
{
    switch (i_Event.type)
    {
    case ALLEGRO_EVENT_KEY_DOWN:
        PressedKeys[i_Event.keyboard.keycode] = true;
        onKeyPressed(i_Event.keyboard.keycode);
        break;

    case ALLEGRO_EVENT_KEY_UP:
        PressedKeys[i_Event.keyboard.keycode] = false;
        onKeyReleased(i_Event.keyboard.keycode);
        break;

    case ALLEGRO_EVENT_KEY_CHAR:
        onCharacterTyped(i_Event.keyboard.keycode);
        break;
    }

    return true;
}

ALLEGRO_EVENT_SOURCE * alpp::event::Keyboard::getEventSource() const
{
    return al_get_keyboard_event_source();
}