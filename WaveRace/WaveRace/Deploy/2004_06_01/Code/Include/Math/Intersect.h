// ----------------------------------------------------------------------------
// File: Intersect.h
// Desc: Intersection test with ray casting
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _INTERSECT_H
#define _INTERSECT_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <vector>
#include "Math/Types.h"
#include "Math/Vec3.h"
#include "Math/Matrix.h"
#include "Common/Utilities.h"


// ----------------------------------------------------------------------------
// Name: Triangle (struct)
// Desc: Holds the definition of a triangles verticies
// ----------------------------------------------------------------------------
struct Triangle
{
    Vec3    p0;
    Vec3    p1;
    Vec3    p2;

    std::string Log()
    {
        std::stringstream ss;
        ss.precision(2);
        ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
        ss << "p0: " << p0.Log() <<"p1: " << p1.Log() <<"p2: " << p2.Log();
        return ss.str();
    } // Log

}; // struct Triangle


// ----------------------------------------------------------------------------
// Name: Ray (class)
// Desc: A ray that is used for ray casting
// ----------------------------------------------------------------------------
class Ray
{
public:
    // ------------------------------------------------------------------------
    // The ray position and direction vector
    // ------------------------------------------------------------------------
    Vec3    position;       // Position of the ray
    Vec3    direction;      // Direction vector for the ray


    // ------------------------------------------------------------------------
    // Name: Ray
    // Desc: Default constructor
    // ------------------------------------------------------------------------
    Ray()
    {
    } // Ray


    // ------------------------------------------------------------------------
    // Name: 
    // Desc: Constructor that cretes a ray from another ray and a world matrix
    // Parm: const Ray &ray          - The ray
    // Parm: const Matrix &world_matrix - the world matrix
    // Note: Actually creates a ray for the inverse of the worl matrix, so 
    //       a ray can be specified in world space, and the world matrix
    //       can also be specified, and the new ray will be in the model
    //       space of the world matrix.
    // ------------------------------------------------------------------------
    Ray (const Ray &ray, const Matrix &world_matrix)
    {
        // Get the inverse world matrix
        Matrix inv_mat;
        inv_mat.Inverse(world_matrix);

        // Transform the new ray into model space
        position.TransformCoord(ray.position, inv_mat);
        direction.TransformNormal(ray.direction, inv_mat);
    } // Ray


    // ------------------------------------------------------------------------
    // Name: IntersectsTriangle
    // Desc: Test if this ray intersects a given triangle
    // Parm: const Triangle &tri - The triangle (CW winding order)
    // Parm: float &u            - the tangent space u coord
    // Parm: float &v            - the tangent space v coord
    // Parm: float &t            - an indicator of the intersection loc giving
    //                             the intersection point:
    //                                 isect = ray.dir * t + ray.origin
    // Retn: bool                - true if the ray intersects the triangle.
    // Note: From "Generic Graphics Toolkit", Original Author: Allen Bierbaum
    // ------------------------------------------------------------------------
    bool IntersectsTriangle(const Triangle &tri, float &u, float &v, float &t) const
    {
        // find vectors for two edges sharing vert0 (using cw winding).  To
        // change winding order, swap edge1 nad edge2.
        Vec3 edge1 = tri.p2 - tri.p0;
        Vec3 edge2 = tri.p1 - tri.p0;

        // begin calculating determinant - also used to calculate U parameter
        Vec3 pvec;
        pvec.Cross(direction, edge2);

        // if determinant is near zero, ray lies in plane of triangle
        float det = edge1.Dot(pvec);
        if (det < EPSILON)
            return false;

        // calculate distance from vert0 to ray origin
        Vec3 tvec = position - tri.p0;

        // calculate U parameter and test bounds
        u = tvec.Dot(pvec);
        if (u < 0.0 || u > det)
            return false;

        // prepare to test V parameter
        Vec3 qvec;
        qvec.Cross(tvec, edge1);

        // calculate V parameter and test bounds
        v = (const_cast<Vec3 &>(direction)).Dot(qvec);
        if (v < 0.0 || u + v > det)
            return false;

        // calculate t, scale parameters, ray intersects triangle
        t = edge2.Dot(qvec);
        float inv_det = 1.0f / det;
        t *= inv_det;
        u *= inv_det;
        v *= inv_det;

        // test if t is within the ray boundary (when t >= 0)
        return t >= 0.0f;
    } // IntersectTriangle

}; // struct Ray


// ----------------------------------------------------------------------------
// Name: RayHit (struct)
// Desc: Holds the info about a ray intersection
// ----------------------------------------------------------------------------
struct RayHit
{
    float           distance;       // Distance from the start of the ray to the intersection point
    float           u_tangent;      // Triangle U (v0 - v1) tangent space (cw winding order)
    float           v_tangent;      // Triangle V (v0 - v2) tangent space (cw winding order)

    Triangle        triangle_w;     // The triangle in world space
    Vec3            normal_w;       // The triangle normal in world space
    Matrix          matrix_w;       // The world matrix where the triangle is

    Triangle        triangle_m;     // The triangle in model space
    Vec3            normal_m;       // The triangle normal in model space
    Matrix          matrix_m;       // The model to world matrix (inverse world matrix)

    std::string     mesh_name;      // The name of the mesh that owns the triangle
}; // RayHit


// ----------------------------------------------------------------------------
// Hit info typedefs
// ----------------------------------------------------------------------------
typedef std::vector<RayHit>     HitInfo;
typedef HitInfo::iterator       HitInfo_Iterator;
typedef HitInfo::const_iterator HitInfo_ConstIterator;


#endif // _INTERSECT_H

// -- EOF
