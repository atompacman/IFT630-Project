#ifndef ALPP_RENDER_COMMAND
#define ALPP_RENDER_COMMAND

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

#include <alpp/Core.h>

struct ALLEGRO_DISPLAY;
struct ALLEGRO_FONT;

namespace alpp { namespace render {

enum class Layer
{
    WORLD,
    UI
};

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