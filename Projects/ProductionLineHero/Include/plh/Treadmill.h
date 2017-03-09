#ifndef PLH_TREADMILL
#define PLH_TREADMILL

#include <plh/ResourceStack.h>

class Workshop;

// Represents the treadmill linking 2 workshops together with which resources are transfered
class Treadmill
{
public:

    explicit Treadmill(sptr<ResourceStack> i_Source, sptr<ResourceStack> i_Destination);
    ~Treadmill();

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    void runThreadmillThread(); // run the treadmill thread

    sptr<ResourceStack> m_SrcStack;     // Source stack
    sptr<ResourceStack> m_DestStack;    // Destination stack
    sptr<Resource>      m_MovingResource;   // Resource moving on the treadmill
    WorldCoords         m_ResourcePos;      // Position of the resource
};

#endif // PLH_TREADMILL