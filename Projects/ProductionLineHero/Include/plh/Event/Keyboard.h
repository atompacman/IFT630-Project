#ifndef PLH_EVENT_KEYBOARD
#define PLH_EVENT_KEYBOARD

#include <alpp/Event/Keyboard.h>

#include <easylogging++.h>

namespace alpp { namespace render {

class Camera;

}}

class Keyboard : public alpp::event::Keyboard
{
public:

    explicit Keyboard(sptr<alpp::render::Camera> io_Camera) :
        alpp::event::Keyboard(),
        m_Camera(io_Camera)
    {}

protected:

    bool onCharacterTyped(uint8_t i_Key) override;

private:

    sptr<alpp::render::Camera> m_Camera;
};

#endif // PLH_EVENT_KEYBOARD