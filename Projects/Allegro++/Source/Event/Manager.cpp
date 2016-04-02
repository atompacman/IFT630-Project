#include <allegro5/events.h>
#include <Core.h>
#include <Event/Agent.h>
#include <Event/Manager.h>

alpp::event::Manager::Manager() :
    AllegroInitializable(),
    m_EventQueue (nullptr),
    m_EventAgents()
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

void alpp::event::Manager::run()
{
    auto doExit = false;

    while (!doExit)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(m_EventQueue, &event);
        doExit = !m_EventAgents[event.any.source]->handleEvent(event);
    }
}