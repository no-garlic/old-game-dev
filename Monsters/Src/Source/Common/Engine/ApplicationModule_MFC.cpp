// ----------------------------------------------------------------------------
// File: ApplicationModule_MFC.cpp
// Desc: The MFC direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/ApplicationModule_MFC.h"
#include "Engine/ApplicationCentral.h"
#include "Engine/MFCDisplay.h"


// ----------------------------------------------------------------------------
// Only include this file if MFC is enabled
// ----------------------------------------------------------------------------
#ifdef __MFC_ENABLED


// ----------------------------------------------------------------------------
// Use the MFC Main function
// ----------------------------------------------------------------------------
extern int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);


// ----------------------------------------------------------------------------
// Name: ApplicationModule_MFC::ApplicationModule_MFC
// Desc: Constructor
// ----------------------------------------------------------------------------
ApplicationModule_MFC::ApplicationModule_MFC()
: ApplicationModule()
{
  REF_COUNT_CTOR(ApplicationModule_MFC);

  MFCDisplay::SetModule(this);
} // ApplicationModule_MFC


// ----------------------------------------------------------------------------
// Name: ApplicationModule_MFC::~ApplicationModule_MFC
// Desc: destructor
// ----------------------------------------------------------------------------
ApplicationModule_MFC::~ApplicationModule_MFC()
{
  REF_COUNT_DTOR(ApplicationModule_MFC);
} // ~ApplicationModule_MFC


// ----------------------------------------------------------------------------
// Name: ApplicationModule_MFC::Main
// Desc: The startup function for the module
// Parm: HINSTANCE hInstance      - the app instance
// Parm: HINSTANCE hPrevInstance  - the prev instance
// Parm: LPTSTR lpCmdLine         - the command line
// Parm: int iCmdShow             - the show mode
// Retn: int                      - the app return value
// ----------------------------------------------------------------------------
int ApplicationModule_MFC::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
  // Create the MFC Application here so we can configure the HWND
  MFCDisplay::SetApp(CreateApp(m_DisplaySettings));

  // Run the AFX version of WinMain
  AfxGetModuleState()->m_bDLL = 0;
  return AfxWinMain(hInstance, hPrevInstance, lpCmdLine, iCmdShow);
} // Main


// ----------------------------------------------------------------------------
// Name: ApplicationModule_MFC::CreateApp
// Desc: Create the application
// Parm: DisplaySettings ds  - the display settings
// Retn: CWinApp *           - the application
// ----------------------------------------------------------------------------
CWinApp *ApplicationModule_MFC::CreateApp(DisplaySettings ds)
{
  // Override this function to implement your own 
  // MFC application.

  MFCDisplay::GetDisplaySettings() = ds;

  return new MFC_Application();
} // CreateApp


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::Create
// Desc: Set the module's display
// ----------------------------------------------------------------------------
bool ApplicationModule_MFC::Create()
{
  // Create the application
  if (!ApplicationCentral.Init(MFCDisplay::GetWnd()->GetSafeHwnd(), this))
    return false;

  return true;
} // Create


// --------------------------------------------------------------------------
// Reset the device
// --------------------------------------------------------------------------
bool ApplicationModule_MFC::ResetDisplay(bool toggleFullScreen, bool isFullScreen)
{
  // We dont support fullscreen with MFC, so just ignore 
  // the request.
  if (toggleFullScreen)
    return true;

  // Get the window
  HWND hWnd = ApplicationCentral.GetHWND();

  // Release our device objects if we have already
  // created them
  if (m_DeviceObjectsCreated && !ReleaseDeviceObjects())
    return false;

  // Set the device objects as released
  m_DeviceObjectsCreated = false;

  // Get the client rect
  RECT clientRect;
  GetClientRect(hWnd, &clientRect);
  m_DisplaySettings.WindowParams.BackBufferWidth  = clientRect.right - clientRect.left;
  m_DisplaySettings.WindowParams.BackBufferHeight = clientRect.bottom - clientRect.top;

  // Reset the device
  if (FAILED(m_pDevice->Reset(&m_DisplaySettings.WindowParams)))
    return false;

  // Tell the module that the window size has changed
  Resize();

  // Recreate the device objects
  if (!CreateDeviceObjects())
    return false;

  // Set the device objects as created
  m_DeviceObjectsCreated = true;

  return true;
} // ResetDisplay


// ----------------------------------------------------------------------------
// Only include this file if MFC is enabled
// ----------------------------------------------------------------------------
#endif // __MFC_ENABLED


// -- EOF
