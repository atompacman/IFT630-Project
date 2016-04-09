#include <aplib/Random.h>

#include <plh/Common.h>
#include <plh/Resource.h>
#include <plh/Event/Gameloop.h>

GameLoop::GameLoop(alpp::render::WindowSettings i_WinSettings) :
    alpp::event::GameLoop(i_WinSettings, TARGET_FPS),
    m_Factory()
{

};

bool GameLoop::tick()
{
    static long currTick = 0;
    static std::list<Resource> resources;
    static uint16_t numWorkshops = 0;

    // Draw factory
    m_Factory.render(Renderer);

    if (currTick % 30 == 0 && numWorkshops < MAX_NUM_WORKSHOPS.area())
    {
        WorkshopCoords pos;
        do
        {
            pos.x = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_X);
            pos.y = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_Y);
        } while (m_Factory.hasWorkshopAt(pos));
        
        m_Factory.buildWorkshop(pos, CardinalDir(randValue(0, 3)))->addWorker(1.);
        ++numWorkshops;
    }

    if (currTick % 5 == 0)
    {
        WorkshopCoords pos;
        do
        {
            pos.x = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_X);
            pos.y = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_Y);
        } while (!m_Factory.hasWorkshopAt(pos));

        for (auto stack : m_Factory.getWorkshop(pos)->getInputStacks())
        {
            for (auto i = 0; i < 3; ++i)
            {
                resources.emplace_back();
                stack->push(resources.back());
            }
        }
    }

    ++currTick;

    return true;
}