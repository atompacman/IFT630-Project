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
    
    // Place treadmills and resource stacks where possible
    connectToAdjacentWorkshopIfPossible(i_Pos, CardinalDir::NORTH);
    connectToAdjacentWorkshopIfPossible(i_Pos, CardinalDir::EAST);
    connectToAdjacentWorkshopIfPossible(i_Pos, CardinalDir::SOUTH);
    connectToAdjacentWorkshopIfPossible(i_Pos, CardinalDir::WEST);

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
            auto newStack = adjWS->addInputStack(oppDir);
            auto treadmill = std::make_shared<Treadmill>(newWS->getOutputStack(), newStack);
            m_Treadmills[linearizeTreadmill(i_Pos, i_Dir)] = treadmill;
        }
    }
    // If adjacent workshop has an output stack that needs to be connected to the new workshop
    else if (adjStack && adjStack->type() == ResourceStack::Type::OUTPUT)
    {
        auto newStack = newWS->addInputStack(i_Dir);
        auto treadmill = std::make_shared<Treadmill>(adjStack, newStack);
        m_Treadmills[linearizeTreadmill(i_Pos, i_Dir)] = treadmill;
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

    // Render treadmills
    for (auto threadmill : m_Treadmills)
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

uint16_t Factory::linearizeTreadmill(WorkshopCoords i_Pos, CardinalDir i_Dir)
{
    if (i_Dir == CardinalDir::NORTH)
    {
        --i_Pos.y;
    }
    else if (i_Dir == CardinalDir::WEST)
    {
        --i_Pos.x;
    }

    bool isVertical = i_Dir == CardinalDir::NORTH || i_Dir == CardinalDir::SOUTH;

    LOG_IF( isVertical && i_Pos.y >= MAX_NUM_WORKSHOPS_Y - 1, FATAL) << "There is no treadmill down";
    LOG_IF(!isVertical && i_Pos.x >= MAX_NUM_WORKSHOPS_X - 1, FATAL) << "There is no treadmill right";

    return isVertical ? MAX_NUM_WORKSHOPS.area() - MAX_NUM_WORKSHOPS_Y + linearize(i_Pos) : linearize(i_Pos) - i_Pos.y;
}