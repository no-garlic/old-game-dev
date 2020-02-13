// ----------------------------------------------------------------------------
// File: Vec4.h
// Desc: 4D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _VEC4_H
#define _VEC4_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Vec2;
class Vec3;
class Vec4;
class Matrix;


// ----------------------------------------------------------------------------
// Name: Vec4  (class)
// Desc: 4D vector
// ----------------------------------------------------------------------------
class Vec4 : public D3DXVECTOR4
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    Vec4();
    Vec4(const float *f);
    Vec4(const D3DXFLOAT16 *f);
    Vec4(float x, float y, float z, float w);

    // ------------------------------------------------------------------------
    // Member functions
    // ------------------------------------------------------------------------
    float   Dot(const Vec4 &v);
    float   Length();
    float   LengthSq();
    Vec4   &Set(float x, float y, float z, float w);
    Vec4   &Add(const Vec4 &v1, const Vec4 &v2);
    Vec4   &Scale(const Vec4 &v, float s);
    Vec4   &Subtract(const Vec4 &v1, const Vec4 &v2);
    Vec4   &Lerp(const Vec4 &v1, const Vec4 &v2, float s);
    Vec4   &Normalize(const Vec4 &v1);
    Vec4   &Maximize(const Vec4 &v1, const Vec4 &v2);
    Vec4   &Minimize(const Vec4 &v1, const Vec4 &v2);
    Vec4   &BaryCentric(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, float f, float g);
    Vec4   &CatmullRom(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4, float s);
    Vec4   &Hermite(const Vec4 &v1, const Vec4 &t1, const Vec4 &v2, const Vec4 &t2, float s);
    Vec4   &Cross(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);
    Vec4   &Transform(const Vec2 &v, const Matrix &m);
    Vec4   &Transform(const Vec3 &v, const Matrix &m);
    Vec4   &Transform(const Vec4 &v, const Matrix &m);
    Vec4   &TransformArray(uint out_stride, const Vec2 *vec_array, 
              uint v_stride, const Matrix &m, uint n);
    Vec4   &TransformArray(uint out_stride, const Vec3 *vec_array, 
              uint v_stride, const Matrix &m, uint n);
    Vec4   &TransformArray(uint out_stride, const Vec4 *vec_array, 
              uint v_stride, const Matrix &m, uint n);

}; // class Vec4


#endif //_VEC4_H

// -- EOF

