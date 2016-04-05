// alpp
#include <Render/Command.h>
#include <Render/Renderer.h>

// el
#include <easylogging++.h>

// plh
#include <ResourceStack.h>

// std
#include <sstream>

ResourceStack::ResourceStack(Type           i_Type, 
                             WorkshopCoords i_Pos, 
                             CardinalDir    i_Side, 
                             Resource       i_ResourceArchetype) :
    m_Type             (i_Type),
    m_Pos              (),
    m_ResourceArchetype(i_ResourceArchetype),
    m_StackSize        (0),
    m_Mutex            (),
    m_WaitingList      ()
{
    // Compute center position in pixel
    m_Pos = i_Pos * WORKSHOP_SIZE_PXL + (i_Pos + PixelCoords(1, 1)) * SPACE_BETWEEN_WORKSHOPS;

    switch (i_Side)
    {
    case CardinalDir::NORTH:
        m_Pos.x += WORKSHOP_SIZE_PXL.x * 0.5f;
        break;
    case CardinalDir::EAST:
        m_Pos.x += WORKSHOP_SIZE_PXL.x;
        m_Pos.y += WORKSHOP_SIZE_PXL.y * 0.5f;
        break;

    case CardinalDir::SOUTH:
        m_Pos.x += WORKSHOP_SIZE_PXL.x * 0.5f;
        m_Pos.y += WORKSHOP_SIZE_PXL.y;
        break;

    case CardinalDir::WEST:
        m_Pos.y += WORKSHOP_SIZE_PXL.y * 0.5f;
        break;
    }
}

Resource ResourceStack::poll()
{
    // Get mutex
    std::unique_lock<std::mutex> lock(m_Mutex);

    // Check if stack is empty
    while (m_StackSize == 0)
    {
        // Wait for a push notification
        m_WaitingList.wait(lock);
    }

    // Get the resource
    --m_StackSize;
    return Resource(m_ResourceArchetype);
}

void ResourceStack::push()
{
    ++m_StackSize;
    // Notify a worker in the waiting list
    m_WaitingList.notify_one();
}

void ResourceStack::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto const d = RESRC_STACK_SIZE_PXL / PixelCoords(2, 2);

    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->PosLeft   = m_Pos.x - d.x;
    cmd->PosRight  = m_Pos.x + d.x;
    cmd->PosTop    = m_Pos.y - d.y;
    cmd->PosBottom = m_Pos.y + d.y;
    cmd->Color     = m_Type == Type::INPUT ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0);
    i_Renderer->enqueueCommand(cmd);

    auto cmd2 = std::make_shared<alpp::render::DrawCenteredText>();
    cmd2->PosX  = m_Pos.x - 2 * d.x;
    cmd2->PosY  = m_Pos.y - 2 * d.y;
    cmd2->Font  = i_Renderer->StandardFont;
    cmd2->Color = al_map_rgb(255, 255, 255);
    std::stringstream ss;
    ss << m_StackSize;
    cmd2->Text = ss.str();
    i_Renderer->enqueueCommand(cmd2);
}