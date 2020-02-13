// ----------------------------------------------------------------------------
// File: Vec4.cpp
// Desc: 4D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Vec4.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Matrix.h"


Vec4::Vec4()                                    : D3DXVECTOR4()             {}
Vec4::Vec4(const float *f)                      : D3DXVECTOR4(f)            {}
Vec4::Vec4(const D3DXFLOAT16 *f)                : D3DXVECTOR4(f)            {}
Vec4::Vec4(float x, float y, float z, float w)  : D3DXVECTOR4(x, y, z, w)   {}

    
Vec4 &Vec4::Set(float x, float y, float z, float w)
{
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
    (*this)[3] = w;
    return *this;
} // Set
	
	
Vec4 &Vec4::Add(const Vec4 &v1, const Vec4 &v2)
{
    D3DXVec4Add(this, &v1, &v2);
    return *this;
} // Add
	
	
Vec4 &Vec4::Scale(const Vec4 &v, float s)
{
    D3DXVec4Scale(this, &v, s);
    return *this;
} // Scale
	
	
Vec4 &Vec4::Subtract(const Vec4 &v1, const Vec4 &v2)
{
    D3DXVec4Subtract(this, &v1, &v2);
    return *this;
} // Subtract
	
	
Vec4 &Vec4::Lerp(const Vec4 &v1, const Vec4 &v2, float s)
{
    D3DXVec4Lerp(this, &v1, &v2, s);
    return *this;
} // Lerp
	
	
Vec4 &Vec4::Normalize(const Vec4 &v1)
{
    D3DXVec4Normalize(this, &v1);
    return *this;
} // Normalize
	
	
Vec4 &Vec4::Maximize(const Vec4 &v1, const Vec4 &v2)
{
    D3DXVec4Maximize(this, &v1, &v2);
    return *this;
} // Maximize
	
	
Vec4 &Vec4::Minimize(const Vec4 &v1, const Vec4 &v2)
{
    D3DXVec4Minimize(this, &v1, &v2);
    return *this;
} // Minimize
	
	
float Vec4::Dot(const Vec4 &v)
{
    return D3DXVec4Dot(this, &v);
} // Dot
	
	
float Vec4::Length()
{
    return D3DXVec4Length(this);
} // Length
	
	
float Vec4::LengthSq()
{
    return D3DXVec4LengthSq(this);
} // LengthSq
	
	
Vec4 &Vec4::BaryCentric(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, 
                        float f, float g)
{
    D3DXVec4BaryCentric(this, &v1, &v2, &v3, f, g);
    return *this;
} // BaryCentric
	
	
Vec4 &Vec4::CatmullRom(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, 
                       const Vec4 &v4, float s)
{
    D3DXVec4CatmullRom(this, &v1, &v2, &v3, &v4, s);
    return *this;
} // CatmullRom
	
	
Vec4 &Vec4::Hermite(const Vec4 &v1, const Vec4 &t1, const Vec4 &v2, 
                    const Vec4 &t2, float s)
{
    D3DXVec4Hermite(this, &v1, &t1, &v2, &t2, s);
    return *this;
} // Hermite
	
	
Vec4 &Vec4::Cross(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3)
{
    D3DXVec4Cross(this, &v1, &v2, &v3);
    return *this;
} // Cross


Vec4 &Vec4::Transform(const Vec2 &v, const Matrix &m)
{
    D3DXVec2Transform(this, &v, &m);
    return *this;
} // Transform
	
	
Vec4 &Vec4::Transform(const Vec3 &v, const Matrix &m)
{
    D3DXVec3Transform(this, &v, &m);
    return *this;
} // Transform
	
	
Vec4 &Vec4::Transform(const Vec4 &v, const Matrix &m)
{
    D3DXVec4Transform(this, &v, &m);
    return *this;
} // Transform
	

Vec4 &Vec4::TransformArray(uint out_stride, const Vec2 *vec_array, 
                           uint v_stride, const Matrix &m, uint n)
{
    D3DXVec2TransformArray(this, out_stride, vec_array, v_stride, &m, n);
    return *this;
} // TransformArray


Vec4 &Vec4::TransformArray(uint out_stride, const Vec3 *vec_array, 
                           uint v_stride, const Matrix &m, uint n)
{
    D3DXVec3TransformArray(this, out_stride, vec_array, v_stride, &m, n);
    return *this;
} // TransformArray


Vec4 &Vec4::TransformArray(uint out_stride, const Vec4 *vec_array, 
                           uint v_stride, const Matrix &m, uint n)
{
    D3DXVec4TransformArray(this, out_stride, vec_array, v_stride, &m, n);
    return *this;
} // TransformArray


// -- EOF

