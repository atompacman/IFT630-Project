#include <alpp/Core.h>
#include <alpp/Render/Camera.h>
#include <alpp/Render/WindowSettings.h>

#include <plh/Event/GameLoop.h>
#include <plh/Event/Keyboard.h>
#include <plh/Event/Mouse.h>

int main()
{
    // Initialize Allegro++ wrapper
    alpp::init(LOGGER_CONFIG_FILE);

    // Set window settings
    alpp::render::WindowSettings winSettings;
    winSettings.DisplayMode = alpp::render::DisplayMode::WINDOWED;
    winSettings.Library     = alpp::render::GraphicsLibrary::OPEN_GL;
    winSettings.Dimensions  = INIT_WIN_DIM;
    winSettings.IsResizable = true;
    winSettings.Title       = "Test";

    // Create game loop
    auto gameloop = std::make_shared<GameLoop>(winSettings);

    // Center camera
    gameloop->Renderer->Camera->translate(WorldCoords(INIT_WIN_DIM) / 2.f);

    // Register custom mouse handler
    gameloop->registerAgent(std::make_shared<Mouse>(gameloop));

    // Register custom keyboard handler
    gameloop->registerAgent(std::make_shared<Keyboard>(gameloop->Renderer->Camera));

    // Run game loop
    gameloop->run();
}