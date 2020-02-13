// ----------------------------------------------------------------------------
// File: Line.cpp
// Desc: Line class
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Maths/Line.h"
#include "Maths/Vec3.h"
#include "Maths/Matrix.h"
#include "Maths/Sphere.h"
#include "Maths/Plane.h"


// ----------------------------------------------------------------------------
// Name: Line::Translate
// Desc: Translate the line
// Parm: const Vec3 &delta - the vector to translate the line to
// ----------------------------------------------------------------------------
Line &Line::Translate(const Vec3 &delta)
{
  position.Add(delta);
  return *this;
} // Translate


// ----------------------------------------------------------------------------
// Name: Line::Rotate
// Desc: Rotate the line using the supplied rotation and translation matrix
// Parm: const Matrix &m - the rotation matrix
// ----------------------------------------------------------------------------
Line &Line::Rotate(const Matrix &m)
{
  direction = direction.TransformCoord(m);
  position  = position.TransformCoord(m);
  return *this;
} // Rotate


// ----------------------------------------------------------------------------
// Name: Line::SelfRotate
// Desc: Rotate the line around it's position using hte supplied rotation 
//       matrix
// Parm: const Matrix &m - the rotation matrix
// ----------------------------------------------------------------------------
Line &Line::SelfRotate(const Matrix &m)
{
  direction = direction.TransformCoord(m);
  return *this;
} // SelfRotate


// ----------------------------------------------------------------------------
// Name: Line::Scale
// Desc: scale the line's position
// Parm: float s - the scale
// ----------------------------------------------------------------------------
Line &Line::Scale(float s)
{
  position.Scale(s);
  return *this;
} // Scale


// ----------------------------------------------------------------------------
// Name: Line::Normalize
// Desc: Normalize the lines direction vector
// ----------------------------------------------------------------------------
Line &Line::Normalize()
{
  direction.Normalize();
  return *this;
} // Normalize


// ----------------------------------------------------------------------------
// Name: Line::Distance
// Desc: Calculate the minimum distance between the line and the given point
// Parm: const Vec3 &point - the point
// Retn: float             - the distance
// ----------------------------------------------------------------------------
float Line::Distance(const Vec3 &point) const
{
  Vec3 displacement = point - position;
  float projectedDistance = displacement.Dot(direction);

  return (float) sqrtf(displacement.LengthSq() - projectedDistance*projectedDistance/direction.LengthSq());
} // Distance


// ----------------------------------------------------------------------------
// Name: Line::Distance
// Desc: Calculate the distance between the line and the given line
// Parm: const Line &line - the line
// Retn: float            - the distance
// ----------------------------------------------------------------------------
float Line::Distance(const Line &line) const
{
  Vec3 normal = direction;
  normal.Cross(line.direction);

  float normalMag;
  if ((normalMag = normal.LengthSq()) < 1.0e-4)
  {
    // The lines are parallel
    // just take the distance between the points
    return Vec3(position - line.position).Length();
  } // if

  // Otherwise calculate the minimum distance between
  // the lines
  normal /= (float) sqrtf(normalMag);
  return (float) ::fabs(normal.Dot(position - line.position));
} // Distance


// ----------------------------------------------------------------------------
// Name: Line::DistanceSquared
// Desc: Calculate the distance squared between the point and the line
// Parm: const Vec3 &testPoint - the point
// Retn: float                 - the distance squared
// ----------------------------------------------------------------------------
float Line::DistanceSquared(const Vec3 &testPoint) const
{
  Vec3 displacement = testPoint;
  displacement.Subtract(position);

  float projectedDistance = displacement.Dot(direction);

  return displacement.LengthSq() - projectedDistance * projectedDistance;
} // DistanceSquared


// ----------------------------------------------------------------------------
// Name: Line::IsColinear
// Desc: Test if the point is colinear with the line
// Parm: const Vec3 &p    - the point
// Parm: float threshold  - the threashold
// Retn: bool             - true if the point is colinear within the given 
//                          threashold
// ----------------------------------------------------------------------------
bool Line::IsColinear(const Vec3 &p, float threshold) const
{
  return DistanceSquared(p) < threshold;
} // IsColinear


// ----------------------------------------------------------------------------
// Name: Line::TestCollision
// Desc: Test if the line intersects the sphere
// Parm: const Sphere &sphere - the sphere
// ----------------------------------------------------------------------------
bool Line::TestCollision(const Sphere &sphere) const
{
  return (sphere.TestCollision(*this));
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Line::TestCollision
// Desc: test if the line intersects the plane 
// Parm: const Plane &plane - the plane
// ----------------------------------------------------------------------------
bool Line::TestCollision(const Plane &plane) const
{
  float planeDotNorm = plane.GetNormal().Dot(direction);
  if (planeDotNorm >= 1.0e-6f || planeDotNorm <= -1.0e-6f)
    return true;
  else
    return false;
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Line::TestCollision
// Desc: test if the line intersects the spehre
// Parm: const Sphere &sphere  - the sphere
// Parm: Vec3 &collisionPoint  - the point of intersection
// ----------------------------------------------------------------------------
bool Line::TestCollision(const Sphere &sphere, Vec3 &collisionPoint) const
{
  float distance1, distance2;
  if (TestCollision(sphere, distance1, distance2))
  {
    // Take the distance that is nearest to the reference point
    if (fabsf(distance1) < fabsf(distance2))
      collisionPoint = position + direction * distance1;
    else
      collisionPoint = position + direction * distance2;
    return true;
  } // if

  return false;
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Line::TestCollision
// Desc: Test if the line intersects the sphere
// Parm: const Sphere &sphere   - the sphere
// Parm: Vec3 &collisionPoint1  - the collision point
// Parm: Vec3 &collisionPoint2  - the second collision point
// ----------------------------------------------------------------------------
bool Line::TestCollision(const Sphere &sphere, Vec3 &collisionPoint1, Vec3 &collisionPoint2) const
{
  float distance1, distance2;
  if (TestCollision(sphere, distance1, distance2))
  {
    collisionPoint1 = position + direction * distance1;
    collisionPoint2 = position + direction * distance2;
    return true;
  } // if

  return false;
} // TestCollision


// ----------------------------------------------------------------------------
// Name: Line::TestCollision
// Desc: Test if the line intersects the sphere
// Parm: const Sphere &sphere - the sphere
// Parm: float &distance1     - the distance from line origin to the first 
//                              collision point
// Parm: float &distance2     - the distance from line origin to the second
//                              collision point
// ----------------------------------------------------------------------------
bool Line::TestCollision(const Sphere &sphere, float &distance1, float &distance2) const
{
  // Set up data to hold the ax^2+bx+c (for each x,y,z)
  Vec3 a(0.0f,0.0f,0.0f), b(0.0f,0.0f,0.0f), c(0.0f,0.0f,0.0f);

  float aTotal, bTotal, cTotal;
  float underSqrt, sqrtUnderSqrt;

  // Set a,b,c values
  a.x = direction.x * direction.x;
  a.y = direction.y * direction.y;
  a.z = direction.z * direction.z;

  b.x = 2 * direction.x * position.x -2 * direction.x * sphere.center.x;
  b.y = 2 * direction.y * position.y -2 * direction.y * sphere.center.y;
  b.z = 2 * direction.z * position.z -2 * direction.z * sphere.center.z;

  c.x = position.x * position.x - 2 * position.x * sphere.center.x + sphere.center.x * sphere.center.x;
  c.y = position.y * position.y - 2 * position.y * sphere.center.y + sphere.center.y * sphere.center.y;
  c.z = position.z * position.z - 2 * position.z * sphere.center.z + sphere.center.z * sphere.center.z;

  // total a,b,c
  aTotal = a.x + a.y + a.z;
  bTotal = b.x + b.y + b.z;
  cTotal = c.x + c.y + c.z - (sphere.radius * sphere.radius);

  // Detect collision  ( if b^2 < 4ac)
  underSqrt = bTotal * bTotal - 4.0f * aTotal * cTotal;

  if (underSqrt<0)
  {
    // can't find sqrt therefore no collision
    return false;
  } // if
  else if (underSqrt==0)
  {
    // just touching
    distance1 = (-bTotal) / (2.0f * aTotal);
    distance2 = distance1;
    return true;
  } // else if
  else
  {
    // Cuts with point pair to1,to2
    sqrtUnderSqrt = (float) sqrt (underSqrt);

    distance1 = (-bTotal + sqrtUnderSqrt) / (2.0f * aTotal);
    distance2 = (-bTotal - sqrtUnderSqrt) / (2.0f * aTotal);

    return true;
  } // else
} // TestCollision


// -- EOF

