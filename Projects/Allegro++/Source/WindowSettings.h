#ifndef ALLEGROPP_WINDOW_SETTINGS
#define ALLEGROPP_WINDOW_SETTINGS

#include <allegro5/display.h>
#include <string>

namespace alpp
{

enum class DisplayMode
{
    WINDOWED          = ALLEGRO_WINDOWED,
    FULLSCREEN_WINDOW = ALLEGRO_FULLSCREEN_WINDOW,
    FULLSCREEN        = ALLEGRO_FULLSCREEN
};

enum class GraphicsLibrary
{
    OPEN_GL   = ALLEGRO_OPENGL,
    DIRECT_3D = ALLEGRO_DIRECT3D_INTERNAL
};

struct WindowSettings
{
    DisplayMode     displayMode = DisplayMode::WINDOWED;
    GraphicsLibrary library     = GraphicsLibrary::OPEN_GL;
    uint32_t        width       = 800;
    uint32_t        height      = 600;
    bool            isResizable = true;
    std::string     title       = "No title";
};

}

#endif // ALLEGROPP_WINDOW_SETTINGS