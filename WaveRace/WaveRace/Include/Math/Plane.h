// ----------------------------------------------------------------------------
// File: Plane.h
// Desc: Class to manage a plane
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _PLANE_H
#define _PLANE_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Matrix;
class Vec3;
class Vec4;


// ----------------------------------------------------------------------------
// Name: Plane  (class)
// Desc: Class to manage a plane
// ----------------------------------------------------------------------------
class Plane : public D3DXPLANE
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    Plane();
    Plane(const float *f);
    Plane(const D3DXFLOAT16 *f);
    Plane(float a, float b, float c, float d);

    
    // ------------------------------------------------------------------------
    // Member functions
    // ------------------------------------------------------------------------
    float  Dot(const Vec4 &v);
    float  DotCoord(const Vec3 &v);
    float  DotNormal(const Vec3 &v);
    Plane &FromPointNormal(const Vec3 &point, const Vec3 &normal);
    Plane &FromPoints(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);
    Plane &Normalize(const Plane &p);
    Plane &Scale(const Plane &p, float s);
    Plane &Transform(const Plane &p, const Matrix &m);
    Plane &TransformArray(uint out_stride, Plane *plane_array, uint p_stride, const Matrix &m, uint n);

}; // class Plane


#endif //_PLANE_H

// -- EOF

