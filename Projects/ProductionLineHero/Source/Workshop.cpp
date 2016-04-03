// alpp
#include <Render/Command.h>
#include <Render/Renderer.h>

// plh
#include <Factory.h>
#include <Workshop.h>

Workshop::Workshop(uint16_t i_X, uint16_t i_Y) :
    m_X(i_X),
    m_Y(i_Y)
{
    
}

void Workshop::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto minX = m_X * SIZE_PXL + (m_X + 1) * Factory::WORKSHOP_BORDER_WIDTH;
    auto minY = m_Y * SIZE_PXL + (m_Y + 1) * Factory::WORKSHOP_BORDER_WIDTH;

    i_Renderer->enqueueCommand(std::make_shared<alpp::render::DrawFilledRectangle>(
        minX, minY, minX + SIZE_PXL, minY + SIZE_PXL, al_map_rgb(10, 40, 53)));
}