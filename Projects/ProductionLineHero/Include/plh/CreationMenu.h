#ifndef PLH_CREATION_MENU
#define PLH_CREATION_MENU

#include <plh\UIElement.h>
#include <plh\CreationButton.h>

#include <vector>


class CreationMenu : UIElement 
{

public:
    CreationMenu();
    CreationMenu(PixelCoords position, PixelCoords size);
    virtual void render(sptr<alpp::render::Renderer> i_Renderer);

private:
    std::vector<sptr<CreationButton>> m_Buttons;

};

#endif // PLH_CREATION_MENU