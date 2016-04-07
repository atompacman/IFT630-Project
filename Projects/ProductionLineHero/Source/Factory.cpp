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

    auto workshop = std::make_shared<Workshop>(i_Pos, i_OutputStackSide);
    m_Workshops[linearize(i_Pos)] = workshop;

    return workshop;
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
    WorkshopCoords coord;
    for (coord.y = 0; coord.y < MAX_NUM_WORKSHOPS_Y; ++coord.y)
    {
        for (coord.x = 0; coord.x < MAX_NUM_WORKSHOPS_X; ++coord.x)
        {
            auto workshop = getWorkshop(coord);
            if (workshop)
            {
                workshop->render(i_Renderer);
            }
        }
    }
}

uint16_t Factory::linearize(WorkshopCoords i_Pos)
{
    checkWorkshopCoords(i_Pos);
    return i_Pos.x + i_Pos.y * MAX_NUM_WORKSHOPS_X;
}