#include <plh/CreationButton.h>
#include <plh/CreationMenu.h>

CreationMenu::CreationMenu(WorldCoords i_Position, WorldCoords i_Size, ALLEGRO_COLOR i_Color) :
    UIElement(i_Position, i_Size, i_Color)
{

}

void CreationMenu::addButton(CreationButton * button)
{
    m_Buttons.push_back(button);
}

std::vector<CreationButton*> CreationMenu::getButtons() const
{
    return m_Buttons;
}

void CreationMenu::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->UpperLeftPos = m_Pos;
    cmd->LowerRightPos = cmd->UpperLeftPos + m_Size;
    cmd->Color = m_Color;
    cmd->Layer = alpp::render::Layer::UI;
    i_Renderer->enqueueCommand(cmd);

    for (auto const & button : m_Buttons)
    {
        button->render(i_Renderer);
    }
}
