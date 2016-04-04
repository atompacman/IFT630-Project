#ifndef PLH_WORKSHOP
#define PLH_WORKSHOP

// alpp
#include <Core.h>

// plh
#include <ResourceStack.h>
#include <Worker.h>

// std
#include <list>

namespace alpp { namespace render {

class Renderer;

}}

class Workshop : public std::enable_shared_from_this<Workshop>
{
public:

    explicit Workshop(WorkshopCoords i_Pos, CardinalDir i_OutputStackSide);

    void addWorker(double i_Speed);

    void moveOutputStack (CardinalDir i_Side);
    void addInputStack   (CardinalDir i_Side);
    void removeInputStack(CardinalDir i_Side);
    bool hasStack        (CardinalDir i_Side) const;

    std::list<sptr<ResourceStack>> getInputStacks() const;
    sptr<ResourceStack>            getOutputStack() const;

    sptr<ResourceStack>            getStack(CardinalDir i_Side) const;

    PixelCoords getUpperLeftPixelPos() const;

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

    std::string toString() const;

private:

    void addStack   (CardinalDir i_Side, ResourceStack::Type i_Type);
    void removeStack(CardinalDir i_Side);

    WorkshopCoords            m_Pos;
    sptr<ResourceStack>       m_ResourceStacks[4];
    CardinalDir               m_OutputStackSide;
    std::vector<sptr<Worker>> m_Workers;
};

#endif // PLH_WORKSHOP