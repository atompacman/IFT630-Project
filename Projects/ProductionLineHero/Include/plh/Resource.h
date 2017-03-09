#ifndef PLH_RESOURCE
#define PLH_RESOURCE

#include <plh/Common.h>

#include <list>

namespace alpp { namespace render {

class Renderer;

}}

// Represents a resource, which can be raffined or mixed with another (composite)
class Resource
{
public:

    explicit Resource() :
        m_RaffinementLvl(0)
    {}

    virtual ~Resource() { };

    virtual sptr<Resource> copy() = 0;

    void raffine() { ++m_RaffinementLvl; }

    void render(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos) const;

    virtual void render(sptr<alpp::render::Renderer> i_Renderer, 
                        WorldCoords                  i_Pos, 
                        uint8_t                      i_ScaleLvl) const = 0;

    virtual Dollar worth() const = 0;

protected:

    uint8_t m_RaffinementLvl;
};

class BasicResource : public Resource
{
public:

    explicit BasicResource(uint8_t i_ColorID) :
        Resource(),
        m_ColorID(i_ColorID)
    {}

    sptr<Resource> copy() override
    {
        auto copy = std::make_shared<BasicResource>(m_ColorID);
        copy->m_RaffinementLvl = m_RaffinementLvl;
        return copy;
    }

    void render(sptr<alpp::render::Renderer> i_Renderer, 
                WorldCoords                  i_Pos, 
                uint8_t                      i_ScaleLvl) const override;

    Dollar worth() const override;

private:

    uint8_t m_ColorID;
};

class CompositeResource : public Resource
{
public:

    explicit CompositeResource(std::list<sptr<Resource>> const & i_Components) :
        Resource(),
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

    explicit CompositeResource(sptr<Resource> * i_SubResource) :
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
        auto copy = std::make_shared<CompositeResource>(&m_SubResource[0]);
        copy->m_RaffinementLvl = m_RaffinementLvl;
        return copy;
    }

    void render(sptr<alpp::render::Renderer> i_Renderer, 
                WorldCoords                  i_Pos, 
                uint8_t                      i_ScaleLvl) const override;

    Dollar worth() const override;

private:

    sptr<Resource> m_SubResource[3];
};

#endif // PLH_RESOURCE