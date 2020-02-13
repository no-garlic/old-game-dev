// ----------------------------------------------------------------------------
// File: Line.h
// Desc: Line class
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef _LINE_H_
#define _LINE_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Maths/Vec3.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Sphere;
class Plane;
class Matrix;


// ----------------------------------------------------------------------------
// Name: Line (class)
// Desc: Line class
// ----------------------------------------------------------------------------
class Line
{
public:
  // --------------------------------------------------------------------------
  // Constructors
  // --------------------------------------------------------------------------
  Line() {}
  Line(const Vec3 &d, const Vec3 &p) : direction(d), position(p) { direction.Normalize();   }

  // --------------------------------------------------------------------------
  // Manage the direction and position of the line
  // --------------------------------------------------------------------------
  void SetDirection(const Vec3 &direction)  { this->direction = direction; }
  void SetPosition(const Vec3 &position)    { this->position  = position;  }
  const Vec3 &GetDirection() const          { return direction; }
  const Vec3 &GetPosition() const           { return position;  }

  // --------------------------------------------------------------------------
  // Determines if the given point is on this ray.
  // --------------------------------------------------------------------------
  bool IsColinear(const Vec3 &p, float threshold = EPSILON) const;

  // --------------------------------------------------------------------------
  // Translates this line.
  // --------------------------------------------------------------------------
  Line &Translate(const Vec3 &delta);
  
  // --------------------------------------------------------------------------
  // Rotates this line about the origin.
  // --------------------------------------------------------------------------
  Line &Rotate(const Matrix &m);

  // --------------------------------------------------------------------------
  // Rotates this line about itself (ie origin is not rotated).
  // --------------------------------------------------------------------------
  Line &SelfRotate(const Matrix &m);
  
  // --------------------------------------------------------------------------
  // Scales this line about its origin.
  // --------------------------------------------------------------------------
  Line &Scale(float s);
  
  // --------------------------------------------------------------------------
  // Normalizes the direction of this line,
  // --------------------------------------------------------------------------
  Line &Normalize();

  // --------------------------------------------------------------------------
  // Calculates the perpendicular distance from this line to the given point.
  // --------------------------------------------------------------------------
  float Distance(const Vec3 &point) const;

  // --------------------------------------------------------------------------
  // Calculates the perpendicular distance from this line to <I>line</I>.
  // --------------------------------------------------------------------------
  float Distance(const Line &line) const;

  // --------------------------------------------------------------------------
  // Calculates the perpendicular distance from the line to the point.
  // --------------------------------------------------------------------------
  float DistanceSquared(const Vec3 &testPoint) const;

  // --------------------------------------------------------------------------
  // Tests for a collision between this line and the given primitive.
  // (Collisions are two sided so two collision points may occur)
  // --------------------------------------------------------------------------
  bool TestCollision(const Sphere &sphere) const;
  bool TestCollision(const Plane &plane) const;
  bool TestCollision(const Sphere &sphere, Vec3 &collisionPoint) const;
  bool TestCollision(const Sphere &sphere, Vec3 &collisionPoint1, Vec3 &collisionPoint2) const;
  bool TestCollision(const Sphere &sphere, float &distance1, float &distance2) const;

  // --------------------------------------------------------------------------
  // The line position and direction
  // --------------------------------------------------------------------------
  Vec3  position;
  Vec3  direction;

}; // class Line


#endif // _LINE_H_

// -- EOF

