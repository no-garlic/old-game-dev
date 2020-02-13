// ----------------------------------------------------------------------------
// File: Vec4.h
// Desc: 4D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _VEC4_H
#define _VEC4_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Vec2;
class Vec3;
class Vec4;
class Matrix;


// ----------------------------------------------------------------------------
// Name: Vec4  (class)
// Desc: 4D vector
// ----------------------------------------------------------------------------
class Vec4 : public D3DXVECTOR4
{
public:
  // ------------------------------------------------------------------------
  // Constructors
  // ------------------------------------------------------------------------
  Vec4();
  Vec4(const float *f);
  Vec4(const D3DXFLOAT16 *f);
  Vec4(float x, float y, float z, float w);
  Vec4(const Vec3 &vec, float w);

  // ------------------------------------------------------------------------
  // Length
  // ------------------------------------------------------------------------
  float Length() const;
  float LengthSq()const;

  // --------------------------------------------------------------------------
  // Set teh vector
  // --------------------------------------------------------------------------
  Vec4 &Set(float x, float y, float z, float w);

  // --------------------------------------------------------------------------
  // Dot Product
  // --------------------------------------------------------------------------
  float Dot(const Vec4 &v) const;
  float Dot() const { return Dot(*this); }

  // --------------------------------------------------------------------------
  // Add vectors
  // --------------------------------------------------------------------------
  Vec4 &Add(const Vec4 &v1, const Vec4 &v2);
  Vec4 &Add(const Vec4 &v2) { return Add(*this, v2); }

  // --------------------------------------------------------------------------
  // Scale teh vector
  // --------------------------------------------------------------------------
  Vec4 &Scale(const Vec4 &v, float s);
  Vec4 &Scale(float s) { return Scale(*this, s); }

  // --------------------------------------------------------------------------
  // subtract vectors
  // --------------------------------------------------------------------------
  Vec4 &Subtract(const Vec4 &v1, const Vec4 &v2);
  Vec4 &Subtract(const Vec4 &v2) { return Subtract(*this, v2); }

  // --------------------------------------------------------------------------
  // Interpolate vectors
  // --------------------------------------------------------------------------
  Vec4 &Lerp(const Vec4 &v1, const Vec4 &v2, float s);
  Vec4 &Lerp(const Vec4 &v2, float s) { return Lerp(*this, v2, s); }

  // --------------------------------------------------------------------------
  // Normalize vectors
  // --------------------------------------------------------------------------
  Vec4 &Normalize(const Vec4 &v1);
  Vec4 &Normalize() { return Normalize(*this); }

  // --------------------------------------------------------------------------
  // Maximize the vector
  // --------------------------------------------------------------------------
  Vec4 &Maximize(const Vec4 &v1, const Vec4 &v2);
  Vec4 &Maximize(const Vec4 &v2) { return Maximize(*this, v2); }

  // --------------------------------------------------------------------------
  // Minimize the vector
  // --------------------------------------------------------------------------
  Vec4 &Minimize(const Vec4 &v1, const Vec4 &v2);
  Vec4 &Minimize(const Vec4 &v2) { return Minimize(*this, v2); }

  // --------------------------------------------------------------------------
  // Cross Product
  // --------------------------------------------------------------------------
  Vec4 &Cross(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);
  Vec4 &Cross(const Vec4 &v2, const Vec4 &v3) { return Cross(*this, v2, v3); }

  // --------------------------------------------------------------------------
  // Transformation
  // --------------------------------------------------------------------------
  Vec4 &Transform(const Vec2 &v, const Matrix &m);
  Vec4 &Transform(const Vec3 &v, const Matrix &m);
  Vec4 &Transform(const Vec4 &v, const Matrix &m);

  // --------------------------------------------------------------------------
  // Interpolation
  // --------------------------------------------------------------------------
  Vec4 &BaryCentric(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, float f, float g);
  Vec4 &CatmullRom(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4, float s);
  Vec4 &Hermite(const Vec4 &v1, const Vec4 &t1, const Vec4 &v2, const Vec4 &t2, float s);

  // --------------------------------------------------------------------------
  // Parse teh string and set teh vector
  // --------------------------------------------------------------------------
  bool FromString(const String &str);

  // --------------------------------------------------------------------------
  // Print the vector to a string
  // --------------------------------------------------------------------------
  inline String ToString() const
  {
    StringStream ss;
    ss.precision(2);
    ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
    ss << "[" << (*this)[0] + 0.001f << ", " << (*this)[1] + 0.001f << ", " << (*this)[2] + 0.001f << ", " << (*this)[3] + 0.001f << "]";
    return ss.str();
  } // ToString

}; // class Vec4


#endif //_VEC4_H

// -- EOF

