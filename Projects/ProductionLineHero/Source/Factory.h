// alpp
#include <Core.h>

// plh
#include <Workshop.h>

// std
#include <cstdint>

class Factory
{
public:

    static uint16_t const WORKSHOP_BORDER_WIDTH = 60;

    explicit Factory();

    void buildWorkshop(uint16_t i_X, uint16_t i_Y);

    bool hasWorkshopAt(uint16_t i_X, uint16_t i_Y) const;

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    static uint16_t linearizeWorkshopPos(uint16_t i_X, uint16_t i_Y);

    static uint16_t const MAX_NUM_WORKSHOP_X = 6;
    static uint16_t const MAX_NUM_WORKSHOP_Y = 4;

    sptr<Workshop> m_Workshops[MAX_NUM_WORKSHOP_Y * MAX_NUM_WORKSHOP_X];
};