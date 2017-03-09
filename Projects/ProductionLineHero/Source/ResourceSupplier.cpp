#include <allegro5/events.h>
#include <allegro5/timer.h>

#include <plh/ResourceSupplier.h>

ResourceSupplier::ResourceSupplier(sptr<BasicResource> i_RsrcArchetype,
                                   sptr<ResourceStack> i_StackToSupply,
                                   float               i_SpeedSec) :
    m_Ticker       (nullptr),
    m_StackToSupply(i_StackToSupply),
    m_RsrcArchetype(i_RsrcArchetype)
{

    CHECK_AL_FUNC(al_create_timer(i_SpeedSec), m_Ticker, 
        m_InitSuccess, "Could not create ticker timer");
    al_start_timer(m_Ticker);
}

ResourceSupplier::~ResourceSupplier()
{
    al_destroy_timer(m_Ticker);
}

bool ResourceSupplier::handleEvent(ALLEGRO_EVENT /* i_Event */)
{
    m_StackToSupply->push(m_RsrcArchetype->copy());
    return true;
}

ALLEGRO_EVENT_SOURCE * ResourceSupplier::getEventSource() const
{
    return al_get_timer_event_source(m_Ticker);
}
