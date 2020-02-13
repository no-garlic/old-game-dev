// ----------------------------------------------------------------------------
// File: Color.cpp
// Desc: Class to manage colors
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Color.h"
#include "Math/Vec3.h"


// ----------------------------------------------------------------------------
// Color constructors
// ----------------------------------------------------------------------------
Color::Color()                                      : D3DXCOLOR()                       {}
Color::Color(DWORD argb)                            : D3DXCOLOR(argb)                   {}
Color::Color(const float *f)                        : D3DXCOLOR(f)                      {}
Color::Color(const D3DCOLORVALUE &v)                : D3DXCOLOR(v)                      {}
Color::Color(float r, float g, float b, float a)    : D3DXCOLOR(r, g, b, a)             {}
Color::Color(const Vec3 &v)                         : D3DXCOLOR(v[0], v[1], v[2], 1.0f) {}


// ----------------------------------------------------------------------------
// Standard color constants
// ----------------------------------------------------------------------------
Color Color::Black(D3DCOLOR_XRGB(0, 0, 0));
Color Color::Gray(D3DCOLOR_XRGB(127,127,127));
Color Color::White(D3DCOLOR_XRGB(255,255,255));
Color Color::Red(D3DCOLOR_XRGB(255,0,0));
Color Color::Green(D3DCOLOR_XRGB(0,255,0));
Color Color::Blue(D3DCOLOR_XRGB(0,0,255));
Color Color::Magenta(D3DCOLOR_XRGB(255,0,255));
Color Color::Cyan(D3DCOLOR_XRGB(0,255,255));
Color Color::Yellow(D3DCOLOR_XRGB(255,255,0));


Color &Color::Add(const Color &c1, const Color &c2)
{
    D3DXColorAdd(this, &c1, &c2);
    return *this;
} // Add


Color &Color::AdjustContrast(const Color &c1, float contrast)
{
    D3DXColorAdjustContrast(this, &c1, contrast);
    return *this;
} // AdjustContrast


Color &Color::AdjustSaturation(const Color &c1, float saturation)
{
    D3DXColorAdjustSaturation(this, &c1, saturation);
    return *this;
} // AdjustSaturation


Color &Color::Lerp(const Color &c1, const Color &c2, float s)
{
    D3DXColorLerp(this, &c1, &c2, s);
    return *this;
} // Lerp


Color &Color::Modulate(const Color &c1, const Color &c2)
{
    D3DXColorModulate(this, &c1, &c2);
    return *this;
} // Modulate


Color &Color::Negative(const Color &c1)
{
    D3DXColorNegative(this, &c1);
    return *this;
} // Negative


Color &Color::Scale(const Color &c1, float s)
{
    D3DXColorScale(this, &c1, s);
    return *this;
} // Scale


Color &Color::Subtract(const Color &c1, const Color &c2)
{
    D3DXColorSubtract(this, &c1, &c2);
    return *this;
} // Subtract


// -- EOF
