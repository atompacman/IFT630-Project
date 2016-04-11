#ifndef PLH_CREATION_BUTTON
#define PLH_CREATION_BUTTON

#include <plh\UIElement.h>
#include <plh/Common.h>

class CreationButton : public UIElement
{

public:
    CreationButton();
    CreationButton(WorldCoords position, WorldCoords size, UIElement * parent, ALLEGRO_COLOR color, CreatableRoomType objType);
    void render(sptr<alpp::render::Renderer> i_Renderer) const;
    CreatableRoomType getRoomType() { return m_RoomType; }

private:
    UIElement * m_ParentUI;
    ALLEGRO_COLOR m_Color;
    CreatableRoomType m_RoomType; // #TODO: rename


};

#endif // PLH_CREATION_BUTTON