#ifndef PLH_EVENT_GAME_LOOP
#define PLH_EVENT_GAME_LOOP

#include <alpp/Event/Gameloop.h>

#include <plh/Factory.h>

class GameLoop : public alpp::event::GameLoop
{
public:

    explicit GameLoop(alpp::render::WindowSettings i_WinSettings);

protected:

    bool tick() override;

private:

    Factory m_Factory;
};

#endif // PLH_EVENT_GAME_LOOP