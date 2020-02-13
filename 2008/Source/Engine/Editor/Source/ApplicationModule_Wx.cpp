// ----------------------------------------------------------------------------
// File: ApplicationModule_Wx.cpp
// Desc: The Wx direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "ApplicationModule_Wx.h"
#include "wxWindows/wxDisplay.h"


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Wx::ApplicationModule_Wx
// Desc: Constructor
// ----------------------------------------------------------------------------
ApplicationModule_Wx::ApplicationModule_Wx(const String &name)
: ApplicationModule(name)
{
  REF_COUNT_CTOR(ApplicationModule_Wx);

  WxDisplay::SetModule(this);
} // ApplicationModule_Wx


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Wx::~ApplicationModule_Wx
// Desc: destructor
// ----------------------------------------------------------------------------
ApplicationModule_Wx::~ApplicationModule_Wx()
{
  REF_COUNT_DTOR(ApplicationModule_Wx);
  Input.DestroyInstance();
} // ~ApplicationModule_Wx


// --------------------------------------------------------------------------
// Set the display settings
// --------------------------------------------------------------------------
bool ApplicationModule_Wx::SetDisplaySettings(DisplaySettings &settings)
{
  DisplaySettings defaultSettings;
  settings = defaultSettings;

  return true;
}


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Wx::Main
// Desc: The startup function for the module
// Parm: HINSTANCE hInstance      - the app instance
// Parm: HINSTANCE hPrevInstance  - the prev instance
// Parm: LPTSTR lpCmdLine         - the command line
// Parm: int iCmdShow             - the show mode
// Retn: int                      - the app return value
// ----------------------------------------------------------------------------
int ApplicationModule_Wx::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
  // Create the display settings
  DisplaySettings displaySettings;
  SetDisplaySettings(displaySettings);

  // Create the Wx Application here so we can configure the HWND
  WxDisplay::SetApp(CreateApp(displaySettings));

  // Set the module handle
  wxSetInstance(GetModuleHandle(NULL));

  // wxWidgets wants to call free(...) on the program arguments we pass in.
  // This means that we need to malloc some new memory and copy the program
  // name and path to this memory. We don't want or need to give wxWidgets
  // any additional arguments.
  const char *argv0 = lpCmdLine;

  wxASSERT(argv0);
  size_t  exeLength = strlen(argv0);
  char   *exeName   = (char *)malloc(sizeof(char) * exeLength + 1);
  strcpy(exeName, argv0);

  int    dummyArgc = 1;
  char **dummyArgv = (char **)malloc(sizeof(char *) * dummyArgc);
  dummyArgv[0] = exeName;

  int returnCode = wxEntry(dummyArgc, dummyArgv);
  return returnCode;
} // Main


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Wx::SetWindowTitle
// Desc: Sets the window title
// Parm: const String &str - the title
// ----------------------------------------------------------------------------
void ApplicationModule_Wx::SetWindowTitle(const String &str)
{
  WxDisplay::GetApp()->GetTopWindow()->SetTitle(str.c_str());
} // SetWindowTitle


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Wx::CreateApp
// Desc: Create the application
// Parm: DisplaySettings ds  - the display settings
// Retn: CWinApp *           - the application
// ----------------------------------------------------------------------------
WxDisplayApp *ApplicationModule_Wx::CreateApp(DisplaySettings ds)
{
  // Override this function to implement your own 
  // Wx application.

  WxDisplay::GetDisplaySettings() = ds;
  return new WxDisplayApp;
} // CreateApp


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::Create
// Desc: Set the module's display
// ----------------------------------------------------------------------------
bool ApplicationModule_Wx::Create()
{
  // Get the display settings
  DisplaySettings ds;
  if (!SetDisplaySettings(ds))
    return false;

  // Create the application
  if (!Application.Init(WxDisplay::GetHWND(), this))
    return false;

  return true;
} // Create


// --------------------------------------------------------------------------
// Name: ApplicationModuleManager::RequestExit
// Desc: Request the module to exit
// --------------------------------------------------------------------------
void ApplicationModule_Wx::RequestExit(int exitCode)
{
  // Not Working -> Application.RequestExit(exitCode);
  WxDisplay::GetApp()->ExitMainLoop();
} // RequestExit


// --------------------------------------------------------------------------
// Reset the device
// --------------------------------------------------------------------------
bool ApplicationModule_Wx::ResetDisplay(bool toggleFullScreen, bool isFullScreen)
{
  if (toggleFullScreen)
  {
    WxDisplayFrame *pFrame = WxDisplay::GetFrame();
    pFrame->ShowFullScreen(!pFrame->IsFullScreen(), wxFULLSCREEN_ALL);
  }

  // Get the window
  HWND hWnd = Application.GetHWND();

  // Get the client rect
  RECT clientRect;
  GetClientRect(hWnd, &clientRect);

  // Create the display settings
  DisplaySettings displaySettings;
  SetDisplaySettings(displaySettings);
  displaySettings.WindowParams.BackBufferWidth  = clientRect.right - clientRect.left;
  displaySettings.WindowParams.BackBufferHeight = clientRect.bottom - clientRect.top;

  // Reset the device
  if (FAILED(m_pDevice->Reset(&displaySettings.WindowParams)))
    return false;

  // Tell the module that the window size has changed
  Resize();
  return true;
} // ResetDisplay


// -- EOF
