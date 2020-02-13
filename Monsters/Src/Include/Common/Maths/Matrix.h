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
#include "Kernel/KernelInc.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Matrix;
class Plane;
class Quat;
class Vec2;
class Vec3;
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
  Matrix(const D3DXFLOAT16 *f);
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

  // ------------------------------------------------------------------------
  // Identity
  // ------------------------------------------------------------------------
  static Matrix &GetIdentityRef();
  bool    IsIdentity();
  float   Determinant();
  Matrix &Identity();
  
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
  Matrix &MultiplyTranspose(const Matrix &m1, const Matrix &m2);

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
  Matrix &Transformation2D(const Vec2 &scaling_center, float scaling_rotation, const Vec2 &scaling,
            const Vec2 &rotation_center, float rotation, const Vec2 &translation);
  Matrix &AffineTransformation(float scaling, const Vec3 &rotation_center, 
              const Quat &rotation, const Vec3 &translation);
  Matrix &AffineTransformation2D(float scaling, const Vec2 &rotation_center, 
              float rotation, const Vec2 &translation);

}; // class Matrix


#endif //_MATRIX_H

// -- EOF

