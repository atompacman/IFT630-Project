#ifndef ALPP_RENDER_CAMERA
#define ALPP_RENDER_CAMERA

#include <alpp/Core.h>

#include <allegro5/transformations.h>

#include <aplib/Bounds.h>

namespace alpp { namespace render {

/*================================================================================================\\
| Manages info needed to generate the 2D transform used by Allegro to simulate an interactive camera
|--------------------------------------------------------------------------------------------------|
| Exposes camera parameter setters, getters and the getTransform method.
\=================================================================================================*/

class Camera
{
public:

    explicit Camera(float i_MinZoomLvl = DEFAULT_MIN_ZOOM_LVL, 
                    float i_MaxZoomLvl = DEFAULT_MAX_ZOOM_LVL) :
        m_Position   (),
        m_Zoom       (1),
        m_Rotation   (0),
        m_ZoomLimits (i_MinZoomLvl, i_MaxZoomLvl),
        m_Transform  () {}

    void translate (WorldCoords i_Delta) { m_Position += i_Delta; }
    void rotate    (float       i_Delta) { m_Rotation += i_Delta; }    
    void adjustZoom(float       i_Delta) { m_Zoom      = m_ZoomLimits.clamp(m_Zoom + i_Delta); }

    float getZoom() const { return m_Zoom; }

    WorldCoords getPosition() const { return m_Position; }

    ALLEGRO_TRANSFORM * getTransform(PixelDimensions i_WindowSize) const
    {
        al_identity_transform (&m_Transform);
        al_translate_transform(&m_Transform, -m_Position.x, -m_Position.y);
        al_rotate_transform   (&m_Transform, m_Rotation);
        al_scale_transform    (&m_Transform, m_Zoom, m_Zoom);
        al_translate_transform(&m_Transform, i_WindowSize.x * 0.5, i_WindowSize.y * 0.5);
        return &m_Transform;
    }

private:

    static float constexpr DEFAULT_MIN_ZOOM_LVL = 0.1f;
    static float constexpr DEFAULT_MAX_ZOOM_LVL = 2.f;

    WorldCoords m_Position;
    float       m_Zoom;
    float       m_Rotation;

    Bounds<float> m_ZoomLimits;

    ALLEGRO_TRANSFORM mutable m_Transform;
};

}}

#endif // ALPP_RENDER_CAMERA