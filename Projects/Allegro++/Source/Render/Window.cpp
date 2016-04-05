#include <allegro5/display.h>
#include <allegro5/fullscreen_mode.h>
#include <allegro5/mouse_cursor.h>
#include <Render/Window.h>

alpp::render::Window::Window(WindowSettings i_WinSettings) :
    Agent(),
    m_Window(nullptr)
{
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

    if (i_WinSettings.displayMode == DisplayMode::FULLSCREEN)
    {
        struct ALLEGRO_DISPLAY_MODE bestRes;
        al_get_display_mode(al_get_num_display_modes() - 1, &bestRes);
        i_WinSettings.width  = bestRes.width;
        i_WinSettings.height = bestRes.height;
    }

    CHECK_AL_FUNC(al_create_display(i_WinSettings.width, i_WinSettings.height), 
                  m_Window, m_InitSuccess, "Could not create Window");

    // Set default cursor
    CHECK_BOOL_AL_FUNC(al_set_system_mouse_cursor(m_Window, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT), 
        m_InitSuccess, "Could not set the default mouse cursor");
}
