#include <Allegro++.h>
#include <Renderer.h>
#include <GameLoop.h>

namespace alpp
{

GameLoop::GameLoop(Renderer & io_Renderer) :
    m_Renderer   (io_Renderer),
    m_EventQueue (nullptr),
    m_RenderTimer(nullptr),
    m_InitSuccess(true)

{
    // Create event queue
    CHECK_AL_FUNC(al_create_event_queue(), m_EventQueue, m_InitSuccess,
                  "Could not create event queue");

    // Create render timer
    CHECK_AL_FUNC(al_create_timer(1.0 / m_Renderer.m_TargetFPS), m_RenderTimer, m_InitSuccess,
                  "Could not create render timer");

    // Register event sources
    al_register_event_source(m_EventQueue, al_get_display_event_source(m_Renderer.m_Window));
    al_register_event_source(m_EventQueue, al_get_timer_event_source  (m_RenderTimer));
}

bool GameLoop::run()
{
    // Start render timer (will tick when backbuffer must be flipped)
    al_start_timer(m_RenderTimer);

    // Run the game loop
    auto doExitLoop = false;
    while (!doExitLoop)
    {
        // Wait for an allegro event
        ALLEGRO_EVENT event;
        al_wait_for_event(m_EventQueue, &event);

        switch (event.type)
        {
            // When main window is closed
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            doExitLoop = true;
            break;
        }
    }

    return EXIT_SUCCESS;
}


bool GameLoop::wasInitSuccessful() const
{
    return m_InitSuccess;
}

}
