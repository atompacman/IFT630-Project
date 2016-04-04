#ifndef PLH_RESOURCE_STACK
#define PLH_RESOURCE_STACK

// alpp
#include <Core.h>

// plh
#include <Common.h>
#include <Resource.h>

// std
#include <stack>

namespace alpp { namespace render {

class Renderer;

}}

enum class CardinalDir;

class ResourceStack
{
public:

    enum class Type
    {
        INPUT,
        OUTPUT
    };

    explicit ResourceStack(Type i_Type, WorkshopCoords i_Pos, CardinalDir i_Side);

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

    Type        type()                const;
    PixelCoords pixelCenterPosition() const;

private:

    WorkshopCoords       m_Pos;
    CardinalDir          m_Side;
    Type                 m_Type;
    std::stack<Resource> m_Stack;
};

#endif // PLH_RESOURCE_STACK