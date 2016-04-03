#ifndef PLH_WORKSHOP
#define PLH_WORKSHOP

// alpp
#include <Core.h>
#include <ResourceStack.h>

namespace alpp { namespace render {

class Renderer;

}}

enum class StackPosition
{
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST  = 3,
};

class Workshop
{
public:

    explicit Workshop(uint16_t i_X, uint16_t i_Y);

    void addResourceStack(StackPosition i_Position, ResourceStack::Type i_Type);

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    uint16_t m_X;
    uint16_t m_Y;

    sptr<ResourceStack> m_ResourceStacks[4];
};

#endif // PLH_WORKSHOP