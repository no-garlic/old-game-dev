// ----------------------------------------------------------------------------
// File: Sphere.h
// Desc: Class to manage a sphere
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _SPHERE_H
#define _SPHERE_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"
#include "Math/Vec3.h"
#include <sstream>


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Matrix;
class Ray;


// ----------------------------------------------------------------------------
// Name: Sphere (class)
// Desc: Class to manage a sphere
// ----------------------------------------------------------------------------
class Sphere
{
public:
    // ------------------------------------------------------------------------
    // constructor
    // ------------------------------------------------------------------------
    Sphere() : radius(0.0f) {}


    // ------------------------------------------------------------------------
    // Members - the center and radius
    // ------------------------------------------------------------------------
    Vec3    center;     // Center of the sphere
    float   radius;     // Radius of the sphere


    // ------------------------------------------------------------------------
    // Member functions
    // ------------------------------------------------------------------------
    void    Reset() { center.Set(0.0f, 0.0f, 0.0f); radius = 0.0f; }
    bool    Intersects(const Sphere &s) const;
    float   RayIntersects(const Ray &ray, const Matrix &matrix) const;
    void    Calculate(const Sphere &s1, const Sphere &s2);

    std::string Log()
    {
        std::stringstream ss;
        ss.precision(2);
        ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
        ss << "(" << center[0] + 0.001f << ", " << center[1] + 0.001f << ", " << center[2] + 0.001f << ") : " << radius;
        return ss.str();
    } // Log


}; // struct Sphere


#endif // _SPHERE_H

// -- EOF

