#ifndef PLH_WORKSHOP
#define PLH_WORKSHOP

// alpp
#include <Core.h>

namespace alpp { namespace render {

class Renderer;

}}

class Workshop
{
public:

    explicit Workshop(uint16_t i_X, uint16_t i_Y);

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    static uint16_t const SIZE_PXL = 150;

    uint16_t m_X;
    uint16_t m_Y;
};

#endif // PLH_WORKSHOP