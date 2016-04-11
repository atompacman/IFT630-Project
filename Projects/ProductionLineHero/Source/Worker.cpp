#include <alpp/Render/Command.h>

#include <aplib/Random.h>

#include <plh/Worker.h>
#include <plh/Workshop.h>

#include <thread>

Worker::Worker(sptr<Workshop> i_Workshop, float i_Speed) :
    m_Pos          (),
    m_Speed        (i_Speed),
    m_ResourcesHeld(),
    m_Workshop     (i_Workshop)
{
    // Put the worker at a random place inside the workshop
    m_Pos  = WorldCoords(i_Workshop->getUpperLeftPixelPos());
    m_Pos += WorldCoords(randUNorm(), randUNorm()) * 
        (WorldCoords(WORKSHOP_SIZE_PXL) - static_cast<float>(2 * WORKER_RADIUS));
    m_Pos += WORKER_RADIUS;

    std::thread(&Worker::runWorkerThread, this).detach();
}

Worker::~Worker()
{

}

void Worker::runWorkerThread()
{
    // Work for eternity
    while (true)
    {
        // Create route (ordered list of resource stacks to visit to make his task)
        // If workshop has no input stack yet, simply wait
        auto route = m_Workshop->getInputStacks();
        while (route.empty())
        {
            route = m_Workshop->getInputStacks();
            std::this_thread::sleep_for(THREAD_SLEEP_TIME);
        }
        route.push_back(m_Workshop->getOutputStack());

        // First destination
        auto currDestination = route.begin();

        while (currDestination != route.end())
        {
            // Get position of next destination
            auto pos = currDestination->get()->centerPosition();
            auto destPos = WorldCoords(pos.x, pos.y);

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
                m_ResourcesHeld.push_back(currDestination->get()->pop());
            }
            else
            {
                // If worker has only one resource in it's hands, raffine it, else merge items
                if (m_ResourcesHeld.size() == 1)
                {
                    auto resource = m_ResourcesHeld.back();
                    resource->raffine();
                    currDestination->get()->push(resource);
                }
                else
                {
                    currDestination->get()->push(std::make_shared<CompositeResource>(m_ResourcesHeld));
                }
                m_ResourcesHeld.clear();
            }

            // Set next destination
            ++currDestination;
        }
    }
}

void Worker::walk(WorldCoords i_DestPos, WorldCoords i_Step)
{
    // Randomly generate a wiggle pattern that will deviate the path a little bit
    static float t = 0;
    t += PATH_WIGGLE_FREQUENCY;
    auto randWiggle    = cos(t * 0.02f + cos(t * 0.3f) * sin(t * 0.5f));
    auto distFactpr    = m_Pos.distanceTo(i_DestPos) / WORKSHOP_SIZE_PXL.x;
    auto overallWiggle = distFactpr * PATH_WIGGLE_AMPLITUDE * randWiggle;

    m_Pos += i_Step + WorldCoords(i_Step.y, -i_Step.x) * overallWiggle;
    
    std::this_thread::sleep_for(THREAD_SLEEP_TIME);
}

void Worker::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledCircle>();
    cmd->CenterPos = m_Pos;
    cmd->Radius    = WORKER_RADIUS;
    cmd->Color     = al_map_rgb(200, 200, 30);
    i_Renderer->enqueueCommand(cmd);
}