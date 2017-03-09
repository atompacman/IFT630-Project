#include <alpp/Render/Camera.h>

#include <easylogging++.h>

#include <plh/CreationMenu.h>
#include <plh/CreationButton.h>
#include <plh/Event/GameLoop.h>
#include <plh/Event/Mouse.h>

void Mouse::onScroll() 
{ 
    // Change cardinal direction when creating workshop or a resource supplier
    if (m_GameObject->getState() == GameState::CREATION_MODE && 
        (m_GameObject->getObjectTypeToCreate() == CreatableObjectType::WORKSHOP
         || m_GameObject->getObjectTypeToCreate() == CreatableObjectType::SUPPLIER))
    {
        int dir = ((int)m_GameObject->getCreationDir() + DeltaScroll) % 4;
        if (dir < 0)
            dir = 3;

        m_GameObject->setCreationDir((CardinalDir)(dir));
    }

    // Zoom screen
    else
    {
        m_GameObject->Renderer->Camera->adjustZoom(MOUSE_SCROLL_ZOOM_FACTOR * DeltaScroll);
    }
        
    
    LOG(INFO) << "onScroll" << "  " << DeltaScroll << "  " 
              << m_GameObject->Renderer->Camera->getZoom();
};

void Mouse::onLeftClick() 
{
    LOG(INFO) << "onLeftClick" << " (" << Position.x << "," << Position.y << ")";

    // Check if the click is on UI
    auto ui = m_GameObject->getUI();
    CreationMenu * createMenu = dynamic_cast<CreationMenu*>(ui[0]);
    auto buttons = createMenu->getButtons();

    if (createMenu->isMouseInArea(Position)) {
        for (CreationButton * button : buttons)
        {
            if (button->isMouseInArea(Position))
            {
                // Tell to the game which object to create
                m_GameObject->setState(GameState::CREATION_MODE);
                m_GameObject->setObjectTypeToCreate(button->getObjectType());
                button->setColor(al_map_rgb(10, 100, 200));
                LOG(INFO) << "BUTTON CLICKED" << " (" << Position.x << "," << Position.y << ")" 
                          << " : " << (int)button->getObjectType();
            }
        }
    }

    // Check if click is for creating object in factory
    else if (m_GameObject->getState() == GameState::CREATION_MODE) 
    {
        // Change click from pixel to world coordinates (and then workshop)
        WorldCoords clickWorldPos = pixelCoordsToWorldCoords(Position, m_GameObject->Renderer);

        // Get which object we want to create
        CreatableObjectType objectType = m_GameObject->getObjectTypeToCreate();

        // Check if creation is valid
        if (!m_GameObject->getFactory().isCoordInFactory(clickWorldPos))
        {
            m_GameObject->setObjectTypeToCreate(CreatableObjectType::NONE);
            m_GameObject->setState(GameState::IDLE_MODE);
        }
        else
        {
            // Get corresponding factory grid position and type of creation
            WorldCoords roomPos = worldCoordsULCornerToWorkshopCoords(clickWorldPos);
            // create room/object
            m_GameObject->CreateFactoryObject(objectType, roomPos);
        }
        
        // reset the normal color
        switch (objectType) 
        {
        case CreatableObjectType::WORKSHOP:
            buttons[(int)objectType]->setColor(getButtonColor(0));
            break;
        case CreatableObjectType::SUPPLIER:
            buttons[(int)objectType]->setColor(getButtonColor(1));
            break;
        case CreatableObjectType::WORKER:
            buttons[(int)objectType]->setColor(getButtonColor(2));
            break;
        default:
            break;
        }
    }

};

void Mouse::onMouseMoved()
{
    WorldCoords translation;

   // check if we must move the camera (mouse is dragged)

    auto ui = m_GameObject->getUI();

    CreationMenu * createMenu = dynamic_cast<CreationMenu*>(ui[0]);

    if (!createMenu->isMouseInArea(Position))
    {
        if (PressedButtons[int(Button::Right)])
        {
            auto cam = m_GameObject->Renderer->Camera;
            translation -= (DeltaPos);
            cam->translate(translation);
        }

        if (m_GameObject->getState() == GameState::CREATION_MODE)
        {
            m_GameObject->setMouseHoverPosition(Position);
        }
    }

};