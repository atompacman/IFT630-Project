// allegro
#include <allegro5/bitmap.h>

// alpp
#include <Event/Mouse.h>
#include <Event/GameLoop.h>
#include <Render/Command.h>
#include <Render/Renderer.h>
#include <Render/WindowSettings.h>

// plh
#include <Factory.h>

// std
#include <string>

using namespace alpp;

std::string const LOGGER_CONFIG_FILE = "../Config/easyloggingpp.config";

uint16_t objPosX;
uint16_t objPosY;

class MyMouse : public event::Mouse
{
protected:

    void onMouseMoved() override
    {
        objPosX = m_PosX;
        objPosY = m_PosY;
    }

    void onButtonPressed(uint8_t i_Button) override
    {

    }

    void onButtonReleased(uint8_t i_Button) override
    {

    }
};

class MyGameLoop : public event::GameLoop
{
public:

    explicit MyGameLoop(render::WindowSettings i_WinSettings, double i_TargetFPS = 60.) :
        GameLoop(i_WinSettings, i_TargetFPS),
        m_Factory()
    {
        auto workshop = m_Factory.buildWorkshop(2, 1);
        workshop->addResourceStack(StackPosition::WEST, ResourceStack::Type::INPUT);
        workshop->addResourceStack(StackPosition::EAST, ResourceStack::Type::OUTPUT);
    };

protected:

    bool tick() override
    {
         // Draw a circle at mouse position
        auto cmd = std::make_shared<render::DrawFilledCircle>();
        cmd->CenterPosX = objPosX;
        cmd->CenterPosY = objPosY;
        cmd->Radius     = 10;
        cmd->Color      = al_map_rgb(20, 20, 150);
        m_Renderer->enqueueCommand(cmd);

        // Draw factory
        m_Factory.render(m_Renderer);
        
        return true;
    }

private:

    Factory m_Factory;
};

int main()
{
    // Initialize Allegro++ wrapper
    init(LOGGER_CONFIG_FILE);

    // Set window settings
    render::WindowSettings winSettings;
    winSettings.displayMode = render::DisplayMode::WINDOWED;
    winSettings.library     = render::GraphicsLibrary::OPEN_GL;
    winSettings.width       = 1200;
    winSettings.height      = 800;
    winSettings.isResizable = true;
    winSettings.title       = "Test";

    // Create game loop
    auto gameLoop = std::make_shared<MyGameLoop>(winSettings);

    // Register custom mouse handler
    gameLoop->registerAgent(std::make_shared<MyMouse>());

    // Run game loop
    gameLoop->run();
}