// ----------------------------------------------------------------------------
// File: ApplicationModule_Win32.h
// Desc: The Win32 direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __APPLICATION_MODULE_WIN32_H_
#define __APPLICATION_MODULE_WIN32_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Engine/DisplaySettings.h"
#include "Engine/ApplicationModule.h"


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32 (class)
// Desc: The Win32 direct3d driver
// ----------------------------------------------------------------------------
class ApplicationModule_Win32 : public ApplicationModule
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ApplicationModule_Win32();
  virtual ~ApplicationModule_Win32();

  // --------------------------------------------------------------------------
  // The module's startup function
  // --------------------------------------------------------------------------
  virtual int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow);

  // --------------------------------------------------------------------------
  // Initialise the module
  // --------------------------------------------------------------------------
  virtual bool Create();

  // --------------------------------------------------------------------------
  // The windows procedure
  // --------------------------------------------------------------------------
  virtual LRESULT DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

  // --------------------------------------------------------------------------
  // Run the module
  // --------------------------------------------------------------------------
  virtual int Run();

  // --------------------------------------------------------------------------
  // Reset the device
  // --------------------------------------------------------------------------
  virtual bool ResetDisplay(bool toggleFullScreen, bool isFullScreen);

}; // class ApplicationModule_Win32


#endif // __APPLICATION_MODULE_WIN32_H_

// -- EOF

