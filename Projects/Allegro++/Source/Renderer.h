#ifndef ALLEGROPP_RENDERER
#define ALLEGROPP_RENDERER

#include <WindowSettings.h>

namespace alpp
{

class GameLoop;

class Renderer
{
    friend GameLoop;

public:

    explicit Renderer(WindowSettings const & i_WinSettings, double i_TargetFPS = 60.);
    ~Renderer();

    bool wasInitSuccessful() const;

private:

    ALLEGRO_DISPLAY * m_Window;
    double            m_TargetFPS;

    bool m_InitSuccess;
};

}

#endif // ALLEGROPP_RENDERER 