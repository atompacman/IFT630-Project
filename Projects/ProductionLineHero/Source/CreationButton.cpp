#include <plh\CreationButton.h>

CreationButton::CreationButton() :
    UIElement()
{
}

CreationButton::CreationButton(WorldCoords position, WorldCoords size, UIElement * parent, ALLEGRO_COLOR color) :
    UIElement(position, size),
    m_ParentUI(parent),
    m_Color(color)
{}

void CreationButton::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->UpperLeftPos = m_Pos;
    cmd->LowerRightPos = cmd->UpperLeftPos + m_Size;
    cmd->Color = m_Color;
    i_Renderer->enqueueCommand(cmd);
}