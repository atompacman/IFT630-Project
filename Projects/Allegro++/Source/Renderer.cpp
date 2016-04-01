#include <Allegro++.h>
#include <allegro5/allegro_primitives.h>
#include <easylogging++.h>
#include <Renderer.h>

namespace alpp
{

Renderer::Renderer(WindowSettings const & i_WinSettings, double i_TargetFPS /* = 60. */) :
    m_Window     (nullptr),
    m_TargetFPS  (i_TargetFPS),
    m_InitSuccess(true)
{
    // Initialize primitive addon
    CHECK_BOOL_AL_FUNC(al_init_primitives_addon(), m_InitSuccess,
        "Primitives add-on initialization failed");

    // Create window
    auto displayFlags = 0;
    displayFlags |= static_cast<int>(i_WinSettings.displayMode);
    displayFlags |= static_cast<int>(i_WinSettings.library);
    displayFlags |= i_WinSettings.isResizable ? ALLEGRO_RESIZABLE : 0;

    al_set_new_display_flags(displayFlags);

    if (i_WinSettings.title.length() > ALLEGRO_NEW_WINDOW_TITLE_MAX_SIZE)
    {
        LOG(WARNING) << "Window title is too long";
    }
    else
    {
        al_set_new_window_title(i_WinSettings.title.c_str());
    }

    LOG(INFO) << "Creating window";

    int width  = i_WinSettings.width;
    int height = i_WinSettings.height;

    if (i_WinSettings.displayMode == DisplayMode::FULLSCREEN)
    {
        ALLEGRO_DISPLAY_MODE bestRes;
        al_get_display_mode(al_get_num_display_modes() - 1, &bestRes);
        width  = bestRes.width;
        height = bestRes.height;
    }

    CHECK_AL_FUNC(al_create_display(width,height),m_Window,m_InitSuccess,"Window creation failed");
}

Renderer::~Renderer()
{
    al_destroy_display(m_Window);
}

bool Renderer::wasInitSuccessful() const
{
    return m_InitSuccess;
}

}