// ----------------------------------------------------------------------------
// File: Color.cpp
// Desc: Class to manage colors
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Maths/Color.h"
#include "Maths/Vec3.h"


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


// ----------------------------------------------------------------------------
// Name: Color::ClampMin
// Desc: Create the minimum color
// Parm: const Color &c1 - the other color
// ----------------------------------------------------------------------------
Color &Color::ClampMin(const Color &c1)
{
  r = Min<float>(r, c1.r);
  g = Min<float>(g, c1.g);
  b = Min<float>(b, c1.b);
  a = Min<float>(a, c1.a);

  return *this;
} // ClampMin


// ----------------------------------------------------------------------------
// Name: Color::ClampMax
// Desc: Create the maximum color
// Parm: const Color &c1 - the other color
// ----------------------------------------------------------------------------
Color &Color::ClampMax(const Color &c1)
{
  r = Max<float>(r, c1.r);
  g = Max<float>(g, c1.g);
  b = Max<float>(b, c1.b);
  a = Max<float>(a, c1.a);

  return *this;
} // ClampMax


// ----------------------------------------------------------------------------
// Name: Color::Add
// Desc: Add the two colors
// Parm: const Color &c1  - the color to add
// ----------------------------------------------------------------------------
Color &Color::Add(const Color &c1)
{
  D3DXColorAdd(this, this, &c1);
  return *this;
} // Add


// ----------------------------------------------------------------------------
// Name: Color::AdjustContrast
// Desc: adjust the contrast of the color
// Parm: float contrast - the contrast
// ----------------------------------------------------------------------------
Color &Color::AdjustContrast(float contrast)
{
  D3DXColorAdjustContrast(this, this, contrast);
  return *this;
} // AdjustContrast


// ----------------------------------------------------------------------------
// Name: Color::AdjustSaturation
// Desc: Adjust the saturation of the color
// Parm: float saturation - the saturation
// ----------------------------------------------------------------------------
Color &Color::AdjustSaturation(float saturation)
{
  D3DXColorAdjustSaturation(this, this, saturation);
  return *this;
} // AdjustSaturation


// ----------------------------------------------------------------------------
// Name: Color::Lerp
// Desc: Interpolate between two colors
// Parm: const Color &c1  - the first color
// Parm: const Color &c2  - the second color
// Parm: float s          - the interpolant
// ----------------------------------------------------------------------------
Color &Color::Lerp(const Color &c1, const Color &c2, float s)
{
  D3DXColorLerp(this, &c1, &c2, s);
  return *this;
} // Lerp


// ----------------------------------------------------------------------------
// Name: Color::Modulate
// Desc: Modulate with the given color
// Parm: const Color &c1 - the color
// ----------------------------------------------------------------------------
Color &Color::Modulate(const Color &c1)
{
  D3DXColorModulate(this, this, &c1);
  return *this;
} // Modulate


// ----------------------------------------------------------------------------
// Name: Color::Modulate
// Desc: Modulate with the scalar color
// Parm: float f - the scalar
// ----------------------------------------------------------------------------
Color &Color::Modulate(float f)
{
  D3DXColorScale(this, this, f);
  return *this;
} // Modulate


// ----------------------------------------------------------------------------
// Name: Color::Negative
// Desc: Negate the color
// Retn: Color & - the color
// ----------------------------------------------------------------------------
Color &Color::Negative()
{
  D3DXColorNegative(this, this);
  return *this;
} // Negative


// ----------------------------------------------------------------------------
// Name: Color::Scale
// Desc: scale the color
// Parm: const float s - the scale
// ----------------------------------------------------------------------------
Color &Color::Scale(const float s)
{
  D3DXColorScale(this, this, s);
  return *this;
} // Scale


// ----------------------------------------------------------------------------
// Name: Color::Subtract
// Desc: Subtract the color
// Parm: const Color &c1 - the color to subtract
// ----------------------------------------------------------------------------
Color &Color::Subtract(const Color &c1)
{
  D3DXColorSubtract(this, this, &c1);
  return *this;
} // Subtract


// -- EOF
