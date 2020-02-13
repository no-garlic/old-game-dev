// ----------------------------------------------------------------------------
// File: ApplicationModule_WX.h
// Desc: The WX direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __APPLICATION_MODULE_WX_H_
#define __APPLICATION_MODULE_WX_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "wxWindows/wxDisplay.h"


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Wx (class)
// Desc: The Wx direct3d driver
// ----------------------------------------------------------------------------
class ApplicationModule_Wx : public ApplicationModule
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ApplicationModule_Wx(const String &name);
  virtual ~ApplicationModule_Wx();

  // --------------------------------------------------------------------------
  // The module's startup function
  // --------------------------------------------------------------------------
  virtual int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow);

  // --------------------------------------------------------------------------
  // Create the Wx application isntance
  // --------------------------------------------------------------------------
  virtual WxDisplayApp *CreateApp(DisplaySettings ds);

  // --------------------------------------------------------------------------
  // Initialise the module
  // --------------------------------------------------------------------------
  virtual bool Create();
  
  // --------------------------------------------------------------------------
  // Set the display settings
  // --------------------------------------------------------------------------
  virtual bool SetDisplaySettings(DisplaySettings &settings);

  // --------------------------------------------------------------------------
  // Request the module to exit
  // --------------------------------------------------------------------------
  virtual void RequestExit(int exitCode);

  // --------------------------------------------------------------------------
  // Reset the device
  // --------------------------------------------------------------------------
  virtual bool ResetDisplay(bool toggleFullScreen, bool isFullScreen);

  // --------------------------------------------------------------------------
  // Set the window title
  // --------------------------------------------------------------------------
  virtual void SetWindowTitle(const String &str);

}; // class ApplicationModule_Wx


#endif // __APPLICATION_MODULE_WX_H_

// -- EOF

