// ----------------------------------------------------------------------------
// File: RenderTarget.cpp
// Desc: Manages a render target.
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "RenderTarget.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
RenderTarget::RenderTarget()
: DeviceObject          (),
  m_ColorSurface        (NULL),
  m_DepthStencilSurface (NULL)
{
  REF_COUNT_CTOR(RenderTarget);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
RenderTarget::~RenderTarget()
{
  REF_COUNT_DTOR(RenderTarget);
}


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
BackBufferRenderTarget::BackBufferRenderTarget()
: RenderTarget()
{
  REF_COUNT_CTOR(BackBufferRenderTarget);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
BackBufferRenderTarget::~BackBufferRenderTarget()
{
  REF_COUNT_DTOR(BackBufferRenderTarget);
}


// ----------------------------------------------------------------------------
// Create the back buffer render target (note - the width and height are ignored)
// ----------------------------------------------------------------------------
bool BackBufferRenderTarget::Create(uint width, uint height)
{
#if XBOX
  Device->GetRenderTarget(&m_ColorSurface);
#else
  Device->GetRenderTarget(0, &m_ColorSurface);
#endif
  Device->GetDepthStencilSurface(&m_DepthStencilSurface);

  if (m_ColorSurface && m_DepthStencilSurface)
    return true;

  return false;
}


// ----------------------------------------------------------------------------
// Binds the render target
// ----------------------------------------------------------------------------
void BackBufferRenderTarget::Apply()
{
#if XBOX
  Device->SetRenderTarget(m_ColorSurface, m_DepthStencilSurface);
#else
  Device->SetRenderTarget(0, m_ColorSurface);
  Device->SetDepthStencilSurface(m_DepthStencilSurface);
#endif
}


// ----------------------------------------------------------------------------
// Create the device objects
// ----------------------------------------------------------------------------
bool BackBufferRenderTarget::AllocateDeviceMemory()
{
#if XBOX
  Device->GetRenderTarget(&m_ColorSurface);
#else
  Device->GetRenderTarget(0, &m_ColorSurface);
#endif
  Device->GetDepthStencilSurface(&m_DepthStencilSurface);

  if (m_ColorSurface && m_DepthStencilSurface)
    return true;

  return false;
}


// ----------------------------------------------------------------------------
// Destroy teh device objects
// ----------------------------------------------------------------------------
bool BackBufferRenderTarget::ReleaseDeviceMemory()
{
  SafeRelease(m_ColorSurface);
  SafeRelease(m_DepthStencilSurface);

  return true;
}



// -- EOF


