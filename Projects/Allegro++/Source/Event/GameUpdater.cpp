#include <Core.h>
#include <event/GameUpdater.h>

alpp::event::GameUpdater::GameUpdater(sptr<render::Renderer> io_Renderer, 
                                      double                 i_TargetFPS /* = 60. */) :
    Agent(),
    m_Ticker  (nullptr),
    m_Renderer(io_Renderer)
{
    CHECK_AL_FUNC(al_create_timer(1.0 / i_TargetFPS), m_Ticker, m_InitSuccess, 
                  "Could not create ticker timer");
    al_start_timer(m_Ticker);
}

alpp::event::GameUpdater::~GameUpdater()
{
    al_destroy_timer(m_Ticker);
}

bool alpp::event::GameUpdater::handleEvent(ALLEGRO_EVENT /* i_Event */)
{
    // Tick the game
    auto success = tick();

    // Flip display (or wait after render thread to finish current frame)
    m_Renderer->flip();

    return success;
}

ALLEGRO_EVENT_SOURCE * alpp::event::GameUpdater::getEventSource() const
{
    return al_get_timer_event_source(m_Ticker);
}