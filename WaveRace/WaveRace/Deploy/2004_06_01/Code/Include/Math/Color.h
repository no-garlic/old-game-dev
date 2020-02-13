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
#include "Math/Types.h"


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
    Color &Add(const Color &c1, const Color &c2);
    Color &AdjustContrast(const Color &c1, float contrast);
    Color &AdjustSaturation(const Color &c1, float saturation);
    Color &Lerp(const Color &c1, const Color &c2, float s);
    Color &Modulate(const Color &c1, const Color &c2);
    Color &Negative(const Color &c1);
    Color &Scale(const Color &c1, float s);
    Color &Subtract(const Color &c1, const Color &c2);

    
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

