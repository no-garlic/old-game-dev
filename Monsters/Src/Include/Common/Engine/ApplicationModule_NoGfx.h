// ----------------------------------------------------------------------------
// File: ApplicationModule_NoGfx.h
// Desc: The NULL renderer driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __APPLICATION_MODULE_NOGFX_H_
#define __APPLICATION_MODULE_NOGFX_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Engine/DisplaySettings.h"
#include "Engine/ApplicationModule.h"


// ----------------------------------------------------------------------------
// Name: ApplicationModule_NoGfx (class)
// Desc: The Win32 direct3d driver
// ----------------------------------------------------------------------------
class ApplicationModule_NoGfx : public ApplicationModule
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ApplicationModule_NoGfx();
  virtual ~ApplicationModule_NoGfx();

  // --------------------------------------------------------------------------
  // The module's startup function
  // --------------------------------------------------------------------------
  virtual int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow);

  // --------------------------------------------------------------------------
  // Initialise the module
  // --------------------------------------------------------------------------
  virtual bool Create();

  // --------------------------------------------------------------------------
  // Run the module (implement in the descendant class)
  // --------------------------------------------------------------------------
  virtual int Run() = 0;

  // --------------------------------------------------------------------------
  // Initialsiation
  // --------------------------------------------------------------------------
  virtual bool Init();
  virtual void Shutdown();

  // --------------------------------------------------------------------------
  // Process the given processId
  // --------------------------------------------------------------------------
  virtual void App();
  virtual void Cull();
  virtual void Draw();

  // --------------------------------------------------------------------------
  // Other callback functions
  // --------------------------------------------------------------------------
  virtual bool ResetDisplay(bool toggleFullScreen, bool isFullScreen);
  virtual bool CreateSafeObjects();
  virtual bool CreateDeviceObjects();
  virtual bool ReleaseSafeObjects();
  virtual bool ReleaseDeviceObjects();
  virtual void Resize();

}; // class ApplicationModule_NoGfx


#endif // __APPLICATION_MODULE_NOGFX_H_

// -- EOF

