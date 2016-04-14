#include <allegro5/display.h>

#include <alpp/Render/Command.h>
#include <alpp/Render/Renderer.h>

#include <plh/Treadmill.h>

#include <thread>

Treadmill::Treadmill(sptr<ResourceStack> i_Source, 
                     sptr<ResourceStack> i_Destination) :
    m_SrcStack      (i_Source),
    m_DestStack     (i_Destination),
    m_MovingResource(),
    m_ResourcePos   ()
{
    LOG_IF(m_SrcStack->type() == ResourceStack::Type::INPUT, FATAL) 
        << "A threadmill source stack cannot be a stack of type input";
    LOG_IF(m_DestStack->type() == ResourceStack::Type::OUTPUT, FATAL)
        << "A threadmill destination stack cannot be a stack of type output";

    i_Source->setConnected();
    i_Destination->setConnected();

    std::thread(&Treadmill::runThreadmillThread, this).detach();
}

Treadmill::~Treadmill()
{

}

void Treadmill::runThreadmillThread()
{
    while (true)
    {
        // Get a resource from the input stack
        m_MovingResource = m_SrcStack->pop();

        // Set initial resource position
        m_ResourcePos = m_SrcStack->centerPosition();

        // Compute distance increment
        auto destPos = WorldCoords(m_DestStack->centerPosition());
        auto step = (destPos - m_ResourcePos) / 60.f;

        // Move object towards destination until it's reached
        while (m_ResourcePos.distanceTo(destPos) > 1e-2)
        {
            std::this_thread::sleep_for(THREAD_SLEEP_TIME);
            m_ResourcePos += step;
        }

        // Push resource to destination stack
        m_DestStack->push(m_MovingResource);

        // Reset resource position to tell the render method to not render the resource
        m_ResourcePos = WorldCoords();
    }
}

void Treadmill::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    // Draw treadmill
    auto cmd = std::make_shared<alpp::render::DrawLine>();
    cmd->BegPos    = m_SrcStack->centerPosition();
    cmd->EndPos    = m_DestStack->centerPosition();
    cmd->Thickness = 15;
    cmd->Color     = al_map_rgb(120, 70, 10);
    i_Renderer->enqueueCommand(cmd);

    // Skip drawing if there is not resource on the threadmill
    if (m_ResourcePos == WorldCoords(0, 0))
    {
        return;
    }

    // Draw moving resource
    auto cmd2 = std::make_shared<alpp::render::DrawFilledCircle>();
    cmd2->CenterPos = m_ResourcePos;
    cmd2->Radius = 5;
    cmd2->Color = al_map_rgb(120, 235, 250);
    i_Renderer->enqueueCommand(cmd2);
}