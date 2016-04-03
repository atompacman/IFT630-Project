// allegro
#include <allegro5/bitmap.h>

// alpp
#include <Event/Mouse.h>
#include <Event/GameLoop.h>
#include <Render/Command.h>
#include <Render/Renderer.h>
#include <Render/WindowSettings.h>

// el
#include <easylogging++.h>

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
        GameLoop(i_WinSettings, i_TargetFPS)
    {};

protected:

    bool tick() override
    {
        LOG_EVERY_N(60, INFO) << "Game tick";
        auto color = al_map_rgb(20, 20, 150);
        sptr<render::Command> cmd = std::make_shared<render::DrawFilledCircle>(objPosX, objPosY, 50, color);

        m_Renderer->enqueueCommand(cmd);

        color = al_map_rgb(170, 170, 10);
        cmd = std::make_shared<render::DrawFilledRectangle>(0, 0, 100, 800, color);

        m_Renderer->enqueueCommand(cmd);
        return true;
    }
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