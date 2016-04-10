#ifndef PLH_CREATION_BUTTON
#define PLH_CREATION_BUTTON

#include <plh\UIElement.h>

class CreationButton : public UIElement
{

public:
    CreationButton();
    CreationButton(WorldCoords position, WorldCoords size, UIElement * parent, ALLEGRO_COLOR color);
    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:
    UIElement * m_ParentUI;
    ALLEGRO_COLOR m_Color;


};

#endif // PLH_CREATION_BUTTON