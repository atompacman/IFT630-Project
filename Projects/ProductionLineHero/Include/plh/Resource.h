#ifndef PLH_RESOURCE
#define PLH_RESOURCE

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

    virtual sptr<Resource> copy() = 0;

    void raffine() { ++m_RaffinementLvl; }

    void render(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos) const;

    virtual void render(sptr<alpp::render::Renderer> i_Renderer, 
                        WorldCoords                  i_Pos, 
                        uint8_t                      i_ScaleLvl) const = 0;

protected:

    void drawRaffinment(sptr<alpp::render::Renderer> i_Renderer, 
                        WorldCoords                  i_Pos, 
                        uint8_t                      i_ScaleLvl) const;

    uint8_t m_RaffinementLvl;
};

class BasicResource : public Resource
{
public:

    BasicResource(uint8_t i_ColorID) :
        m_ColorID(i_ColorID)
    {}

    sptr<Resource> copy() override
    {
        return std::make_shared<BasicResource>(m_ColorID);
    }

    void render(sptr<alpp::render::Renderer> i_Renderer, 
                WorldCoords                  i_Pos, 
                uint8_t                      i_ScaleLvl) const override;

private:

    uint8_t m_ColorID;
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
            m_SubResource[i++] = component->copy();
        }
    }

    CompositeResource(sptr<Resource> * i_SubResource) :
        m_SubResource()
    {
        for (auto i = 0; i < 3; ++i)
        {
            if (i_SubResource[i])
            {
                m_SubResource[i] = i_SubResource[i]->copy();
            }
        }
    }

    sptr<Resource> copy() override
    {
        return std::make_shared<CompositeResource>(&m_SubResource[0]);
    }

    void render(sptr<alpp::render::Renderer> i_Renderer, 
                WorldCoords                  i_Pos, 
                uint8_t                      i_ScaleLvl) const override;

private:

    sptr<Resource> m_SubResource[3];
};

#endif // PLH_RESOURCE