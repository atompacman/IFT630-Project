#ifndef PLH_CREATION_BUTTON
#define PLH_CREATION_BUTTON

#include <plh/Common.h>
#include <plh/UIElement.h>

class CreationButton : public UIElement
{
public:

    CreationButton(WorldCoords       i_Position, 
                   WorldCoords       i_Size, 
                   UIElement *       i_Parent, 
                   ALLEGRO_COLOR     i_Color, 
                   CreatableObjectType i_ObjType);
    virtual ~CreationButton() { }

    void render(sptr<alpp::render::Renderer> i_Renderer) const override;

    CreatableObjectType getObjectType() const { return m_RoomType; }

private:

    UIElement *       m_ParentUI;
    CreatableObjectType m_RoomType; // #TODO: rename
};

#endif // PLH_CREATION_BUTTON