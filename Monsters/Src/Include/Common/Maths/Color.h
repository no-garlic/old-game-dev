// ----------------------------------------------------------------------------
// File: Color.h
// Desc: Class to manage colors
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _COLOR_H
#define _COLOR_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Vec3;


// ----------------------------------------------------------------------------
// Name: Color  (struct)
// Desc: Class to manage a color
// ----------------------------------------------------------------------------
struct Color : public D3DXCOLOR
{
  // ------------------------------------------------------------------------
  // Constructors
  // ------------------------------------------------------------------------
  Color();
  Color(DWORD argb);
  Color(const float *f);
  Color(const D3DCOLORVALUE &v);
  Color(float r, float g, float b, float a);
  Color(const Vec3 &v);

  // ------------------------------------------------------------------------
  // Color functions
  // ------------------------------------------------------------------------
  Color &Add(const Color &c1);
  Color &AdjustContrast(float contrast);
  Color &AdjustSaturation(float saturation);
  Color &Lerp(const Color &c1, const Color &c2, float s);
  Color &Modulate(const Color &c1);
  Color &Modulate(float f);
  Color &Negative();
  Color &Scale(float s);
  Color &Subtract(const Color &c1);
  Color &ClampMin(const Color &c1);
  Color &ClampMax(const Color &c1);

  // ------------------------------------------------------------------------
  // Standard color constants
  // ------------------------------------------------------------------------
  static Color    Black;
  static Color    Gray;
  static Color    White;
  static Color    Red;
  static Color    Green;
  static Color    Blue;
  static Color    Magenta;
  static Color    Cyan;
  static Color    Yellow;
}; // struct Color


#endif // __COLOR_H

// -- EOF

