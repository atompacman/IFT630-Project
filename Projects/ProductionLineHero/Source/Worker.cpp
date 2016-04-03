// alpp
#include <Render/Command.h>

// plh
#include <Worker.h>

// std
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

Worker::Worker(uint16_t i_PosX, uint16_t i_PosY, float i_Speed) :
    m_PosX (i_PosX),
    m_PosY (i_PosY),
    m_Speed(i_Speed)
{
    std::thread(&Worker::runWorkerThread, this).detach();
}

Worker::~Worker()
{

}

void Worker::runWorkerThread()
{
    while (true)
    {
        // #TODO: replace hardcoded values for position by the workshop's bounding box
        if ((m_Speed > 0) && (m_PosX >= 800) || (m_Speed < 0) && (m_PosX <= 400))
        {
            m_Speed *= -1.0;
        }
        work();
    }

}

void Worker::work()
{
    m_PosX += static_cast<int>(m_Speed);
    std::this_thread::sleep_for(10ms);
}

void Worker::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledCircle>();
    cmd->CenterPosX = m_PosX;
    cmd->CenterPosY = m_PosY;
    cmd->Radius     = RADIUS;
    cmd->Color      = al_map_rgb(200, 200, 30);
    i_Renderer->enqueueCommand(cmd);
}