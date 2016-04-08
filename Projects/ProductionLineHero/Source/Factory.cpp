#include <alpp/Render/Command.h>

#include <plh/Factory.h>
#include <plh/Workshop.h>

Factory::Factory() :
    m_Workshops()
{

}

sptr<Workshop> Factory::buildWorkshop(WorkshopCoords i_Pos, CardinalDir i_OutputStackSide)
{
    LOG_IF(hasWorkshopAt(i_Pos), FATAL) << "Cannot build a workshop at ("
        << i_Pos.x << ", " << i_Pos .y << "): there's already one there";

    // Build workshop
    auto workshop = std::make_shared<Workshop>(i_Pos, i_OutputStackSide);
    m_Workshops[linearize(i_Pos)] = workshop;
    
    // Place threadmills and resource stacks where possible

    // Up
    auto up = incremented(i_Pos, Dir2DWithDiag::UP);
    if (i_Pos.y > 0 && hasWorkshopAt(up))
    {
        auto otherWorkshop = getWorkshop(up);
        if (i_OutputStackSide == CardinalDir::NORTH)
        {
            if (!otherWorkshop->hasStack(CardinalDir::SOUTH))
            {
                auto stack = otherWorkshop->addInputStack(CardinalDir::SOUTH);
                auto threadmill = std::make_shared<Threadmill>(workshop->getOutputStack(), stack);
                m_Threadmills[linearizeThreadmill(up, true)] = threadmill;
            }
        }
        else if (otherWorkshop->hasStack(CardinalDir::SOUTH))
        {
            auto stack = workshop->addInputStack(CardinalDir::NORTH);
            auto threadmill = std::make_shared<Threadmill>(otherWorkshop->getOutputStack(), stack);
            m_Threadmills[linearizeThreadmill(up, true)] = threadmill;
        }



        auto newStack = workshop->addInputStack(CardinalDir::NORTH);
        auto threadmill = std::make_shared<Threadmill>(otherWorkshop->getOutputStack(), newStack);
        m_Threadmills[linearizeThreadmill(up, true)] = threadmill;



    }



    return workshop;
}

void Factory::connectToAdjacentWorkshopIfPossible(WorkshopCoords i_Pos, CardinalDir i_Dir)
{
    // Get adjacent position
    auto adjPos = incremented(i_Pos, Dir2DWithDiag(i_Dir));

    // Exit if it is outside the factory
    if (!(adjPos <= MAX_NUM_WORKSHOPS))
    {
        return;
    }

    // Exit if there is no adjacent workshop
    if (!hasWorkshopAt(adjPos))
    {
        return;
    }

    // Get new and adjacent workshop
    auto newWS = getWorkshop(i_Pos);
    auto adjWS = getWorkshop(adjPos);

    // Get stack of adjacent workshop that could be connected
    auto oppDir = CardinalDir(oppositeOf(Dir2DWithDiag(i_Dir)));
    auto adjStack = adjWS->hasStack(oppDir) ? adjWS->getStack(oppDir) : nullptr;

    // If new workshop has an output stack in the direction of the adjacent workshop
    if (newWS->outputStackSide() == i_Dir)
    {
        // If adjacent workshop also has an output stack, then don't connect two output stacks
        if (!adjStack)
        {

        }
    }
    // If adjacent workshop has an output stack that needs to be connected to the new workshop
    else if (adjStack)
    {
        
    }
}

sptr<Workshop> Factory::getWorkshop(WorkshopCoords i_Pos) const
{
    return m_Workshops[linearize(i_Pos)];
}

bool Factory::hasWorkshopAt(WorkshopCoords i_Pos) const
{
    return m_Workshops[linearize(i_Pos)] != nullptr;
}

void Factory::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    // Render factory floor
    WorldCoords factoryBorders(SPACE_BETWEEN_WORKSHOPS, SPACE_BETWEEN_WORKSHOPS);
    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->UpperLeftPos  = workshopCoordsToWorldCoordsULCorner(WorkshopCoords(0, 0)) - factoryBorders;
    cmd->LowerRightPos = workshopCoordsToWorldCoordsULCorner(MAX_NUM_WORKSHOPS - 
        WorkshopCoords(1, 1)) + WORKSHOP_SIZE_PXL + SPACE_BETWEEN_WORKSHOPS;
    cmd->Color = al_map_rgb(30, 30, 30);
    i_Renderer->enqueueCommand(cmd);

    // Render workshops
    for (auto workshop : m_Workshops)
    {
        if (workshop)
        {
            workshop->render(i_Renderer);
        }
    }

    // Render threadmills
    for (auto threadmill : m_Threadmills)
    {
        if (threadmill)
        {
            threadmill->render(i_Renderer);
        }
    }
}

uint16_t Factory::linearize(WorkshopCoords i_Pos)
{
    checkWorkshopCoords(i_Pos);
    return i_Pos.x + i_Pos.y * MAX_NUM_WORKSHOPS_X;
}

uint16_t Factory::linearizeThreadmill(WorkshopCoords i_Pos, bool i_IsDown)
{
    LOG_IF(i_IsDown  && i_Pos.y == MAX_NUM_WORKSHOPS_Y, FATAL) << "There is no threadmill down";
    LOG_IF(!i_IsDown && i_Pos.x == MAX_NUM_WORKSHOPS_X, FATAL) << "There is no threadmill right";

    if (i_IsDown)
    {
        return MAX_NUM_WORKSHOPS.area() - MAX_NUM_WORKSHOPS_Y + linearize(i_Pos) - i_Pos.y;
    }

    return linearize(i_Pos) - i_Pos.y;
}