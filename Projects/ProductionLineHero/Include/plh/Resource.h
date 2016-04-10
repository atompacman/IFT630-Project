#ifndef PLH_RESOURCE
#define PLH_RESOURCE

#include <allegro5/color.h>

#include <plh/Common.h>

#include <list>

namespace alpp { namespace render {

    class Renderer;

}}

class Resource
{
public:

    Resource() :
        m_RaffinementLvl(0)
    {}

    virtual ~Resource() { };

    void raffine() { ++m_RaffinementLvl; }

    void render(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos) const;

    virtual void render(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos, uint8_t i_ScaleLvl) const = 0;

protected:

    void drawRaffinment(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos, uint8_t i_ScaleLvl) const;

    uint8_t m_RaffinementLvl;
};

class BasicResource : public Resource
{
public:

    BasicResource(ALLEGRO_COLOR i_Color) :
        m_Color(i_Color)
    {}

    void render(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos, uint8_t i_ScaleLvl) const;

private:

    ALLEGRO_COLOR m_Color;
};

class CompositeResource : public Resource
{
public:

    CompositeResource(std::list<sptr<Resource>> const & i_Components) :
        m_SubResource()
    {
        LOG_IF(i_Components.size() != 2 && i_Components.size() != 3, FATAL) <<
            "Can only create composite resources from 2 or 3 components";
        auto i = 0;
        for (auto component : i_Components)
        {
            m_SubResource[i++] = component;
        }
    }

    void render(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos, uint8_t i_ScaleLvl) const;

private:

    sptr<Resource> m_SubResource[3];
};

#endif // PLH_RESOURCE