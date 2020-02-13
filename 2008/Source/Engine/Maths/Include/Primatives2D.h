// ----------------------------------------------------------------------------
// File: Primatives2D.h
// Desc: 2D Primative classes
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef _PRIMATIVES_2_D_H_
#define _PRIMATIVES_2_D_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "Vec2.h"
#include "Vec3.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
struct Circle2D;
struct Box2D;


// ----------------------------------------------------------------------------
// Name: Circle2D (struct)
// Desc: Circle class
// ----------------------------------------------------------------------------
struct Circle2D
{
  // --------------------------------------------------------------------------
  // Constructors
  // --------------------------------------------------------------------------
  Circle2D() : center(0.0f, 0.0f), radius(0.0f) {}
  Circle2D(const Vec2 &center, float radius) : center(center), radius(radius) {}

  // --------------------------------------------------------------------------
  // Members
  // --------------------------------------------------------------------------
  Vec2  center;
  float radius;

}; // struct Circle2D


// ----------------------------------------------------------------------------
// Name: Box2D (struct)
// Desc: Box class
// ----------------------------------------------------------------------------
struct Box2D
{
  // --------------------------------------------------------------------------
  // Constructors
  // --------------------------------------------------------------------------
  Box2D() : MinPt(0.0f, 0.0f), MaxPt(0.0f, 0.0f) {}
  Box2D(const Vec2 &MinPt, const Vec2 &MaxPt) : MinPt(MinPt), MaxPt(MaxPt) {}
  Box2D(float x1, float x2, float y1, float y2) { MinPt.Set(x1, y1); MaxPt.Set(x2, y2); }
  Box2D(const Circle2D &circle) { MinPt.Set(circle.center.x - circle.radius, circle.center.y - circle.radius);
                                  MaxPt.Set(circle.center.x + circle.radius, circle.center.y + circle.radius); }

  // --------------------------------------------------------------------------
  // Name: Maximize
  // Desc: Maximize this box to include the given box
  // Parm: const Box2D &box - the other box
  // --------------------------------------------------------------------------
  Box2D &Maximize(const Box2D &box)
  {
    MinPt.x = Min<float>(MinPt.x, box.MinPt.x);  MinPt.y = Min<float>(MinPt.y, box.MinPt.y);
    MaxPt.x = Max<float>(MaxPt.x, box.MaxPt.x);  MaxPt.y = Max<float>(MaxPt.y, box.MaxPt.y);
    return *this;
  } // Maximize

  // --------------------------------------------------------------------------
  // Name: Maximize
  // Desc: Maximise this box to include the given circle
  // Parm: const Circle2D &circle - the circle
  // --------------------------------------------------------------------------
  Box2D &Maximize(const Circle2D &circle)
  {
    Box2D box(circle);
    MinPt.x = Min<float>(MinPt.x, box.MinPt.x);  MinPt.y = Min<float>(MinPt.y, box.MinPt.y);
    MaxPt.x = Max<float>(MaxPt.x, box.MaxPt.x);  MaxPt.y = Max<float>(MaxPt.y, box.MaxPt.y);
    return *this;
  } // Maximize

  // --------------------------------------------------------------------------
  // Name: Translate
  // Desc: Trnaslate this box
  // Parm: const Vec2 &trans - the translation vector
  // --------------------------------------------------------------------------
  Box2D &Translate(const Vec2 &trans)
  {
    MinPt += trans;
    MaxPt += trans;
    return *this;
  } // Translate

  // --------------------------------------------------------------------------
  // Name: IsWithin
  // Desc: Test if the given point is within the box
  // Parm: const Vec2 &pos - the point
  // --------------------------------------------------------------------------
  bool IsWithin(const Vec2 &pos) const 
  {
    return (pos.x >= MinPt.x && pos.y >= MinPt.y && pos.x <= MaxPt.x && pos.y <= MaxPt.y); 
  } // IsWithin

  // --------------------------------------------------------------------------
  // Name: GetNearestPoint
  // Desc: Get a point within the box (or on the edge) that is as close as 
  //       possible to the given point.
  // Parm: const Vec2 test_point - the source point
  // Parm: Vec2 &point         - the nearest point to the source point
  // --------------------------------------------------------------------------
  void GetNearestPoint(const Vec2 test_point, Vec2 &point) const;

  // --------------------------------------------------------------------------
  // Members
  // --------------------------------------------------------------------------
  Vec2 MinPt;
  Vec2 MaxPt;

}; // struct Box2D


#endif // _PRIMATIVES_2_D_H_

// -- EOF

