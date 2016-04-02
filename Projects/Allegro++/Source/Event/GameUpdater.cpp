#include <Core.h>
#include <event/GameUpdater.h>

alpp::event::GameUpdater::GameUpdater(double i_TargetFPS /* = 60. */) :
    Agent(),
    m_Ticker(nullptr)
{
    CHECK_AL_FUNC(al_create_timer(1.0 / i_TargetFPS), m_Ticker, m_InitSuccess, 
                  "Could not create render timer");
    al_start_timer(m_Ticker);
}

alpp::event::GameUpdater::~GameUpdater()
{
    al_destroy_timer(m_Ticker);
}

bool alpp::event::GameUpdater::handleEvent(ALLEGRO_EVENT /* i_Event */)
{
    return tick();
}

ALLEGRO_EVENT_SOURCE * alpp::event::GameUpdater::getEventSource() const
{
    return al_get_timer_event_source(m_Ticker);
}