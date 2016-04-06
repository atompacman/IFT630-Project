#ifndef ALPP_RENDER_WINDOW_SETTINGS
#define ALPP_RENDER_WINDOW_SETTINGS

#include <allegro5/display.h>

namespace alpp { namespace render {

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
    PixelDimensions dimensions  = PixelDimensions(800, 600);
    bool            isResizable = true;
    std::string     title       = "No title";
};

}}

#endif // ALPP_RENDER_WINDOW_SETTINGS 