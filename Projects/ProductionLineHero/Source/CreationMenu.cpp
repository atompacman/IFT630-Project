#include <plh\CreationMenu.h>

CreationMenu::CreationMenu() :
    UIElement()
{
}

CreationMenu::CreationMenu(PixelCoords position, PixelCoords size) :
    UIElement(position, size)
{    
}

void CreationMenu::render(sptr<alpp::render::Renderer> i_Renderer)
{
    // render the menu, and all its buttons
}
