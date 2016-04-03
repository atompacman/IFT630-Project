// alpp
#include <Render/Command.h>
#include <Render/Renderer.h>

//el
#include <easylogging++.h>

// plh
#include <Factory.h>
#include <Workshop.h>

Workshop::Workshop(uint16_t i_X, uint16_t i_Y) :
    m_ResourceStacks(),
    m_X             (i_X),
    m_Y             (i_Y)
{

}

void Workshop::addResourceStack(StackPosition i_Position, ResourceStack::Type i_Type)
{
    auto stackNum = static_cast<uint32_t>(i_Position);

    LOG_IF(m_ResourceStacks[stackNum] != nullptr, FATAL) 
        << "Cannot add a resource stack to workshop (" << m_X << ", " << m_Y 
        << ") at position " << stackNum << ": there is already a stack there";

    auto stack = std::make_shared<ResourceStack>(i_Type);
    m_ResourceStacks[stackNum] = stack;
}

void Workshop::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto minX = m_X * WORKSHOP_SIZE_PXL + (m_X + 1) * WORKSHOP_BORDER_WIDTH;
    auto minY = m_Y * WORKSHOP_SIZE_PXL + (m_Y + 1) * WORKSHOP_BORDER_WIDTH;

    i_Renderer->enqueueCommand(std::make_shared<alpp::render::DrawFilledRectangle>(
        minX, minY, minX + WORKSHOP_SIZE_PXL, minY + WORKSHOP_SIZE_PXL, al_map_rgb(10, 40, 53)));

    for (uint8_t i = 0; i < 4; ++i)
    {
        if (m_ResourceStacks[i])
        {
            m_ResourceStacks[i]->render(i_Renderer, m_X, m_Y, StackPosition(i));
        }
    }
}