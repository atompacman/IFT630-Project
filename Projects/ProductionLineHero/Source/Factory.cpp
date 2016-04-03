// el
#include <easylogging++.h>

// plh
#include <Factory.h>
#include <Workshop.h>

Factory::Factory() :
    m_Workshops()
{

}

uint16_t Factory::linearizeWorkshopPos(uint16_t i_X, uint16_t i_Y)
{
    LOG_IF(i_X >= MAX_NUM_WORKSHOP_X || i_Y >= MAX_NUM_WORKSHOP_Y, FATAL) 
        << "Invalid workshop position (" << i_X << ", " << i_Y << ")";
    return i_X + i_Y * MAX_NUM_WORKSHOP_X;
}

sptr<Workshop> Factory::buildWorkshop(uint16_t i_X, uint16_t i_Y)
{
    LOG_IF(hasWorkshopAt(i_X, i_Y), FATAL) << "Cannot build a workshop at (" 
        << i_X << ", " << i_Y << "): there's already one there";

    auto workshop = std::make_shared<Workshop>(i_X, i_Y);
    m_Workshops[linearizeWorkshopPos(i_X, i_Y)] = workshop;

    return workshop;
}

bool Factory::hasWorkshopAt(uint16_t i_X, uint16_t i_Y) const
{
    return m_Workshops[linearizeWorkshopPos(i_X, i_Y)] != nullptr;
}

void Factory::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    for (uint16_t i = 0; i < MAX_NUM_WORKSHOP_Y * MAX_NUM_WORKSHOP_X; ++i)
    {
        auto workshop = m_Workshops[i];
        if (workshop)
        {
            workshop->render(i_Renderer);
        }
    }
}