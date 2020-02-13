// ----------------------------------------------------------------------------
// File: Vec3.h
// Desc: 3D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _VECTOR3_H
#define _VECTOR3_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Maths/Matrix.h"
#include <sstream>


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Vec2;
class Vec4;
class Plane;


// ----------------------------------------------------------------------------
// Name: D3DXVec3Set
// Desc: Set a D3DXVECTOR3
// Parm: D3DXVECTOR3 *pVec - the vector
// Parm: float x           - the x val
// Parm: float y           - the y val
// Parm: float z           - the z val
// Retn: D3DXVECTOR3 *     - the vector
// ----------------------------------------------------------------------------
inline D3DXVECTOR3 *D3DXVec3Set(D3DXVECTOR3 *pVec, float x, float y, float z)
{
  (*pVec)[0] = x;
  (*pVec)[1] = y;
  (*pVec)[2] = z;
  return pVec;
} // D3DXVec3Set


// ----------------------------------------------------------------------------
// 3D vector
// ----------------------------------------------------------------------------
class Vec3 : public D3DXVECTOR3
{
public:
  // ------------------------------------------------------------------------
  // Constructors
  // ------------------------------------------------------------------------
  Vec3();
  Vec3(const float *f);
  Vec3(const D3DVECTOR &v);
  Vec3(const D3DXFLOAT16 *f);
  Vec3(float x, float y, float z);

  // ------------------------------------------------------------------------
  // Dot product
  // ------------------------------------------------------------------------
  float Dot(const Vec3 &v) const;
  float Dot() const { return Dot(*this); }

  // --------------------------------------------------------------------------
  // Length
  // --------------------------------------------------------------------------
  float Length() const;
  float LengthSq() const;
  Vec3 &Set(float x, float y, float z);

  // --------------------------------------------------------------------------
  // Add vectors
  // --------------------------------------------------------------------------
  Vec3 &Add(const Vec3 &v1, const Vec3 &v2);
  Vec3 &Add(const Vec3 &v2) { return Add(*this, v2); }

  // --------------------------------------------------------------------------
  // Scale the vector
  // --------------------------------------------------------------------------
  Vec3 &Scale(const Vec3 &v, float s);
  Vec3 &Scale(float s) { return Scale(*this, s); }

  // --------------------------------------------------------------------------
  // Subtract vectors
  // --------------------------------------------------------------------------
  Vec3 &Subtract(const Vec3 &v1, const Vec3 &v2);
  Vec3 &Subtract(const Vec3 &v2) { return Subtract(*this, v2); }

  // --------------------------------------------------------------------------
  // Interpolate
  // --------------------------------------------------------------------------
  Vec3 &Lerp(const Vec3 &v1, const Vec3 &v2, float s);
  Vec3 &Lerp(const Vec3 &v2, float s) { return Lerp(*this, v2, s); }

  // --------------------------------------------------------------------------
  // Normalize
  // --------------------------------------------------------------------------
  Vec3 &Normalize(const Vec3 &v1);
  Vec3 &Normalize() { return Normalize(*this); }

  // --------------------------------------------------------------------------
  // Maximize
  // --------------------------------------------------------------------------
  Vec3 &Maximize(const Vec3 &v1, const Vec3 &v2);
  Vec3 &Maximize(const Vec3 &v2) { return Maximize(*this, v2); }

  // --------------------------------------------------------------------------
  // Minimize
  // --------------------------------------------------------------------------
  Vec3 &Minimize(const Vec3 &v1, const Vec3 &v2);
  Vec3 &Minimize(const Vec3 &v2) { return Minimize(*this, v2); }

  // --------------------------------------------------------------------------
  // Cross Product
  // --------------------------------------------------------------------------
  Vec3 &Cross(const Vec3 &v1, const Vec3 &v2);
  Vec3 &Cross(const Vec3 &v2) { return Cross(*this, v2); }

  // --------------------------------------------------------------------------
  // Transform the vector
  // --------------------------------------------------------------------------
  Vec3 &TransformCoord(const Vec3 &v, const Matrix &m);
  Vec3 &TransformCoord(const Matrix &m) { return TransformCoord(*this, m); }

  // --------------------------------------------------------------------------
  // Transform the normal
  // --------------------------------------------------------------------------
  Vec3 &TransformNormal(const Vec3 &v, const Matrix &m);
  Vec3 &TransformNormal(const Matrix &m) { return TransformNormal(*this, m); }

  // --------------------------------------------------------------------------
  // Test intersection between a plane and a line
  // --------------------------------------------------------------------------
  Vec3 &PlaneIntersectLine(const Plane &p, const Vec3 &v1, const Vec3 &v2);

  // --------------------------------------------------------------------------
  // Interpolate
  // --------------------------------------------------------------------------
  Vec3 &BaryCentric(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, float f, float g);
  Vec3 &CatmullRom(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, const Vec3 &v4, float s);
  Vec3 &Hermite(const Vec3 &v1, const Vec3 &t1, const Vec3 &v2, const Vec3 &t2, float s);

  // --------------------------------------------------------------------------
  // Project and Unproject
  // --------------------------------------------------------------------------
  Vec3 &Project(const Vec3 &v, D3DVIEWPORT9 *viewport, const Matrix &projection, 
    const Matrix &view, const Matrix &world);
  Vec3 &Unproject(const Vec3 &v, D3DVIEWPORT9 *viewport, const Matrix &projection, 
    const Matrix &view, const Matrix &world);

  // --------------------------------------------------------------------------
  // Clamp
  // --------------------------------------------------------------------------
  Vec3 &Clamp(Vec3 &v1, float c);

  // ----------------------------------------------------------------------------
  // Name: MatrixToEulerRH
  // Desc: Convert a matrix to right handed euler angles
  // Parm: const Matrix &m - the matrix
  // Retn: Vec3            - the euler angles
  // ----------------------------------------------------------------------------
  Vec3 &MatrixToEulerRH(const Matrix &m)
  {
    Vec3 &euler = *this;
    if (m._21 > 0.998f) 
    { 
      // North pole
      euler[0] = atan2(m._13, m._33);
      euler[1] = D3DX_PI / 2;
      euler[2] = 0.0f;
      return euler;
    }
    if (m._21 < -0.998f)
    {
      // South pole
      euler[0] = atan2(m._13, m._33);
      euler[1] = -D3DX_PI / 2;
      euler[2] = 0.0f;
      return euler;
    }
    euler[0] = atan2(-m._31, m._11);
    euler[1] = asin(m._21);
    euler[2] = atan2(-m._23, m._22);
    return euler;
  } // GetEulerRH


  // ----------------------------------------------------------------------------
  // Name: MatrixToEulerLH
  // Desc: Convert a matrix to left handed euler angles
  // Parm: const Matrix &m - the matrix
  // Retn: Vec3            - the euler angles
  // ----------------------------------------------------------------------------
  Vec3 &MatrixToEulerLH(const Matrix &m)
  {
    Vec3 &euler = *this;
    if (m._21 > 0.998f) 
    { 
      // North pole
      euler[0] = 0.0f;
      euler[1] = atan2(m._13, m._33);
      euler[2] = D3DX_PI / 2;
      return euler;
    }
    if (m._21 < -0.998f)
    {
      // South pole
      euler[0] = 0.0f;
      euler[1] = atan2(m._13, m._33);
      euler[2] = -D3DX_PI / 2;
      return euler;
    }
    euler[0] = -atan2(-m._23, m._22);
    euler[1] = atan2(-m._31, m._11);
    euler[2] = asin(m._21);
    return euler;
  } // GetEulerLH

  // --------------------------------------------------------------------------
  // Make the vector by parsing a string
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
    ss << "[" << (*this)[0] + 0.001f << ", " << (*this)[1] + 0.001f << ", " << (*this)[2] + 0.001f << "]";
    return ss.str();
  } // ToString

}; // class Vec3


/*
// ----------------------------------------------------------------------------
// Name: MatrixToEulerRH
// Desc: Convert a matrix to right handed euler angles
// Parm: const Matrix &m - the matrix
// Retn: Vec3            - the euler angles
// ----------------------------------------------------------------------------
inline Vec3 MatrixToEulerRH(const Matrix &m)
{
  Vec3 euler;
  if (m._21 > 0.998f) 
  { 
    // North pole
    euler[0] = atan2(m._13, m._33);
    euler[1] = D3DX_PI / 2;
    euler[2] = 0.0f;
    return euler;
  }
  if (m._21 < -0.998f)
  {
    // South pole
    euler[0] = atan2(m._13, m._33);
    euler[1] = -D3DX_PI / 2;
    euler[2] = 0.0f;
    return euler;
  }
  euler[0] = atan2(-m._31, m._11);
  euler[1] = asin(m._21);
  euler[2] = atan2(-m._23, m._22);
  return euler;
} // GetEulerRH


// ----------------------------------------------------------------------------
// Name: MatrixToEulerLH
// Desc: Convert a matrix to left handed euler angles
// Parm: const Matrix &m - the matrix
// Retn: Vec3            - the euler angles
// ----------------------------------------------------------------------------
inline Vec3 MatrixToEulerLH(const Matrix &m)
{
  Vec3 euler;
  if (m._21 > 0.998f) 
  { 
    // North pole
    euler[0] = 0.0f;
    euler[1] = atan2(m._13, m._33);
    euler[2] = D3DX_PI / 2;
    return euler;
  }
  if (m._21 < -0.998f)
  {
    // South pole
    euler[0] = 0.0f;
    euler[1] = atan2(m._13, m._33);
    euler[2] = -D3DX_PI / 2;
    return euler;
  }
  euler[0] = -atan2(-m._23, m._22);
  euler[1] = atan2(-m._31, m._11);
  euler[2] = asin(m._21);
  return euler;
} // GetEulerLH
*/




#endif //_VEC3_H

// -- EOF

