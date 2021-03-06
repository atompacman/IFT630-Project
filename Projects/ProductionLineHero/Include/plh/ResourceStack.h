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

// Represents a workshop resource stack, which can be an input or an output to another workshop
class ResourceStack
{
public:

    enum class Type
    {
        INPUT,
        OUTPUT
    };

    explicit ResourceStack(Type i_Type, WorkshopCoords i_Pos, CardinalDir i_Side);

    sptr<Resource> pop();
    void           push(sptr<Resource> i_Resource);

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

    void setConnected()       { m_IsConnected = true; }
    bool isConnected () const { return m_IsConnected; }

    Type           type()               const { return m_Type; };
    WorldCoords    centerPosition()     const { return m_Pos;  };
    uint32_t       numResources()       const { return static_cast<uint32_t>(m_Resources.size()); };
    sptr<Resource> lastPushedResource() const { return m_LastPushed; }

private:

    Type                       m_Type;
    WorldCoords                m_Pos;
    std::stack<sptr<Resource>> m_Resources;
    sptr<Resource>             m_LastPushed;
    bool                       m_IsConnected;
    std::mutex                 m_Mutex;     // Mutex to manage the worker access to the stack
    std::condition_variable    m_WaitingList;   // Condition variable used as a list of workers waiting for acces to the stack
};

#endif // PLH_RESOURCE_STACK