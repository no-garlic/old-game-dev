// ----------------------------------------------------------------------------
// File: ShadowRenderTarget.h
// Desc: Manages a render target for shadow mapping.
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __SHADOW_RENDER_TARGET_H_
#define __SHADOW_RENDER_TARGET_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "Texture.h"


// ----------------------------------------------------------------------------
// Render target implementation for shadow textures
// ----------------------------------------------------------------------------
class ShadowRenderTarget : public RenderTarget
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ShadowRenderTarget();
  virtual ~ShadowRenderTarget();

  // --------------------------------------------------------------------------
  // Get the color texture
  // --------------------------------------------------------------------------
  Texture *GetColorTexture()  { return m_pColorTexture; }

  // --------------------------------------------------------------------------
  // Save the color surface
  // --------------------------------------------------------------------------
#if PC
  bool SaveColorSurfaceToFile(FileHandle handle);
#endif

  // --------------------------------------------------------------------------
  // Show the color surface
  // --------------------------------------------------------------------------
  void RenderColorSurfaceToScreen();

protected:
  // --------------------------------------------------------------------------
  // Allow the functor to create the render target
  // --------------------------------------------------------------------------
  friend struct RenderTargetFunctorTemplate<ShadowRenderTarget>;

  // --------------------------------------------------------------------------
  // Create the render target
  // --------------------------------------------------------------------------
  virtual bool Create(uint width, uint height);

  // --------------------------------------------------------------------------
  // Apply the render target as teh default drawing surface
  // --------------------------------------------------------------------------
  virtual void Apply();

  // --------------------------------------------------------------------------
  // Manage the device memory
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory();
  virtual bool ReleaseDeviceMemory();

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Texture            *m_pColorTexture;
  LPD3DXSPRITE        m_pSprite;
  uint                m_Width;
  uint                m_Height;

};


// ----------------------------------------------------------------------------
// Functor to create a shadow buffer render target
// ----------------------------------------------------------------------------
typedef RenderTargetFunctorTemplate<ShadowRenderTarget> ShadowRenderTargetFunctor;


#endif // __SHADOW_RENDER_TARGET_H_

// -- EOF

