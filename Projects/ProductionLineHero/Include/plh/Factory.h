#ifndef PLH_FACTORY
#define PLH_FACTORY

#include <alpp/Core.h>

#include <plh/Common.h>
#include <plh/Workshop.h>

#include <cstdint>

class Factory
{
public:

    explicit Factory();

    sptr<Workshop> buildWorkshop(WorkshopCoords i_Pos, CardinalDir i_OutputStackSide);
    sptr<Workshop> getWorkshop  (WorkshopCoords i_Pos) const;
    bool           hasWorkshopAt(WorkshopCoords i_Pos) const;

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    static uint16_t linearize(WorkshopCoords i_Pos);

    sptr<Workshop> m_Workshops[MAX_NUM_WORKSHOPS_X * MAX_NUM_WORKSHOPS_Y];
};

#endif // PLH_FACTORY