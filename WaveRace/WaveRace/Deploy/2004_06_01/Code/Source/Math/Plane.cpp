// ----------------------------------------------------------------------------
// File: Plane.cpp
// Desc: Manages a plane
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Plane.h"
#include "Math/Matrix.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"


Plane::Plane()                                      : D3DXPLANE()           {}
Plane::Plane(const float *f)                        : D3DXPLANE(f)          {}
Plane::Plane(const D3DXFLOAT16 *f)                  : D3DXPLANE(f)          {}
Plane::Plane(float a, float b, float c, float d)    : D3DXPLANE(a, b, c, d) {}


float Plane::Dot(const Vec4 &v)
{
    return D3DXPlaneDot(this, &v);
} // Dot


float  Plane::DotCoord(const Vec3 &v)
{
    return D3DXPlaneDotCoord(this, &v);
} // DotCoord


float  Plane::DotNormal(const Vec3 &v)
{
    return D3DXPlaneDotNormal(this, &v);
} // DotNormal


Plane &Plane::FromPointNormal(const Vec3 &point, const Vec3 &normal)
{
    D3DXPlaneFromPointNormal(this, &point, &normal);
    return *this;
} // FromPointNormal


Plane &Plane::FromPoints(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
{
    D3DXPlaneFromPoints(this, &v1, &v2, &v3);
    return *this;
} // FromPoints


Plane &Plane::Normalize(const Plane &p)
{
    D3DXPlaneNormalize(this, &p);
    return *this;
} // Normalize


Plane &Plane::Scale(const Plane &p, float s)
{
//    D3DXPlaneScale(this, &p, s);
    return *this;
} // Scale


Plane &Plane::Transform(const Plane &p, const Matrix &m)
{
    D3DXPlaneTransform(this, &p, &m);
    return *this;
} // Transform


Plane &Plane::TransformArray(uint out_stride, Plane *plane_array, uint p_stride, const Matrix &m, uint n)
{
    D3DXPlaneTransformArray(this, out_stride, plane_array, p_stride, &m, n);
    return *this;
} // TransformArray


// -- EOF
