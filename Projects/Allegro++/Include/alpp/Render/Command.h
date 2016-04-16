#ifndef ALPP_RENDER_COMMAND
#define ALPP_RENDER_COMMAND

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

#include <alpp/Core.h>

namespace alpp { namespace render {

enum class Layer
{
    WORLD,
    UI,
    MAX
};

/*================================================================================================\\
| Rendering commands that can be enqueued by the Renderer
|--------------------------------------------------------------------------------------------------|
| Commands have an assigned layer: WORLD if the camera transform should be applied on the command
| and UI if it should not. UI commands are also rendered on top of the world commands.
\=================================================================================================*/

struct Command
{
    Layer Layer = Layer::WORLD;

    virtual ~Command() { }

    virtual void execute() = 0;
};

struct ResizeWindow : Command
{
    ALLEGRO_DISPLAY * Window;

    void execute() override
    {
        al_acknowledge_resize(Window);
    }
};

struct DrawLine : Command
{
    WorldCoords   BegPos;
    WorldCoords   EndPos;
    float         Thickness;
    ALLEGRO_COLOR Color;

    void execute() override
    {
        al_draw_line(BegPos.x + 0.5, BegPos.y + 0.5, EndPos.x + 0.5, 
                     EndPos.y + 0.5, Color, Thickness);
    }
};

struct DrawFilledTriangle : Command
{
    WorldCoords   Points[3];
    ALLEGRO_COLOR Color;

    void execute() override
    {
        al_draw_filled_triangle(Points[0].x + 0.5, Points[0].y + 0.5, Points[1].x + 0.5, 
                                Points[1].y + 0.5, Points[2].x + 0.5, Points[2].y + 0.5, Color);
    }
};

struct DrawFilledCircle : Command
{
    WorldCoords   CenterPos;
    float         Radius;
    ALLEGRO_COLOR Color;

    void execute() override
    {
        al_draw_filled_circle(CenterPos.x + 0.5, CenterPos.y + 0.5, Radius, Color);
    }
};

struct DrawRectangle : Command
{
    WorldCoords   UpperLeftPos;
    WorldCoords   LowerRightPos;
    float         Thickness;
    ALLEGRO_COLOR Color;

    void execute() override
    {
        al_draw_rectangle(UpperLeftPos.x + 0.5, UpperLeftPos.y + 0.5,
            LowerRightPos.x + 0.5, LowerRightPos.y + 0.5, Color, Thickness);
    }
};

struct DrawFilledRectangle : Command
{
    WorldCoords   UpperLeftPos;
    WorldCoords   LowerRightPos;
    ALLEGRO_COLOR Color;

    void execute() override
    {
        al_draw_filled_rectangle(UpperLeftPos .x + 0.5, UpperLeftPos .y + 0.5, 
                                 LowerRightPos.x + 0.5, LowerRightPos.y + 0.5, Color);
    }
}; 

struct DrawFilledRoundedRectangle : DrawFilledRectangle
{
    float Radius;

    void execute() override
    {
        al_draw_filled_rounded_rectangle(UpperLeftPos.x + 0.5, UpperLeftPos.y + 0.5,
            LowerRightPos.x + 0.5, LowerRightPos.y + 0.5, Radius, Radius, Color);
    }
};

struct DrawFilledDiamond : DrawFilledRectangle
{
    void execute() override
    {
        auto center = (UpperLeftPos + LowerRightPos) / 2.f;
        auto extent = (LowerRightPos - UpperLeftPos) / 2.f;
        float vertices[] = { center.x,            center.y - extent.y,
                             center.x - extent.x, center.y,
                             center.x,            center.y + extent.y,
                             center.x + extent.x, center.y };
        al_draw_filled_polygon(vertices, 8, Color);
    }
};

struct DrawCenteredText : Command
{
    WorldCoords    CenterPos;
    std::string    Text;
    ALLEGRO_FONT * Font;
    ALLEGRO_COLOR  Color;

    void execute() override
    {
        al_draw_text(Font, Color, CenterPos.x + 0.5, CenterPos.y + 0.5, 0, Text.c_str());
    }
};

}}

#endif // ALPP_RENDER_COMMAND 