#ifndef PLH_CREATION_MENU
#define PLH_CREATION_MENU

#include <plh\UIElement.h>

#include <vector>

class CreationButton;

class CreationMenu : public UIElement 
{

public:
    CreationMenu();
    CreationMenu(WorldCoords position, WorldCoords size);
    virtual void render(sptr<alpp::render::Renderer> i_Renderer) const;
    void addButton(CreationButton * button);

private:
    std::vector<CreationButton *> m_Buttons;

};

#endif // PLH_CREATION_MENU