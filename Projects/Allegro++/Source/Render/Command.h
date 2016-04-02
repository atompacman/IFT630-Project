#ifndef ALPP_RENDER_COMMAND
#define ALPP_RENDER_COMMAND

#include <allegro5\color.h>

namespace alpp { namespace render {

class Command
{
public:

    virtual ~Command() { }

    virtual void execute() = 0;
};

class ResizeWindow : public Command
{
public:
    
    explicit ResizeWindow(ALLEGRO_DISPLAY * io_Window);
    void execute() override;

private:

    ALLEGRO_DISPLAY * m_Window;
};

class DrawFilledCircle : public Command
{
public:

    explicit DrawFilledCircle(float         i_CenterPosX,
                              float         i_CenterPosY, 
                              float         i_Radius, 
                              ALLEGRO_COLOR i_Color);

    void execute() override;

private:

    float         m_CenterPosX;
    float         m_CenterPosY;
    float         m_Radius;
    ALLEGRO_COLOR m_Color;
};

}}

#endif // ALPP_RENDER_COMMAND 