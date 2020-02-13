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
#include "Math/Types.h"
#include <sstream>


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Vec2;
class Vec4;
class Plane;
class Matrix;


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
    Vec3(const D3DXFLOAT16 *f);
    Vec3(float x, float y, float z);


    // ------------------------------------------------------------------------
    // Member functions
    // ------------------------------------------------------------------------
    float   Dot(const Vec3 &v);
    float   Length();
    float   LengthSq();
    Vec3    &Set(float x, float y, float z);
    Vec3    &Add(const Vec3 &v1, const Vec3 &v2);
    Vec3    &Scale(const Vec3 &v, float s);
    Vec3    &Subtract(const Vec3 &v1, const Vec3 &v2);
    Vec3    &Lerp(const Vec3 &v1, const Vec3 &v2, float s);
    Vec3    &Normalize(const Vec3 &v1);
    Vec3    &Maximize(const Vec3 &v1, const Vec3 &v2);
    Vec3    &Minimize(const Vec3 &v1, const Vec3 &v2);
    Vec3    &BaryCentric(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, float f, float g);
    Vec3    &CatmullRom(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, const Vec3 &v4, float s);
    Vec3    &Hermite(const Vec3 &v1, const Vec3 &t1, const Vec3 &v2, const Vec3 &t2, float s);
    Vec3    &Cross(const Vec3 &v1, const Vec3 &v2);
    Vec3    &PlaneIntersectLine(const Plane &p, const Vec3 &v1, const Vec3 &v2);
    Vec3    &TransformCoord(const Vec3 &v, const Matrix &m);
    Vec3    &TransformNormal(const Vec3 &v, const Matrix &m);
    Vec3    &TransformCoordArray(uint out_stride, const Vec3 *vec_array, 
               uint v_stride, const Matrix &m, uint n);
    Vec3    &TransformNormalArray(uint out_stride, const Vec3 *vec_array, 
               uint v_stride, const Matrix &m, uint n);
    Vec3    &Project(const Vec3 &v, D3DVIEWPORT9 *viewport, const Matrix &projection, 
               const Matrix &view, const Matrix &world);
    Vec3    &Unproject(const Vec3 &v, D3DVIEWPORT9 *viewport, const Matrix &projection, 
               const Matrix &view, const Matrix &world);
    Vec3    &ProjectArray(uint out_stride, const Vec3 *vec_array, 
               uint v_stride, D3DVIEWPORT9 *viewport, const Matrix &projection, 
               const Matrix &view, const Matrix &world, uint n);
    Vec3    &UnprojectArray(uint out_stride, const Vec3 *vec_array, 
               uint v_stride, D3DVIEWPORT9 *viewport, const Matrix &projection, 
               const Matrix &view, const Matrix &world, uint n);

    Vec3    &Clamp(Vec3 &v1, float c);

    std::string Log() const
    {
        std::stringstream ss;
        ss.precision(2);
        ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
        ss << "(" << (*this)[0] + 0.001f << ", " << (*this)[1] + 0.001f << ", " << (*this)[2] + 0.001f << ")";
        return ss.str();
    } // Log

}; // class Vec3



#endif //_VEC3_H

// -- EOF

