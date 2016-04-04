// alpp
#include <Render/Command.h>

// plh
#include <Worker.h>
#include <Workshop.h>

// std
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

Worker::Worker(sptr<Workshop> i_Workshop, double i_Speed) :
    m_Pos        (),
    m_Speed      (i_Speed),
    m_Workshop   (i_Workshop)
{
    // Put the worker at a random place inside the workshop
    auto ulCorner = i_Workshop->getUpperLeftPixelPos();
    m_Pos.x = ulCorner.x + rand() % (WORKSHOP_SIZE_PXL.x - WORKER_RADIUS) + WORKER_RADIUS;
    m_Pos.y = ulCorner.y + rand() % (WORKSHOP_SIZE_PXL.y - WORKER_RADIUS) + WORKER_RADIUS;
     
    std::thread(&Worker::runWorkerThread, this).detach();
}

Worker::~Worker()
{

}

void Worker::runWorkerThread()
{
    auto dest = m_Workshop->getInputStacks().begin()->get()->pixelCenterPosition();
    auto destination = RealCoords(dest.x, dest.y);
    auto increment = (destination - m_Pos).normalize() * m_Speed;

    while (true)
    {
        if (m_Pos.distanceTo(destination) > 1)
        {
            m_Pos += increment;
            std::this_thread::sleep_for(10ms);
        }
    }
}

void Worker::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledCircle>();
    cmd->CenterPosX = m_Pos.x;
    cmd->CenterPosY = m_Pos.y;
    cmd->Radius     = WORKER_RADIUS;
    cmd->Color      = al_map_rgb(200, 200, 30);
    i_Renderer->enqueueCommand(cmd);
}