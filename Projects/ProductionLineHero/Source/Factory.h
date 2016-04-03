#ifndef PLH_FACTORY
#define PLH_FACTORY

// alpp
#include <Core.h>

// plh
#include <Workshop.h>

// std
#include <cstdint>
#include <Settings.h>

class Factory
{
public:

    explicit Factory();

    sptr<Workshop> buildWorkshop(uint16_t i_X, uint16_t i_Y);

    bool hasWorkshopAt(uint16_t i_X, uint16_t i_Y) const;

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    static uint16_t linearizeWorkshopPos(uint16_t i_X, uint16_t i_Y);


    sptr<Workshop> m_Workshops[MAX_NUM_WORKSHOP_Y * MAX_NUM_WORKSHOP_X];
};

#endif // PLH_FACTORY