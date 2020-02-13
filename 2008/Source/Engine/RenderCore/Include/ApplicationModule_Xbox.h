// ----------------------------------------------------------------------------
// File: ApplicationModule_Xbox.h
// Desc: The Xbox direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __APPLICATION_MODULE_XBOX_H_
#define __APPLICATION_MODULE_XBOX_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "DisplaySettings.h"
#include "ApplicationModule.h"


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Xbox (class)
// Desc: The Xbox direct3d driver
// ----------------------------------------------------------------------------
class ApplicationModule_Xbox : public ApplicationModule
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ApplicationModule_Xbox(const String &name);
  virtual ~ApplicationModule_Xbox();

  // --------------------------------------------------------------------------
  // The module's startup function
  // --------------------------------------------------------------------------
  virtual int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow);

  // --------------------------------------------------------------------------
  // Initialise the module
  // --------------------------------------------------------------------------
  virtual bool Create();

  // --------------------------------------------------------------------------
  // Run the module
  // --------------------------------------------------------------------------
  virtual int Run();

  // --------------------------------------------------------------------------
  // Reset the device
  // --------------------------------------------------------------------------
  virtual bool ResetDisplay(bool toggleFullScreen, bool isFullScreen);

  // --------------------------------------------------------------------------
  // Set the window title
  // --------------------------------------------------------------------------
  virtual void SetWindowTitle(const String &str);

}; // class ApplicationModule_Xbox


#endif // __APPLICATION_MODULE_XBOX_H_

// -- EOF

