#include <string>
#include <Event/GameUpdater.h>
#include <Event/Manager.h>
#include <Event/Mouse.h>
#include <Render/Window.h>

std::string const LOGGER_CONFIG_FILE = "../Config/easyloggingpp.config";

class MyMouse : public alpp::event::Mouse
{
protected:

    void onMouseMoved() override
    {
        LOG(INFO) << "Mouse moved";
    }

    void onButtonPressed(uint8_t i_Button) override
    {
        LOG(INFO) << "Mouse button " << i_Button << " was pressed";
    }

    void onButtonReleased(uint8_t i_Button) override
    {
        LOG(INFO) << "Mouse button " << i_Button << " was released";
    }
};

class MyGameUpdater : public alpp::event::GameUpdater
{
public:

    explicit MyGameUpdater() { };

protected:

    bool tick() override
    {
        LOG(INFO) << "Game tick";
        return true;
    }
};

int main()
{
    alpp::init(LOGGER_CONFIG_FILE);

    alpp::event::Manager eventManager;

    eventManager.registerAgent(std::make_shared<alpp::render::Window>(
                                    alpp::render::DisplayMode::WINDOWED,
                                    alpp::render::GraphicsLibrary::OPEN_GL,
                                    1600,
                                    800,
                                    true,
                                    "Test"));
    eventManager.registerAgent(std::make_shared<MyMouse>());
    eventManager.registerAgent(std::make_shared<MyGameUpdater>());

    eventManager.run();
}