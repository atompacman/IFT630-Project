#include <alpp/Render/Camera.h>

#include <plh/Common.h>
#include <plh/Event/Keyboard.h>

bool Keyboard::onCharacterTyped(uint8_t i_Key)
{
    WorldCoords translation;

    switch (i_Key)
    {
    case ALLEGRO_KEY_LEFT   : translation.x -= KEYBOARD_SCROLL_SPEED; break;
    case ALLEGRO_KEY_RIGHT  : translation.x += KEYBOARD_SCROLL_SPEED; break;
    case ALLEGRO_KEY_UP     : translation.y -= KEYBOARD_SCROLL_SPEED; break;
    case ALLEGRO_KEY_DOWN   : translation.y += KEYBOARD_SCROLL_SPEED; break;
    case ALLEGRO_KEY_ESCAPE : return false;
    }

    m_Camera->translate(translation);
    return true;
}