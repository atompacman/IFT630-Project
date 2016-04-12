#include <alpp/Render/Camera.h>

#include <easylogging++.h>

#include <plh/CreationMenu.h>
#include <plh/CreationButton.h>
#include <plh/Event/GameLoop.h>
#include <plh/Event/Mouse.h>

void Mouse::onScroll() 
{ 

    m_GameObject->Renderer->Camera->adjustZoom(MOUSE_SCROLL_ZOOM_FACTOR * DeltaScroll);
    
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
                m_GameObject->setState(GameState::CREATION_MODE);
                m_GameObject->setRoomTypeToCreate(button->getRoomType());
                button->setColor(al_map_rgb(10, 100, 200));
                LOG(INFO) << "BUTTON CLICKED" << " (" << Position.x << "," << Position.y << ")" 
                          << " : " << (int)button->getRoomType();
            }
        }
    }

    // Check if click is for creating room in factory

    else if (m_GameObject->getState() == GameState::CREATION_MODE) 
    {
        // Change click from pixel to world coordinates (and then workshop)
        PixelCoords winSize = m_GameObject->Renderer->windowSize();
        WorldCoords clickWorldPos = Position;

        ALLEGRO_TRANSFORM * transform = m_GameObject->Renderer->Camera->getTransform(winSize);
        al_invert_transform(transform);
        al_transform_coordinates(transform, &clickWorldPos.x, &clickWorldPos.y);
        
        WorldCoords roomPos = worldCoordsULCornerToWorkshopCoords(clickWorldPos);
        CreatableRoomType roomType = m_GameObject->getRoomTypeToCreate();
        // create room/object
        m_GameObject->CreateFactoryRoom(roomType, roomPos);

        // reset the normal color
        switch (roomType) 
        {
        case CreatableRoomType::WORKSHOP:
            buttons[(int)roomType]->setColor(al_map_rgb(0, 255, 0));
            break;
        case CreatableRoomType::SUPPLIER:
            buttons[(int)roomType]->setColor(al_map_rgb(255, 255, 0));
        default:
            break;
        }

        
    }
    

    // Check if the click is <insert something else here>
    

};

void Mouse::onMouseMoved()
{
    WorldCoords translation;

   // check if we must move the camera (mouse is dragged)

    auto ui = m_GameObject->getUI();

    CreationMenu * createMenu = dynamic_cast<CreationMenu*>(ui[0]);

    if (PressedButtons[int(Button::Right)] && !createMenu->isMouseInArea(Position))
    {
        auto cam = m_GameObject->Renderer->Camera;
        translation -= (DeltaPos);
        cam->translate(translation);
    }
};