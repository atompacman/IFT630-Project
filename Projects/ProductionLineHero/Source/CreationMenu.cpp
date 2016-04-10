#include <plh/CreationMenu.h>
#include <plh/CreationButton.h>

CreationMenu::CreationMenu() :
    UIElement()
{
}

CreationMenu::CreationMenu(WorldCoords position, WorldCoords size) :
    UIElement(position, size)
{    
}

void CreationMenu::addButton(CreationButton * button)
{
    m_Buttons.push_back(button);
}

void CreationMenu::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->UpperLeftPos = m_Pos;
    cmd->LowerRightPos = cmd->UpperLeftPos + m_Size;
    cmd->Color = al_map_rgb(200, 200, 200);
    cmd->Layer = alpp::render::Layer::UI;
    i_Renderer->enqueueCommand(cmd);

    for (auto const & button : m_Buttons)
    {
        button->render(i_Renderer);
    }
}
