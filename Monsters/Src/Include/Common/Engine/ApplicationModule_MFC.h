// ----------------------------------------------------------------------------
// File: ApplicationModule_MFC.h
// Desc: The MFC direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __APPLICATION_MODULE_MFC_H_
#define __APPLICATION_MODULE_MFC_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Engine/DisplaySettings.h"
#include "Engine/ApplicationModule.h"


// ----------------------------------------------------------------------------
// Only include this if we want to include MFC in out build
// ----------------------------------------------------------------------------
#ifdef __MFC_ENABLED


// ----------------------------------------------------------------------------
// Name: ApplicationModule_MFC (class)
// Desc: The MFC direct3d driver
// ----------------------------------------------------------------------------
class ApplicationModule_MFC : public ApplicationModule
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ApplicationModule_MFC();
  virtual ~ApplicationModule_MFC();

  // --------------------------------------------------------------------------
  // The module's startup function
  // --------------------------------------------------------------------------
  virtual int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow);

  // --------------------------------------------------------------------------
  // Create the MFC application isntance
  // --------------------------------------------------------------------------
  virtual CWinApp *CreateApp(DisplaySettings ds);

  // --------------------------------------------------------------------------
  // Initialise the module
  // --------------------------------------------------------------------------
  virtual bool Create();
  
  // --------------------------------------------------------------------------
  // Reset the device
  // --------------------------------------------------------------------------
  virtual bool ResetDisplay(bool toggleFullScreen, bool isFullScreen);

}; // class ApplicationModule_MFC


#endif // __MFC_ENABLED
#endif // __APPLICATION_MODULE_MFC_H_

// -- EOF

