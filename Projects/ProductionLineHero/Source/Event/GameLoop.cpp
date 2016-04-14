#include <aplib/Random.h>

#include <plh/Event/Gameloop.h>
#include <plh/ResourceSupplier.h>
#include <plh/ResourceStack.h>
#include <plh/Workshop.h>
#include <alpp/Render/Command.h>

#include <plh/CreationButton.h>
#include <plh/CreationMenu.h>


GameLoop::GameLoop(alpp::render::WindowSettings i_WinSettings) :
    alpp::event::GameLoop(i_WinSettings, TARGET_FPS),
    m_Factory(),
    m_ObjectToCreate(CreatableObjectType::NONE),
    m_State(GameState::IDLE_MODE),
    m_MouseHoverPixelPos(i_WinSettings.dimensions.x + 1, i_WinSettings.dimensions.y + 1),
    m_CreationDir(CardinalDir::NORTH)
{
    // Create game UI
    InitUI(i_WinSettings);

    //Test workshop TODO: remove me
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
    // Re-compute the position and size of the menu and buttons using the current window size
    WorldCoords creationMenuSize(i_WindowSize.x / 4.2, i_WindowSize.y / 8);
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

    // Create the Creation Menu
    CreationMenu * creationMenu = new CreationMenu(creationMenuPos, creationMenuSize, al_map_rgb(200,200,200));

    float buttonSide = creationMenuSize.y - 20;
    WorldCoords buttonSize = WorldCoords(buttonSide, buttonSide);

    // Create the Workshop creation button
    CreationButton * workshopButton = new CreationButton(WorldCoords(creationMenuPos.x + 10,
        creationMenuPos.y + 10), buttonSize, creationMenu, getButtonColor(0), CreatableObjectType::WORKSHOP);

    // Create the Supplier creation button
    CreationButton * supplierButton = new CreationButton(
        WorldCoords(workshopButton->getPosition().x + workshopButton->getSize().x + 10,
        creationMenuPos.y + 10), buttonSize, creationMenu, getButtonColor(1), CreatableObjectType::SUPPLIER);

    // Create the Worker creation button
    CreationButton * workerButton = new CreationButton(
        WorldCoords(supplierButton->getPosition().x + supplierButton->getSize().x + 10,
            creationMenuPos.y + 10), buttonSize, creationMenu, getButtonColor(2), CreatableObjectType::WORKER);

    // Add the buttons to the menu
    creationMenu->addButton(workshopButton);
    creationMenu->addButton(supplierButton);
    creationMenu->addButton(workerButton);

    m_UI.push_back(creationMenu);
}

void GameLoop::RenderUI()
{
    // Render each UI element
    for (auto const & element : m_UI)
    {
        element->render(Renderer);
    }
}

std::vector<UIElement*> GameLoop::getUI() const
{
    return m_UI;
}

void GameLoop::CreateFactoryObject(CreatableObjectType i_ObjectType, WorkshopCoords i_ObjectPos)
{
    switch (i_ObjectType)
    {
        // Create workshop on a factory tile
    case CreatableObjectType::WORKSHOP:
        if (!m_Factory.hasWorkshopAt(i_ObjectPos))
        {
            m_Factory.buildWorkshop(i_ObjectPos, m_CreationDir)->addWorker(1.);
        }
        
        break;

        // Create Resource Supplier on the side of a workshop
    case CreatableObjectType::SUPPLIER:
        if (m_Factory.hasWorkshopAt(i_ObjectPos) && !m_Factory.getWorkshop(i_ObjectPos)->hasStack(m_CreationDir))
        {
            registerAgent(m_Factory.addResourceSupplier(i_ObjectPos,
                        std::make_shared<BasicResource>(0), 3, m_CreationDir));
        }

        break;

        // Create Worker in a workshop
    case CreatableObjectType::WORKER:
        if (m_Factory.hasWorkshopAt(i_ObjectPos))
        {
            m_Factory.getWorkshop(i_ObjectPos)->addWorker(1.);
        }

    default:
        break;
    }

    // Reset the game state since the creation has been done (or not if placement was invalid)
    setState(GameState::IDLE_MODE);
    setObjectTypeToCreate(CreatableObjectType::NONE);
}

void GameLoop::previewCreation()
{
    // Check if we're not in the UI
    if (m_UI[0]->isMouseInArea(m_MouseHoverPixelPos))
        return;

    // Check if we're in a valid workshop position
    WorldCoords worldPos = pixelCoordsToWorldCoords(m_MouseHoverPixelPos, Renderer);
    WorkshopCoords posWS = worldCoordsULCornerToWorkshopCoords(worldPos);
    if (posWS.x > MAX_NUM_WORKSHOPS.x || posWS.y > MAX_NUM_WORKSHOPS.y 
        || posWS.x < 0 || posWS.y < 0)
        return;

    // Represents the upper left corner of the workshop in world coordinates
    WorldCoords upperLeftWS = workshopCoordsToWorldCoordsULCorner(posWS);
    
    switch (m_ObjectToCreate)
    {
        // Workshop preview
    case CreatableObjectType::WORKSHOP:
        if (m_Factory.isCoordInFactory(upperLeftWS + WorldCoords(1,1)) && !m_Factory.hasWorkshopAt(posWS))
        {
            // Render workshop tile
            auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
            cmd->UpperLeftPos = upperLeftWS;
            cmd->LowerRightPos = cmd->UpperLeftPos + WorldCoords(WORKSHOP_SIZE);
            cmd->Color = al_map_rgb(65, 143, 63);
            cmd->Layer = alpp::render::Layer::WORLD;
            Renderer->enqueueCommand(cmd);

            // Render workshop output stack
            auto const d = RESRC_STACK_SIZE_PXL / WorldCoords(2, 2);

            WorldCoords realPos = cardinalDirToWorldCoords(upperLeftWS, m_CreationDir);
            auto cmd2 = std::make_shared<alpp::render::DrawFilledRectangle>();
            cmd2->UpperLeftPos = realPos - d;
            cmd2->LowerRightPos = realPos + d;
            cmd2->Color = al_map_rgb(110, 0, 0);
            Renderer->enqueueCommand(cmd2);
        }
        break;

        // Supplier preview
    case CreatableObjectType::SUPPLIER:
        if (m_Factory.hasWorkshopAt(posWS) && 
            !m_Factory.getWorkshop(posWS)->hasStack(m_CreationDir))
        {
            // Render supplier stack
            auto const d = RESRC_STACK_SIZE_PXL / WorldCoords(2, 2);

            WorldCoords realPos = cardinalDirToWorldCoords(upperLeftWS, m_CreationDir);
            auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
            cmd->UpperLeftPos = realPos - d;
            cmd->LowerRightPos = realPos + d;
            cmd->Color = al_map_rgb(160, 194, 128);
            Renderer->enqueueCommand(cmd);
        }

        break;

        // Worker preview
    case CreatableObjectType::WORKER:
        if (m_Factory.hasWorkshopAt(posWS))
        {
            // Render worker
            auto cmd = std::make_shared<alpp::render::DrawFilledCircle>();
            cmd->Radius = WORKER_RADIUS;
            cmd->CenterPos = upperLeftWS + WorldCoords(WORKSHOP_SIZE.x/2, WORKSHOP_SIZE.y/2);
            cmd->Color = al_map_rgb(65, 143, 63);
            cmd->Layer = alpp::render::Layer::WORLD;
            Renderer->enqueueCommand(cmd);
        }
        break;

    default:
        break;
    }
    
}

bool GameLoop::tick()
{
    // Draw factory
    m_Factory.render(Renderer);


    // Draw creation preview
    if (m_State == GameState::CREATION_MODE)
        previewCreation();
    

    // Resize the UI in case the window size changed
    ResizeUI(Renderer->windowSize());

    // Draw UI
    RenderUI();

    return true;
}