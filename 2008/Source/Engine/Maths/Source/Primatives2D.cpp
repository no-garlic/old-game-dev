// ----------------------------------------------------------------------------
// File: Primatives2D.cpp
// Desc: 2D Primative classes
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Primatives2D.h"
#include "stdMath.h"


// ----------------------------------------------------------------------------
// Name: Box2D::GetNearestPoint
// Desc: Get a point within the box (or on the edge) that is as close as 
//       possible to the given point.
// Parm: const Vec2 test_point - the source point
// Parm: Vec2 &point         - the nearest point to the source point
// ----------------------------------------------------------------------------
void Box2D::GetNearestPoint(const Vec2 test_point, Vec2 &point) const
{
  // Check if the test point is within the x 
  // range of the box.
  if (IsBetween(test_point.x, MinPt.x, MaxPt.x))
  {
    point.x = test_point.x;
    point.y = (abs(test_point.y - MinPt.y) < abs(test_point.y - MaxPt.y)) ? MinPt.y : MaxPt.y;
    return;
  } // if

  // Check if the test point is within the y
  // range of the box.
  if (IsBetween(test_point.y, MinPt.y, MaxPt.y))
  {
    point.x = (abs(test_point.x - MinPt.x) < abs(test_point.x - MaxPt.x)) ? MinPt.x : MaxPt.x;
    point.y = test_point.y;
    return;
  } // if

  // Now find which ocrner quadrant that the
  // point lies in and then return that corner point.
  if (test_point.x < MinPt.x)
  {
    if (test_point.y < MinPt.y)
    {
      point = MinPt;
    } // if
    else
    {
      point.x = MinPt.x;
      point.y = MaxPt.y;
    } // else
  } // if
  else
  {
    if (test_point.y < MinPt.y)
    {
      point.x = MaxPt.x;
      point.y = MinPt.y;
    } // if
    else
    {
      point = MaxPt;
    } // else
  } // else
} // GetNearestPoint


// -- EOF

