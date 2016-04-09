#ifndef PLH_EVENT_MOUSE
#define PLH_EVENT_MOUSE

#include <alpp/Event/Mouse.h>

class Mouse : public alpp::event::Mouse
{
public:

    explicit Mouse() :
        alpp::event::Mouse(500)
    {}

protected:

    void onScroll() override;
};

#endif // PLH_EVENT_MOUSE