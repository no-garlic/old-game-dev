// ----------------------------------------------------------------------------
// File: Vec2.cpp
// Desc: 2D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Vec2.h"
#include "Math/Matrix.h"


Vec2::Vec2()                        : D3DXVECTOR2()     {}
Vec2::Vec2(const float *f)          : D3DXVECTOR2(f)    {}
Vec2::Vec2(const D3DXFLOAT16 *f)    : D3DXVECTOR2(f)    {}
Vec2::Vec2(float x, float y)        : D3DXVECTOR2(x, y) {}


Vec2 &Vec2::Clamp(Vec2 &v1, float c)
{
    (*this)[0] = std::min<float>(c, v1[0]);
    (*this)[1] = std::min<float>(c, v1[1]);
    return *this;
} // Clamp


Vec2 &Vec2::Set(float x, float y)
{
    (*this)[0] = x;
    (*this)[1] = y;
    return *this;
} // Set
	
	
Vec2 &Vec2::Add(const Vec2 &v1, const Vec2 &v2)
{
    D3DXVec2Add(this, &v1, &v2);
    return *this;
} // Add
	
	
Vec2 &Vec2::Scale(const Vec2 &v, float s)
{
    D3DXVec2Scale(this, &v, s);
    return *this;
} // Scale
	
	
Vec2 &Vec2::Subtract(const Vec2 &v1, const Vec2 &v2)
{
    D3DXVec2Subtract(this, &v1, &v2);
    return *this;
} // Subtract
	
	
Vec2 &Vec2::Lerp(const Vec2 &v1, const Vec2 &v2, float s)
{
    D3DXVec2Lerp(this, &v1, &v2, s);
    return *this;
} // Lerp
	
	
Vec2 &Vec2::Maximize(const Vec2 &v1, const Vec2 &v2)
{
    D3DXVec2Maximize(this, &v1, &v2);
    return *this;
} // Maximize
	
	
Vec2 &Vec2::Minimize(const Vec2 &v1, const Vec2 &v2)
{
    D3DXVec2Minimize(this, &v1, &v2);
    return *this;
} // Minimize
	
	
float Vec2::CCW(const Vec2 &v)
{
    return D3DXVec2CCW(this, &v);
} // Dot
	
	
float Vec2::Dot(const Vec2 &v)
{
    return D3DXVec2Dot(this, &v);
} // Dot
	
	
float Vec2::Length()
{
    return D3DXVec2Length(this);
} // Length
	
	
float Vec2::LengthSq()
{
    return D3DXVec2LengthSq(this);
} // LengthSq
	
	
Vec2 &Vec2::BaryCentric(const Vec2 &v1, const Vec2 &v2, 
    const Vec2 &v3, float f, float g)
{
    D3DXVec2BaryCentric(this, &v1, &v2, &v3, f, g);
    return *this;
} // BaryCentric
	
	
Vec2 &Vec2::CatmullRom(const Vec2 &v1, const Vec2 &v2, 
    const Vec2 &v3, const Vec2 &v4, float s)
{
    D3DXVec2CatmullRom(this, &v1, &v2, &v3, &v4, s);
    return *this;
} // CatmullRom
	
	
Vec2 &Vec2::Hermite(const Vec2 &v1, const Vec2 &t1, 
    const Vec2 &v2, const Vec2 &t2, float s)
{
    D3DXVec2Hermite(this, &v1, &t1, &v2, &t2, s);
    return *this;
} // Hermite
	

Vec2 &Vec2::TransformCoord(const Vec2 &v, const Matrix &m)
{
    D3DXVec2TransformCoord(this, &v, &m);
    return *this;
} // TransformCoord
	
	
Vec2 &Vec2::TransformNormal(const Vec2 &v, const Matrix &m)
{
    D3DXVec2TransformNormal(this, &v, &m);
    return *this;
} // TransformNormal
	

Vec2 &Vec2::TransformCoordArray(uint out_stride, const Vec2 *vec_array, 
    uint v_stride, const Matrix &m, uint n)
{
    D3DXVec2TransformCoordArray(this, out_stride, vec_array, v_stride, &m, n);
    return *this;
} // TransformCoordArray


Vec2 &Vec2::TransformNormalArray(uint out_stride, const Vec2 *vec_array, 
    uint v_stride, const Matrix &m, uint n)
{
    D3DXVec2TransformNormalArray(this, out_stride, vec_array, v_stride, &m, n);
    return *this;
} // TransformNormalArray


// -- EOF

