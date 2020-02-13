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
#include "stdType.h"
#include "stdStr.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Vec2;
class Vec4;
class Plane;
class Matrix;


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
  Vec3 &Project(const Vec3 &v, VIEWPORT *viewport, const Matrix &projection, 
    const Matrix &view, const Matrix &world);
  Vec3 &Unproject(const Vec3 &v, VIEWPORT *viewport, const Matrix &projection, 
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
  Vec3 &MatrixToEulerRH(const Matrix &m);

  // ----------------------------------------------------------------------------
  // Name: MatrixToEulerLH
  // Desc: Convert a matrix to left handed euler angles
  // Parm: const Matrix &m - the matrix
  // Retn: Vec3            - the euler angles
  // ----------------------------------------------------------------------------
  Vec3 &MatrixToEulerLH(const Matrix &m);

  // --------------------------------------------------------------------------
  // Make the vector by parsing a string
  // --------------------------------------------------------------------------
  bool FromString(const String &str);

  // --------------------------------------------------------------------------
  // Print the vector to a string
  // --------------------------------------------------------------------------
  String ToString() const;

}; // class Vec3


// ----------------------------------------------------------------------------
// Create a vec3 and normalize it
// ----------------------------------------------------------------------------
inline Vec3 Vec3N(float x, float y, float z)
{
  Vec3 v(x, y, z);
  v.Normalize();
  return v;
}


#endif //_VEC3_H

// -- EOF

