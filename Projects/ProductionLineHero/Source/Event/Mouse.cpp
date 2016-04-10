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

    for (CreationButton * button : createMenu->getButtons())
    {
        if (button->isMouseInArea(Position))
        {
            LOG(INFO) << "BUTTON CLICKED" << " (" << Position.x << "," << Position.y << ")";
        }
    }

    // Check if the click is <insert something here>
    

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