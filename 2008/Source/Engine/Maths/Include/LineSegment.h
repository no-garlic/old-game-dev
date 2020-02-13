// ----------------------------------------------------------------------------
// File: LineSegment.h
// Desc: LineSegment class
// Auth: Michael Petrou
// (C) Copyright: 2007
// ----------------------------------------------------------------------------
#ifndef _LINE_SEGMENT_H_
#define _LINE_SEGMENT_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "stdMath.h"
#include "Vec3.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Sphere;
class Plane;
class Matrix;


// ----------------------------------------------------------------------------
// Name: LineSegment (class)
// Desc: LineSegment class
// ----------------------------------------------------------------------------
class LineSegment
{
public:
  // --------------------------------------------------------------------------
  // Constructors
  // --------------------------------------------------------------------------
  LineSegment() {}
  LineSegment(const Vec3 &point1, const Vec3 &point2);
  LineSegment(const LineSegment &lineSegment);
  LineSegment(const Vec3 points[2]);

  // --------------------------------------------------------------------------
  // Manage the direction and position of the line
  // --------------------------------------------------------------------------
  const Vec3 &GetStartPoint() const { return startPoint; }
  const Vec3 &GetEndPoint()   const { return endPoint;   }
  const Vec3 &GetDirection()  const { return direction;  }

  inline void SetStartPoint(const Vec3 &newPoint);
  inline void SetEndPoint(const Vec3 &newPoint);

  // --------------------------------------------------------------------------
  // Distance functions
  // --------------------------------------------------------------------------
  float Distance(const Vec3 &point) const;
  inline float DistanceSquared(const Vec3 &testPoint) const;

  // --------------------------------------------------------------------------
  // Test the points
  // --------------------------------------------------------------------------
  bool InSegment(const Vec3 &testPoint) const;
  bool IsColinear(const Vec3 &p, float threshold = FLOAT_EPSILON) const;

  // --------------------------------------------------------------------------
  // Translates this line.
  // --------------------------------------------------------------------------
  void Translate(const Vec3 &delta);
  
  // --------------------------------------------------------------------------
  // Rotates this line about the origin.
  // --------------------------------------------------------------------------
  void Rotate(const Matrix &m);

  // --------------------------------------------------------------------------
  // Normalizes the direction of this line,
  // --------------------------------------------------------------------------
  void Normalize();    

  // --------------------------------------------------------------------------
  // Tests for a collision between this line and the given primitive.
  // (Collisions are two sided so two collision points may occur)
  // --------------------------------------------------------------------------
  bool TestCollision(const Plane &plane) const;
  bool TestCollision(const Sphere &sphere) const;

private:
  // --------------------------------------------------------------------------
  // The line position and direction
  // --------------------------------------------------------------------------
  Vec3  direction;
  Vec3  startPoint;
  Vec3  endPoint;

}; // class LineSegment



inline void LineSegment::SetEndPoint(const Vec3 &newEndPoint)
{
  endPoint = newEndPoint;
  direction = Vec3(endPoint - startPoint).Normalize();
}


inline void LineSegment::SetStartPoint(const Vec3 &newStartPoint)
{
  startPoint = newStartPoint;
  direction = Vec3(endPoint - startPoint).Normalize();
}


inline float LineSegment::DistanceSquared(const Vec3 &testPoint) const
{
  Vec3 displacement = testPoint - startPoint;
  float projectedDistance = displacement.Dot(direction);

  // Test the projection
  if (projectedDistance > 0.0f)
  {
    // Test if the point is behind the end point
    if (projectedDistance > Vec3(endPoint - startPoint).Dot(direction))
    {
      // If the point is behind the end point, get the distance squared from the end point
      return Vec3(testPoint - endPoint).LengthSq();
    }
    else
    {
      // If between both lines, get the offset^2 from the line
      return (displacement.LengthSq() - projectedDistance*projectedDistance);
    }
  }
  else
  {
    // If behind the point, get the distance^2 from the point
    return displacement.LengthSq();
  }
}

#endif // _LINE_SEGMENT_H_

// -- EOF

