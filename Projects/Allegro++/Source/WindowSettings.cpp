#include <WindowSettings.h>

namespace alpp
{

WindowSettings::WindowSettings() :
    m_DisplayMode(DisplayMode::WINDOWED),
    m_Width      (800),
    m_Height     (600)
{

}

void WindowSettings::setDisplayMode(DisplayMode i_Mode)
{
    m_DisplayMode = i_Mode;
}

void WindowSettings::setDimensions(uint32_t i_Width, uint32_t i_Height)
{
    m_Width  = i_Width;
    m_Height = i_Height;
}

}