// ----------------------------------------------------------------------------
// File: Vec3.cpp
// Desc: 3D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Maths/Vec3.h"
#include "Maths/Vec2.h"
#include "Maths/Vec4.h"
#include "Maths/Plane.h"
#include "Maths/Matrix.h"


// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------
Vec3::Vec3()                          : D3DXVECTOR3()         {}
Vec3::Vec3(const float *f)            : D3DXVECTOR3(f)        {}
Vec3::Vec3(const D3DVECTOR &v)        : D3DXVECTOR3(v)        {}
Vec3::Vec3(const D3DXFLOAT16 *f)      : D3DXVECTOR3(f)        {}
Vec3::Vec3(float x, float y, float z) : D3DXVECTOR3(x, y, z)  {}


// ----------------------------------------------------------------------------
// Name: Vec3::FromString
// Desc: Parse the string and set the vector
// Parm: const String &str - the string
// ----------------------------------------------------------------------------
bool Vec3::FromString(const String &str)
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

        if (index == 3)
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
// Name: Vec3::Clamp
// Desc: Clamp the vector to the give value [min(v1, c)]
// Parm: Vec3 &v1 - the vector to clamp
// Parm: float c  - the maximum value to clamp to
// ----------------------------------------------------------------------------
Vec3 &Vec3::Clamp(Vec3 &v1, float c)
{
  (*this)[0] = Min<float>(c, v1[0]);
  (*this)[1] = Min<float>(c, v1[1]);
  (*this)[2] = Min<float>(c, v1[2]);
  return *this;
} // Clamp


// ----------------------------------------------------------------------------
// Name: Vec3::Set
// Desc: Set the vector
// Parm: float x  - the x
// Parm: float y  - the y
// Parm: float z  - the z
// ----------------------------------------------------------------------------
Vec3 &Vec3::Set(float x, float y, float z)
{
  (*this)[0] = x;
  (*this)[1] = y;
  (*this)[2] = z;
  return *this;
} // Set


// ----------------------------------------------------------------------------
// Name: Vec3::Add
// Desc: Add two vectors
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec3 &Vec3::Add(const Vec3 &v1, const Vec3 &v2)
{
  D3DXVec3Add(this, &v1, &v2);
  return *this;
} // Add


// ----------------------------------------------------------------------------
// Name: Vec3::Scale
// Desc: Scale the vector
// Parm: const Vec3 &v - the vector
// Parm: float s       - the uniform scale
// ----------------------------------------------------------------------------
Vec3 &Vec3::Scale(const Vec3 &v, float s)
{
  D3DXVec3Scale(this, &v, s);
  return *this;
} // Scale


// ----------------------------------------------------------------------------
// Name: Vec3::Subtract
// Desc: Subtract two vectors
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec3 &Vec3::Subtract(const Vec3 &v1, const Vec3 &v2)
{
  D3DXVec3Subtract(this, &v1, &v2);
  return *this;
} // Subtract


// ----------------------------------------------------------------------------
// Name: Vec3::Lerp
// Desc: Interpolate between two vectors
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// Parm: float s         - the interpolant
// ----------------------------------------------------------------------------
Vec3 &Vec3::Lerp(const Vec3 &v1, const Vec3 &v2, float s)
{
  D3DXVec3Lerp(this, &v1, &v2, s);
  return *this;
} // Lerp


// ----------------------------------------------------------------------------
// Name: Vec3::Normalize
// Desc: Normalize the vector
// Parm: const Vec3 &v1 - the vector to normalize
// ----------------------------------------------------------------------------
Vec3 &Vec3::Normalize(const Vec3 &v1)
{
  D3DXVec3Normalize(this, &v1);
  return *this;
} // Normalize


// ----------------------------------------------------------------------------
// Name: Vec3::Maximize
// Desc: Maximize two vectors
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec3 &Vec3::Maximize(const Vec3 &v1, const Vec3 &v2)
{
  D3DXVec3Maximize(this, &v1, &v2);
  return *this;
} // Maximize


// ----------------------------------------------------------------------------
// Name: Vec3::Minimize
// Desc: Minimize two vectors
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec3 &Vec3::Minimize(const Vec3 &v1, const Vec3 &v2)
{
  D3DXVec3Minimize(this, &v1, &v2);
  return *this;
} // Minimize


// ----------------------------------------------------------------------------
// Name: Vec3::Dot
// Desc: Determines the dot product
// Parm: const Vec3 &v - the other vector
// Retn: float         - the dot product
// ----------------------------------------------------------------------------
float Vec3::Dot(const Vec3 &v) const
{
  return D3DXVec3Dot(this, &v);
} // Dot


// ----------------------------------------------------------------------------
// Name: Vec3::Length
// Desc: Gets the length of this vector
// Retn: float - the length
// ----------------------------------------------------------------------------
float Vec3::Length() const
{
  return D3DXVec3Length(this);
} // Length


// ----------------------------------------------------------------------------
// Name: Vec3::LengthSq
// Desc: Gets the length squared of this vector
// Retn: float - the length squared
// ----------------------------------------------------------------------------
float Vec3::LengthSq() const
{
  return D3DXVec3LengthSq(this);
} // LengthSq


// ----------------------------------------------------------------------------
// Name: Vec3::BaryCentric
// Desc: Returns a point in Barycentric coordinates, using the specified 
//       vectors
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// Parm: const Vec3 &v3  - the third vector
// Parm: float f         - th first weighting factor
// Parm: float g         - the second weighting factor
// ----------------------------------------------------------------------------
Vec3 &Vec3::BaryCentric(const Vec3 &v1, const Vec3 &v2, 
                        const Vec3 &v3, float f, float g)
{
  D3DXVec3BaryCentric(this, &v1, &v2, &v3, f, g);
  return *this;
} // BaryCentric


// ----------------------------------------------------------------------------
// Name: Vec3::CatmullRom
// Desc: Performs a Catmull-Rom interpolation, using the specified 2D vectors.
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// Parm: const Vec3 &v3  - the third vector
// Parm: const Vec3 &v4  - the fourth vector
// Parm: float s         - the weighting factor
// ----------------------------------------------------------------------------
Vec3 &Vec3::CatmullRom(const Vec3 &v1, const Vec3 &v2, 
                       const Vec3 &v3, const Vec3 &v4, float s)
{
  D3DXVec3CatmullRom(this, &v1, &v2, &v3, &v4, s);
  return *this;
} // CatmullRom


// ----------------------------------------------------------------------------
// Name: Vec3::Hermite
// Desc: Performs a Hermite spline interpolation, using the specified 2D vectors.
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// Parm: const Vec3 &v3  - the third vector
// Parm: const Vec3 &v4  - the fourth vector
// Parm: float s         - the weighting factor
// ----------------------------------------------------------------------------
Vec3 &Vec3::Hermite(const Vec3 &v1, const Vec3 &t1, const Vec3 &v2, 
                    const Vec3 &t2, float s)
{
  D3DXVec3Hermite(this, &v1, &t1, &v2, &t2, s);
  return *this;
} // Hermite


// ----------------------------------------------------------------------------
// Name: Vec3::Cross
// Desc: Calculate hte cross product between two vectors
// Parm: const Vec3 &v1  - the first vector
// Parm: const Vec3 &v2  - the second vector
// ----------------------------------------------------------------------------
Vec3 &Vec3::Cross(const Vec3 &v1, const Vec3 &v2)
{
  D3DXVec3Cross(this, &v1, &v2);
  return *this;
} // Cross


// ----------------------------------------------------------------------------
// Name: Vec3::PlaneIntersectLine
// Desc: Get teh intersection between the plane and te line
// Parm: const Plane &p  - the plane
// Parm: const Vec3 &v1  - the lstart of the line
// Parm: const Vec3 &v2  - the end of the line
// ----------------------------------------------------------------------------
Vec3 &Vec3::PlaneIntersectLine(const Plane &p, const Vec3 &v1, const Vec3 &v2)
{
  // TODO
  // This may break - D3DX function can set p1 as NULL
  D3DXPlaneIntersectLine(this, &p, &v1, &v2);
  return *this;
} // PlaneIntersectLine


// ----------------------------------------------------------------------------
// Name: Vec3::TransformCoord
// Desc: Transforms a 2D vector by a given matrix, projecting the result back 
//       into w = 1.
// Parm: const Vec3 &v    - the vector
// Parm: const Matrix &m  - the matrix
// ----------------------------------------------------------------------------
Vec3 &Vec3::TransformCoord(const Vec3 &v, const Matrix &m)
{
  D3DXVec3TransformCoord(this, &v, &m);
  return *this;
} // TransformCoord


// ----------------------------------------------------------------------------
// Name: Vec3::TransformNormal
// Desc: Transforms the 2D vector normal by the given matrix
// Parm: const Vec3 &v    - the vector
// Parm: const Matrix &m  - the matrix
// ----------------------------------------------------------------------------
Vec3 &Vec3::TransformNormal(const Vec3 &v, const Matrix &m)
{
  D3DXVec3TransformNormal(this, &v, &m);
  return *this;
} // TransformNormal


// ----------------------------------------------------------------------------
// Name: Vec3::Project
// Desc: Projects a 3D vector from object space into screen space
// Parm: const Vec3 &v             - the vector to project
// Parm: D3DVIEWPORT9 *viewport    - the viewport
// Parm: const Matrix &projection  - the projection matrix
// Parm: const Matrix &view        - the view matrix
// Parm: const Matrix &world       - the world matrix
// ----------------------------------------------------------------------------
Vec3 &Vec3::Project(const Vec3 &v, D3DVIEWPORT9 *viewport, const Matrix &projection, const Matrix &view, const Matrix &world)
{
  D3DXVec3Project(this, &v, viewport, &projection, &view, &world);
  return *this;
} // Project


// ----------------------------------------------------------------------------
// Name: Vec3::Unproject
// Desc: Projects a vector from screen space into object space.
// Parm: const Vec3 &v             - the vector to unproject
// Parm: D3DVIEWPORT9 *viewport    - the viewport
// Parm: const Matrix &projection  - the projection matrix
// Parm: const Matrix &view        - the view matrix
// Parm: const Matrix &world       - the world matrix
// ----------------------------------------------------------------------------
Vec3 &Vec3::Unproject(const Vec3 &v, D3DVIEWPORT9 *viewport, const Matrix &projection, const Matrix &view, const Matrix &world)
{
  D3DXVec3Unproject(this, &v, viewport, &projection, &view, &world);
  return *this;
} // Unproject



// -- EOF

