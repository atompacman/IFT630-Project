#include <plh\CreationButton.h>

CreationButton::CreationButton()
{

}

CreationButton::CreationButton(PixelCoords position, PixelCoords size, sptr<UIElement> parent) :
    UIElement(position, size),
    m_ParentUI(parent)
{}

void CreationButton::render(sptr<alpp::render::Renderer> i_Renderer)
{

}