#include <aplib/Random.h>

#include <plh/Event/Gameloop.h>
#include <plh/ResourceSupplier.h>
#include <plh/Workshop.h>

GameLoop::GameLoop(alpp::render::WindowSettings i_WinSettings) :
    alpp::event::GameLoop(i_WinSettings, TARGET_FPS),
    m_Factory()
{

};

bool GameLoop::tick()
{
    static long currTick = 0;
    static std::list<sptr<Resource>> resources;
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

    if (currTick >= 500 && currTick % 500 == 0)
    {
        auto i = 0;
        WorkshopCoords pos;
        do
        {
            i = 0;

            do
            {
                pos.x = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_X);
                pos.y = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_Y);
            } while (!m_Factory.hasWorkshopAt(pos));

            while (m_Factory.getWorkshop(pos)->hasStack(CardinalDir(i)) && i < 4)
            {
                ++i;
            }
        } while (i == 4);

        auto resource = std::make_shared<BasicResource>(randValue(0, 2));
        registerAgent(m_Factory.addResourceSupplier(pos, resource, 0.1f, CardinalDir(i)));
    }

    ++currTick;

    return true;
}