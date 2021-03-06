#ifndef PLH_CREATION_MENU
#define PLH_CREATION_MENU

#include <plh/UIElement.h>

#include <vector>

class CreationButton;

// Represents the menu used to create objects in the factory
class CreationMenu : public UIElement 
{
public:

    CreationMenu(WorldCoords i_Position, WorldCoords i_Size, ALLEGRO_COLOR i_Color);

    void render(sptr<alpp::render::Renderer> i_Renderer) const override;

    void addButton(CreationButton * i_Button);
    std::vector<CreationButton *> getButtons() const;

private:

    std::vector<CreationButton *> m_Buttons;
};

#endif // PLH_CREATION_MENU