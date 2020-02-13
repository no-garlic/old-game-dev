// ----------------------------------------------------------------------------
// File: ShadowCaster.cpp
// Desc: Performs the maths for casting shadows onto a depth texture
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "ShadowCaster.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
ShadowCaster::ShadowCaster()
{
  REF_COUNT_CTOR(ShadowCaster);

  m_pShadowRenderTarget = NULL;
  m_Width = 256;
  m_Height = 256;
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
ShadowCaster::~ShadowCaster()
{
  REF_COUNT_DTOR(ShadowCaster);
}


// ----------------------------------------------------------------------------
// Set the light direction
// ----------------------------------------------------------------------------
void ShadowCaster::SetLightDirection(const Vec3 &dir)
{
  m_LightDirection = dir;
  m_LightDirection.Normalize();
}


// ----------------------------------------------------------------------------
// Set the entire sphere that the light's frustum must include for
// generating the shadow texture (in world coords).
// ----------------------------------------------------------------------------
void ShadowCaster::SetLightFocus(const Sphere &focus)
{
  m_LightFocus = focus;
}


// ----------------------------------------------------------------------------
// Create the render target
// ----------------------------------------------------------------------------
bool ShadowCaster::CreateRenderTarget(uint width, uint height)
{
  if (m_pShadowRenderTarget)
    return false;

  // Store the width and height
  m_Width = width;
  m_Height = height;

  // Create the render target
  m_pShadowRenderTarget = (ShadowRenderTarget *) 
    Application.CreateRenderTarget(width, height, ShadowRenderTargetFunctor());

  // Check it was sucessfully created
  if (!m_pShadowRenderTarget)
    return false;

  return true;
}


// ----------------------------------------------------------------------------
// Get the light matrix to be used when rendering the scene into the shadow
// texture render target.
// ----------------------------------------------------------------------------
Matrix ShadowCaster::GetWorldViewProjLightMatrix(const Matrix &worldMatrix)
{
  Matrix view, proj;

  // Set the view matrix
  view.LookAtLH(m_LightFocus.center - m_LightDirection, m_LightFocus.center, Vec3(0.0f, 1.0f, 0.0f));

  // Set the projection matrix
  proj.OrthoLH(m_LightFocus.radius * 2.0f, m_LightFocus.radius * 2.0f, 
    m_LightFocus.radius * -2.0f, m_LightFocus.radius * 2.0f);

  // Return the combined view * projection matrix
  return (Matrix)((D3DXMATRIX) worldMatrix * (D3DXMATRIX) view * (D3DXMATRIX) proj);
}


// ----------------------------------------------------------------------------
// Get the texture matrix for looking up the depth shadow texture from the 
// normal scene render.  This matrix transforms a world space position into
// texture space.
// ----------------------------------------------------------------------------
Matrix ShadowCaster::GetShadowTextureMatrix(const Matrix &worldMatrix)
{
  float offsetX = 0.5f + (0.5f / (float) m_Width);
  float offsetY = 0.5f + (0.5f / (float) m_Height);

  // Compute the texture lookup bias matrix
  Matrix biasMatrix(
    0.5f,       0.0f,     0.0f,    0.0f,
    0.0f,      -0.5f,     0.0f,    0.0f,
    0.0f,       0.0f,     1.0f,    0.0f,
    offsetX,    offsetY,  0.0f,    1.0f);

  // Return the view * projection * bias matrix
  return GetWorldViewProjLightMatrix(worldMatrix).Multiply(biasMatrix);
}


// -- EOF

