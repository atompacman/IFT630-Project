#ifndef PLH_RESOURCE_STACK
#define PLH_RESOURCE_STACK

// alpp
#include <Core.h>

// plh
#include <Resource.h>

// std
#include <stack>

namespace alpp { namespace render {

class Renderer;

}}

enum class StackPosition;

class ResourceStack
{
public:

    enum class Type
    {
        INPUT,
        OUTPUT
    };

    explicit ResourceStack(Type i_Type);

    void render(sptr<alpp::render::Renderer> i_Renderer,
                uint16_t                     i_WorkshopPosX,
                uint16_t                     i_WorkshopPosY,
                StackPosition                i_StackPos) const;

private:

    Type                 m_Type;
    std::stack<Resource> m_Stack;
};

#endif // PLH_RESOURCE_STACK