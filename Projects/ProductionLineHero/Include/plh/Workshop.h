#ifndef PLH_WORKSHOP
#define PLH_WORKSHOP

#include <alpp/Core.h>

#include <plh/ResourceStack.h>
#include <plh/Worker.h>

#include <list>

namespace alpp { namespace render {

class Renderer;

}}

/*================================================================================================\\
| Basic building blocks of the factory
|--------------------------------------------------------------------------------------------------|
| Can hold any number of workers that gather resource from up to 3 input resource stacks attached to
| the workshop put a resulting product in the output stack.
\=================================================================================================*/

class Workshop : public std::enable_shared_from_this<Workshop>
{
public:

    explicit Workshop(WorkshopCoords i_Pos, CardinalDir i_OutputStackSide);

    void addWorker(double i_Speed);

    void                moveOutputStack  (CardinalDir i_Side);
    sptr<ResourceStack> addInputStack    (CardinalDir i_Side);
    void                removeInputStack (CardinalDir i_Side);

    bool hasStack(CardinalDir i_Side) const;

    std::list<sptr<ResourceStack>> getInputStacks() const;
    sptr<ResourceStack>            getOutputStack() const { return getStack(m_OutputStackSide); }

    sptr<ResourceStack>            getStack(CardinalDir i_Side) const;

    WorldCoords upperLeftPixelPos() const { return workshopCoordsToWorldCoordsULCorner(m_Pos); }
    
    CardinalDir outputStackSide() const { return m_OutputStackSide; };

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

    std::string toString() const;

private:

    sptr<ResourceStack> addStack(CardinalDir i_Side, ResourceStack::Type i_Type);

    void removeStack(CardinalDir i_Side);

    WorkshopCoords            m_Pos;
    sptr<ResourceStack>       m_ResourceStacks[4];
    CardinalDir               m_OutputStackSide;
    std::vector<sptr<Worker>> m_Workers;
};

#endif // PLH_WORKSHOP