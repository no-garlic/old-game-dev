// ----------------------------------------------------------------------------
// File: PerspectiveFrustum.h
// Desc: Describes a prespective frustum
// Auth: Michael Petrou
// (C) Copyright:   2007
// ----------------------------------------------------------------------------
#ifndef __PERSPECTIVE_FRUSTUM_H
#define __PERSPECTIVE_FRUSTUM_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Frustum.h"


// ----------------------------------------------------------------------------
// Name: PerspectiveFrustum (class)
// Desc: Describes a perspective frustum
// ----------------------------------------------------------------------------
class PerspectiveFrustum : public Frustum
{
public:
  // ------------------------------------------------------------------------
  // Constructor
  // ------------------------------------------------------------------------
  PerspectiveFrustum();

  // ------------------------------------------------------------------------
  // Set the frustum planes
  // ------------------------------------------------------------------------
  void SetViewMatrix(const Matrix &m);
  void SetProjMatrix(const Matrix &m);

protected:
  // ------------------------------------------------------------------------
  // Private functions
  // ------------------------------------------------------------------------
  virtual void RecalculateFrustum() const;

  // ------------------------------------------------------------------------
  // Privates members
  // ------------------------------------------------------------------------
  mutable Matrix      m_view_mat;     // The view matrix
  mutable Matrix      m_proj_mat;     // The projection matrix

}; // class PerspectiveFrustum


#endif // __PERSPECTIVE_FRUSTUM_H

// -- EOF

