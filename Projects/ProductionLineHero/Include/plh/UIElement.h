#ifndef PLH_UIELEMENT
#define PLH_UIELEMENT

#include <alpp/Core.h>
#include <alpp/Render/Renderer.h>
#include <alpp/Render/Command.h>

class UIElement
{
public:
    UIElement() :
    m_Pos(0, 0),
    m_Size(0, 0)
    {};

    UIElement(WorldCoords position, WorldCoords size) :
        m_Pos(position),
        m_Size(size)
    {};

    virtual void render(sptr<alpp::render::Renderer> i_Renderer) const = 0;
    bool isMouseInArea(PixelCoords mousePos) 
    {
        WorldCoords mouseWP(mousePos);
        if ((mouseWP.x >= m_Pos.x && mouseWP.x <= m_Pos.x + m_Size.x)
            && (mouseWP.y >= m_Pos.y && mouseWP.y <= m_Pos.y + m_Size.y))
        {
            return true;
        }

        return false;
    };

    ~UIElement();
    WorldCoords getPosition() { return m_Pos; };
    WorldCoords getSize() { return m_Size; };

    void setPositionAndSize(WorldCoords pos, WorldCoords size)
    {
        m_Pos = pos;
        m_Size = size;
    };

protected:
    WorldCoords m_Pos;
    WorldCoords m_Size;
};

#endif // PLH_UIELEMENT