#include <Allegro++.h>
#include <GameLoop.h>
#include <Renderer.h>

std::string const LOGGER_CONFIG_FILE = "../Config/easyloggingpp.config";

int main()
{
    // Initializes the Allegro++ wrapper library
    alpp::init(LOGGER_CONFIG_FILE);

    // Set window creation settings
    alpp::WindowSettings winSettings;
    winSettings.displayMode = alpp::DisplayMode::WINDOWED;
    winSettings.library     = alpp::GraphicsLibrary::OPEN_GL;
    winSettings.width       = 1600;
    winSettings.height      = 800;
    winSettings.isResizable = true;
    winSettings.title       = "Test";

    // Create the renderer, which will create the window for us
    alpp::Renderer renderer(winSettings, 60);

    // Create the game loop
    alpp::GameLoop loop(renderer);

    // Run the game loop
    loop.run();
}