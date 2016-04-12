#include <plh/CreationButton.h>

CreationButton::CreationButton(WorldCoords       i_Position, 
                               WorldCoords       i_Size, 
                               UIElement *       i_Parent, 
                               ALLEGRO_COLOR     i_Color, 
                               CreatableRoomType i_ObjType) :
    UIElement(i_Position, i_Size, i_Color),
    m_ParentUI(i_Parent),
    m_RoomType(i_ObjType)
{}

void CreationButton::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->UpperLeftPos = m_Pos;
    cmd->LowerRightPos = cmd->UpperLeftPos + m_Size;
    cmd->Color = m_Color;
    cmd->Layer = alpp::render::Layer::UI;
    i_Renderer->enqueueCommand(cmd);
}