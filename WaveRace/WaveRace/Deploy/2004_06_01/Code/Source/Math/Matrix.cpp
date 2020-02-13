// ----------------------------------------------------------------------------
// File: Matrix.cpp
// Desc: Describes a matrix
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Matrix.h"
#include "Math/Plane.h"
#include "Math/Quat.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include "Math/Coords.h"


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

Matrix Matrix::MakeNewIdentity()
{
    Matrix m;
    m.Identity();
    return m;
} // MakeNewIdentity


Matrix Matrix::MakeNewCoords(const Coords &coords)
{
    Matrix m;
    m.Set(coords);
    return m;
} // MakeNewCoords


Matrix Matrix::MakeNewRotationAxis(const Vec3 &axis, float angle)
{
    Matrix m;
    m.RotationAxis(axis, angle);
    return m;
} // MakeNewRotationAxis


Matrix Matrix::MakeNewRotationQuaternion(const Quat &q)
{
    Matrix m;
    m.RotationQuaternion(q);
    return m;
} // MakeNewRotationQuaternion


Matrix Matrix::MakeNewRotationYawPitchRoll(float yaw, float pitch, float roll)
{
    Matrix m;
    m.RotationYawPitchRoll(yaw, pitch, roll);
    return m;
} // MakeNewRotationYawPitchRoll


Matrix Matrix::MakeNewTranslation(float x, float y, float z)
{
    Matrix m;
    m.Translation(x, y, z);
    return m;
} // MakeNewTranslation


Matrix Matrix::MakeNewTranslation(const Vec3 &trans)
{
    Matrix m;
    m.Translation(trans);
    return m;
} // MakeNewTranslation


Matrix Matrix::MakeNewScaling(float x, float y, float z)
{
    Matrix m;
    m.Scaling(x, y, x);
    return m;
} // MakeNewScaling


Matrix &Matrix::GetIdentityRef()
{
    static Matrix m = Matrix::MakeNewIdentity();
    return m;
} // GetIdentityRef


Matrix &Matrix::AffineTransformation(float scaling, const Vec3 &rotation_center, 
                                     const Quat &rotation, const Vec3 &translation)
{
    D3DXMatrixAffineTransformation(this, scaling, 
        &rotation_center, &rotation, &translation);
    return *this;
} // AffineTransformation


Matrix &Matrix::AffineTransformation2D(float scaling, const Vec2 &rotation_center, 
                                       float rotation, const Vec2 &translation)
{
//    D3DXMatrixAffineTransformation2D(this, scaling, &rotation_center, 
//        rotation, &translation);
    return *this;
} //AffineTransformation2D


float Matrix::Determinant()
{
    return D3DXMatrixDeterminant(this);
} // Determinant


Matrix &Matrix::Identity()
{
    D3DXMatrixIdentity(this);
    return *this;
} // Identity


Matrix &Matrix::Set(const Coords &coords)
{
    Matrix mt, mr;
    D3DXMatrixTranslation(&mt, coords.xyz[0], coords.xyz[1], coords.xyz[2]);
    D3DXMatrixRotationQuaternion(&mr, &coords.quat);
    D3DXMatrixMultiply(this, &mr, &mt);
    return *this;
} // Set


Matrix &Matrix::Inverse(float determinant, const Matrix &m)
{
    D3DXMatrixInverse(this, &determinant, &m);
    return *this;
} // Inverse


Matrix &Matrix::Inverse(const Matrix &m)
{
    D3DXMatrixInverse(this, 0, &m);
    return *this;
} // Inverse


bool Matrix::IsIdentity()
{
    return D3DXMatrixIsIdentity(this) == TRUE;
} // IsIdentity


Matrix &Matrix::LookAtLH(const Vec3 &eye, const Vec3 &at, const Vec3 &up)
{
    D3DXMatrixLookAtLH(this, &eye, &at, &up);
    return *this;
} // LookAtLH


Matrix &Matrix::LookAtRH(const Vec3 &eye, const Vec3 &at, const Vec3 &up)
{
    D3DXMatrixLookAtRH(this, &eye, &at, &up);
    return *this;
} // LookAtRH


Matrix &Matrix::Multiply(const Matrix &m1, const Matrix &m2)
{
    D3DXMatrixMultiply(this, &m1, &m2);
    return *this;
} // Multiply


Matrix &Matrix::PreMultiply(const Matrix &m)
{
    D3DXMatrixMultiply(this, this, &m);
    return *this;
} // Multiply


Matrix &Matrix::PostMultiply(const Matrix &m)
{
    D3DXMatrixMultiply(this, &m, this);
    return *this;
} // Multiply


Matrix &Matrix::MultiplyTranspose(const Matrix &m1, const Matrix &m2)
{
    D3DXMatrixMultiplyTranspose(this, &m1, &m2);
    return *this;
} // MultiplyTranspose


Matrix &Matrix::OrthoLH(float width, float height, float z_near, float z_far)
{
    D3DXMatrixOrthoLH(this, width, height, z_near, z_far);
    return *this;
} // OrthoLH


Matrix &Matrix::OrthoRH(float width, float height, float z_near, float z_far)
{
    D3DXMatrixOrthoRH(this, width, height, z_near, z_far);
    return *this;
} // OrthoRH


Matrix &Matrix::OrthoOffCenterLH(float left, float right, float bottom, 
                                 float top, float z_near, float z_far)
{
    D3DXMatrixOrthoOffCenterLH(this, left, right, bottom, top, z_near, z_far);
    return *this;
} // OrthoOffCenterLH


Matrix &Matrix::OrthoOffCenterRH(float left, float right, float bottom, 
                                 float top, float z_near, float z_far)
{
    D3DXMatrixOrthoOffCenterRH(this, left, right, top, bottom, z_near, z_far);
    return *this;
} // OrthoOffCenterRH


Matrix &Matrix::PerspectiveFovLH(float fov, float aspect, float z_near, float z_far)
{
    D3DXMatrixPerspectiveFovLH(this, fov, aspect, z_near, z_far);
    return *this;
} // PerspectiveFovLH


Matrix &Matrix::PerspectiveFovRH(float fov, float aspect, float z_near, float z_far)
{
    D3DXMatrixPerspectiveFovRH(this, fov, aspect, z_near, z_far);
    return *this;
} // PerspectiveFovRHfloat 


Matrix &Matrix::PerspectiveLH(float width, float height, float z_near, float z_far)
{
    D3DXMatrixPerspectiveLH(this, width, height, z_near, z_far);
    return *this;
} // PerspectiveLH


Matrix &Matrix::PerspectiveRH(float width, float height, float z_near, float z_far)
{
    D3DXMatrixPerspectiveRH(this, width, height, z_near, z_far);
    return *this;
} // PerspectiveRH


Matrix &Matrix::PerspectiveOffCenterLH(float left, float right, float bottom, 
                                       float top, float z_near, float z_far)
{
    D3DXMatrixPerspectiveOffCenterLH(this, left, right, bottom, top, z_near, z_far);
    return *this;
} // PerspectiveOffCenterLH


Matrix &Matrix::PerspectiveOffCenterRH(float left, float right, float bottom, 
                                       float top, float z_near, float z_far)
{
    D3DXMatrixPerspectiveOffCenterRH(this, left, right, bottom, top, z_near, z_far);
    return *this;
} // PerspectiveOffCenterRH


Matrix &Matrix::Reflect(const Plane &plane)
{
    D3DXMatrixReflect(this, &plane);
    return *this;
} // Reflect


Matrix &Matrix::Shadow(const Vec4 &light, const Plane &plane)
{
    D3DXMatrixShadow(this, &light, &plane);
    return *this;
} // Shadow


Matrix &Matrix::RotationAxis(const Vec3 &axis, float angle)
{
    D3DXMatrixRotationAxis(this, &axis, angle);
    return *this;
} // RotationAxis


Matrix &Matrix::RotationQuaternion(const Quat &q)
{
    D3DXMatrixRotationQuaternion(this, &q);
    return *this;
} // RotationQuaternion


Matrix &Matrix::RotationYawPitchRoll(float yaw, float pitch, float roll)
{
    D3DXMatrixRotationYawPitchRoll(this, yaw, pitch, roll);
    return *this;
} // RotationYawPitchRoll


Matrix &Matrix::RotationX(float angle)
{
    D3DXMatrixRotationX(this, angle);
    return *this;
} // RotationX


Matrix &Matrix::RotationY(float angle)
{
    D3DXMatrixRotationY(this, angle);
    return *this;
} // RotationY


Matrix &Matrix::RotationZ(float angle)
{
    D3DXMatrixRotationZ(this, angle);
    return *this;
} // RotationZ


Matrix &Matrix::Scaling(float x, float y, float z)
{
    D3DXMatrixScaling(this, x, y, z);
    return *this;
} // Scaling


Matrix &Matrix::Transformation(const Vec3 &scaling_center, const Quat &scaling_rotation, const Vec3 &scaling,
    const Vec3 &rotation_center, const Quat &rotation, const Vec3 &translation)
{
    D3DXMatrixTransformation(this, &scaling_center, &scaling_rotation, &scaling, 
        &rotation_center, &rotation, &translation);
    return *this;
} // Transformation


Matrix &Matrix::Transformation2D(const Vec2 &scaling_center, float scaling_rotation, const Vec2 &scaling,
    const Vec2 &rotation_center, float rotation, const Vec2 &translation)
{
//    D3DXMatrixTransformation2D(this, &scaling_center, scaling_rotation, &scaling, 
//        &rotation_center, rotation, &translation);
    return *this;
} // Transformation2D


Matrix &Matrix::Translation(float x, float y, float z)
{
    D3DXMatrixTranslation(this, x, y, z);
    return *this;
} // Translation


Matrix &Matrix::Translation(const Vec3 &trans)
{
    D3DXMatrixTranslation(this, trans[0], trans[1], trans[2]);
    return *this;
} // Translation


Matrix &Matrix::Transpose(const Matrix &m)
{
    D3DXMatrixTranspose(this, &m);
    return *this;
} // Transpose


// -- EOF

