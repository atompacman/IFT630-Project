#include <alpp/Render/Command.h>

#include <easylogging++.h>

#include <plh/Threadmill.h>

#include <thread>

Threadmill::Threadmill(sptr<ResourceStack> i_Source, 
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
    std::thread(&Threadmill::runThreadmillThread, this).detach();
}

Threadmill::~Threadmill()
{

}

void Threadmill::runThreadmillThread()
{
    while (true)
    {
        // Get a resource from the input stack
        m_MovingResource = m_SrcStack->poll();

        // Set initial resource position
        m_ResourcePos = m_SrcStack->centerPosition();

        // Compute distance increment
        auto destPos = RealCoords(m_DestStack->centerPosition());
        auto step = (destPos - m_ResourcePos) / 60.;

        // Move object towards destination until it's reached
        while (m_ResourcePos.distanceTo(destPos) > 1e-2)
        {
            std::this_thread::sleep_for(THREAD_SLEEP_TIME);
            m_ResourcePos += step;
        }

        // Push resource to destination stack
        m_DestStack->push(m_MovingResource);
    }
}

void Threadmill::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledCircle>();
    cmd->CenterPosX = m_ResourcePos.x;
    cmd->CenterPosY = m_ResourcePos.y;
    cmd->Radius     = 5;
    cmd->Color      = al_map_rgb(150, 40, 140);
    i_Renderer->enqueueCommand(cmd);
}