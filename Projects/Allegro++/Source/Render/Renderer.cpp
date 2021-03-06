#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/display.h>

#include <alpp/Render/Camera.h>
#include <alpp/Render/Renderer.h>

#include <easylogging++.h>

#include <thread>

alpp::render::Renderer::Renderer(WindowSettings i_WinSettings) :
    Agent(),
    Camera             (std::make_shared<render::Camera>()),
    StandardFont       (nullptr),
    m_Window           (nullptr),
    m_CurrQueue        (0),
    m_StopRenderThread (false),
    m_CmdQueues        (),
    m_RenderThreadMutex(),
    m_Flip             (),
    m_DrawingStarted   ()
{
    // Initialize primitive addon
    CHECK_BOOL_AL_FUNC(al_init_primitives_addon(), m_InitSuccess,
        "Primitives add-on initialization failed");

    // Initialize font addon
    CHECK_BOOL_AL_FUNC(al_init_font_addon(), m_InitSuccess,
        "Font add-on initialization failed");

    // Initialize TTF font addon
    CHECK_BOOL_AL_FUNC(al_init_ttf_addon(), m_InitSuccess,
        "TTF font add-on initialization failed");

    // Load game font
    CHECK_AL_FUNC(al_load_ttf_font(FONT_FILE, FONT_SIZE, 0), StandardFont, m_InitSuccess,
        "Could not load standard font");

    // Start the render thread
    std::unique_lock<std::mutex> lock(m_RenderThreadMutex);
    std::thread(&Renderer::runRenderThread, this, i_WinSettings).detach();

    // Wait for render thread to be started (and for window to be created)
    m_DrawingStarted.wait(lock);
}

void alpp::render::Renderer::createWindow(WindowSettings i_WinSettings)
{
    // Create window
    auto displayFlags = 0;
    displayFlags |= static_cast<int>(i_WinSettings.DisplayMode);
    displayFlags |= static_cast<int>(i_WinSettings.Library);
    displayFlags |= i_WinSettings.IsResizable ? ALLEGRO_RESIZABLE : 0;

    al_set_new_display_flags(displayFlags);

    if (i_WinSettings.Title.length() > ALLEGRO_NEW_WINDOW_TITLE_MAX_SIZE)
    {
        LOG(WARNING) << "Window title is too long";
    }
    else
    {
        al_set_new_window_title(i_WinSettings.Title.c_str());
    }

    LOG(INFO) << "Creating window";

    if (i_WinSettings.DisplayMode == DisplayMode::FULLSCREEN)
    {
        struct ALLEGRO_DISPLAY_MODE bestRes;
        al_get_display_mode(al_get_num_display_modes() - 1, &bestRes);
        i_WinSettings.Dimensions = PixelDimensions(bestRes.width, bestRes.height);
    }

    CHECK_AL_FUNC(al_create_display(i_WinSettings.Dimensions.x, i_WinSettings.Dimensions.y),
        m_Window, m_InitSuccess, "Could not create Window");

    // Set default cursor
    CHECK_BOOL_AL_FUNC(al_set_system_mouse_cursor(m_Window, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT),
        m_InitSuccess, "Could not set the default mouse cursor");
}

alpp::render::Renderer::~Renderer()
{
    // Wait for render thread to finish its current frame
    std::unique_lock<std::mutex> lock(m_RenderThreadMutex);

    // Tell the render thread to exit its loop
    m_StopRenderThread = true;
    m_Flip.notify_one();

    // Wait for it to exit
    m_DrawingStarted.wait(lock);
}

void alpp::render::Renderer::runRenderThread(WindowSettings i_WinSettings)
{
    // Hold the render thread mutex for entire thread, except when waiting for main thread to flip
    std::unique_lock<std::mutex> lock(m_RenderThreadMutex);

    // Create window
    createWindow(i_WinSettings);

    // Notify main thread that drawing started
    m_DrawingStarted.notify_one();

    // Identity transform (for UI layer)
    ALLEGRO_TRANSFORM identityTranform;
    al_identity_transform(&identityTranform);

    // Until thread is asked to stop (by main thread destructor)
    while (!m_StopRenderThread)
    {   
        // Clear frame
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Execute World commands with camera transform
        executeCommands(Camera->getTransform(windowSize()), 
                        m_CmdQueues[2 * int(Layer::WORLD) + m_CurrQueue]);

        // Execute UI commands with identity transform
        executeCommands(&identityTranform, m_CmdQueues[2 * int(Layer::UI) + m_CurrQueue]);

        // Wait for main thread to flip display
        m_Flip.wait(lock);

        // Flip backbuffer
        al_flip_display();
    }

    // Destroy window
    al_destroy_display(m_Window);

    // Tell main thread that execution finished
    m_DrawingStarted.notify_one();
}

void alpp::render::Renderer::executeCommands(ALLEGRO_TRANSFORM *         i_Transform, 
                                             std::queue<sptr<Command>> & i_Queue)
{
    // Apply transform
    al_use_transform(i_Transform);

    // Execute commands
    while (!i_Queue.empty())
    {
        i_Queue.front()->execute();
        i_Queue.pop();
    }
}

void alpp::render::Renderer::enqueueCommand(sptr<Command> i_Cmd)
{
    // Enqueue command in a the queue that will be used to draw the next frame
    m_CmdQueues[2 * int(i_Cmd->Layer) + !m_CurrQueue].push(i_Cmd);
}

void alpp::render::Renderer::flip()
{
    // Wait for render thread to finish its current frame
    std::unique_lock<std::mutex> lock(m_RenderThreadMutex);

    // Switch draw queue and accumulation queue
    m_CurrQueue = !m_CurrQueue;

    // Notify render thread that it can start executing render commands for next frame
    m_Flip.notify_one();
}

bool alpp::render::Renderer::handleEvent(ALLEGRO_EVENT i_Event)
{
    switch (i_Event.type)
    {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        return false;

    case ALLEGRO_EVENT_DISPLAY_RESIZE:
        auto cmd = std::make_shared<ResizeWindow>();
        cmd->Window = m_Window;
        enqueueCommand(cmd);
        break;
    }

    return true;
}

PixelDimensions alpp::render::Renderer::windowSize() const
{
    return PixelDimensions(al_get_display_width(m_Window), al_get_display_height(m_Window));
}

ALLEGRO_EVENT_SOURCE* alpp::render::Renderer::getEventSource() const
{
    return al_get_display_event_source(m_Window);
}