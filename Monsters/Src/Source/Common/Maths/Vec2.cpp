// ----------------------------------------------------------------------------
// File: Vec2.cpp
// Desc: 2D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Maths/Vec2.h"
#include "Maths/Matrix.h"


// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------
Vec2::Vec2()                        : D3DXVECTOR2()     {}
Vec2::Vec2(const float *f)          : D3DXVECTOR2(f)    {}
Vec2::Vec2(const D3DXFLOAT16 *f)    : D3DXVECTOR2(f)    {}
Vec2::Vec2(float x, float y)        : D3DXVECTOR2(x, y) {}


// ----------------------------------------------------------------------------
// Name: Vec2::FromString
// Desc: Parse the string and set the vector
// Parm: const String &str - the string
// ----------------------------------------------------------------------------
bool Vec2::FromString(const String &str)
{
  try
  {
    String token;
    uint index = 0;

    for (uint i = 0; i < str.size(); i++)
    {
      char c = str[i];

      if (c == '[' || c == ']' || c == ' ')
        continue;

      if (c == ',')
      {
        float number = LexicalCast<float>(token);
        (*this)[index++] = number;

        if (index == 2)
          return true;

        token.clear();
      } // if
      else
      {
        token += c;
      } // else
    } // for

    if (!token.empty())
    {
      float number = LexicalCast<float>(token);
      (*this)[index++] = number;
      return true;
    } // if

  } // try
  catch (InvalidParameterException &e)
  {
    LOG_EXCEPTION(e);
    return false;
  } // catch
  return true;
} // FromString


// ----------------------------------------------------------------------------
// Name: Vec2::Clamp
// Desc: Clamp the vector to the give value [min(v1, c)]
// Parm: Vec2 &v1 - the vector to clamp
// Parm: float c  - the maximum value to clamp to
// ----------------------------------------------------------------------------
Vec2 &Vec2::Clamp(Vec2 &v1, float c)
{
  (*this)[0] = Min<float>(c, v1[0]);
  (*this)[1] = Min<float>(c, v1[1]);
  return *this;
} // Clamp


// ----------------------------------------------------------------------------
// Name: Vec2::Set
// Desc: Set the vector
// Parm: float x  - the x
// Parm: float y  - the y
// ----------------------------------------------------------------------------
Vec2 &Vec2::Set(float x, float y)
{
  (*this)[0] = x;
  (*this)[1] = y;
  return *this;
} // Set


// ----------------------------------------------------------------------------
// Name: Vec2::Add
// Desc: Add two vectors
// Parm: const Vec2 &v1  - the first vector
// Parm: const Vec2 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec2 &Vec2::Add(const Vec2 &v1, const Vec2 &v2)
{
  D3DXVec2Add(this, &v1, &v2);
  return *this;
} // Add


// ----------------------------------------------------------------------------
// Name: Vec2::Scale
// Desc: Scale the vector
// Parm: const Vec2 &v - the vector
// Parm: float s       - the uniform scale
// ----------------------------------------------------------------------------
Vec2 &Vec2::Scale(const Vec2 &v, float s)
{
  D3DXVec2Scale(this, &v, s);
  return *this;
} // Scale


// ----------------------------------------------------------------------------
// Name: Vec2::Subtract
// Desc: Subtract two vectors
// Parm: const Vec2 &v1  - the first vector
// Parm: const Vec2 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec2 &Vec2::Subtract(const Vec2 &v1, const Vec2 &v2)
{
  D3DXVec2Subtract(this, &v1, &v2);
  return *this;
} // Subtract


// ----------------------------------------------------------------------------
// Name: Vec2::Lerp
// Desc: Interpolate between two vectors
// Parm: const Vec2 &v1  - the first vector
// Parm: const Vec2 &v2  - the second vector
// Parm: float s         - the interpolant
// ----------------------------------------------------------------------------
Vec2 &Vec2::Lerp(const Vec2 &v1, const Vec2 &v2, float s)
{
  D3DXVec2Lerp(this, &v1, &v2, s);
  return *this;
} // Lerp


// ----------------------------------------------------------------------------
// Name: Vec2::Maximize
// Desc: Maximize two vectors
// Parm: const Vec2 &v1  - the first vector
// Parm: const Vec2 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec2 &Vec2::Maximize(const Vec2 &v1, const Vec2 &v2)
{
  D3DXVec2Maximize(this, &v1, &v2);
  return *this;
} // Maximize


// ----------------------------------------------------------------------------
// Name: Vec2::Minimize
// Desc: Minimize two vectors
// Parm: const Vec2 &v1  - the first vector
// Parm: const Vec2 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec2 &Vec2::Minimize(const Vec2 &v1, const Vec2 &v2)
{
  D3DXVec2Minimize(this, &v1, &v2);
  return *this;
} // Minimize


// ----------------------------------------------------------------------------
// Name: Vec2::CCW
// Desc: Returns the z-component by taking the cross product of two 2D vectors
// Parm: const Vec2 &v - the other vector
// Retn: float         - the z value
// ----------------------------------------------------------------------------
float Vec2::CCW(const Vec2 &v) const
{
  return D3DXVec2CCW(this, &v);
} // Dot


// ----------------------------------------------------------------------------
// Name: Vec2::Dot
// Desc: Determines the dot product
// Parm: const Vec2 &v - the other vector
// Retn: float         - the dot product
// ----------------------------------------------------------------------------
float Vec2::Dot(const Vec2 &v) const
{
  return D3DXVec2Dot(this, &v);
} // Dot


// ----------------------------------------------------------------------------
// Name: Vec2::Length
// Desc: Gets the length of this vector
// Retn: float - the length
// ----------------------------------------------------------------------------
float Vec2::Length() const
{
  return D3DXVec2Length(this);
} // Length


// ----------------------------------------------------------------------------
// Name: Vec2::LengthSq
// Desc: Gets the length squared of this vector
// Retn: float - the length squared
// ----------------------------------------------------------------------------
float Vec2::LengthSq() const
{
  return D3DXVec2LengthSq(this);
} // LengthSq


// ----------------------------------------------------------------------------
// Name: Vec2::BaryCentric
// Desc: Returns a point in Barycentric coordinates, using the specified 2D 
//       vectors
// Parm: const Vec2 &v1  - the first vector
// Parm: const Vec2 &v2  - the second vector
// Parm: const Vec2 &v3  - the third vector
// Parm: float f         - th first weighting factor
// Parm: float g         - the second weighting factor
// ----------------------------------------------------------------------------
Vec2 &Vec2::BaryCentric(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, float f, float g)
{
  D3DXVec2BaryCentric(this, &v1, &v2, &v3, f, g);
  return *this;
} // BaryCentric


// ----------------------------------------------------------------------------
// Name: Vec2::CatmullRom
// Desc: Performs a Catmull-Rom interpolation, using the specified 2D vectors.
// Parm: const Vec2 &v1  - the first vector
// Parm: const Vec2 &v2  - the second vector
// Parm: const Vec2 &v3  - the third vector
// Parm: const Vec2 &v4  - the fourth vector
// Parm: float s         - the weighting factor
// ----------------------------------------------------------------------------
Vec2 &Vec2::CatmullRom(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec2 &v4, float s)
{
  D3DXVec2CatmullRom(this, &v1, &v2, &v3, &v4, s);
  return *this;
} // CatmullRom


// ----------------------------------------------------------------------------
// Name: Vec2::Hermite
// Desc: Performs a Hermite spline interpolation, using the specified 2D vectors.
// Parm: const Vec2 &v1  - the first vector
// Parm: const Vec2 &v2  - the second vector
// Parm: const Vec2 &v3  - the third vector
// Parm: const Vec2 &v4  - the fourth vector
// Parm: float s         - the weighting factor
// ----------------------------------------------------------------------------
Vec2 &Vec2::Hermite(const Vec2 &v1, const Vec2 &t1, const Vec2 &v2, const Vec2 &t2, float s)
{
  D3DXVec2Hermite(this, &v1, &t1, &v2, &t2, s);
  return *this;
} // Hermite


// ----------------------------------------------------------------------------
// Name: Vec2::TransformCoord
// Desc: Transforms a 2D vector by a given matrix, projecting the result back 
//       into w = 1.
// Parm: const Vec2 &v    - the vector
// Parm: const Matrix &m  - the matrix
// ----------------------------------------------------------------------------
Vec2 &Vec2::TransformCoord(const Vec2 &v, const Matrix &m)
{
  D3DXVec2TransformCoord(this, &v, &m);
  return *this;
} // TransformCoord


// ----------------------------------------------------------------------------
// Name: Vec2::TransformNormal
// Desc: Transforms the 2D vector normal by the given matrix
// Parm: const Vec2 &v    - the vector
// Parm: const Matrix &m  - the matrix
// ----------------------------------------------------------------------------
Vec2 &Vec2::TransformNormal(const Vec2 &v, const Matrix &m)
{
  D3DXVec2TransformNormal(this, &v, &m);
  return *this;
} // TransformNormal


// -- EOF

