#ifndef ALPP_EVENT_AGENT
#define ALPP_EVENT_AGENT

// allegro
#include <allegro5/events.h>

// alpp
#include <Core.h>

namespace alpp { namespace event {

class GameLoop;

class Agent : public AllegroInitializable
{
    friend GameLoop;

public:

    virtual ~Agent() { }

    virtual bool handleEvent(ALLEGRO_EVENT i_Event) = 0;

protected:

    virtual ALLEGRO_EVENT_SOURCE * getEventSource() const = 0;
};

}}

#endif // ALPP_EVENT_AGENT