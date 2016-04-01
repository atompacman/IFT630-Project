#ifndef ALLEGROPP_GAMELOOP
#define ALLEGROPP_GAMELOOP

#include <allegro5/allegro.h>
#include <Renderer.h>

namespace alpp
{

class GameLoop
{
public:

    explicit GameLoop(Renderer & io_Renderer);

    bool run();

    bool wasInitSuccessful() const;

private:

    Renderer & m_Renderer;

    ALLEGRO_EVENT_QUEUE * m_EventQueue;
    ALLEGRO_TIMER       * m_RenderTimer;

    bool m_InitSuccess;
};

}

#endif // ALLEGROPP_GAMELOOP