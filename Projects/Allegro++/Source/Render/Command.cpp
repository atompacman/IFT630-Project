// allegro
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>

// alpp
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

alpp::render::DrawFilledRectangle::DrawFilledRectangle(float         i_PosLeft,
                                                       float         i_PosTop,
                                                       float         i_PosRight,
                                                       float         i_PosBottom,
                                                       ALLEGRO_COLOR i_Color) :
    Command(),
    m_PosLeft  (i_PosLeft),
    m_PosTop   (i_PosTop),
    m_PosRight (i_PosRight),
    m_PosBottom(i_PosBottom),
    m_Color    (i_Color)
{

}

void alpp::render::DrawFilledRectangle::execute()
{
    al_draw_filled_rectangle(m_PosLeft, m_PosTop, m_PosRight, m_PosBottom, m_Color);
}