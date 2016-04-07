#ifndef ALPP_EVENT_GAME_LOOP
#define ALPP_EVENT_GAME_LOOP

#include <allegro5/events.h>

#include <alpp/Render/Renderer.h>

#include <unordered_map>

struct ALLEGRO_TIMER;

namespace alpp { namespace event {

class GameLoop : public Agent, std::enable_shared_from_this<GameLoop>
{
public:

    explicit GameLoop(render::WindowSettings i_WinSettings, double i_TargetFPS = 60.);
    ~GameLoop() override;

    void registerAgent(sptr<Agent> i_Agent);

    bool handleEvent(ALLEGRO_EVENT i_Event) override;

    void run();

    sptr<render::Renderer> Renderer;

protected:

    virtual bool tick() = 0;

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

private:

    ALLEGRO_EVENT_QUEUE *                                   m_EventQueue;
    std::unordered_map<ALLEGRO_EVENT_SOURCE *, sptr<Agent>> m_EventAgents;

    ALLEGRO_TIMER *        m_Ticker;
    ALLEGRO_EVENT_SOURCE * m_TickerEventSource;
};

}}

#endif // ALPP_EVENT_GAME_LOOP