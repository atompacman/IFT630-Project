#ifndef PLH_TREADMILL
#define PLH_TREADMILL

#include <plh/ResourceStack.h>

class Workshop;

class Treadmill
{
public:

    explicit Treadmill(sptr<ResourceStack> i_Source, sptr<ResourceStack> i_Destination);
    ~Treadmill();

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    void runThreadmillThread();

    sptr<ResourceStack> m_SrcStack;
    sptr<ResourceStack> m_DestStack;
    sptr<Resource>      m_MovingResource;
    WorldCoords         m_ResourcePos;
};

#endif // PLH_TREADMILL