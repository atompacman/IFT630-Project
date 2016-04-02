#include <allegro5/bitmap.h>
#include <Event/GameUpdater.h>
#include <Event/Manager.h>
#include <Event/Mouse.h>
#include <Render/Command.h>
#include <Render/WindowSettings.h>
#include <string>

std::string const LOGGER_CONFIG_FILE = "../Config/easyloggingpp.config";

class MyMouse : public alpp::event::Mouse
{
protected:

    void onMouseMoved() override
    {

    }

    void onButtonPressed(uint8_t i_Button) override
    {
		
    }

    void onButtonReleased(uint8_t i_Button) override
    {

    }
};

class MyGameUpdater : public alpp::event::GameUpdater
{
public:

    explicit MyGameUpdater(sptr<alpp::render::Renderer> io_Renderer,
                           sptrc<alpp::event::Mouse>    i_Mouse,
                           double                       i_TargetFPS = 60.) :
        GameUpdater(io_Renderer, i_TargetFPS),
        m_Mouse(i_Mouse)
    {};

protected:

    bool tick() override
    {
        LOG_EVERY_N(60, INFO) << "Game tick";
        auto color = al_map_rgb(20, 20, 150);
        auto cmd = std::make_shared<alpp::render::DrawFilledCircle>(m_Mouse->m_PosX, m_Mouse->m_PosY, 50, color);

        m_Renderer->enqueueCommand(cmd);

		color = al_map_rgb(170, 170, 10);
		auto cmd2 = std::make_shared<alpp::render::DrawFilledRectangle>(0, 0, 100, 800, color);

		m_Renderer->enqueueCommand(cmd2);
        return true;
    }

private:

    sptrc<alpp::event::Mouse> m_Mouse;
};

int main()
{
    // Initialize Allegro++ wrapper
    alpp::init(LOGGER_CONFIG_FILE);

    // Set window settings
    alpp::render::WindowSettings winSettings;
    winSettings.displayMode = alpp::render::DisplayMode::WINDOWED;
    winSettings.library     = alpp::render::GraphicsLibrary::OPEN_GL;
    winSettings.width       = 1200;
    winSettings.height      = 800;
    winSettings.isResizable = true;
    winSettings.title       = "Test";

    // Create renderer
    auto renderer = std::make_shared<alpp::render::Renderer>(winSettings);

    // Create mouse event handler
    auto mouseHandler = std::make_shared<MyMouse>();

    // Create game updater
    auto gameUpdater = std::make_shared<MyGameUpdater>(renderer, mouseHandler);
    
    // Create event manager and register all event agents
    alpp::event::Manager eventManager;
    eventManager.registerAgent(renderer);
    eventManager.registerGameUpdaterAgent(gameUpdater);
    eventManager.registerAgent(mouseHandler);
    eventManager.run();
}