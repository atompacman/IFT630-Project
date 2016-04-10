#ifndef PLH_UIELEMENT
#define PLH_UIELEMENT

#include <alpp/Core.h>
#include <alpp/Render/Renderer.h>

class UIElement
{
public:
    UIElement();
    UIElement(PixelCoords position, PixelCoords size);
    virtual void render(sptr<alpp::render::Renderer> i_Renderer) const = 0;
    ~UIElement();

protected:
    PixelCoords m_Pos;
    PixelCoords m_Size;
};

UIElement::UIElement() :
    m_Pos(0, 0),
    m_Size(0, 0)
{};

UIElement::UIElement(PixelCoords position, PixelCoords size) :
    m_Pos(position),
    m_Size(size)
{};


#endif // PLH_UIELEMENT