// ----------------------------------------------------------------------------
// File: Box.h
// Desc: Bounding box class
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _BOX_H
#define _BOX_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "Vec3.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Frustum;
class Sphere;
class Line;
class Ray;


// ----------------------------------------------------------------------------
// Name: Box (struct)
// Desc: Class to define an axis aligned bounding box (aabb).
// ----------------------------------------------------------------------------
class Box
{
public:
  // --------------------------------------------------------------------------
  // Constructors
  // --------------------------------------------------------------------------
  Box() {}
  Box(const Vec3 &min_pt, const Vec3 max_pt) : MinPt(min_pt), MaxPt(max_pt) {}
  Box(uint num_points, const Vec3 *points);

  // --------------------------------------------------------------------------
  // Get the extents of the box
  // --------------------------------------------------------------------------
  const Vec3 &GetMin() const  { return MinPt; }
  const Vec3 &GetMax() const  { return MaxPt; }

  // --------------------------------------------------------------------------
  // Set the extents of the box
  // --------------------------------------------------------------------------
  void SetMin(const Vec3 &min_pt) { MinPt = min_pt; }
  void SetMax(const Vec3 &max_pt) { MaxPt = max_pt; }
  void SetHeights(float h_min, float h_max) { MinPt.z = h_min; MaxPt.z = h_max; }

  // --------------------------------------------------------------------------
  // Get the center of the box
  // --------------------------------------------------------------------------
  Vec3 GetCenter() const;
  Vec3 GetSize() const;

  // --------------------------------------------------------------------------
  // Get the size of the box
  // --------------------------------------------------------------------------
  float GetWidth()  const { return MaxPt.x - MinPt.x; }
  float GetHeight() const { return MaxPt.y - MinPt.y; }
  float GetDepth()  const { return MaxPt.z - MinPt.z; }
  
  // --------------------------------------------------------------------------
  // Clamp the point to the extents of the box
  // --------------------------------------------------------------------------
  Vec3 Clamp(const Vec3 &point) const;

  // --------------------------------------------------------------------------
  // Maximize of minimize the box
  // --------------------------------------------------------------------------
  void Maximize(const Box &box);
  void Minimize(const Box &box);

  // --------------------------------------------------------------------------
  // Test if the item is within hte box
  // --------------------------------------------------------------------------
  bool IsWithin(const Vec3 &point) const;
  bool IsWithin(const Box &box) const; 
  bool IsWithin(const Frustum &frustum) const; 

  // --------------------------------------------------------------------------
  // Calculate the corners of the box (must supply a Vec3[8] array)
  // --------------------------------------------------------------------------
  void CalcCorners(Vec3 *vertex) const;

 // ---------------------------------------------------------------------------
 // Test for a collision with the box
 // ---------------------------------------------------------------------------
  bool TestCollision(const Sphere &sphere) const;
  bool TestCollision(const Box &box) const;
  bool TestCollision(const Line &line) const;
  bool TestCollision(const Ray &ray) const;

  // --------------------------------------------------------------------------
  // Create a zero suize box at the origin
  // --------------------------------------------------------------------------
  void Zero();
  bool IsEmpty() const;

  // --------------------------------------------------------------------------
  // Get the min and max collision points of the box with the line
  // --------------------------------------------------------------------------
  bool GetMinMaxCollision(const Line &line, float &min_t, float &max_t) const;

  // --------------------------------------------------------------------------
  // The min and max extents of the box
  // --------------------------------------------------------------------------
  Vec3    MinPt;
  Vec3    MaxPt;

}; // class Box


#endif // _BOX_H

// -- EOF

