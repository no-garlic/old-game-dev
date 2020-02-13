// ----------------------------------------------------------------------------
// File: Frustum.h
// Desc: Describes a viewing frustum
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef __FRUSTUM_H
#define __FRUSTUM_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"
#include "Math/Matrix.h"
#include "Math/Plane.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Sphere;
class Matrix;
class Box;


// ----------------------------------------------------------------------------
// Name: Frustum (class)
// Desc: Describes a viewing frustum
// ----------------------------------------------------------------------------
class Frustum
{
public:
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    Frustum();


    // ------------------------------------------------------------------------
    // Name: FrustumPlane (enum)
    // Desc: The planes of the frustum
    // ------------------------------------------------------------------------
    enum FrustumPlane
    {
        RIGHT   = 0,    // The RIGHT plane of the frustum
        LEFT    = 1,    // The LEFT  plane of the frustum
        BOTTOM  = 2,    // The BOTTOM plane of the frustum
        TOP     = 3,    // The TOP plane of the frustum
        BACK    = 4,    // The BACK plane of the frustum
        FRONT   = 5     // The FRONT plane of the frustum
    }; // enum FrustumPlane


    // ------------------------------------------------------------------------
    // Name: FrustumIntersect (enum)
    // Desc: The intersection test result values
    // ------------------------------------------------------------------------
    enum FrustumIntersect
    {
        IN_FRUSTUM      = 0,    // The object is totally within the frustum
        OUT_FRUSTUM     = 1,    // The object is totally out of the frustum
        PARTIAL         = 2     // The object intersects one of the planes
    }; // enum FrustumIntersect
        

    // ------------------------------------------------------------------------
    // Set the frustum planes
    // ------------------------------------------------------------------------
    void    SetViewMatrix(const Matrix &m);
    void    SetProjMatrix(const Matrix &m);


    // ------------------------------------------------------------------------
    // Get the planes array from the frustum
    // ------------------------------------------------------------------------
    Plane  *GetPlanes();


    // ------------------------------------------------------------------------
    // Collision tests
    // ------------------------------------------------------------------------
    int     Intersects(const Sphere &sphere, const Matrix &world_matrix);
    int     Intersects(const Sphere &sphere);
    int     Intersects(const Box &box);

private:
    // ------------------------------------------------------------------------
    // Private functions
    // ------------------------------------------------------------------------
    void RecalculateFrustum();


    // ------------------------------------------------------------------------
    // Privates members
    // ------------------------------------------------------------------------
    Plane       m_planes[6];    // The planes of the frustum
    Matrix      m_view_mat;     // The view matrix
    Matrix      m_proj_mat;     // The projection matrix
    bool        m_dirty;        // Have the matricies changed
}; // struct Frustum


#endif // __FRUSTUM_H

// -- EOF

