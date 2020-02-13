// ----------------------------------------------------------------------------
// File: Vec3.cpp
// Desc: 3D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Math/Vec4.h"
#include "Math/Plane.h"
#include "Math/Matrix.h"


Vec3::Vec3()                          : D3DXVECTOR3()         {}
Vec3::Vec3(const float *f)            : D3DXVECTOR3(f)        {}
Vec3::Vec3(const D3DVECTOR &v)        : D3DXVECTOR3(v)        {}
Vec3::Vec3(const D3DXFLOAT16 *f)      : D3DXVECTOR3(f)        {}
Vec3::Vec3(float x, float y, float z) : D3DXVECTOR3(x, y, z)  {}

    
Vec3 &Vec3::Clamp(Vec3 &v1, float c)
{
    (*this)[0] = std::min<float>(c, v1[0]);
    (*this)[1] = std::min<float>(c, v1[1]);
    (*this)[2] = std::min<float>(c, v1[2]);
    return *this;
} // Clamp


Vec3 &Vec3::Set(float x, float y, float z)
{
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
    return *this;
} // Set
	
	
Vec3 &Vec3::Add(const Vec3 &v1, const Vec3 &v2)
{
    D3DXVec3Add(this, &v1, &v2);
    return *this;
} // Add
	
	
Vec3 &Vec3::Scale(const Vec3 &v, float s)
{
    D3DXVec3Scale(this, &v, s);
    return *this;
} // Scale
	
	
Vec3 &Vec3::Subtract(const Vec3 &v1, const Vec3 &v2)
{
    D3DXVec3Subtract(this, &v1, &v2);
    return *this;
} // Subtract
	
	
Vec3 &Vec3::Lerp(const Vec3 &v1, const Vec3 &v2, float s)
{
    D3DXVec3Lerp(this, &v1, &v2, s);
    return *this;
} // Lerp
	
	
Vec3 &Vec3::Normalize(const Vec3 &v1)
{
    D3DXVec3Normalize(this, &v1);
    return *this;
} // Normalize
	
	
Vec3 &Vec3::Maximize(const Vec3 &v1, const Vec3 &v2)
{
    D3DXVec3Maximize(this, &v1, &v2);
    return *this;
} // Maximize
	
	
Vec3 &Vec3::Minimize(const Vec3 &v1, const Vec3 &v2)
{
    D3DXVec3Minimize(this, &v1, &v2);
    return *this;
} // Minimize
	
	
float Vec3::Dot(const Vec3 &v)
{
    return D3DXVec3Dot(this, &v);
} // Dot
	
	
float Vec3::Length()
{
    return D3DXVec3Length(this);
} // Length
	
	
float Vec3::LengthSq()
{
    return D3DXVec3LengthSq(this);
} // LengthSq
	
	
Vec3 &Vec3::BaryCentric(const Vec3 &v1, const Vec3 &v2, 
                        const Vec3 &v3, float f, float g)
{
    D3DXVec3BaryCentric(this, &v1, &v2, &v3, f, g);
    return *this;
} // BaryCentric
	
	
Vec3 &Vec3::CatmullRom(const Vec3 &v1, const Vec3 &v2, 
                       const Vec3 &v3, const Vec3 &v4, float s)
{
    D3DXVec3CatmullRom(this, &v1, &v2, &v3, &v4, s);
    return *this;
} // CatmullRom
	
	
Vec3 &Vec3::Hermite(const Vec3 &v1, const Vec3 &t1, const Vec3 &v2, 
                    const Vec3 &t2, float s)
{
    D3DXVec3Hermite(this, &v1, &t1, &v2, &t2, s);
    return *this;
} // Hermite
	

Vec3 &Vec3::Cross(const Vec3 &v1, const Vec3 &v2)
{
    D3DXVec3Cross(this, &v1, &v2);
    return *this;
} // Cross


Vec3 &Vec3::PlaneIntersectLine(const Plane &p, const Vec3 &v1, const Vec3 &v2)
{
    // TODO
    // This may break - D3DX function can set p1 as NULL
    D3DXPlaneIntersectLine(this, &p, &v1, &v2);
    return *this;
} // PlaneIntersectLine


Vec3 &Vec3::TransformCoord(const Vec3 &v, const Matrix &m)
{
    D3DXVec3TransformCoord(this, &v, &m);
    return *this;
} // TransformCoord
	
	
Vec3 &Vec3::TransformNormal(const Vec3 &v, const Matrix &m)
{
    D3DXVec3TransformNormal(this, &v, &m);
    return *this;
} // TransformNormal
	

Vec3 &Vec3::TransformCoordArray(uint out_stride, const Vec3 *vec_array, 
                                uint v_stride, const Matrix &m, uint n)
{
    D3DXVec3TransformCoordArray(this, out_stride, vec_array, v_stride, &m, n);
    return *this;
} // TransformCoordArray


Vec3 &Vec3::TransformNormalArray(uint out_stride, const Vec3 *vec_array, 
                                 uint v_stride, const Matrix &m, uint n)
{
    D3DXVec3TransformNormalArray(this, out_stride, vec_array, v_stride, &m, n);
    return *this;
} // TransformNormalArray


Vec3 &Vec3::Project(const Vec3 &v, D3DVIEWPORT9 *viewport, const Matrix &projection, 
                    const Matrix &view, const Matrix &world)
{
    D3DXVec3Project(this, &v, viewport, &projection, &view, &world);
    return *this;
} // Project


Vec3 &Vec3::Unproject(const Vec3 &v, D3DVIEWPORT9 *viewport, const Matrix &projection, 
                      const Matrix &view, const Matrix &world)
{
    D3DXVec3Unproject(this, &v, viewport, &projection, &view, &world);
    return *this;
} // Unproject


Vec3 &Vec3::ProjectArray(uint out_stride, const Vec3 *vec_array, 
                         uint v_stride, D3DVIEWPORT9 *viewport, const Matrix &projection, 
                         const Matrix &view, const Matrix &world, uint n)
{
    D3DXVec3ProjectArray(this, out_stride, vec_array, v_stride,
        viewport, &projection, &view, &world, n);
    return *this;
} // ProjectArray


Vec3 &Vec3::UnprojectArray(uint out_stride, const Vec3 *vec_array, uint v_stride, 
                           D3DVIEWPORT9 *viewport, const Matrix &projection, 
                           const Matrix &view, const Matrix &world, uint n)
{
    D3DXVec3UnprojectArray(this, out_stride, vec_array, v_stride,
        viewport, &projection, &view, &world, n);
    return *this;
} // UnprojectArray


// -- EOF

