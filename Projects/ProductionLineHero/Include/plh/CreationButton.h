#ifndef PLH_CREATION_BUTTON
#define PLH_CREATION_BUTTON

#include <plh\UIElement.h>

class CreationButton : UIElement
{

public:
    CreationButton();
    CreationButton(PixelCoords position, PixelCoords size, sptr<UIElement> parent);
    void render(sptr<alpp::render::Renderer> i_Renderer);

private:
    sptr<UIElement> m_ParentUI;


};

#endif // PLH_CREATION_BUTTON