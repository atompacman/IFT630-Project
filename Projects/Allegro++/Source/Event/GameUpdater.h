#ifndef ALPP_EVENT_GAME_UPDATER
#define ALPP_EVENT_GAME_UPDATER

#include <event/Agent.h>
#include <allegro5/timer.h>

namespace alpp { namespace event {

class GameUpdater : public Agent
{
public:

    explicit GameUpdater(double i_TargetFPS = 60.);
    ~GameUpdater() override;

    bool handleEvent(ALLEGRO_EVENT i_Event) override;

protected:

    virtual bool tick() = 0;

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

private:

    ALLEGRO_TIMER * m_Ticker;
};

}}

#endif // ALPP_EVENT_GAME_UPDATER