#ifndef ALPP_EVENT_MANAGER
#define ALPP_EVENT_MANAGER

#include <Core.h>
#include <unordered_map>

struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_EVENT_SOURCE;

namespace alpp { namespace event {

class Agent;
class GameUpdater;

class Manager : public AllegroInitializable
{
public:

    explicit Manager();
    ~Manager() override;

    void registerAgent(sptr<Agent> i_Agent);
    void registerGameUpdaterAgent(sptr<GameUpdater> i_GameUpdater);

    void run();

private:

    ALLEGRO_EVENT_QUEUE *                                   m_EventQueue;
    std::unordered_map<ALLEGRO_EVENT_SOURCE *, sptr<Agent>> m_EventAgents;
    ALLEGRO_EVENT_SOURCE *                                  m_GameUpdater;
};

}}

#endif // ALPP_EVENT_MANAGER