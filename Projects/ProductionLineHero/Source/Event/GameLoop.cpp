#include <aplib/Random.h>

#include <plh/Event/Gameloop.h>
#include <plh/ResourceSupplier.h>
#include <plh/Workshop.h>

#include <plh/CreationButton.h>
#include <plh/CreationMenu.h>

GameLoop::GameLoop(alpp::render::WindowSettings i_WinSettings) :
    alpp::event::GameLoop(i_WinSettings, TARGET_FPS),
    m_Factory()
{
    // Create game UI
    InitUI(i_WinSettings);

};

void GameLoop::InitUI(alpp::render::WindowSettings i_WinSettings)
{
    WorldCoords creationMenuSize(i_WinSettings.dimensions.x, 180);
    WorldCoords creationMenuPos(0, i_WinSettings.dimensions.y - creationMenuSize.y);
    CreationMenu * creationMenu = new CreationMenu(creationMenuPos, creationMenuSize);

    CreationButton * workshopButton = new CreationButton(WorldCoords(creationMenuPos.x + 10,
        creationMenuPos.y + 10), WorldCoords(160, 160), creationMenu, al_map_rgb(0, 255, 0));

    CreationButton * supplierButton = new CreationButton(
        WorldCoords(workshopButton->getPosition().x + workshopButton->getSize().x + 10,
        creationMenuPos.y + 10), WorldCoords(160, 160), creationMenu, al_map_rgb(255, 255, 0));

    creationMenu->addButton(workshopButton);
    creationMenu->addButton(supplierButton);

    m_UI.push_back(creationMenu);
}

void GameLoop::RenderUI()
{
    for (auto const & element : m_UI)
    {
        element->render(Renderer);
    }
}

bool GameLoop::tick()
{
    static long currTick = 0;
    static std::list<Resource> resources;
    static uint16_t numWorkshops = 0;

    // Draw UI
    RenderUI();

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

        registerAgent(m_Factory.addResourceSupplier(pos, Resource(), 0.1f, CardinalDir(i)));
    }

    ++currTick;

    return true;
}