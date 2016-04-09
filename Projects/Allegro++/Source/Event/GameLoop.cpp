#include <allegro5/events.h>
#include <allegro5/timer.h>

#include <alpp/Core.h>
#include <alpp/Event/GameLoop.h>

#include <easylogging++.h>

alpp::event::GameLoop::GameLoop(render::WindowSettings i_WinSettings,
                                double                 i_TargetFPS /* = 60. */) :
    Agent(),
    Renderer           (std::make_shared<render::Renderer>(i_WinSettings)),
    m_EventQueue       (nullptr),
    m_EventAgents      (),
    m_Ticker           (nullptr),
    m_TickerEventSource(nullptr)
{
    CHECK_AL_FUNC(al_create_event_queue(), m_EventQueue, m_InitSuccess, 
                  "Could not create event queue");

    CHECK_AL_FUNC(al_create_timer(1.0 / i_TargetFPS), m_Ticker, m_InitSuccess, 
                  "Could not create ticker timer");
   
    registerAgent(Renderer);

    m_TickerEventSource = al_get_timer_event_source(m_Ticker);
}

alpp::event::GameLoop::~GameLoop()
{
    al_destroy_timer(m_Ticker);
    al_destroy_event_queue(m_EventQueue);
}

void alpp::event::GameLoop::registerAgent(sptr<Agent> i_Agent)
{
    auto * source = i_Agent->getEventSource();
    m_EventAgents[source] = i_Agent;
    al_register_event_source(m_EventQueue, source);
}

bool alpp::event::GameLoop::handleEvent(ALLEGRO_EVENT /* i_Event */)
{
    // Tick the game
    auto success = tick();

    // Flip display (or wait after render thread to finish current frame)
    Renderer->flip();

    return success;
}

ALLEGRO_EVENT_SOURCE * alpp::event::GameLoop::getEventSource() const
{
    return m_TickerEventSource;
}

void alpp::event::GameLoop::run()
{
    registerAgent(shared_from_this());
    al_start_timer(m_Ticker);

    auto doExit = false;
    auto doTick = false;

    while (!doExit)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(m_EventQueue, &event);

        if (event.any.source == m_TickerEventSource)
        {
            doTick = true;
        }
        else
        {
            doExit = !m_EventAgents[event.any.source]->handleEvent(event);
        }

        if (doTick && al_is_event_queue_empty(m_EventQueue))
        {
            doExit = !handleEvent(event);
            doTick = false;
        }
    }

    m_EventAgents.clear();
}