// alpp
#include <Render/Command.h>

// el
#include <easylogging++.h>

// plh
#include <Threadmill.h>

// std
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