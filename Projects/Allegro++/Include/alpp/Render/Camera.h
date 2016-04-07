#ifndef ALPP_RENDER_CAMERA
#define ALPP_RENDER_CAMERA

#include <alpp/Core.h>

#include <allegro5/transformations.h>

namespace alpp { namespace render {

class Camera
{
public:

    explicit Camera() :
        m_Position (),
        m_Zoom     (1),
        m_Rotation (0),
        m_Transform() {}

    void translate (WorldCoords i_Delta) { m_Position += i_Delta; }
    void rotate    (float i_Delta)       { m_Rotation += i_Delta; }
    void adjustZoom(float i_Delta)       { m_Zoom     += i_Delta; }

    void applyTransform(PixelDimensions i_WindowSize)
    {
        al_identity_transform (&m_Transform);
        al_translate_transform(&m_Transform, -m_Position.x, -m_Position.y);
        al_rotate_transform   (&m_Transform, m_Rotation);
        al_scale_transform    (&m_Transform, m_Zoom, m_Zoom);
        al_translate_transform(&m_Transform, i_WindowSize.x * 0.5, i_WindowSize.y * 0.5);
        al_use_transform      (&m_Transform);
    }

private:

    WorldCoords m_Position;
    float       m_Zoom;
    float       m_Rotation;

    ALLEGRO_TRANSFORM m_Transform;
};

}}

#endif // ALPP_RENDER_CAMERA