#ifndef PLH_EVENT_MOUSE
#define PLH_EVENT_MOUSE

#include <alpp/Event/Mouse.h>
class GameLoop;

class Mouse : public alpp::event::Mouse
{
public:

    explicit Mouse(sptr<GameLoop> game) :
        alpp::event::Mouse(500),
        m_GameObject(game),
        m_LeftPressed(false),
        m_RightPressed(false)
    {}

protected:

    void onScroll() override;
    void onLeftClick() override;
    void onLeftPressed() override;
    void onLeftReleased() override;
    void onRightPressed() override;
    void onRightReleased() override;
    void onMouseMoved() override;

    sptr<GameLoop> m_GameObject;
    bool m_LeftPressed;
    bool m_RightPressed;
};

#endif // PLH_EVENT_MOUSE