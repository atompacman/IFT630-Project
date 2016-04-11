#include <aplib/Random.h>

#include <plh/Event/Gameloop.h>
#include <plh/ResourceSupplier.h>
#include <plh/Workshop.h>

#include <plh/CreationButton.h>
#include <plh/CreationMenu.h>

GameLoop::GameLoop(alpp::render::WindowSettings i_WinSettings) :
    alpp::event::GameLoop(i_WinSettings, TARGET_FPS),
    m_Factory(),
    m_RoomToCreate(CreatableRoomType::NONE),
    m_State(GameState::IDLE_MODE)
{
    // Create game UI
    InitUI(i_WinSettings);

    // Test workshop TODO: remove me
    m_Factory.buildWorkshop(WorkshopCoords(1, 3), CardinalDir::EAST )->addWorker(1);
    m_Factory.buildWorkshop(WorkshopCoords(2, 3), CardinalDir::EAST )->addWorker(1);
    m_Factory.buildWorkshop(WorkshopCoords(2, 2), CardinalDir::SOUTH)->addWorker(1);
    m_Factory.buildWorkshop(WorkshopCoords(3, 3), CardinalDir::EAST )->addWorker(1);
    m_Factory.buildWorkshop(WorkshopCoords(4, 3), CardinalDir::EAST )->addWorker(1);
    m_Factory.buildWorkshop(WorkshopCoords(4, 4), CardinalDir::NORTH)->addWorker(1);
    m_Factory.buildWorkshop(WorkshopCoords(4, 5), CardinalDir::NORTH)->addWorker(1);
    m_Factory.buildWorkshop(WorkshopCoords(3, 5), CardinalDir::EAST )->addWorker(1);
    registerAgent(m_Factory.addResourceSupplier(WorkshopCoords(1, 3), 
        std::make_shared<BasicResource>(0), 3, CardinalDir::WEST));
    registerAgent(m_Factory.addResourceSupplier(WorkshopCoords(2, 2),
        std::make_shared<BasicResource>(0), 3, CardinalDir::NORTH));
    registerAgent(m_Factory.addResourceSupplier(WorkshopCoords(3, 5),
        std::make_shared<BasicResource>(0), 3, CardinalDir::WEST));
    registerAgent(m_Factory.addResourceSupplier(WorkshopCoords(4, 3),
        std::make_shared<BasicResource>(0), 3, CardinalDir::NORTH));
};

void GameLoop::ResizeUI(PixelDimensions i_WindowSize)
{
    WorldCoords creationMenuSize(i_WindowSize.x / 4, i_WindowSize.y / 8);
    WorldCoords creationMenuPos(0, i_WindowSize.y - creationMenuSize.y);

    float buttonSide = creationMenuSize.y - 20;
    WorldCoords newSize = WorldCoords(buttonSide, buttonSide);

    CreationMenu * createMenu = dynamic_cast<CreationMenu*>(m_UI[0]);
    createMenu->setPositionAndSize(creationMenuPos, creationMenuSize);

    WorldCoords firstButtonPos = WorldCoords(creationMenuPos.x + 10, creationMenuPos.y + 10);

    for (int i = 0; i < createMenu->getButtons().size(); ++i)
    {
        WorldCoords newPos = WorldCoords(firstButtonPos.x + i * (newSize.x + 10), firstButtonPos.y);
        createMenu->getButtons().at(i)->setPositionAndSize(newPos, newSize);
    }
}

void GameLoop::InitUI(alpp::render::WindowSettings i_WinSettings)
{
    WorldCoords creationMenuSize(i_WinSettings.dimensions.x, 100);
    WorldCoords creationMenuPos(0, i_WinSettings.dimensions.y - creationMenuSize.y);
    CreationMenu * creationMenu = new CreationMenu(creationMenuPos, creationMenuSize);

    float buttonSide = creationMenuSize.y - 20;
    WorldCoords buttonSize = WorldCoords(buttonSide, buttonSide);

    CreationButton * workshopButton = new CreationButton(WorldCoords(creationMenuPos.x + 10,
        creationMenuPos.y + 10), buttonSize, creationMenu, al_map_rgb(0, 255, 0), CreatableRoomType::WORKSHOP);

    CreationButton * supplierButton = new CreationButton(
        WorldCoords(workshopButton->getPosition().x + workshopButton->getSize().x + 10,
        creationMenuPos.y + 10), buttonSize, creationMenu, al_map_rgb(255, 255, 0), CreatableRoomType::SUPPLIER);

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

std::vector<UIElement*> GameLoop::getUI() const
{
    return m_UI;
}

void GameLoop::CreateFactoryRoom(CreatableRoomType i_RoomType, WorkshopCoords i_RoomPos)
{
    switch (i_RoomType)
    {
    case CreatableRoomType::WORKSHOP:
        // we should change the output to be chosen instead of random
        m_Factory.buildWorkshop(i_RoomPos, CardinalDir(randValue(0, 3)))->addWorker(1.);
        setState(GameState::IDLE_MODE);
        setRoomTypeToCreate(CreatableRoomType::NONE);
        break;

    case CreatableRoomType::SUPPLIER:
        // #TODO
        break;

    default:
        break;
    }
}

bool GameLoop::tick()
{
    // Draw factory
    m_Factory.render(Renderer);

    // Resize the UI in case the window size changed
    ResizeUI(Renderer->windowSize());

    // Draw UI
    RenderUI();

    return true;
}