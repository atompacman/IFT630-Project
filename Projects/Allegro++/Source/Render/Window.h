#ifndef ALPP_RENDER_WINDOW
#define ALPP_RENDER_WINDOW

#include <allegro5/display.h>
#include <Event/Agent.h>
#include <string>

namespace alpp { namespace render {

enum class DisplayMode
{
    WINDOWED = ALLEGRO_WINDOWED,
    FULLSCREEN_WINDOW = ALLEGRO_FULLSCREEN_WINDOW,
    FULLSCREEN = ALLEGRO_FULLSCREEN
};

enum class GraphicsLibrary
{
    OPEN_GL = ALLEGRO_OPENGL,
    DIRECT_3D = ALLEGRO_DIRECT3D_INTERNAL
};

class Window : public event::Agent
{
public:

    explicit Window(DisplayMode     i_DisplayMode = DisplayMode::WINDOWED,
                    GraphicsLibrary i_Library     = GraphicsLibrary::OPEN_GL,
                    uint32_t        i_Width       = 800,
                    uint32_t        i_Height      = 600,
                    bool            i_IsResizable = true,
                    std::string     i_Title       = "Unkown title");
    ~Window() override;

    bool handleEvent(ALLEGRO_EVENT i_Event) override;

protected:

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

private:

    ALLEGRO_DISPLAY * m_Window;
};

}}

#endif // ALPP_RENDER_WINDOW 