// ----------------------------------------------------------------------------
// File: ShadowRenderTarget.cpp
// Desc: Manages a render target for shadow mapping.
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "ShadowRenderTarget.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
ShadowRenderTarget::ShadowRenderTarget()
: RenderTarget          (),
  m_Width               (0),
  m_Height              (0),
  m_pColorTexture       (NULL),
  m_pSprite             (NULL)
{
  REF_COUNT_CTOR(ShadowRenderTarget);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
ShadowRenderTarget::~ShadowRenderTarget()
{
  REF_COUNT_DTOR(ShadowRenderTarget);

  SafeRelease(m_pSprite);
  SafeUnRef(m_pColorTexture);
}


// ----------------------------------------------------------------------------
// Create the render target
// ----------------------------------------------------------------------------
bool ShadowRenderTarget::Create(uint width, uint height)
{
  SafeUnRef(m_pColorTexture);
  m_pColorTexture = NULL;

  m_Width = width;
  m_Height = height;

  DIRECT3DTEXTURE pTexture;

#if XBOX
  // TODO: Guess
  D3DFORMAT renderTargetFormat = D3DFMT_UNKNOWN;
  D3DFORMAT depthStencilFormat = D3DFMT_UNKNOWN;
#else
  D3DFORMAT renderTargetFormat = D3DFMT_R32F;
  D3DFORMAT depthStencilFormat = D3DFMT_D24X8;
#endif

#if XBOX
  if (FAILED(Device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, renderTargetFormat, 
    D3DPOOL_DEFAULT, &pTexture)))
    return false;
#else
  if (FAILED(Device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, renderTargetFormat, 
    D3DPOOL_DEFAULT, &pTexture, NULL)))
    return false;
#endif

  if (FAILED(pTexture->GetSurfaceLevel(0, &m_ColorSurface)))
    return false;

#if XBOX
  if (FAILED(Device->CreateDepthStencilSurface(width, height, depthStencilFormat, D3DMULTISAMPLE_NONE, 
    &m_DepthStencilSurface)))
    return false;
#else
  if (FAILED(Device->CreateDepthStencilSurface(width, height, depthStencilFormat, D3DMULTISAMPLE_NONE, 0, 
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
void ShadowRenderTarget::Apply()
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
bool ShadowRenderTarget::AllocateDeviceMemory()
{
  return Create(m_Width, m_Height);
}


// ----------------------------------------------------------------------------
// Release the device memory
// ----------------------------------------------------------------------------
bool ShadowRenderTarget::ReleaseDeviceMemory()
{
  delete m_pColorTexture;
  m_pColorTexture = NULL;

  SafeRelease(m_ColorSurface);
  SafeRelease(m_DepthStencilSurface);
  SafeRelease(m_pSprite);

  return true;
}


#if PC
// ----------------------------------------------------------------------------
// Save the color surface to a file
// ----------------------------------------------------------------------------
bool ShadowRenderTarget::SaveColorSurfaceToFile(FileHandle handle)
{
  if (FAILED(D3DXSaveSurfaceToFile(handle.GetAbsoluteFilename().c_str(), D3DXIFF_BMP, m_ColorSurface, NULL, NULL)))
    return false;

  return true;
}
#endif


// ----------------------------------------------------------------------------
// Render the color surface to the screen on a sprite
// ----------------------------------------------------------------------------
void ShadowRenderTarget::RenderColorSurfaceToScreen()
{
  VIEWPORT viewport;
  Device->GetViewport(&viewport);

  if (!m_pSprite)
    D3DXCreateSprite(Device, &m_pSprite);

  if (m_pSprite)
  {
#if XBOX
    m_pSprite->Begin();
    Matrix matrix = Matrix::MakeNewScaling(0.2f, 0.2f, 0.2f);
    m_pSprite->DrawTransform(m_pColorTexture->GetPtr(), NULL, &matrix, 0xffffffff);
    m_pSprite->End();
#else
    m_pSprite->SetTransform(&(Matrix::MakeNewScaling(0.2f, 0.2f, 0.2f)));
    m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
    m_pSprite->Draw(m_pColorTexture->GetPtr(), NULL, NULL, NULL, 0xffffffff);
    m_pSprite->End();
#endif
  }
}



// -- EOF

