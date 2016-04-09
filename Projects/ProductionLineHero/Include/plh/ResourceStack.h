#ifndef PLH_RESOURCE_STACK
#define PLH_RESOURCE_STACK

#include <alpp/Core.h>

#include <plh/Common.h>
#include <plh/Resource.h>

#include <mutex>
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

    Resource pop();
    void     push(Resource const & i_Resource);

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

    Type        type()           const { return m_Type;             };
    WorldCoords centerPosition() const { return m_Pos;              };
    uint32_t    numResources()   const { return static_cast<uint32_t>(m_Resources.size()); };

private:

    Type                    m_Type;
    WorldCoords             m_Pos;
    std::stack<Resource>    m_Resources;
    std::mutex              m_Mutex;
    std::condition_variable m_WaitingList;
};

#endif // PLH_RESOURCE_STACK