#include "Worker.h"

// std
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

Worker::Worker()
{
    Worker(0, 0, 1);
}

Worker::Worker(uint16_t posX, uint16_t posY, float speed) :
    m_PosX(posX),
    m_PosY(posY),
    m_Speed(speed)
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
    
    m_PosX += (int) (1.0f * m_Speed);
    //m_PosX += (int)(1.0f * m_Speed);
    std::this_thread::sleep_for(10ms);
}

void Worker::render(sptr<alpp::render::Renderer> i_Renderer)
{
    i_Renderer->enqueueCommand(std::make_shared<alpp::render::DrawFilledCircle>(
        m_PosX, m_PosY, RADIUS, al_map_rgb(200, 200, 30)));
}
