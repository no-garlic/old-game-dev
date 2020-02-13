// ----------------------------------------------------------------------------
// File: RenderTarget.h
// Desc: Manages a render target.
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __RENDER_TARGET_H_
#define __RENDER_TARGET_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "DeviceObject.h"


// ----------------------------------------------------------------------------
// Forward declaration
// ----------------------------------------------------------------------------
class Application;


// ----------------------------------------------------------------------------
// Render target class definition
// ----------------------------------------------------------------------------
class RenderTarget : public DeviceObject
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  RenderTarget();
  virtual ~RenderTarget();

  // --------------------------------------------------------------------------
  // Get the color and depth surfaces
  // --------------------------------------------------------------------------
  DIRECT3DSURFACE GetColorSurface()        { return m_ColorSurface;        }
  DIRECT3DSURFACE GetDepthStencilSurface() { return m_DepthStencilSurface; }

  // --------------------------------------------------------------------------
  // Create the render target
  // --------------------------------------------------------------------------
  virtual bool Create(uint width, uint height) = 0;

protected:
  // --------------------------------------------------------------------------
  // Friend class
  // --------------------------------------------------------------------------
  friend class ApplicationCentral;

  // --------------------------------------------------------------------------
  // Apply the render target as teh default drawing surface
  // --------------------------------------------------------------------------
  virtual void Apply() = 0;

  // --------------------------------------------------------------------------
  // Manage the device memory
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory() = 0;
  virtual bool ReleaseDeviceMemory() = 0;

  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  DIRECT3DSURFACE  m_ColorSurface;
  DIRECT3DSURFACE  m_DepthStencilSurface;

};


// ----------------------------------------------------------------------------
// Base creation functor for a render target
// ----------------------------------------------------------------------------
struct BaseRenderTargetFunctor
{
  virtual RenderTarget *operator()(uint width, uint height) const = 0;
};


// ----------------------------------------------------------------------------
// Templated creation functor for a render target
// ----------------------------------------------------------------------------
template <class T>
struct RenderTargetFunctorTemplate : public BaseRenderTargetFunctor
{
  virtual RenderTarget *operator()(uint width, uint height) const 
  { 
    T *pRenderTarget = new T();

    if (!pRenderTarget->Create(width, height))
      SafeDelete(pRenderTarget);

    return pRenderTarget;
  }
};


// ----------------------------------------------------------------------------
// Render target implementation for the back buffer
// ----------------------------------------------------------------------------
class BackBufferRenderTarget : public RenderTarget
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  BackBufferRenderTarget();
  virtual ~BackBufferRenderTarget();

protected:
  // --------------------------------------------------------------------------
  // Allow the functor to create the render target
  // --------------------------------------------------------------------------
  friend struct RenderTargetFunctorTemplate<BackBufferRenderTarget>;

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

};


// ----------------------------------------------------------------------------
// Functor to create a back buffer render target
// ----------------------------------------------------------------------------
typedef RenderTargetFunctorTemplate<BackBufferRenderTarget> BackBufferRenderTargetFunctor;


#endif // __RENDER_TARGET_H_

// -- EOF

