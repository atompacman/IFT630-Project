#include <plh/CreationButton.h>

CreationButton::CreationButton(WorldCoords       i_Position, 
                               WorldCoords       i_Size, 
                               UIElement *       i_Parent, 
                               ALLEGRO_COLOR     i_Color, 
                               CreatableObjectType i_ObjType) :
    UIElement(i_Position, i_Size, i_Color),
    m_ParentUI(i_Parent),
    m_ObjectType(i_ObjType)
{}

void CreationButton::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    {
        auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
        cmd->UpperLeftPos = m_Pos;
        cmd->LowerRightPos = cmd->UpperLeftPos + m_Size;
        cmd->Color = m_Color;
        cmd->Layer = alpp::render::Layer::UI;
        i_Renderer->enqueueCommand(cmd);
    }{
        // Object name
        auto cmd = std::make_shared<alpp::render::DrawCenteredText>();
        cmd->CenterPos = m_Pos;
        cmd->Font = i_Renderer->StandardFont;
        cmd->Color = al_map_rgb(0, 0, 0);
        cmd->Text = m_ObjectType == CreatableObjectType::SUPPLIER ? "Supplier" 
            : m_ObjectType == CreatableObjectType::WORKER ? "Worker" : "Workshop";
        cmd->Layer = alpp::render::Layer::UI;
        i_Renderer->enqueueCommand(cmd);
    }
    {
        // Object Cost
        std::stringstream ss;
        ss << "(" << CREATABLE_OBJ_PRICES.find(m_ObjectType)->second << "$)";

        auto cmd = std::make_shared<alpp::render::DrawCenteredText>();
        cmd->CenterPos = m_Pos + WorldCoords(10, 50);
        cmd->Font      = i_Renderer->StandardFont;
        cmd->Color     = al_map_rgb(0, 0, 0);
        cmd->Text      = ss.str();
        cmd->Layer     = alpp::render::Layer::UI;
        i_Renderer->enqueueCommand(cmd);
    }
}