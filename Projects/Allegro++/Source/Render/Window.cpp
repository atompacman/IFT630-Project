#include <allegro5/allegro_primitives.h>
#include <Render/Window.h>

alpp::render::Window::Window(DisplayMode     i_DisplayMode /* = DisplayMode::WINDOWED    */, 
                             GraphicsLibrary i_Library     /* = GraphicsLibrary::OPEN_GL */,
                             uint32_t        i_Width       /* = 800                      */,
                             uint32_t        i_Height      /* = 600                      */,
                             bool            i_IsResizable /* = true                     */,
                             std::string     i_Title       /* = "Unkown title"           */) :
    Agent(),
    m_Window(nullptr)
{
    // Initialize primitive addon
    CHECK_BOOL_AL_FUNC(al_init_primitives_addon(), m_InitSuccess,
        "Primitives add-on initialization failed");

    // Create window
    auto displayFlags = 0;
    displayFlags |= static_cast<int>(i_DisplayMode);
    displayFlags |= static_cast<int>(i_Library);
    displayFlags |= i_IsResizable ? ALLEGRO_RESIZABLE : 0;

    al_set_new_display_flags(displayFlags);

    if (i_Title.length() > ALLEGRO_NEW_WINDOW_TITLE_MAX_SIZE)
    {
        LOG(WARNING) << "Window title is too long";
    }
    else
    {
        al_set_new_window_title(i_Title.c_str());
    }

    LOG(INFO) << "Creating window";

    if (i_DisplayMode == DisplayMode::FULLSCREEN)
    {
        ALLEGRO_DISPLAY_MODE bestRes;
        al_get_display_mode(al_get_num_display_modes() - 1, &bestRes);
        i_Width  = bestRes.width;
        i_Height = bestRes.height;
    }

    CHECK_AL_FUNC(al_create_display(i_Width, i_Height), m_Window, m_InitSuccess, 
                  "Could not create Window");

    // Set default cursor
    CHECK_BOOL_AL_FUNC(al_set_system_mouse_cursor(m_Window, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT), 
        m_InitSuccess, "Could not set the default mouse cursor");
}

alpp::render::Window::~Window()
{
    al_destroy_display(m_Window);
}

bool alpp::render::Window::handleEvent(ALLEGRO_EVENT i_Event)
{
    switch (i_Event.type)
    {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        return false; 
        
    case ALLEGRO_EVENT_DISPLAY_RESIZE:
        al_acknowledge_resize(m_Window);
        break;
    }

    return true;
}

ALLEGRO_EVENT_SOURCE* alpp::render::Window::getEventSource() const
{
    return al_get_display_event_source(m_Window);
}