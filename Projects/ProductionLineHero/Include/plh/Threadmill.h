#ifndef PLH_THREADMILL
#define PLH_THREADMILL

#include <alpp/Core.h>
#include <alpp/Render/Renderer.h>

#include <plh/Common.h>
#include <plh/ResourceStack.h>

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
    WorldCoords          m_ResourcePos;
};

#endif // PLH_THREADMILL