#include <alpp/Render/Command.h>
#include <alpp/Render/Renderer.h>

#include <plh/ResourceStack.h>

#include <sstream>

ResourceStack::ResourceStack(Type i_Type, WorkshopCoords i_Pos, CardinalDir i_Side) :
    m_Type       (i_Type),
    m_Pos        (),
    m_Resources  (),
    m_LastPushed (),
    m_IsConnected(false),
    m_Mutex      (),
    m_WaitingList()
{
    // Compute center position in pixel
    m_Pos = workshopCoordsToWorldCoordsULCorner(i_Pos);

    m_Pos = cardinalDirToWorldCoords(m_Pos, i_Side);
}

sptr<Resource> ResourceStack::pop()
{
    // Get mutex
    std::unique_lock<std::mutex> lock(m_Mutex);

    // Check if stack is empty
    while (m_Resources.empty())
    {
        // Wait for a push notification
        m_WaitingList.wait(lock);
    }

    // Get the resource
    auto resource = m_Resources.top();
    m_Resources.pop();
    return resource;
}

void ResourceStack::push(sptr<Resource> i_Resource)
{
    // Get mutex
    std::unique_lock<std::mutex> lock(m_Mutex);

    // Save last pushed resource
    m_LastPushed = i_Resource->copy();

    // Push element
    m_Resources.push(i_Resource);

    // Notify a worker in the waiting list
    m_WaitingList.notify_one();
}

void ResourceStack::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto const d = RESRC_STACK_SIZE_PXL / WorldCoords(2, 2);

    auto const * color = m_Type == Type::INPUT ? (
        m_IsConnected ? CONNECTED_INPUT_RESRC_STACK_COLOR  : UNCONNECTED_INPUT_RESRC_STACK_COLOR) : 
        m_IsConnected ? CONNECTED_OUTPUT_RESRC_STACK_COLOR : UNCONNECTED_OUTPUT_RESRC_STACK_COLOR;


    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->UpperLeftPos  = m_Pos - d;
    cmd->LowerRightPos = m_Pos + d;
    cmd->Color         = al_map_rgb(color[0], color[1], color[2]);
    i_Renderer->enqueueCommand(cmd);

    auto cmd2 = std::make_shared<alpp::render::DrawCenteredText>();
    cmd2->CenterPos = WorldCoords(m_Pos.x - d.x * 0.5f, m_Pos.y - d.y);
    cmd2->Font      = i_Renderer->StandardFont;
    cmd2->Color     = al_map_rgb(0, 0, 10);
    std::stringstream ss;
    ss << numResources();
    cmd2->Text = ss.str();
    i_Renderer->enqueueCommand(cmd2);
}