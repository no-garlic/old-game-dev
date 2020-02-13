// ----------------------------------------------------------------------------
// File: Ray.h
// Desc: Ray intersection class
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Ray.h"


// ----------------------------------------------------------------------------
// Name: Ray::Ray
// Desc: Constructor
// Parm: const Vec3 &d    - the direction vector
// Parm: const Vec3 &p    - the position
// Parm: const Matrix &m  - the inverse world matrix to translate the ray
// ----------------------------------------------------------------------------
Ray::Ray(const Vec3 &d, const Vec3 &p, const Matrix &m)
{
  //DEBUG_BREAK;
  position.TransformCoord(p, m);
  direction.TransformNormal(d, m);
} // Ray


// ----------------------------------------------------------------------------
// Name: Ray::Ray
// Desc: Constructor
// Parm: const Ray &ray   - the source ray
// Parm: const Matrix &m  - the inverse world matrix to translate the ray
// ----------------------------------------------------------------------------
Ray::Ray(const Ray &ray, const Matrix &m)
{
  position.TransformCoord(ray.position, m);
  direction.TransformNormal(ray.direction, m);
} // Ray


// -- EOF

