#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <Render/Command.h>

alpp::render::ResizeWindow::ResizeWindow(ALLEGRO_DISPLAY * io_Window):
    Command(),
    m_Window(io_Window)
{
    
}

void alpp::render::ResizeWindow::execute()
{
    al_acknowledge_resize(m_Window);
}

alpp::render::DrawFilledCircle::DrawFilledCircle(float         i_CenterPosX, 
                                                 float         i_CenterPosY, 
                                                 float         i_Radius, 
                                                 ALLEGRO_COLOR i_Color) :
    Command(),
    m_CenterPosX(i_CenterPosX),
    m_CenterPosY(i_CenterPosY),
    m_Radius    (i_Radius),
    m_Color     (i_Color)
{

}

void alpp::render::DrawFilledCircle::execute()
{
    al_draw_filled_circle(m_CenterPosX, m_CenterPosY, m_Radius, m_Color);
}