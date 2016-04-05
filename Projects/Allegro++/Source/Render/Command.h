#ifndef ALPP_RENDER_COMMAND
#define ALPP_RENDER_COMMAND

// allegro
#include <allegro5\color.h>

// std
#include <string>

struct ALLEGRO_DISPLAY;
struct ALLEGRO_FONT;

namespace alpp { namespace render {

struct Command
{
    virtual ~Command() { }

    virtual void execute() = 0;
};

struct ResizeWindow : Command
{
    ALLEGRO_DISPLAY * Window;

    void execute() override;
};

struct DrawFilledCircle : Command
{
    float         CenterPosX;
    float         CenterPosY;
    float         Radius;
    ALLEGRO_COLOR Color;

    void execute() override;
};

struct DrawFilledRectangle : Command
{
    float         PosLeft;
    float         PosTop;
    float         PosRight;
    float         PosBottom;
    ALLEGRO_COLOR Color;

    void execute() override;
};

struct DrawCenteredText : Command
{
    std::string    Text;
    ALLEGRO_FONT * Font;
    float          PosX;
    float          PosY;
    ALLEGRO_COLOR  Color;

    void execute() override;
};

}}

#endif // ALPP_RENDER_COMMAND 