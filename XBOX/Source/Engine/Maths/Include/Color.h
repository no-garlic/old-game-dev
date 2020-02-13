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
#include "stdType.h"
#include "stdStr.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Vec3;
class Vec4;


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
  Color(float r, float g, float b, float a = 1.0f);
  Color(const Vec3 &v);
  Color(const Vec4 &v);
  Color(const String &str);

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

  // --------------------------------------------------------------------------
  // Parse the string and set teh vector
  // --------------------------------------------------------------------------
  bool FromString(const String &str, bool isFloat = true);

  // --------------------------------------------------------------------------
  // Print the vector to a string
  // --------------------------------------------------------------------------
  inline String ToString() const
  {
    StringStream ss;
    ss.precision(6);
    ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
    ss << "[" << this->r + 0.0000001f << ", " << this->g + 0.0000001f << ", " << this->b + 0.0000001f << ", " << this->a + 0.0000001f << "]";
    return ss.str();
  } // ToString

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

