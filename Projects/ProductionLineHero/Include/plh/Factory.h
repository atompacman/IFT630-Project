#ifndef PLH_FACTORY
#define PLH_FACTORY

#include <plh/Workshop.h>
#include <plh/Treadmill.h>

class Factory
{
public:

    explicit Factory();

    sptr<Workshop> buildWorkshop(WorkshopCoords i_Pos, CardinalDir i_OutputStackSide);
    sptr<Workshop> getWorkshop  (WorkshopCoords i_Pos) const;
    bool           hasWorkshopAt(WorkshopCoords i_Pos) const;

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    static uint16_t const MAX_NUM_TREADMILLS = 2 * MAX_NUM_WORKSHOPS_X * MAX_NUM_WORKSHOPS_Y -
                                                (MAX_NUM_WORKSHOPS_X + MAX_NUM_WORKSHOPS_Y);

    static uint16_t linearize(WorkshopCoords i_Pos);
    static uint16_t linearizeTreadmill(WorkshopCoords i_Pos, CardinalDir i_Dir);

    void connectToAdjacentWorkshopIfPossible(WorkshopCoords i_Pos, CardinalDir i_Dir);

    sptr<Workshop>  m_Workshops [MAX_NUM_WORKSHOPS_X * MAX_NUM_WORKSHOPS_Y];
    sptr<Treadmill> m_Treadmills[MAX_NUM_TREADMILLS];
};

#endif // PLH_FACTORY