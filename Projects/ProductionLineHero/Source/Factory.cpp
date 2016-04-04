// el
#include <easylogging++.h>

// plh
#include <Factory.h>
#include <Workshop.h>

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
    LOG_IF(!(i_Pos <= MAX_NUM_WORKSHOPS), FATAL)
        << "Invalid workshop position (" << i_Pos.x << ", " << i_Pos.y << ")";
    return i_Pos.x + i_Pos.y * MAX_NUM_WORKSHOPS_X;
}