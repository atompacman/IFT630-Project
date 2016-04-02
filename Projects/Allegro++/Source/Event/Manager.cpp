#include <allegro5/events.h>
#include <Core.h>
#include <Event/Agent.h>
#include <Event/GameUpdater.h>
#include <Event/Manager.h>

alpp::event::Manager::Manager() :
    AllegroInitializable(),
    m_EventQueue (nullptr),
    m_EventAgents(),
    m_GameUpdater(nullptr)
{
    CHECK_AL_FUNC(al_create_event_queue(), m_EventQueue,m_InitSuccess,"Error creating event queue");
}

alpp::event::Manager::~Manager()
{
    al_destroy_event_queue(m_EventQueue);
}

void alpp::event::Manager::registerAgent(sptr<Agent> i_Agent)
{
    auto * source = i_Agent->getEventSource();
    m_EventAgents[source] = i_Agent;
    al_register_event_source(m_EventQueue, source);
}

void alpp::event::Manager::registerGameUpdaterAgent(sptr<GameUpdater> i_GameUpdater)
{
    m_GameUpdater = static_cast<sptr<Agent>>(i_GameUpdater)->getEventSource();
    registerAgent(i_GameUpdater);
}

void alpp::event::Manager::run()
{
    auto doExit = false;
    auto doTick = false;

    while (!doExit)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(m_EventQueue, &event);

        if (event.any.source == m_GameUpdater)
        {
            doTick = true;
        }
        else
        {
            doExit = !m_EventAgents[event.any.source]->handleEvent(event);
        }

        if (doTick && al_is_event_queue_empty(m_EventQueue))
        {
            doExit = !m_EventAgents[m_GameUpdater]->handleEvent(event);
            doTick = false;
        }
    }
}