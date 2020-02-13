// ----------------------------------------------------------------------------
// File: TextureRenderTarget.h
// Desc: Manages a generic render target for rendering to a texture.
// Auth: Michael Petrou
// (C) Copyright: 2007
// ----------------------------------------------------------------------------
#ifndef __TEXTURE_RENDER_TARGET_H_
#define __TEXTURE_RENDER_TARGET_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderCore.h"
#include "Texture.h"


// ----------------------------------------------------------------------------
// Render target implementation for textures
// ----------------------------------------------------------------------------
class TextureRenderTarget : public RenderTarget
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  TextureRenderTarget();
  virtual ~TextureRenderTarget();

#if PC
  // --------------------------------------------------------------------------
  // Save the color texture
  // --------------------------------------------------------------------------
  bool SaveColorSurfaceToFile(FileHandle handle);
#endif

  // --------------------------------------------------------------------------
  // Get the color texture
  // --------------------------------------------------------------------------
  Texture *GetColorTexture()  { return m_pColorTexture; }

protected:
  // --------------------------------------------------------------------------
  // Allow the functor to create the render target
  // --------------------------------------------------------------------------
  friend struct RenderTargetFunctorTemplate<TextureRenderTarget>;

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
  uint                m_Width;
  uint                m_Height;

};


// ----------------------------------------------------------------------------
// Functor to create the render target
// ----------------------------------------------------------------------------
typedef RenderTargetFunctorTemplate<TextureRenderTarget> TextureRenderTargetFunctor;


#endif // __TEXTURE_RENDER_TARGET_H_

// -- EOF


