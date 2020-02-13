// ----------------------------------------------------------------------------
// File: Vec2.h
// Desc: 2D vector
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _VECTOR2_H
#define _VECTOR2_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"
#include <sstream>


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Matrix;


// ----------------------------------------------------------------------------
// Name: Vec2  (class)
// Desc: 2D vector
// ----------------------------------------------------------------------------
class Vec2 : public D3DXVECTOR2
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    Vec2();
    Vec2(const float *f);
    Vec2(const D3DXFLOAT16 *f);
    Vec2(float x, float y);


    // ------------------------------------------------------------------------
    // Member functions
    // ------------------------------------------------------------------------
    float   CCW(const Vec2 &v1);
    float   Dot(const Vec2 &v1);
    float   Length();
    float   LengthSq();
    Vec2    &Set(float x, float y);
    Vec2    &Add(const Vec2 &v1, const Vec2 &v2);
    Vec2    &Scale(const Vec2 &v, float s);
    Vec2    &Subtract(const Vec2 &v1, const Vec2 &v2);
    Vec2    &Lerp(const Vec2 &v1, const Vec2 &v2, float s);
    Vec2    &Normalize(const Vec2 &v1);
    Vec2    &Maximize(const Vec2 &v1, const Vec2 &v2);
    Vec2    &Minimize(const Vec2 &v1, const Vec2 &v2);
    Vec2    &BaryCentric(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, float f, float g);
    Vec2    &CatmullRom(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec2 &v4, float s);
    Vec2    &Hermite(const Vec2 &v1, const Vec2 &t1, const Vec2 &v2, const Vec2 &t2, float s);
    Vec2    &TransformCoord(const Vec2 &v, const Matrix &m);
    Vec2    &TransformNormal(const Vec2 &v, const Matrix &m);
    Vec2    &TransformCoordArray(uint out_stride, const Vec2 *vec_array, 
               uint v_stride, const Matrix &m, uint n);
    Vec2    &TransformNormalArray(uint out_stride, const Vec2 *vec_array, 
               uint v_stride, const Matrix &m, uint n);

    Vec2    &Clamp(Vec2 &v1, float c);
    
    std::string Log() const
    {
        std::stringstream ss;
        ss.precision(2);
        ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
        ss << "(" << (*this)[0] + 0.001f << ", " << (*this)[1] + 0.001f << ")";
        return ss.str();
    } // Log


}; // class Vec2


#endif //_VEC2_H

// -- EOF

