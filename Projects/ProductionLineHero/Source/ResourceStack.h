#ifndef PLH_RESOURCE_STACK
#define PLH_RESOURCE_STACK

// alpp
#include <Core.h>

// plh
#include <Common.h>
#include <Resource.h>

// std
#include <mutex>

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

    explicit ResourceStack(Type           i_Type, 
                           WorkshopCoords i_Pos, 
                           CardinalDir    i_Side, 
                           Resource       i_ResourceArchetype);

    Resource poll();
    void     push();

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

    Type        type()           const { return m_Type;      };
    PixelCoords centerPosition() const { return m_Pos;       };
    uint32_t    numResources()   const { return m_StackSize; };

private:

    Type        m_Type;
    PixelCoords m_Pos;
    Resource    m_ResourceArchetype;
    uint32_t    m_StackSize;

    std::mutex              m_Mutex;
    std::condition_variable m_WaitingList;
};

#endif // PLH_RESOURCE_STACK