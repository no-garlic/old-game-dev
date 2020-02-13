// ----------------------------------------------------------------------------
// File: Sphere.cpp
// Desc: Manages a sphere
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Maths/Sphere.h"
#include "Maths/Matrix.h"
#include "Maths/Frustum.h"
#include "Maths/Box.h"
#include "Maths/Line.h"
#include "Maths/Ray.h"


// ----------------------------------------------------------------------------
// Name: Sphere::Maximize
// Desc: Maximize this sphere to contain both spheres (ignoring the existing 
//       sphere data)
// Parm: const Sphere &s1  - the first sphere
// Parm: const Sphere &s2  - the second sphere
// ----------------------------------------------------------------------------
void Sphere::Maximize(const Sphere &s1, const Sphere &s2)
{
  Vec3 vec;
  D3DXVec3Subtract(&vec, &(s1.center), &(s2.center));

  float vec_len = D3DXVec3Length(&vec);

  if (vec_len < 0.001f && vec_len > -0.001f)
  {
    radius = Max<float>(s1.radius, s2.radius);
    return;
  } // if

  float rad = (s1.radius + s2.radius + vec_len) / 2.0f;
  if (rad < s1.radius)
  {
    (*this) = s1;
    return;
  } // if
  else if (rad < s2.radius)
  {
    (*this) = s2;
    return;
  } // else if

  float lerp = (rad - s1.radius) / vec_len;
  D3DXVec3Lerp(&vec, &(s1.center), &(s2.center), lerp);

  center = vec;
  radius = rad;
} // Maximize


// ----------------------------------------------------------------------------
// Name: Sphere::CheckVisibility
// Desc: Check if this sphere is partially or fully within the frustum
// Parm: const Frustum &frustum - the frustum
// Retn: bool                   - true if visible
// ----------------------------------------------------------------------------
bool Sphere::CheckVisibility(const Frustum &frustum) const
{
  const Plane *planes = frustum.GetPlanes();
 
  return
  (
    (!planes[0].IsBehind(*this)) &&
    (!planes[1].IsBehind(*this)) &&
    (!planes[2].IsBehind(*this)) &&
    (!planes[3].IsBehind(*this)) &&
    (!planes[4].IsBehind(*this)) &&
    (!planes[5].IsBehind(*this))
  );
} // CheckVisibility


// ----------------------------------------------------------------------------
// Name: Sphere::TestCollision
// Desc: Test if thepoint is within the sphere
// Parm: const Vec3 &point - the point
// ----------------------------------------------------------------------------
bool Sphere::TestCollision(const Vec3 &point) const
{
  return ((Vec3(point - center).LengthSq() - radius * radius) < 1.0e-4f * 1.0e-4f);
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Sphere::TestCollision
// Desc: Test if the sphere intersects the plane
// Parm: const Plane &plane - the plane
// ----------------------------------------------------------------------------
bool Sphere::TestCollision(const Plane &plane) const
{
  return ((fabs(plane.Distance(center)) - radius) < 1.0e-4f);
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Sphere::TestCollision
// Desc: Tests if the sphere intersects the box
// Parm: const Box &box - the box
// ----------------------------------------------------------------------------
bool Sphere::TestCollision(const Box &box) const
{
  return box.TestCollision (*this);
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Sphere::TestCollision
// Desc: Tests if the sphere intersects the other sphere
// Parm: const Sphere &sphere - the other sphere
// ----------------------------------------------------------------------------
bool Sphere::TestCollision(const Sphere &sphere) const
{
  return ((Vec3(center - sphere.center).LengthSq() - (radius + sphere.radius) * (radius + sphere.radius)) < 1.0e-4f);
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Sphere::TestCollision
// Desc: Tests if the line interscts the sphere
// Parm: const Line &line - the line
// ----------------------------------------------------------------------------
bool Sphere::TestCollision(const Line &line) const
{
  return ((line.DistanceSquared(center) - radius * radius) < 1.0e-4f);
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Sphere::TestCollision
// Desc: tests if the ray intersects the sphere
// Parm: const Ray &ray - the ray
// ----------------------------------------------------------------------------
bool Sphere::TestCollision(const Ray &ray) const
{
  return (D3DXSphereBoundProbe(&center, radius, &ray.position, &ray.direction) == TRUE);
} // TestCollision


/*
// ----------------------------------------------------------------------------
// Name: Sphere::RayIntersects
// Desc: tests if a ray intersects with a sphere
// Parm: const Ray &ray        - the ray
// Parm: const Matrix &matrix  - the world matrix of the sphere
// Retn: float                 - the distance from the origin of the ray to the 
//       nearest point on the surface of the sphere, or -1 for not hit
// ----------------------------------------------------------------------------
float Sphere::RayIntersects(const Ray &ray, const Matrix &matrix) const
{
    Vec3 sphere_ctr;
    D3DXVec3TransformCoord(&sphere_ctr, &center, &matrix);

    BOOL hit = D3DXSphereBoundProbe(&sphere_ctr, radius, &ray.position, &ray.direction);
    if (hit)
    {
        Vec3 dist_vec;
        D3DXVec3Subtract(&dist_vec, &sphere_ctr, &ray.position);
        return fabsf(D3DXVec3Length(&dist_vec));
    } // if
    else
    {
        return -1.0f;
    } // else
} // RayIntersects


// ----------------------------------------------------------------------------
// Name: Sphere::Intersects
// Desc: Tests if the giver spheres intersects this sphere
// Parm: const Sphere& s - the sphere to test
// Retn: bool            - true if the given sphere intersects this sphere
// ----------------------------------------------------------------------------
bool Sphere::Intersects(const Sphere& s) const
{
    // Get the separating axis
    Vec3 sep_axis = center - s.center;

    // Get the sum of the radii
    float sum_rad = radius + s.radius;

    // If the distance between the centers is less than the sum
    // of the radii, then we have an intersection
    // we calculate this using the squared lengths for speed
    float sq_len = D3DXVec3LengthSq(&sep_axis);

    return (sq_len < (sum_rad * sum_rad));
} // Intersects


// ----------------------------------------------------------------------------
// Name: Sphere::Calculate
// Desc: Calculate the bounding sphere of two supplied spheres, and assigns the
//       encompassing sphere to this sphere.
// Parm: const Sphere &s1  - the source sphere 1
// Parm: const Sphere &s2  - the source sphere 2
// ----------------------------------------------------------------------------
void Sphere::Calculate(const Sphere &s1, const Sphere &s2)
{
    Vec3 vec;
    D3DXVec3Subtract(&vec, &(s1.center), &(s2.center));

    float vec_len   = D3DXVec3Length(&vec);

    if (vec_len < 0.001f && vec_len > -0.001f)
    {
        radius = Max<float>(s1.radius, s2.radius);
        return;
    } // if

    float rad       = (s1.radius + s2.radius + vec_len) / 2.0f;
    if (rad < s1.radius)
    {
        (*this) = s1;
        return;
    } // if
    else if (rad < s2.radius)
    {
        (*this) = s2;
        return;
    } // else if

    float lerp      = (rad - s1.radius) / vec_len;
    D3DXVec3Lerp(&vec, &(s1.center), &(s2.center), lerp);

    center      = vec;
    radius      = rad;
} // Calculate

*/


// -- EOF

