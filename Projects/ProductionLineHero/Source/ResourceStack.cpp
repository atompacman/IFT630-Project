// alpp
#include <Render/Command.h>
#include <Render/Renderer.h>

// plh
#include <ResourceStack.h>
#include <Factory.h>

// std
#include <sstream>

ResourceStack::ResourceStack(Type i_Type) :
    m_Type (i_Type),
    m_Stack()
{

}

void ResourceStack::render(sptr<alpp::render::Renderer> i_Renderer, 
                           uint16_t                     i_WorkshopPosX, 
                           uint16_t                     i_WorkshopPosY, 
                           StackPosition                i_StackPos) const
{
    auto minX = i_WorkshopPosX * WORKSHOP_SIZE_PXL + (i_WorkshopPosX + 1) * WORKSHOP_BORDER_WIDTH;
    auto minY = i_WorkshopPosY * WORKSHOP_SIZE_PXL + (i_WorkshopPosY + 1) * WORKSHOP_BORDER_WIDTH;

    switch (i_StackPos)
    {
    case StackPosition::NORTH: 
        minX += WORKSHOP_SIZE_PXL * 0.5f;
        break;
    case StackPosition::EAST: 
        minX += WORKSHOP_SIZE_PXL;
        minY += WORKSHOP_SIZE_PXL * 0.5f;
        break;

    case StackPosition::SOUTH:
        minX += WORKSHOP_SIZE_PXL * 0.5f;
        minY += WORKSHOP_SIZE_PXL;
        break;

    case StackPosition::WEST: 
        minY += WORKSHOP_SIZE_PXL * 0.5f; 
        break;
    }

    auto const d = RESRC_STACK_SIZE_PXL * 0.5f;

    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->PosLeft   = minX - d;
    cmd->PosRight  = minX + d;
    cmd->PosTop    = minY - d;
    cmd->PosBottom = minY + d;
    cmd->Color     = m_Type == Type::INPUT ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0);
    i_Renderer->enqueueCommand(cmd);

    auto cmd2 = std::make_shared<alpp::render::DrawText>();
    cmd2->PosX  = minX - 2 * d;
    cmd2->PosY  = minY - 2 * d;
    cmd2->Font  = i_Renderer->StandardFont;
    cmd2->Color = al_map_rgb(255, 255, 255);
    std::stringstream ss;
    ss << m_Stack.size();
    cmd2->Text = ss.str();
    i_Renderer->enqueueCommand(cmd2);
}