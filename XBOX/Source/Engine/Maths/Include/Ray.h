// ----------------------------------------------------------------------------
// File: Ray.h
// Desc: Ray intersection class
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef _RAY_H_
#define _RAY_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "Line.h"
#include "Vec3.h"
#include "Matrix.h"


// ----------------------------------------------------------------------------
// Name: Triangle (struct)
// Desc: Holds the definition of a triangles verticies
// ----------------------------------------------------------------------------
struct Triangle
{
  // --------------------------------------------------------------------------
  // Members
  // --------------------------------------------------------------------------
  Vec3    p0;
  Vec3    p1;
  Vec3    p2;

  // --------------------------------------------------------------------------
  // Print the triangle to a string
  // --------------------------------------------------------------------------
  String Log()
  {
    StringStream ss;
    ss.precision(2);
    ss.setf(std::ios_base::fixed, std::ios_base::floatfield);
    ss << "p0: " << p0.ToString() <<"p1: " << p1.ToString() <<"p2: " << p2.ToString();
    return ss.str();
  } // Log

}; // struct Triangle


// ----------------------------------------------------------------------------
// Name: Ray  (class)
// Desc: The Ray class
// ----------------------------------------------------------------------------
class Ray : public Line
{
public:
  // --------------------------------------------------------------------------
  // Constructors
  // --------------------------------------------------------------------------
  Ray() {}
  Ray(const Vec3 &d, const Vec3 &p) : Line(d, p) {}

  // --------------------------------------------------------------------------
  // Make sure to put the matrix in model space, you use the 
  // inverse world matrix.
  // --------------------------------------------------------------------------
  Ray(const Vec3 &d, const Vec3 &p, const Matrix &m);
  Ray(const Ray &ray, const Matrix &m);

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
  // ------------------------------------------------------------------------
  inline bool IntersectsTriangle(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, float &u, float &v, float &t) const
  {
    // find vectors for two edges sharing p0 (using cw winding).  To
    // change winding order, swap edge1 nad edge2.
    Vec3 edge1 = p1 - p0;
    Vec3 edge2 = p2 - p0;

    // begin calculating determinant - also used to calculate U parameter
    Vec3 pvec;
    pvec.Cross(direction, edge2);

    // if determinant is near zero, ray lies in plane of triangle
    float det = edge1.Dot(pvec);
    if (det < FLOAT_EPSILON)
      return false;

    // calculate distance from p0 to ray origin
    Vec3 tvec = position - p0;

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
  } // IntersectsTriangle


  // ------------------------------------------------------------------------
  // Name: IntersectsTriangle
  // Desc: Test if this ray intersects a given triangle
  // Parm: const Triangle &tri - The triangle (CW winding order)
  // Parm: float &u            - the tangent space u coord
  // Parm: float &v            - the tangent space v coord
  // Parm: float &t            - an indicator of the intersection loc giving
  //                             the intersection point:
  //                                 isect = ray.dir * t + ray.origin
  // Parm: float &distance     - thedistance to the intersection point.
  // Retn: bool                - true if the ray intersects the triangle.
  // ------------------------------------------------------------------------
  inline bool IntersectsTriangle(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, 
    Vec3 &point, Vec3 &bary, float &distance) const
  {
    // Find vectors for two edges sharing p0
    Vec3 edge0 = p1 - p0;
    Vec3 edge1 = p2 - p0;

    // Begin calculating determinant - also used to calculate U parameter
    Vec3 pvec;
    pvec.Cross(direction, edge1);

    // If determinant is near zero, ray lies in plane of triangle
    float det = edge0.Dot(pvec);
    if (det < FLOAT_EPSILON)
      return false;

    // Calculate distance from p0 to ray origin
    Vec3 tvec = position - p0;

    // Calculate U parameter and test bounds
    bary.y = tvec.Dot(pvec);
    if (bary.y < 0.0f || bary.y > det)
      return false;

    // Prepare to test V parameter
    Vec3 qvec = tvec.Cross(edge0);

    // Calculate V parameter and test bounds
    bary.z = direction.Dot(qvec);
    if (bary.z < 0.0f || bary.y + bary.z > det)
      return false;

    // Calculate t, scale parameters, ray intersects triangle
    distance = edge1.Dot(qvec);
    float inv_det = 1.0f / det;
    distance *= inv_det;
    bary.y   *= inv_det;
    bary.z   *= inv_det;
    bary.x    = 1.0f - (bary.y + bary.z);
    point     = position + direction * distance;

    return true;
  } // IntersectsTriangle


  // ------------------------------------------------------------------------
  // Name: IntersectsTriangle
  // Desc: Test if this ray intersects a given triangle
  // Parm: const Triangle &tri - The triangle (CW winding order)
  // Parm: float &u            - the tangent space u coord
  // Parm: float &v            - the tangent space v coord
  // Parm: float &t            - an indicator of the intersection loc giving
  //                             the intersection point:
  //                                 isect = ray.dir * t + ray.origin
  // Parm: float &distance     - thedistance to the intersection point.
  // Retn: bool                - true if the ray intersects the triangle.
  // ------------------------------------------------------------------------
  inline bool IntersectsTriangle(const Triangle &tri, Vec3 &point, Vec3 &bary, float &distance) const
  {
    return IntersectsTriangle(tri.p0, tri.p1, tri.p2, point, bary, distance);
  } // IntersectsTriangle


  // ------------------------------------------------------------------------
  // Name: IntersectsTriangle
  // Desc: Test if this ray intersects a given triangle
  // Parm: const Triangle &tri - The triangle (CW winding order)
  // Parm: float &u            - the tangent space u coord
  // Parm: float &v            - the tangent space v coord
  // Parm: float &t            - an indicator of the intersection loc giving
  //                             the intersection point:
  //                                 isect = ray.dir * t + ray.origin
  // Parm: float &distance     - thedistance to the intersection point.
  // Retn: bool                - true if the ray intersects the triangle.
  // ------------------------------------------------------------------------
  inline bool IntersectsTriangle(const Triangle &tri, float &u, float &v, float &t) const
  {
    return IntersectsTriangle(tri.p0, tri.p1, tri.p2, u, v, t);
  } // IntersectsTriangle

}; // class Ray


#endif // _RAY_H_

// -- EOF

