#ifndef PLH_THREADMILL
#define PLH_THREADMILL

// alpp
#include <Core.h>
#include <Render/Renderer.h>

// plh
#include <Common.h>
#include <ResourceStack.h>

class Workshop;

class Threadmill
{
public:

    explicit Threadmill(sptr<ResourceStack> i_Source, sptr<ResourceStack> i_Destination);
    ~Threadmill();

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    void runThreadmillThread();

    sptr<ResourceStack> m_SrcStack;
    sptr<ResourceStack> m_DestStack;
    Resource            m_MovingResource;
    RealCoords          m_ResourcePos;
};

#endif // PLH_THREADMILL