// ----------------------------------------------------------------------------
// File: Matrix.h
// Desc: Matrix class
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _MATRIX_H
#define _MATRIX_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "stdStr.h"
#include "stdMath.h"
#include "stdMem.h"
#include "stdLog.h"
#include "Vec3.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Matrix;
class Plane;
class Quat;
class Vec2;
class Vec4;


// ----------------------------------------------------------------------------
// The identity matrix
// ----------------------------------------------------------------------------
extern Matrix MatrixIdentity;


// ----------------------------------------------------------------------------
// Name: Matrix  (class)
// Desc: The 4x4 Matrix
// ----------------------------------------------------------------------------
class Matrix : public D3DXMATRIX
{
public:
  // ------------------------------------------------------------------------
  // Constructors
  // ------------------------------------------------------------------------
  Matrix();
  Matrix(const float *f);
  Matrix(float _11, float _12, float _13, float _14,
          float _21, float _22, float _23, float _24,
          float _31, float _32, float _33, float _34,
          float _41, float _42, float _43, float _44);

  // ------------------------------------------------------------------------
  // Static factory functions - dont confuse floatse with member functions
  // ------------------------------------------------------------------------
  static Matrix MakeNewIdentity();
  static Matrix MakeNewRotationAxis(const Vec3 &axis, float angle);
  static Matrix MakeNewRotationQuaternion(const Quat &q);
  static Matrix MakeNewRotationYawPitchRoll(float yaw, float pitch, float roll);
  static Matrix MakeNewTranslation(float x, float y, float z);
  static Matrix MakeNewTranslation(const Vec3 &trans);
  static Matrix MakeNewScaling(float x, float y, float z);
  static Matrix MakeNewPosRotScale(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale);

  // ------------------------------------------------------------------------
  // Identity
  // ------------------------------------------------------------------------
  static Matrix &GetIdentityRef();
  bool    IsIdentity();
  Matrix &Identity();

  // --------------------------------------------------------------------------
  // Get Axis
  // --------------------------------------------------------------------------
  Vec3 GetTAxis() const { return Vec3(_41, _42, _43); }
  Vec3 GetXAxis() const { return Vec3(_11, _21, _31); }
  Vec3 GetYAxis() const { return Vec3(_12, _22, _32); }
  Vec3 GetZAxis() const { return Vec3(_13, _23, _33); }
  void GetTAxis(Vec3 &v) const { v.Set(_41, _42, _43); }
  void GetXAxis(Vec3 &v) const { v.Set(_11, _21, _31); }
  void GetYAxis(Vec3 &v) const { v.Set(_12, _22, _32); }
  void GetZAxis(Vec3 &v) const { v.Set(_13, _23, _33); }
  
  // --------------------------------------------------------------------------
  // Set Axis
  // --------------------------------------------------------------------------
  void SetTAxis(const Vec3 &v) { _41 = v.x; _42 = v.y; _43 = v.z; }
  void SetXAxis(const Vec3 &v) { _11 = v.x; _21 = v.y; _31 = v.z; }
  void SetYAxis(const Vec3 &v) { _12 = v.x; _22 = v.y; _32 = v.z; }
  void SetZAxis(const Vec3 &v) { _13 = v.x; _23 = v.y; _33 = v.z; }

  // --------------------------------------------------------------------------
  // Get Scale
  // --------------------------------------------------------------------------
  Vec3 GetScale() const { return Vec3(GetXAxis().Length(), GetYAxis().Length(), GetZAxis().Length()); }
  void GetScale(Vec3 &v) const { v.Set(GetXAxis().Length(), GetYAxis().Length(), GetZAxis().Length()); }
  bool IsUnitScale() const;
  inline float GetScaleMax() const;

  // --------------------------------------------------------------------------
  // Inverse
  // --------------------------------------------------------------------------
  Matrix &Inverse(float determinant, const Matrix &m);
  Matrix &Inverse(const Matrix &m);
  Matrix &Inverse() { return Inverse(*this); }

  // --------------------------------------------------------------------------
  // Transpose
  // --------------------------------------------------------------------------
  Matrix &Transpose(const Matrix &m);
  Matrix &Transpose() { return Transpose(*this); }

  // --------------------------------------------------------------------------
  // Look At
  // --------------------------------------------------------------------------
  Matrix &LookAtLH(const Vec3 &eye, const Vec3 &at, const Vec3 &up);
  Matrix &LookAtRH(const Vec3 &eye, const Vec3 &at, const Vec3 &up);
  
  // --------------------------------------------------------------------------
  // Multiply
  // --------------------------------------------------------------------------
  Matrix &Multiply(const Matrix &m1, const Matrix &m2);
  Matrix &Multiply(const Matrix &m2) { return Multiply(*this, m2); }
  Matrix &PreMultiply(const Matrix &m);
  Matrix &PostMultiply(const Matrix &m);

  // --------------------------------------------------------------------------
  // Orthographic
  // --------------------------------------------------------------------------
  Matrix &OrthoLH(float width, float height, float z_near, float z_far);
  Matrix &OrthoRH(float width, float height, float z_near, float z_far);
  Matrix &OrthoOffCenterLH(float left, float right, float bottom, float top, float z_near, float z_far);
  Matrix &OrthoOffCenterRH(float left, float right, float bottom, float top, float z_near, float z_far);

  // --------------------------------------------------------------------------
  // Perspective
  // --------------------------------------------------------------------------
  Matrix &PerspectiveFovLH(float fov, float aspect, float z_near, float z_far);
  Matrix &PerspectiveFovRH(float fov, float aspect, float z_near, float z_far);
  Matrix &PerspectiveLH(float width, float height, float z_near, float z_far);
  Matrix &PerspectiveRH(float width, float height, float z_near, float z_far);
  Matrix &PerspectiveOffCenterLH(float left, float right, float bottom, float top, float z_near, float z_far);
  Matrix &PerspectiveOffCenterRH(float left, float right, float bottom, float top, float z_near, float z_far);
  
  // --------------------------------------------------------------------------
  // Reflection
  // --------------------------------------------------------------------------
  Matrix &Reflect(const Plane &plane);
  Matrix &Shadow(const Vec4 &light, const Plane &plane);
  
  // --------------------------------------------------------------------------
  // Translation
  // --------------------------------------------------------------------------
  Matrix &Translation(float x, float y, float z);
  Matrix &Translation(const Vec3 &trans);
  
  // --------------------------------------------------------------------------
  // Rotation
  // --------------------------------------------------------------------------
  Matrix &RotationAxis(const Vec3 &axis, float angle);
  Matrix &RotationQuaternion(const Quat &q);
  Matrix &RotationYawPitchRoll(float yaw, float pitch, float roll);
  Matrix &RotationX(float angle);
  Matrix &RotationY(float angle);
  Matrix &RotationZ(float angle);
  
  // --------------------------------------------------------------------------
  // Scaling
  // --------------------------------------------------------------------------
  Matrix &Scaling(float x, float y, float z);
  
  // --------------------------------------------------------------------------
  // Transformation
  // --------------------------------------------------------------------------
  Matrix &Transformation(const Vec3 &scaling_center, const Quat &scaling_rotation, const Vec3 &scaling,
            const Vec3 &rotation_center, const Quat &rotation, const Vec3 &translation);
  Matrix &AffineTransformation(float scaling, const Vec3 &rotation_center, 
              const Quat &rotation, const Vec3 &translation);

  String ToString(int row) const;
  bool FromString(const String &str, int row);

}; // class Matrix


inline float Matrix::GetScaleMax() const
{
  float x = GetXAxis().Length();
  float y = GetYAxis().Length();
  float z = GetZAxis().Length();
  float maxScale = Max<float>(x, Max<float>(y, z));
  return maxScale;
}


#endif //_MATRIX_H

// -- EOF

