#ifndef ALPP_EVENT_MANAGER
#define ALPP_EVENT_MANAGER

#include <Core.h>
#include <unordered_map>

struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_EVENT_SOURCE;

namespace alpp { namespace event {

class Agent;

class Manager : public AllegroInitializable
{
public:

    explicit Manager();
    ~Manager() override;

    void registerAgent(sptr<Agent> i_Agent);

    void run();

private:

    ALLEGRO_EVENT_QUEUE *                                   m_EventQueue;
    std::unordered_map<ALLEGRO_EVENT_SOURCE *, sptr<Agent>> m_EventAgents;
};

}}

#endif // ALPP_EVENT_MANAGER