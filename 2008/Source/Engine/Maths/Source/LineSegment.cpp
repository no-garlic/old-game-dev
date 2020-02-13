
#include "LineSegment.h"
#include "Sphere.h"
#include "Plane.h"
#include "Matrix.h"


LineSegment::LineSegment(const Vec3 &point1, const Vec3 &point2)
{
  startPoint = point1;
  endPoint   = point2;

  direction = Vec3(endPoint - startPoint).Normalize();
}


LineSegment::LineSegment(const LineSegment &lineSegment)
{
  *this = lineSegment;
}


LineSegment::LineSegment(const Vec3 points[2])
{
  //Assign the points
  startPoint = points[0];
  endPoint   = points[1];

  direction = Vec3(endPoint - startPoint).Normalize();
}


// Only check to see if the point is between the two points, use IsColinear to determine if it is actually on the line.
bool LineSegment::InSegment(const Vec3 &testPoint) const
{
  return ((Vec3(startPoint - testPoint).Dot(direction) * Vec3(endPoint - testPoint).Dot(direction))<=0);
}


bool LineSegment::IsColinear(const Vec3 &p, float threshold) const
{
  //Compare against the distance squared 
  return DistanceSquared(p) < threshold;
}


void LineSegment::Normalize(void)
{
  // Make the normal to be of unit length
  direction.Normalize();
}


float LineSegment::Distance(const Vec3 &testPoint) const
{
  //Return the square root of the distance squared
  return sqrtf(DistanceSquared(testPoint));
}


void LineSegment::Translate(const Vec3 &delta)
{
  SetStartPoint(startPoint + delta);
  SetEndPoint(endPoint + delta);
}


void LineSegment::Rotate(const Matrix &m)
{
  // rotate the plane about the origin
  SetStartPoint(startPoint.TransformCoord(m));
  SetEndPoint(endPoint.TransformCoord(m));
}


bool LineSegment::TestCollision(const Plane &plane) const
{
  // If the distance from the point to the plane vary in sign
  // a negative result will be returned
  return (plane.GetNormal().Dot(plane.GetPoint() - startPoint) * plane.GetNormal().Dot(plane.GetPoint() - endPoint) <= 0);
}


bool LineSegment::TestCollision(const Sphere &sphere) const
{
  return (sphere.TestCollision (*this));
}


// -- EOF

