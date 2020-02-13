// ----------------------------------------------------------------------------
// File: TextureRenderTarget.cpp
// Desc: Manages a generic render target for rendering to a texture.
// Auth: Michael Petrou
// (C) Copyright: 2007
// ----------------------------------------------------------------------------
#include "TextureRenderTarget.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
TextureRenderTarget::TextureRenderTarget()
: RenderTarget          (),
  m_Width               (0),
  m_Height              (0),
  m_pColorTexture       (NULL)
{
  REF_COUNT_CTOR(TextureRenderTarget);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
TextureRenderTarget::~TextureRenderTarget()
{
  REF_COUNT_DTOR(TextureRenderTarget);

  SafeUnRef(m_pColorTexture);
}


// ----------------------------------------------------------------------------
// Create the render target
// ----------------------------------------------------------------------------
bool TextureRenderTarget::Create(uint width, uint height)
{
  SafeUnRef(m_pColorTexture);
  m_pColorTexture = NULL;

  m_Width = width;
  m_Height = height;

  DIRECT3DTEXTURE pTexture;

#if XBOX
  if (FAILED(Device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, 
    D3DPOOL_DEFAULT, &pTexture)))
    return false;
#else
  if (FAILED(Device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, 
    D3DPOOL_DEFAULT, &pTexture, NULL)))
    return false;
#endif

  if (FAILED(pTexture->GetSurfaceLevel(0, &m_ColorSurface)))
    return false;

#if XBOX
  D3DFORMAT depthStencilFormat = D3DFMT_UNKNOWN;

  if (FAILED(Device->CreateDepthStencilSurface(width, height, depthStencilFormat, D3DMULTISAMPLE_NONE, 
    &m_DepthStencilSurface)))
    return false;
#else
  D3DFORMAT depthStencilFormat = D3DFMT_D24X8;

  if (FAILED(Device->CreateDepthStencilSurface(width, height, D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, 
    TRUE, &m_DepthStencilSurface, NULL)))
    return false;
#endif


  m_pColorTexture = new Texture(pTexture);
  m_pColorTexture->Ref();

  return true;
}


// ----------------------------------------------------------------------------
// Bind the render target
// ----------------------------------------------------------------------------
void TextureRenderTarget::Apply()
{
#if XBOX
  Device->SetRenderTarget(m_ColorSurface, m_DepthStencilSurface);
#else
  Device->SetRenderTarget(0, m_ColorSurface);
  Device->SetDepthStencilSurface(m_DepthStencilSurface);
#endif
}


// ----------------------------------------------------------------------------
// Allocate the device memory
// ----------------------------------------------------------------------------
bool TextureRenderTarget::AllocateDeviceMemory()
{
  return Create(m_Width, m_Height);
}


// ----------------------------------------------------------------------------
// Release the device memory
// ----------------------------------------------------------------------------
bool TextureRenderTarget::ReleaseDeviceMemory()
{
  delete m_pColorTexture;
  m_pColorTexture = NULL;

  SafeRelease(m_ColorSurface);
  SafeRelease(m_DepthStencilSurface);

  return true;
}


#if PC
// ----------------------------------------------------------------------------
// Save the color surface to a file
// ----------------------------------------------------------------------------
bool TextureRenderTarget::SaveColorSurfaceToFile(FileHandle handle)
{
  if (FAILED(D3DXSaveSurfaceToFile(handle.GetAbsoluteFilename().c_str(), D3DXIFF_BMP, m_ColorSurface, NULL, NULL)))
    return false;

  return true;
}
#endif


// -- EOF

