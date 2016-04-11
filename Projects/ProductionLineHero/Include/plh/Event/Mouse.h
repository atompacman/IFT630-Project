#ifndef PLH_EVENT_MOUSE
#define PLH_EVENT_MOUSE

#include <alpp/Event/Mouse.h>

class GameLoop;

class Mouse : public alpp::event::Mouse
{
public:

    explicit Mouse(sptr<GameLoop> i_Game) :
        alpp::event::Mouse(500),
        m_GameObject(i_Game)
    {}

protected:

    void onScroll()     override;
    void onLeftClick()  override;
    void onMouseMoved() override;

    sptr<GameLoop> m_GameObject;
};

#endif // PLH_EVENT_MOUSE