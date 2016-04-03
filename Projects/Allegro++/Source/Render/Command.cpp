// allegro
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// alpp
#include <Render/Command.h>

void alpp::render::ResizeWindow::execute()
{
    al_acknowledge_resize(Window);
}

void alpp::render::DrawFilledCircle::execute()
{
    al_draw_filled_circle(CenterPosX, CenterPosY, Radius, Color);
}

void alpp::render::DrawFilledRectangle::execute()
{
    al_draw_filled_rectangle(PosLeft, PosTop, PosRight, PosBottom, Color);
}

void alpp::render::DrawText::execute()
{
    al_draw_text(Font, Color, PosX, PosY, 0, Text.c_str());
}