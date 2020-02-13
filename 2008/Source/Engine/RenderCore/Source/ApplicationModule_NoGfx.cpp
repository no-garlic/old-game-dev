// ----------------------------------------------------------------------------
// File: ApplicationModule_NoGfx.cpp
// Desc: The Win32 direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "ApplicationModule_NoGfx.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Windows proc callback
// ----------------------------------------------------------------------------
LRESULT CALLBACK StaticWndProcNull(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);


// ----------------------------------------------------------------------------
// Name: ApplicationModule_NoGfx::ApplicationModule_NoGfx
// Desc: Constructor
// ----------------------------------------------------------------------------
ApplicationModule_NoGfx::ApplicationModule_NoGfx(const String &name)
: ApplicationModule(name)
{
  REF_COUNT_CTOR(ApplicationModule_NoGfx);
} // ApplicationModule_NoGfx


// ----------------------------------------------------------------------------
// Name: ApplicationModule_NoGfx::~ApplicationModule_NoGfx
// Desc: destructor
// ----------------------------------------------------------------------------
ApplicationModule_NoGfx::~ApplicationModule_NoGfx()
{
  REF_COUNT_DTOR(ApplicationModule_NoGfx);
} // ~ApplicationModule_NoGfx


// ----------------------------------------------------------------------------
// Name: ApplicationModule_NoGfx::SetWindowTitle
// Desc: Sets the window title
// Parm: const String &str - the title
// ----------------------------------------------------------------------------
void ApplicationModule_NoGfx::SetWindowTitle(const String &str)
{
} // SetWindowTitle


// ----------------------------------------------------------------------------
// Name: ApplicationModule_NoGfx::Main
// Desc: The startup function for the module
// Parm: HINSTANCE hInstance      - the app instance
// Parm: HINSTANCE hPrevInstance  - the prev instance
// Parm: LPTSTR lpCmdLine         - the command line
// Parm: int iCmdShow             - the show mode
// Retn: int                      - the app return value
// ----------------------------------------------------------------------------
int ApplicationModule_NoGfx::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
  // Initialise the engine
  if (!Create())
    return -1;

  // Run the engine
  return Run(lpCmdLine);
} // Main


// ----------------------------------------------------------------------------
// Name: ApplicationModule_NoGfx::Create
// Desc: Set the module's display
// Retn: bool                   - true if the application was initialised
// ----------------------------------------------------------------------------
bool ApplicationModule_NoGfx::Create()
{
  // Build the window class
  WNDCLASS            wc;    
  wc.style            = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc      = &StaticWndProcNull;
  wc.cbClsExtra       = 0;
  wc.cbWndExtra       = 0;
  wc.hInstance        = (HINSTANCE)GetModuleHandle(0);
  wc.hIcon            = 0;
  wc.hCursor          = 0;
  wc.hbrBackground    = 0;
  wc.lpszMenuName     = 0;
  wc.lpszClassName    = "NullDevice";

  // Register the window class
  if (RegisterClass(&wc) == 0)
    return false;

  // Create the window
  HWND hWnd = CreateWindow("NullDevice", "NullDevice", WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, wc.hInstance, 0);;

  // Make sure the window was created
  if (!hWnd)
    return false;

  // Create the application
  if (!Application.Init(hWnd, this))
    return false;

  // Show the window
  return true;
} // Create


// ----------------------------------------------------------------------------
// Name: ApplicationModule_NoGfx::StaticWndProcNull
// Desc: The static windows procedure that is called from the message pump
// Parm: HWND hWnd     - the window
// Parm: UINT Message  - the message
// Parm: WPARAM wParam - the first parameter
// Parm: LPARAM lParam - the second parameter
// Retn: LRESULT       - the result
// ----------------------------------------------------------------------------
LRESULT CALLBACK StaticWndProcNull(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
  // If this is a create message, trap the 'this' pointer 
  // passed in and store it within the window.
  if (Message == WM_CREATE) 
    SetWindowLong(hWnd, GWL_USERDATA, (LONG)(LONGLONG)((CREATESTRUCT FAR *) lParam)->lpCreateParams);

  // Obtain the correct destination for this message
  ApplicationModule_NoGfx *app = (ApplicationModule_NoGfx *) (LONGLONG)GetWindowLong(hWnd, GWL_USERDATA);
  if (app)
    return TRUE;

  // No destination found, defer to system...
  return DefWindowProc(hWnd, Message, wParam, lParam);
} // StaticWndProcNull


// --------------------------------------------------------------------------
// Set the display settings
// --------------------------------------------------------------------------
bool ApplicationModule_NoGfx::SetDisplaySettings(DisplaySettings &settings)
{
  DisplaySettings defaultSettings;
  defaultSettings.IsNull = true;
  settings = defaultSettings;

  return true;
}


// --------------------------------------------------------------------------
// Reset the device
// --------------------------------------------------------------------------
bool ApplicationModule_NoGfx::ResetDisplay(bool toggleFullScreen, bool isFullScreen)
{
  return true;
} // ResetDisplay


// --------------------------------------------------------------------------
// Initialise the module
// --------------------------------------------------------------------------
bool ApplicationModule_NoGfx::Init()
{
  return true;
} // Init


// --------------------------------------------------------------------------
// Shutdown the module
// --------------------------------------------------------------------------
void ApplicationModule_NoGfx::Shutdown()
{
} // Shutdown


// --------------------------------------------------------------------------
// Run the app process
// --------------------------------------------------------------------------
void ApplicationModule_NoGfx::App()
{
} // App


// --------------------------------------------------------------------------
// Run the cull process
// --------------------------------------------------------------------------
void ApplicationModule_NoGfx::Cull()
{
} // Cull


// --------------------------------------------------------------------------
// Run the draw process
// --------------------------------------------------------------------------
void ApplicationModule_NoGfx::Draw()
{
} // Draw


// --------------------------------------------------------------------------
// Called when the application windpw is resized
// --------------------------------------------------------------------------
void ApplicationModule_NoGfx::Resize()
{
} // Resize


// --------------------------------------------------------------------------
// Set the render state
// --------------------------------------------------------------------------
void ApplicationModule_NoGfx::SetRenderState()
{
} // SetRenderState


// -- EOF
