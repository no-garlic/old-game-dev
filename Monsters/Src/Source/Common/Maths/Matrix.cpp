// ----------------------------------------------------------------------------
// File: Matrix.cpp
// Desc: Describes a matrix
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Maths/Matrix.h"
#include "Maths/Plane.h"
#include "Maths/Quat.h"
#include "Maths/Vec2.h"
#include "Maths/Vec3.h"
#include "Maths/Vec4.h"


// ----------------------------------------------------------------------------
// The identity matrix
// ----------------------------------------------------------------------------
Matrix MatrixIdentity(Matrix::MakeNewIdentity());


// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------
Matrix::Matrix()                        : D3DXMATRIX()  {}
Matrix::Matrix(const float *f)          : D3DXMATRIX(f) {}
Matrix::Matrix(const D3DXFLOAT16 *f)    : D3DXMATRIX(f) {}
Matrix::Matrix(float _11, float _12, float _13, float _14,
               float _21, float _22, float _23, float _24,
               float _31, float _32, float _33, float _34,
               float _41, float _42, float _43, float _44) : 
               D3DXMATRIX(_11, _12, _13, _14, 
                          _21, _22, _23, _24, 
                          _31, _32, _33, _34, 
                          _41, _42, _43, _44) {}


// ----------------------------------------------------------------------------
// Make a new identity matrix
// ----------------------------------------------------------------------------
Matrix Matrix::MakeNewIdentity()
{
  Matrix m;
  m.Identity();
  return m;
} // MakeNewIdentity


// ----------------------------------------------------------------------------
// Make a nw rotation axis matrix
// ----------------------------------------------------------------------------
Matrix Matrix::MakeNewRotationAxis(const Vec3 &axis, float angle)
{
  Matrix m;
  m.RotationAxis(axis, angle);
  return m;
} // MakeNewRotationAxis


// ----------------------------------------------------------------------------
// Make a new quaternion rotation matrix
// ----------------------------------------------------------------------------
Matrix Matrix::MakeNewRotationQuaternion(const Quat &q)
{
  Matrix m;
  m.RotationQuaternion(q);
  return m;
} // MakeNewRotationQuaternion


// ----------------------------------------------------------------------------
// Make a new YPR rotation matrix
// ----------------------------------------------------------------------------
Matrix Matrix::MakeNewRotationYawPitchRoll(float yaw, float pitch, float roll)
{
  Matrix m;
  m.RotationYawPitchRoll(yaw, pitch, roll);
  return m;
} // MakeNewRotationYawPitchRoll


// ----------------------------------------------------------------------------
// Make a new translation matrix
// ----------------------------------------------------------------------------
Matrix Matrix::MakeNewTranslation(float x, float y, float z)
{
  Matrix m;
  m.Translation(x, y, z);
  return m;
} // MakeNewTranslation


// ----------------------------------------------------------------------------
// Make a new translation matrix
// ----------------------------------------------------------------------------
Matrix Matrix::MakeNewTranslation(const Vec3 &trans)
{
  Matrix m;
  m.Translation(trans);
  return m;
} // MakeNewTranslation


// ----------------------------------------------------------------------------
// Make a new scaling matrix
// ----------------------------------------------------------------------------
Matrix Matrix::MakeNewScaling(float x, float y, float z)
{
  Matrix m;
  m.Scaling(x, y, x);
  return m;
} // MakeNewScaling


// ----------------------------------------------------------------------------
// Get the ientity reference matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::GetIdentityRef()
{
  static Matrix m = Matrix::MakeNewIdentity();
  return m;
} // GetIdentityRef


// ----------------------------------------------------------------------------
// Affine transform
// ----------------------------------------------------------------------------
Matrix &Matrix::AffineTransformation(float scaling, const Vec3 &rotation_center, 
                                    const Quat &rotation, const Vec3 &translation)
{
  D3DXMatrixAffineTransformation(this, scaling, 
      &rotation_center, &rotation, &translation);
  return *this;
} // AffineTransformation


// ----------------------------------------------------------------------------
// Affine transform in 2D
// ----------------------------------------------------------------------------
Matrix &Matrix::AffineTransformation2D(float scaling, const Vec2 &rotation_center, 
                                      float rotation, const Vec2 &translation)
{
  D3DXMatrixAffineTransformation2D(this, scaling, &rotation_center, 
    rotation, &translation);
  return *this;
} //AffineTransformation2D


// ----------------------------------------------------------------------------
// Get the determinant
// ----------------------------------------------------------------------------
float Matrix::Determinant()
{
  return D3DXMatrixDeterminant(this);
} // Determinant


// ----------------------------------------------------------------------------
// Make the matrix the identity matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::Identity()
{
  D3DXMatrixIdentity(this);
  return *this;
} // Identity


// ----------------------------------------------------------------------------
// Get the inverse
// ----------------------------------------------------------------------------
Matrix &Matrix::Inverse(float determinant, const Matrix &m)
{
  D3DXMatrixInverse(this, &determinant, &m);
  return *this;
} // Inverse


// ----------------------------------------------------------------------------
// Get the inverse
// ----------------------------------------------------------------------------
Matrix &Matrix::Inverse(const Matrix &m)
{
  D3DXMatrixInverse(this, 0, &m);
  return *this;
} // Inverse


// ----------------------------------------------------------------------------
// Is the matrix identity?
// ----------------------------------------------------------------------------
bool Matrix::IsIdentity()
{
  return D3DXMatrixIsIdentity(this) == TRUE;
} // IsIdentity


// ----------------------------------------------------------------------------
// LookAt Matrix (LH)
// ----------------------------------------------------------------------------
Matrix &Matrix::LookAtLH(const Vec3 &eye, const Vec3 &at, const Vec3 &up)
{
  D3DXMatrixLookAtLH(this, &eye, &at, &up);
  return *this;
} // LookAtLH


// ----------------------------------------------------------------------------
// LookAt Matrix (RH)
// ----------------------------------------------------------------------------
Matrix &Matrix::LookAtRH(const Vec3 &eye, const Vec3 &at, const Vec3 &up)
{
  D3DXMatrixLookAtRH(this, &eye, &at, &up);
  return *this;
} // LookAtRH


// ----------------------------------------------------------------------------
// Multiply two matrices
// ----------------------------------------------------------------------------
Matrix &Matrix::Multiply(const Matrix &m1, const Matrix &m2)
{
  D3DXMatrixMultiply(this, &m1, &m2);
  return *this;
} // Multiply


// ----------------------------------------------------------------------------
// Premultiply this matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::PreMultiply(const Matrix &m)
{
  D3DXMatrixMultiply(this, this, &m);
  return *this;
} // Multiply


// ----------------------------------------------------------------------------
// Postmultiply this matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::PostMultiply(const Matrix &m)
{
  D3DXMatrixMultiply(this, &m, this);
  return *this;
} // Multiply


// ----------------------------------------------------------------------------
// Multply and transpose this matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::MultiplyTranspose(const Matrix &m1, const Matrix &m2)
{
  D3DXMatrixMultiplyTranspose(this, &m1, &m2);
  return *this;
} // MultiplyTranspose


// ----------------------------------------------------------------------------
// Orthographic matrix (LH)
// ----------------------------------------------------------------------------
Matrix &Matrix::OrthoLH(float width, float height, float z_near, float z_far)
{
  D3DXMatrixOrthoLH(this, width, height, z_near, z_far);
  return *this;
} // OrthoLH


// ----------------------------------------------------------------------------
// Orthographic matrix (RH)
// ----------------------------------------------------------------------------
Matrix &Matrix::OrthoRH(float width, float height, float z_near, float z_far)
{
  D3DXMatrixOrthoRH(this, width, height, z_near, z_far);
  return *this;
} // OrthoRH


// ----------------------------------------------------------------------------
// Orthographic matrix (LH off center)
// ----------------------------------------------------------------------------
Matrix &Matrix::OrthoOffCenterLH(float left, float right, float bottom, 
                                float top, float z_near, float z_far)
{
  D3DXMatrixOrthoOffCenterLH(this, left, right, bottom, top, z_near, z_far);
  return *this;
} // OrthoOffCenterLH


// ----------------------------------------------------------------------------
// Orthographic matrix (RH off center)
// ----------------------------------------------------------------------------
Matrix &Matrix::OrthoOffCenterRH(float left, float right, float bottom, 
                                float top, float z_near, float z_far)
{
  D3DXMatrixOrthoOffCenterRH(this, left, right, top, bottom, z_near, z_far);
  return *this;
} // OrthoOffCenterRH


// ----------------------------------------------------------------------------
// Perspective FOV matrix (LH)
// ----------------------------------------------------------------------------
Matrix &Matrix::PerspectiveFovLH(float fov, float aspect, float z_near, float z_far)
{
  D3DXMatrixPerspectiveFovLH(this, fov, aspect, z_near, z_far);
  return *this;
} // PerspectiveFovLH


// ----------------------------------------------------------------------------
// Perspectice FOV matrix (RH)
// ----------------------------------------------------------------------------
Matrix &Matrix::PerspectiveFovRH(float fov, float aspect, float z_near, float z_far)
{
  D3DXMatrixPerspectiveFovRH(this, fov, aspect, z_near, z_far);
  return *this;
} // PerspectiveFovRH 


// ----------------------------------------------------------------------------
// Perspective matrix (LH)
// ----------------------------------------------------------------------------
Matrix &Matrix::PerspectiveLH(float width, float height, float z_near, float z_far)
{
  D3DXMatrixPerspectiveLH(this, width, height, z_near, z_far);
  return *this;
} // PerspectiveLH


// ----------------------------------------------------------------------------
// Perspective matrix (RH)
// ----------------------------------------------------------------------------
Matrix &Matrix::PerspectiveRH(float width, float height, float z_near, float z_far)
{
  D3DXMatrixPerspectiveRH(this, width, height, z_near, z_far);
  return *this;
} // PerspectiveRH


// ----------------------------------------------------------------------------
// Perspective off center matrix (LH)
// ----------------------------------------------------------------------------
Matrix &Matrix::PerspectiveOffCenterLH(float left, float right, float bottom, 
                                      float top, float z_near, float z_far)
{
  D3DXMatrixPerspectiveOffCenterLH(this, left, right, bottom, top, z_near, z_far);
  return *this;
} // PerspectiveOffCenterLH


// ----------------------------------------------------------------------------
// Perspective off center matrix (RH)
// ----------------------------------------------------------------------------
Matrix &Matrix::PerspectiveOffCenterRH(float left, float right, float bottom, 
                                      float top, float z_near, float z_far)
{
  D3DXMatrixPerspectiveOffCenterRH(this, left, right, bottom, top, z_near, z_far);
  return *this;
} // PerspectiveOffCenterRH


// ----------------------------------------------------------------------------
// Reflection matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::Reflect(const Plane &plane)
{
  D3DXMatrixReflect(this, &plane);
  return *this;
} // Reflect


// ----------------------------------------------------------------------------
// Shadow matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::Shadow(const Vec4 &light, const Plane &plane)
{
  D3DXMatrixShadow(this, &light, &plane);
  return *this;
} // Shadow


// ----------------------------------------------------------------------------
// Rotation axis matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::RotationAxis(const Vec3 &axis, float angle)
{
  D3DXMatrixRotationAxis(this, &axis, angle);
  return *this;
} // RotationAxis


// ----------------------------------------------------------------------------
// Rotation quaternion matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::RotationQuaternion(const Quat &q)
{
  D3DXMatrixRotationQuaternion(this, &q);
  return *this;
} // RotationQuaternion


// ----------------------------------------------------------------------------
// Rotation HPR matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::RotationYawPitchRoll(float yaw, float pitch, float roll)
{
  D3DXMatrixRotationYawPitchRoll(this, yaw, pitch, roll);
  return *this;
} // RotationYawPitchRoll


// ----------------------------------------------------------------------------
// Rotation matrix around x axis
// ----------------------------------------------------------------------------
Matrix &Matrix::RotationX(float angle)
{
  D3DXMatrixRotationX(this, angle);
  return *this;
} // RotationX


// ----------------------------------------------------------------------------
// Rotation matrix around y axis
// ----------------------------------------------------------------------------
Matrix &Matrix::RotationY(float angle)
{
  D3DXMatrixRotationY(this, angle);
  return *this;
} // RotationY


// ----------------------------------------------------------------------------
// Rotation matrix around z xis
// ----------------------------------------------------------------------------
Matrix &Matrix::RotationZ(float angle)
{
  D3DXMatrixRotationZ(this, angle);
  return *this;
} // RotationZ


// ----------------------------------------------------------------------------
// Scaling matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::Scaling(float x, float y, float z)
{
  D3DXMatrixScaling(this, x, y, z);
  return *this;
} // Scaling


// ----------------------------------------------------------------------------
// Transformation matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::Transformation(const Vec3 &scaling_center, const Quat &scaling_rotation, const Vec3 &scaling,
  const Vec3 &rotation_center, const Quat &rotation, const Vec3 &translation)
{
  D3DXMatrixTransformation(this, &scaling_center, &scaling_rotation, &scaling, 
      &rotation_center, &rotation, &translation);
  return *this;
} // Transformation


// ----------------------------------------------------------------------------
// Transformation matrix (2D)
// ----------------------------------------------------------------------------
Matrix &Matrix::Transformation2D(const Vec2 &scaling_center, float scaling_rotation, const Vec2 &scaling,
  const Vec2 &rotation_center, float rotation, const Vec2 &translation)
{
  D3DXMatrixTransformation2D(this, &scaling_center, scaling_rotation, &scaling, 
    &rotation_center, rotation, &translation);
  return *this;
} // Transformation2D


// ----------------------------------------------------------------------------
// Translation matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::Translation(float x, float y, float z)
{
  D3DXMatrixTranslation(this, x, y, z);
  return *this;
} // Translation


// ----------------------------------------------------------------------------
// Translation matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::Translation(const Vec3 &trans)
{
  D3DXMatrixTranslation(this, trans[0], trans[1], trans[2]);
  return *this;
} // Translation


// ----------------------------------------------------------------------------
// Transpose the matrix
// ----------------------------------------------------------------------------
Matrix &Matrix::Transpose(const Matrix &m)
{
  D3DXMatrixTranspose(this, &m);
  return *this;
} // Transpose


// -- EOF

