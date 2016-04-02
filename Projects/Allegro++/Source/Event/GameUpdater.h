#ifndef ALPP_EVENT_GAME_UPDATER
#define ALPP_EVENT_GAME_UPDATER

#include <allegro5/events.h>
#include <allegro5/timer.h>
#include <event/Agent.h>
#include <Render/Renderer.h>

namespace alpp { namespace event {

class GameUpdater : public Agent
{
public:

    explicit GameUpdater(sptr<render::Renderer> io_Renderer, double i_TargetFPS = 60.);
    ~GameUpdater() override;

    bool handleEvent(ALLEGRO_EVENT i_Event) override;

protected:

    virtual bool tick() = 0;

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

    sptr<render::Renderer> m_Renderer;

private:

    ALLEGRO_TIMER *        m_Ticker;
};

}}

#endif // ALPP_EVENT_GAME_UPDATER