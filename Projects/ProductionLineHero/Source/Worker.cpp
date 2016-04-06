// alpp
#include <Render/Command.h>

// aplib
#include <aplib/Random.h>

// plh
#include <Worker.h>
#include <Workshop.h>

// std
#include <thread>

Worker::Worker(sptr<Workshop> i_Workshop, double i_Speed) :
    m_Pos          (),
    m_Speed        (i_Speed),
    m_ResourcesHeld(),
    m_Workshop     (i_Workshop)
{
    // Put the worker at a random place inside the workshop
    m_Pos  = RealCoords(i_Workshop->getUpperLeftPixelPos());
    m_Pos += RealCoords(randUNorm(), randUNorm()) * 
        (RealCoords(WORKSHOP_SIZE_PXL) - static_cast<double>(2 * WORKER_RADIUS));
    m_Pos += WORKER_RADIUS;

    std::thread(&Worker::runWorkerThread, this).detach();
}

Worker::~Worker()
{

}

void Worker::runWorkerThread()
{
    // Create route (ordered list of resource stacks to visit to make his task)
    auto route = m_Workshop->getInputStacks();
    route.push_back(m_Workshop->getOutputStack());

    // First destination
    auto currDestination = route.begin();

    // Work for eternity
    while (true)
    {
        // Get position of next destination
        auto pos = currDestination->get()->centerPosition();
        auto destPos = RealCoords(pos.x, pos.y);

        // Compute the position increment at each step
        auto step = (destPos - m_Pos).normalize() * m_Speed;

        // Walk towards destination until it's reached
        while (m_Pos.distanceTo(destPos) > RESRC_STACK_SIZE_PXL.x)
        {
            walk(destPos, step);
        }

        // If we arrived at an input stack
        if (currDestination->get()->type() == ResourceStack::Type::INPUT)
        {
            // Get a resource (or wait for one)
            m_ResourcesHeld.push_back(currDestination->get()->poll());
        }
        else
        {
            currDestination->get()->push(m_ResourcesHeld.back());
            m_ResourcesHeld.pop_back();
        }

        // Set next destination
        ++currDestination;
        if (currDestination == route.end())
        {
            currDestination = route.begin();
        }
    }
}

void Worker::walk(RealCoords i_DestPos, RealCoords i_Step)
{
    // Randomly generate a wiggle pattern that will deviate the path a little bit
    static double t = 0;
    t += PATH_WIGGLE_FREQUENCY;
    auto randWiggle    = cos(t * 0.02 + cos(t * 0.3) * sin(t * 0.5));
    auto distFactpr    = m_Pos.distanceTo(i_DestPos) / WORKSHOP_SIZE_PXL.x;
    auto overallWiggle = distFactpr * PATH_WIGGLE_AMPLITUDE * randWiggle;

    m_Pos += i_Step + RealCoords(i_Step.y, -i_Step.x) * overallWiggle;
    
    std::this_thread::sleep_for(THREAD_SLEEP_TIME);
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