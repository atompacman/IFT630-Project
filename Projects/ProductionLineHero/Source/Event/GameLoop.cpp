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

    if (currTick == 0)
    {
        auto b1 = std::make_shared<BasicResource>(al_map_rgb(100, 100,  40));
        auto b2 = std::make_shared<BasicResource>(al_map_rgb( 80,  10, 230));
        b2->raffine();
        b2->raffine();
        auto b3 = std::make_shared<BasicResource>(al_map_rgb( 89,  40, 140));
        auto b4 = std::make_shared<BasicResource>(al_map_rgb( 45, 200,  30));

        std::list<sptr<Resource>> list;
        list.push_back(b1);
        list.push_back(b2);
        auto c1 = std::make_shared<CompositeResource>(list);

        list.push_back(b3);
        auto c2 = std::make_shared<CompositeResource>(list);
        c2->raffine();
        list.clear();

        list.push_back(b4);
        list.push_back(c1);
        auto c3 = std::make_shared<CompositeResource>(list);
        list.clear();

        list.push_back(c2);
        list.push_back(c3);
        auto c4 = std::make_shared<CompositeResource>(list);

        list.push_back(c4);
        auto c5 = std::make_shared<CompositeResource>(list);

        resources.push_back(b1);
        resources.push_back(c1);
        resources.push_back(c2);
        resources.push_back(c3);
        resources.push_back(c4);
        resources.push_back(c5);
    }

    auto i = 0;
    for (auto resource : resources)
    {
        resource->render(Renderer, WorldCoords(100, 100 + i++ * 40    * 5));
    }

    // Draw factory
    //m_Factory.render(Renderer);

    //if (currTick % 30 == 0 && numWorkshops < MAX_NUM_WORKSHOPS.area())
    //{
    //    WorkshopCoords pos;
    //    do
    //    {
    //        pos.x = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_X);
    //        pos.y = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_Y);
    //    } while (m_Factory.hasWorkshopAt(pos));
    //    
    //    m_Factory.buildWorkshop(pos, CardinalDir(randValue(0, 3)))->addWorker(1.);
    //    ++numWorkshops;
    //}

    //if (currTick >= 500 && currTick % 500 == 0)
    //{
    //    auto i = 0;
    //    WorkshopCoords pos;

    //    do
    //    {
    //        i = 0;

    //        do
    //        {
    //            pos.x = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_X);
    //            pos.y = randValue(static_cast<uint16_t>(0), MAX_NUM_WORKSHOPS_Y);
    //        } while (!m_Factory.hasWorkshopAt(pos));

    //        while (m_Factory.getWorkshop(pos)->hasStack(CardinalDir(i)) && i < 4)
    //        {
    //            ++i;
    //        }
    //    } while (i == 4);

    //    auto resource = std::make_shared<BasicResource>(al_map_rgb(100, 100, 40));
    //    registerAgent(m_Factory.addResourceSupplier(pos, resource, 0.1f, CardinalDir(i)));
    //}



    ++currTick;

    return true;
}