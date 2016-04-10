#ifndef PLH_EVENT_GAME_LOOP
#define PLH_EVENT_GAME_LOOP

#include <alpp/Event/Gameloop.h>

#include <plh/Factory.h>
#include <vector>

class UIElement;

class GameLoop : public alpp::event::GameLoop
{
public:

    explicit GameLoop(alpp::render::WindowSettings i_WinSettings);

protected:

    bool tick() override;
    void InitUI(alpp::render::WindowSettings i_WinSettings);
    void RenderUI();

private:

    Factory m_Factory;
    std::vector<UIElement*> m_UI;
};

#endif // PLH_EVENT_GAME_LOOP