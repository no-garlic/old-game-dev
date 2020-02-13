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
#include "libStandard.h"
#include "DisplaySettings.h"
#include "ApplicationModule.h"


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
  ApplicationModule_NoGfx(const String &name);
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
  virtual int Run(const String &commandLine) = 0;

  // --------------------------------------------------------------------------
  // Initialsiation
  // --------------------------------------------------------------------------
  virtual bool Init();
  virtual void Shutdown();

  // --------------------------------------------------------------------------
  // Set the window title
  // --------------------------------------------------------------------------
  virtual void SetWindowTitle(const String &str);

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
  virtual void Resize();
  virtual void SetRenderState();
  virtual bool SetDisplaySettings(DisplaySettings &settings);

protected:
  // --------------------------------------------------------------------------
  // Is this a null render module type?
  // --------------------------------------------------------------------------
  virtual bool IsNullRender() { return true; }

}; // class ApplicationModule_NoGfx


#endif // __APPLICATION_MODULE_NOGFX_H_

// -- EOF

