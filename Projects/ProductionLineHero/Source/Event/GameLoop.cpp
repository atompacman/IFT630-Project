#include <plh/Common.h>
#include <plh/Resource.h>
#include <plh/Event/Gameloop.h>

GameLoop::GameLoop(alpp::render::WindowSettings i_WinSettings) :
    alpp::event::GameLoop(i_WinSettings, TARGET_FPS),
    m_Factory()
{
    //for (uint8_t i = 0; i < 3; ++i)
    //{
    //    auto workshop = m_Factory.buildWorkshop(WorkshopCoords(i + 1, 1), CardinalDir::EAST);
    //    workshop->addInputStack(CardinalDir::WEST);
    //    for (uint8_t j = 0; j < 5; ++j)
    //    {
    //        workshop->addWorker(0.7 + j * 0.1);
    //    }
    //}
};

bool GameLoop::tick()
{
    static long currTick = 0;

    // Draw factory
    m_Factory.render(Renderer);

    //// Regularly add resource to input stack
    //if (currTick % 120 == 0)
    //{
    //    for (uint8_t i = 0; i < 3; ++i)
    //    {
    //        auto stack = m_Factory.getWorkshop(WorkshopCoords(i + 1, 1))->getStack(CardinalDir::WEST);
    //        for (uint8_t j = 0; j < 3; ++j)
    //        {
    //            stack->push(Resource());
    //        }
    //    }
    //}

    ++currTick;

    return true;
}