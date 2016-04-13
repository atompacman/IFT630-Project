#include <aplib/Random.h>

#include <plh/Event/Gameloop.h>
#include <plh/ResourceSupplier.h>
#include <plh/Workshop.h>
#include <alpp/Render/Command.h>

#include <plh/CreationButton.h>
#include <plh/CreationMenu.h>


GameLoop::GameLoop(alpp::render::WindowSettings i_WinSettings) :
    alpp::event::GameLoop(i_WinSettings, TARGET_FPS),
    m_Factory(),
    m_ObjectToCreate(CreatableObjectType::NONE),
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
    WorldCoords creationMenuSize(i_WindowSize.x / 3, i_WindowSize.y / 8);
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
    CreationMenu * creationMenu = new CreationMenu(creationMenuPos, creationMenuSize, al_map_rgb(200,200,200));

    float buttonSide = creationMenuSize.y - 20;
    WorldCoords buttonSize = WorldCoords(buttonSide, buttonSide);

    CreationButton * workshopButton = new CreationButton(WorldCoords(creationMenuPos.x + 10,
        creationMenuPos.y + 10), buttonSize, creationMenu, getButtonColor(0), CreatableObjectType::WORKSHOP);

    CreationButton * supplierButton = new CreationButton(
        WorldCoords(workshopButton->getPosition().x + workshopButton->getSize().x + 10,
        creationMenuPos.y + 10), buttonSize, creationMenu, getButtonColor(1), CreatableObjectType::SUPPLIER);

    CreationButton * workerButton = new CreationButton(
        WorldCoords(supplierButton->getPosition().x + supplierButton->getSize().x + 10,
            creationMenuPos.y + 10), buttonSize, creationMenu, getButtonColor(2), CreatableObjectType::WORKER);

    creationMenu->addButton(workshopButton);
    creationMenu->addButton(supplierButton);
    creationMenu->addButton(workerButton);

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

void GameLoop::CreateFactoryObject(CreatableObjectType i_RoomType, WorkshopCoords i_RoomPos)
{
    switch (i_RoomType)
    {
    case CreatableObjectType::WORKSHOP:
        // we should change the output to be chosen instead of random
        m_Factory.buildWorkshop(i_RoomPos, CardinalDir(randValue(0, 3)))->addWorker(1.);
        setState(GameState::IDLE_MODE);
        setObjectTypeToCreate(CreatableObjectType::NONE);
        break;

    case CreatableObjectType::SUPPLIER:
        if (m_Factory.hasWorkshopAt(i_RoomPos))
        {
            registerAgent(m_Factory.addResourceSupplier(i_RoomPos,
                        std::make_shared<BasicResource>(0), 3, CardinalDir(randValue(0, 3))));
        }

        setState(GameState::IDLE_MODE);
        setObjectTypeToCreate(CreatableObjectType::NONE);
        break;

    case CreatableObjectType::WORKER:
        if (m_Factory.hasWorkshopAt(i_RoomPos))
        {
            m_Factory.getWorkshop(i_RoomPos)->addWorker(1.);
        }
        setState(GameState::IDLE_MODE);
        setObjectTypeToCreate(CreatableObjectType::NONE);

    default:
        break;
    }
}

void GameLoop::previewCreation()
{
    WorkshopCoords posWS = worldCoordsULCornerToWorkshopCoords(m_MouseHoverWorldPos);
    if (posWS.x > MAX_NUM_WORKSHOPS.x || posWS.y > MAX_NUM_WORKSHOPS.y)
        return;
    WorldCoords upperLeftWS = workshopCoordsToWorldCoordsULCorner(posWS);
    upperLeftWS = pixelCoordsToWorldCoords(upperLeftWS, Renderer);

    switch (m_ObjectToCreate)
    {
    case CreatableObjectType::WORKSHOP:
        if (m_Factory.isCoordInFactory(upperLeftWS) && !m_Factory.hasWorkshopAt(posWS))
        {
            auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
            cmd->UpperLeftPos = upperLeftWS;
            cmd->LowerRightPos = cmd->UpperLeftPos + WorldCoords(WORKSHOP_SIZE);
            cmd->Color = al_map_rgb(65, 143, 63);
            cmd->Layer = alpp::render::Layer::UI;   // HACK
            Renderer->enqueueCommand(cmd);
        }
        break;

    case CreatableObjectType::SUPPLIER:
        break;

    case CreatableObjectType::WORKER:
        break;

    default:
        break;
    }
    
}

bool GameLoop::tick()
{
    if (m_State == GameState::CREATION_MODE)
        previewCreation();

    // Draw factory
    m_Factory.render(Renderer);

    

    // Resize the UI in case the window size changed
    ResizeUI(Renderer->windowSize());

    // Draw UI
    RenderUI();

    return true;
}