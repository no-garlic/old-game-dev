// ----------------------------------------------------------------------------
// File: ShadowCaster.h
// Desc: Performs the maths for casting shadows onto a depth texture
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __SHADOW_CASTER_H_
#define __SHADOW_CASTER_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderCore.h"
#include "Texture.h"
#include "ShadowRenderTarget.h"


// ----------------------------------------------------------------------------
// Performs the maths for casting shadows onto a depth texture
// ----------------------------------------------------------------------------
class ShadowCaster
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ShadowCaster();
  ~ShadowCaster();

  // --------------------------------------------------------------------------
  // Get the light matrix and the texture matrix
  // --------------------------------------------------------------------------
  Matrix GetWorldViewProjLightMatrix(const Matrix &worldMatrix);
  Matrix GetShadowTextureMatrix(const Matrix &worldMatrix);

  // --------------------------------------------------------------------------
  // Create the depth texture render target
  // --------------------------------------------------------------------------
  bool CreateRenderTarget(uint width, uint height);
  ShadowRenderTarget *GetRenderTarget()   { return m_pShadowRenderTarget; }

  // --------------------------------------------------------------------------
  // Set the light direction
  // --------------------------------------------------------------------------
  void SetLightDirection(const Vec3 &dir);

  // --------------------------------------------------------------------------
  // Set the entire sphere that the light's frustum must include for
  // generating the shadow texture (in world coords). This is typically the
  // bounding sphere of the geometry that casts a shadow.
  // --------------------------------------------------------------------------
  void SetLightFocus(const Sphere &focus);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  ShadowRenderTarget   *m_pShadowRenderTarget;
  Matrix                m_ViewProjMatrix;
  Vec3                  m_LightPosition;
  Vec3                  m_LightDirection;
  Sphere                m_LightFocus;
  uint                  m_Width;
  uint                  m_Height;

};


#endif // __SHADOW_CASTER_H_

// -- EOF

