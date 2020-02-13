// ----------------------------------------------------------------------------
// File: Frustum.h
// Desc: Describes a viewing frustum
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef __FRUSTUM_H
#define __FRUSTUM_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "Matrix.h"
#include "Plane.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Sphere;
class Matrix;
class Box;


// ----------------------------------------------------------------------------
// Name: Frustum (class)
// Desc: Describes a viewing frustum
// ----------------------------------------------------------------------------
class Frustum
{
public:
  // ------------------------------------------------------------------------
  // Constructor
  // ------------------------------------------------------------------------
  Frustum();

  // ------------------------------------------------------------------------
  // Name: FrustumPlane (enum)
  // Desc: The planes of the frustum
  // ------------------------------------------------------------------------
  enum FrustumPlane
  {
    FRONT   = 0,    // The FRONT plane of the frustum
    LEFT    = 1,    // The LEFT  plane of the frustum
    RIGHT   = 2,    // The RIGHT plane of the frustum
    TOP     = 3,    // The TOP plane of the frustum
    BOTTOM  = 4,    // The BOTTOM plane of the frustum
    BACK    = 5     // The BACK plane of the frustum
  }; // enum FrustumPlane

  // ------------------------------------------------------------------------
  // Name: FrustumIntersect (enum)
  // Desc: The intersection test result values
  // ------------------------------------------------------------------------
  enum FrustumIntersect
  {
    IN_FRUSTUM      = 0,    // The object is totally within the frustum
    OUT_FRUSTUM     = 1,    // The object is totally out of the frustum
    PARTIAL         = 2     // The object intersects one of the planes
  }; // enum FrustumIntersect

  // ------------------------------------------------------------------------
  // Get the planes array from the frustum
  // ------------------------------------------------------------------------
  Plane *GetPlanes();
  const Plane *GetPlanes() const;

  // ------------------------------------------------------------------------
  // Collision tests
  // ------------------------------------------------------------------------
  virtual int Intersects(const Sphere &sphere, const Matrix &world_matrix) const;
  virtual int Intersects(const Box &box, const Matrix &world_matrix) const;
  virtual int Intersects(const Sphere &sphere) const;
  virtual int Intersects(const Box &box) const;

  // --------------------------------------------------------------------------
  // Create a string debugging the frustum planes
  // --------------------------------------------------------------------------
  virtual String ToString() const;

protected:
  // ------------------------------------------------------------------------
  // Private functions
  // ------------------------------------------------------------------------
  virtual void RecalculateFrustum() const = 0;

  // ------------------------------------------------------------------------
  // Privates members
  // ------------------------------------------------------------------------
  mutable Plane       m_planes[6];    // The planes of the frustum
  mutable bool        m_dirty;        // Have the matricies changed

}; // class Frustum


#endif // __FRUSTUM_H

// -- EOF

