#include <easylogging++.h>

#include <plh/Event/Mouse.h>

#include <plh/Event/GameLoop.h>
#include <plh/CreationMenu.h>
#include <plh/CreationButton.h>
#include <alpp/Render/Camera.h>

void Mouse::onScroll() 
{ 

    m_GameObject->Renderer->Camera->adjustZoom(MOUSE_SCROLL_ZOOM_FACTOR * DeltaScroll);
    
    LOG(INFO) << "onScroll" << "  " << DeltaScroll << "  " << m_GameObject->Renderer->Camera->getZoom();
};

void Mouse::onLeftClick() 
{
    LOG(INFO) << "onLeftClick" << " (" << Position.x << "," << Position.y << ")";

    // Check if the click is on UI

    auto ui = m_GameObject->getUI();

    CreationMenu * createMenu = dynamic_cast<CreationMenu*>(ui[0]);

    if (createMenu->isMouseInArea(Position)) {
        for (CreationButton * button : createMenu->getButtons())
        {
            if (button->isMouseInArea(Position))
            {
                m_GameObject->setState(GameState::CREATION_MODE);
                m_GameObject->setRoomTypeToCreate(button->getRoomType());
                LOG(INFO) << "BUTTON CLICKED" << " (" << Position.x << "," << Position.y << ")" << " : " << (int)button->getRoomType();
            }
        }
    }

    // Check if click is for creating room in factory

    else if (m_GameObject->getState() == GameState::CREATION_MODE) 
    {

        // In progress
        /*WorldCoords camPos = m_GameObject->Renderer->Camera->getPosition();
        camPos /= 2.0;*/
        
        WorldCoords roomPos = worldCoordsToWorkshopCoordsULCorner(WorldCoords(Position)/* + camPos*/);
        CreatableRoomType roomType = m_GameObject->getRoomTypeToCreate();   // Might be redundant...

        m_GameObject->CreateFactoryRoom(roomType, roomPos); // Same ...
    }
    

    // Check if the click is <insert something else here>
    

};

void Mouse::onLeftPressed()
{
    m_LeftPressed = true;
};

void Mouse::onLeftReleased()
{
    m_LeftPressed = false;
};

void Mouse::onRightPressed()
{
    m_RightPressed = true;
};

void Mouse::onRightReleased()
{
    m_RightPressed = false;
};

void Mouse::onMouseMoved()
{
    WorldCoords translation;

   // check if we must move the camera (mouse is dragged)

    auto ui = m_GameObject->getUI();

    CreationMenu * createMenu = dynamic_cast<CreationMenu*>(ui[0]);

    if (m_RightPressed && !createMenu->isMouseInArea(Position))
    {
        auto cam = m_GameObject->Renderer->Camera;
        translation -= (DeltaPos);
        cam->translate(translation);
    }
};