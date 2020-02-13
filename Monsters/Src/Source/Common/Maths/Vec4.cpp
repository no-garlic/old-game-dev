// ----------------------------------------------------------------------------
// File: Vec4.cpp
// Desc: 4D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Maths/Vec4.h"
#include "Maths/Vec2.h"
#include "Maths/Vec3.h"
#include "Maths/Matrix.h"


// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------
Vec4::Vec4()                                    : D3DXVECTOR4()             {}
Vec4::Vec4(const float *f)                      : D3DXVECTOR4(f)            {}
Vec4::Vec4(const D3DXFLOAT16 *f)                : D3DXVECTOR4(f)            {}
Vec4::Vec4(float x, float y, float z, float w)  : D3DXVECTOR4(x, y, z, w)   {}
Vec4::Vec4(const Vec3 &vec, float w)            : D3DXVECTOR4(vec.x, vec.y, vec.z, w)   {}


// ----------------------------------------------------------------------------
// Name: Vec4::FromString
// Desc: Parse the string and set the vector
// Parm: const String &str - the string
// ----------------------------------------------------------------------------
bool Vec4::FromString(const String &str)
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

        if (index == 4)
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
// Name: Vec4::Set
// Desc: Set hte vector
// Parm: float x  - x
// Parm: float y  - y
// Parm: float z  - z
// Parm: float w  - w
// ----------------------------------------------------------------------------
Vec4 &Vec4::Set(float x, float y, float z, float w)
{
  (*this)[0] = x;
  (*this)[1] = y;
  (*this)[2] = z;
  (*this)[3] = w;
  return *this;
} // Set


// ----------------------------------------------------------------------------
// Name: Vec4::Add
// Desc: Add two vectors
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec4 &Vec4::Add(const Vec4 &v1, const Vec4 &v2)
{
  D3DXVec4Add(this, &v1, &v2);
  return *this;
} // Add


// ----------------------------------------------------------------------------
// Name: Vec4::Scale
// Desc: Scale the vector
// Parm: const Vec4 &v - the vector to scale
// Parm: float s       - the scale
// ----------------------------------------------------------------------------
Vec4 &Vec4::Scale(const Vec4 &v, float s)
{
  D3DXVec4Scale(this, &v, s);
  return *this;
} // Scale


// ----------------------------------------------------------------------------
// Name: Vec4::Subtract
// Desc: Subtract the vectors
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec4 &Vec4::Subtract(const Vec4 &v1, const Vec4 &v2)
{
  D3DXVec4Subtract(this, &v1, &v2);
  return *this;
} // Subtract


// ----------------------------------------------------------------------------
// Name: Vec4::Lerp
// Desc: Interpolate between two vectors
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// Parm: float s         - the interpolant
// ----------------------------------------------------------------------------
Vec4 &Vec4::Lerp(const Vec4 &v1, const Vec4 &v2, float s)
{
  D3DXVec4Lerp(this, &v1, &v2, s);
  return *this;
} // Lerp


// ----------------------------------------------------------------------------
// Name: Vec4::Normalize
// Desc: Normalize the vector
// Parm: const Vec4 &v1 - the vector
// ----------------------------------------------------------------------------
Vec4 &Vec4::Normalize(const Vec4 &v1)
{
  D3DXVec4Normalize(this, &v1);
  return *this;
} // Normalize


// ----------------------------------------------------------------------------
// Name: Vec4::Maximize
// Desc: Maximize the vector
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec4 &Vec4::Maximize(const Vec4 &v1, const Vec4 &v2)
{
  D3DXVec4Maximize(this, &v1, &v2);
  return *this;
} // Maximize


// ----------------------------------------------------------------------------
// Name: Vec4::Minimize
// Desc: Minimize the vector
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec4 &Vec4::Minimize(const Vec4 &v1, const Vec4 &v2)
{
  D3DXVec4Minimize(this, &v1, &v2);
  return *this;
} // Minimize


// ----------------------------------------------------------------------------
// Name: Vec4::Dot
// Desc: Calculate the dot product between this vector and the supplied vector
// Parm: const Vec4 &v - the vector
// Retn: float         - the dot product
// ----------------------------------------------------------------------------
float Vec4::Dot(const Vec4 &v) const
{
  return D3DXVec4Dot(this, &v);
} // Dot


// ----------------------------------------------------------------------------
// Name: Vec4::Length
// Desc: Get the length of this vector
// Retn: float - the length
// ----------------------------------------------------------------------------
float Vec4::Length() const
{
  return D3DXVec4Length(this);
} // Length


// ----------------------------------------------------------------------------
// Name: Vec4::LengthSq
// Desc: Get the length squared of this vector
// Retn: float - the length squared
// ----------------------------------------------------------------------------
float Vec4::LengthSq() const
{
  return D3DXVec4LengthSq(this);
} // LengthSq


// ----------------------------------------------------------------------------
// Name: Vec4::BaryCentric
// Desc: Returns a point in Barycentric coordinates, using the specified 
//       vectors
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// Parm: const Vec4 &v3  - the third vector
// Parm: float f         - th first weighting factor
// Parm: float g         - the second weighting factor
// ----------------------------------------------------------------------------
Vec4 &Vec4::BaryCentric(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, float f, float g)
{
  D3DXVec4BaryCentric(this, &v1, &v2, &v3, f, g);
  return *this;
} // BaryCentric


// ----------------------------------------------------------------------------
// Name: Vec4::CatmullRom
// Desc: Performs a Catmull-Rom interpolation, using the specified 2D vectors.
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// Parm: const Vec4 &v3  - the third vector
// Parm: const Vec4 &v4  - the fourth vector
// Parm: float s         - the weighting factor
// ----------------------------------------------------------------------------
Vec4 &Vec4::CatmullRom(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4, float s)
{
  D3DXVec4CatmullRom(this, &v1, &v2, &v3, &v4, s);
  return *this;
} // CatmullRom


// ----------------------------------------------------------------------------
// Name: Vec4::Hermite
// Desc: Performs a Hermite spline interpolation, using the specified 2D vectors.
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// Parm: const Vec4 &v3  - the third vector
// Parm: const Vec4 &v4  - the fourth vector
// Parm: float s         - the weighting factor
// ----------------------------------------------------------------------------
Vec4 &Vec4::Hermite(const Vec4 &v1, const Vec4 &t1, const Vec4 &v2, const Vec4 &t2, float s)
{
  D3DXVec4Hermite(this, &v1, &t1, &v2, &t2, s);
  return *this;
} // Hermite


// ----------------------------------------------------------------------------
// Name: Vec4::Cross
// Desc: Determines the cross-product in four dimensions
// Parm: const Vec4 &v1  - the first vector
// Parm: const Vec4 &v2  - the second vector
// Parm: const Vec4 &v3  - the third vector
// ----------------------------------------------------------------------------
Vec4 &Vec4::Cross(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3)
{
  D3DXVec4Cross(this, &v1, &v2, &v3);
  return *this;
} // Cross


// ----------------------------------------------------------------------------
// Name: Vec4::Transform
// Desc: Transforms a 2D vector by a given matrix
// Parm: const Vec2 &v    - the vector
// Parm: const Matrix &m  - the marix
// ----------------------------------------------------------------------------
Vec4 &Vec4::Transform(const Vec2 &v, const Matrix &m)
{
  D3DXVec2Transform(this, &v, &m);
  return *this;
} // Transform


// ----------------------------------------------------------------------------
// Name: Vec4::Transform
// Desc: Transforms a 3D vector by a given matrix
// Parm: const Vec3 &v    - the vector
// Parm: const Matrix &m  - the matrix
// ----------------------------------------------------------------------------
Vec4 &Vec4::Transform(const Vec3 &v, const Matrix &m)
{
  D3DXVec3Transform(this, &v, &m);
  return *this;
} // Transform


// ----------------------------------------------------------------------------
// Name: Vec4::Transform
// Desc: Transforms a 4D vector by a given matrix
// Parm: const Vec4 &v    - the vector
// Parm: const Matrix &m  - the matrx
// ----------------------------------------------------------------------------
Vec4 &Vec4::Transform(const Vec4 &v, const Matrix &m)
{
  D3DXVec4Transform(this, &v, &m);
  return *this;
} // Transform


// -- EOF

