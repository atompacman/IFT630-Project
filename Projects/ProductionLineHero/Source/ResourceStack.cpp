// alpp
#include <Render/Command.h>
#include <Render/Renderer.h>

// plh
#include <ResourceStack.h>

// std
#include <sstream>

ResourceStack::ResourceStack(Type i_Type, WorkshopCoords i_Pos, CardinalDir i_Side) :
    m_Pos  (i_Pos),
    m_Side (i_Side),
    m_Type (i_Type),
    m_Stack()
{

}

void ResourceStack::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto center = pixelCenterPosition();

    auto const d = RESRC_STACK_SIZE_PXL / PixelCoords(2, 2);

    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->PosLeft   = center.x - d.x;
    cmd->PosRight  = center.x + d.x;
    cmd->PosTop    = center.y - d.y;
    cmd->PosBottom = center.y + d.y;
    cmd->Color     = m_Type == Type::INPUT ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0);
    i_Renderer->enqueueCommand(cmd);

    auto cmd2 = std::make_shared<alpp::render::DrawText>();
    cmd2->PosX  = center.x - 2 * d.x;
    cmd2->PosY  = center.y - 2 * d.y;
    cmd2->Font  = i_Renderer->StandardFont;
    cmd2->Color = al_map_rgb(255, 255, 255);
    std::stringstream ss;
    ss << m_Stack.size();
    cmd2->Text = ss.str();
    i_Renderer->enqueueCommand(cmd2);
}

ResourceStack::Type ResourceStack::type() const
{
    return m_Type;
}

PixelCoords ResourceStack::pixelCenterPosition() const
{
    auto pos = m_Pos * WORKSHOP_SIZE_PXL + (m_Pos + PixelCoords(1, 1)) * SPACE_BETWEEN_WORKSHOPS;

    switch (m_Side)
    {
    case CardinalDir::NORTH:
        pos.x += WORKSHOP_SIZE_PXL.x * 0.5f;
        break;
    case CardinalDir::EAST:
        pos.x += WORKSHOP_SIZE_PXL.x;
        pos.y += WORKSHOP_SIZE_PXL.y * 0.5f;
        break;

    case CardinalDir::SOUTH:
        pos.x += WORKSHOP_SIZE_PXL.x * 0.5f;
        pos.y += WORKSHOP_SIZE_PXL.y;
        break;

    case CardinalDir::WEST:
        pos.y += WORKSHOP_SIZE_PXL.y * 0.5f;
        break;
    }

    return pos;
}