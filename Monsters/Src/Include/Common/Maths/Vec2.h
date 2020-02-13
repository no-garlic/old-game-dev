// ----------------------------------------------------------------------------
// File: Vec2.h
// Desc: 2D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _VECTOR2_H
#define _VECTOR2_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include <sstream>


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Matrix;


// ----------------------------------------------------------------------------
// Name: Vec2  (class)
// Desc: 2D vector
// ----------------------------------------------------------------------------
class Vec2 : public D3DXVECTOR2
{
public:
  // --------------------------------------------------------------------------
  // Constructors
  // --------------------------------------------------------------------------
  Vec2();
  Vec2(const float *f);
  Vec2(const D3DXFLOAT16 *f);
  Vec2(float x, float y);

  // --------------------------------------------------------------------------
  // Vector length
  // --------------------------------------------------------------------------
  float Length() const;
  float LengthSq() const;

  // --------------------------------------------------------------------------
  // Set the vector
  // --------------------------------------------------------------------------
  Vec2 &Set(float x, float y);

  // --------------------------------------------------------------------------
  // Dot product
  // --------------------------------------------------------------------------
  float Dot(const Vec2 &v1) const;
  float Dot() const { return Dot(*this); }

  // --------------------------------------------------------------------------
  // Add vectors
  // --------------------------------------------------------------------------
  Vec2 &Add(const Vec2 &v1, const Vec2 &v2);
  Vec2 &Add(const Vec2 &v2) { return Add(*this, v2); }

  // --------------------------------------------------------------------------
  // Scale the vector
  // --------------------------------------------------------------------------
  Vec2 &Scale(const Vec2 &v, float s);
  Vec2 &Scale(float s) { return Scale(*this, s); }

  // --------------------------------------------------------------------------
  // Subtract another vector
  // --------------------------------------------------------------------------
  Vec2 &Subtract(const Vec2 &v1, const Vec2 &v2);
  Vec2 &Subtract(const Vec2 &v2) { return Subtract(*this, v2); }

  // --------------------------------------------------------------------------
  // Interpolate between vectors
  // --------------------------------------------------------------------------
  Vec2 &Lerp(const Vec2 &v1, const Vec2 &v2, float s);
  Vec2 &Lerp(const Vec2 &v2, float s) { return Lerp(*this, v2, s); }

  // --------------------------------------------------------------------------
  // Normalize the vector
  // --------------------------------------------------------------------------
  Vec2 &Normalize(const Vec2 &v1);
  Vec2 &Normalize() { return Normalize(*this); }

  // --------------------------------------------------------------------------
  // Maximize the vector
  // --------------------------------------------------------------------------
  Vec2 &Maximize(const Vec2 &v1, const Vec2 &v2);
  Vec2 &Maximize(const Vec2 &v2) { return Maximize(*this, v2); }

  // --------------------------------------------------------------------------
  // Minimize the vector
  // --------------------------------------------------------------------------
  Vec2 &Minimize(const Vec2 &v1, const Vec2 &v2);
  Vec2 &Minimize(const Vec2 &v2) { return Minimize(*this, v2); }

  // --------------------------------------------------------------------------
  // Transform the vector
  // --------------------------------------------------------------------------
  Vec2 &TransformCoord(const Vec2 &v, const Matrix &m);
  Vec2 &TransformCoord(const Matrix &m) { return TransformCoord(*this, m); }
  Vec2 &TransformNormal(const Vec2 &v, const Matrix &m);
  Vec2 &TransformNormal(const Matrix &m) { return TransformNormal(*this, m); }

  // --------------------------------------------------------------------------
  // Returns the z component of the cross product
  // --------------------------------------------------------------------------
  float CCW(const Vec2 &v1) const;

  // --------------------------------------------------------------------------
  // Interpolate points
  // --------------------------------------------------------------------------
  Vec2 &BaryCentric(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, float f, float g);
  Vec2 &CatmullRom(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec2 &v4, float s);
  Vec2 &Hermite(const Vec2 &v1, const Vec2 &t1, const Vec2 &v2, const Vec2 &t2, float s);

  // --------------------------------------------------------------------------
  // Clamp
  // --------------------------------------------------------------------------
  Vec2 &Clamp(Vec2 &v1, float c);

  // --------------------------------------------------------------------------
  // Print the vector to a string
  // --------------------------------------------------------------------------
  String ToString() const
  {
    StringStream ss;
    ss.precision(2);
    ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
    ss << "[" << (*this)[0] + 0.001f << ", " << (*this)[1] + 0.001f << "]";
    return ss.str();
  } // ToString

  // --------------------------------------------------------------------------
  // Parse the string and set the vector
  // --------------------------------------------------------------------------
  bool FromString(const String &str);

}; // class Vec2


#endif //_VEC2_H

// -- EOF

