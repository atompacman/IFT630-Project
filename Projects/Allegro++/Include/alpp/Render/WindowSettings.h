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

/*================================================================================================\\
| Contains info needed to create a window
\=================================================================================================*/

struct WindowSettings
{
    DisplayMode     DisplayMode = DisplayMode::WINDOWED;
    GraphicsLibrary Library     = GraphicsLibrary::OPEN_GL;
    PixelDimensions Dimensions  = PixelDimensions(800, 600);
    bool            IsResizable = true;
    std::string     Title       = "No title";
};

}}

#endif // ALPP_RENDER_WINDOW_SETTINGS 