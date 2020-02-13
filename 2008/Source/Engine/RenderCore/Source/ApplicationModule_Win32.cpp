// ----------------------------------------------------------------------------
// File: ApplicationModule_Win32.cpp
// Desc: The Win32 direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "ApplicationModule_Win32.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Windows proc callback
// ----------------------------------------------------------------------------
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::ApplicationModule_Win32
// Desc: Constructor
// ----------------------------------------------------------------------------
ApplicationModule_Win32::ApplicationModule_Win32(const String &name)
: ApplicationModule(name)
{
  REF_COUNT_CTOR(ApplicationModule_Win32);
} // ApplicationModule_Win32


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::~ApplicationModule_Win32
// Desc: destructor
// ----------------------------------------------------------------------------
ApplicationModule_Win32::~ApplicationModule_Win32()
{
  REF_COUNT_DTOR(ApplicationModule_Win32);
} // ~ApplicationModule_Win32


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::SetWindowTitle
// Desc: Sets the window title
// Parm: const String &str - the title
// ----------------------------------------------------------------------------
void ApplicationModule_Win32::SetWindowTitle(const String &str)
{
  ::SetWindowText(Application.GetHWND(), str.c_str());
} // SetWindowTitle


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::Main
// Desc: The startup function for the module
// Parm: HINSTANCE hInstance      - the app instance
// Parm: HINSTANCE hPrevInstance  - the prev instance
// Parm: LPTSTR lpCmdLine         - the command line
// Parm: int iCmdShow             - the show mode
// Retn: int                      - the app return value
// ----------------------------------------------------------------------------
int ApplicationModule_Win32::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
  // Initialise the engine
  if (!Create())
    return -1;

  // Run the engine
  return Run();
} // Main


// --------------------------------------------------------------------------
// Set the display settings
// --------------------------------------------------------------------------
bool ApplicationModule_Win32::SetDisplaySettings(DisplaySettings &settings)
{
  DisplaySettings defaultSettings;
  settings = defaultSettings;

  return true;
}


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::Create
// Desc: Set the module's display
// Retn: bool                   - true if the application was initialised
// ----------------------------------------------------------------------------
bool ApplicationModule_Win32::Create()
{
  // Get the display settings
  DisplaySettings ds;
  if (!SetDisplaySettings(ds))
    return false;

  // Build the window class
  WNDCLASS            wc;    
  wc.style            = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc      = StaticWndProc;
  wc.cbClsExtra       = 0;
  wc.cbWndExtra       = 0;
  wc.hInstance        = (HINSTANCE)GetModuleHandle(0);
  wc.hIcon            = 0;
  wc.hCursor          = LoadCursor(0, IDC_ARROW);
  wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName     = 0;
  wc.lpszClassName    = ds.WindowClassName.c_str();

  // Register the window class
  if (RegisterClass(&wc) == 0)
    return false;

  // Create the window
  HWND hWnd = NULL;
  
  // Create the window based on the fullscreen setting
  if (ds.StartFullScreen)
  {
    hWnd = CreateWindow(ds.WindowClassName.c_str(), ds.InitialWindowCaption.c_str(), 
      ds.FullScreenStyle, 0, 0, ds.FullScreenParams.BackBufferWidth, 
      ds.FullScreenParams.BackBufferHeight, NULL, NULL, wc.hInstance, this);
  } // if
  else
  {
    hWnd = CreateWindow(ds.WindowClassName.c_str(), ds.InitialWindowCaption.c_str(), 
      ds.WindowStyle, ds.InitialWindowPosition.x, ds.InitialWindowPosition.y, 
      ds.InitialWindowSize.cx, ds.InitialWindowSize.cy, NULL, NULL, wc.hInstance, this);
  } // else

  // Make sure the window was created
  if (!hWnd)
    return false;

  // Create the application
  if (!Application.Init(hWnd, this))
    return false;

  // Show the window
  ShowWindow(hWnd, SW_SHOW);
  return true;
} // Create


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::Run
// Desc: Run the module
// Retn: int - the application return code
// ----------------------------------------------------------------------------
int ApplicationModule_Win32::Run()
{
  bool run = true;
  while (run)
  {
    run = Application.RunFrame();

    MSG msg;
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
      if (msg.message != WM_QUIT)
      {
        // Process the message
        TranslateMessage(&msg);
        DispatchMessage (&msg);
      } // if
      else
      {
        Application.RequestExit(0);
        PostQuitMessage(0);
        break;
      }
    }  // while
  } // while

  return Application.GetExitCode();
} // Run


// --------------------------------------------------------------------------
// Reset the device
// --------------------------------------------------------------------------
bool ApplicationModule_Win32::ResetDisplay(bool toggleFullScreen, bool isFullScreen)
{
  // Get the window
  HWND hWnd = Application.GetHWND();

  // Get the display settings
  DisplaySettings ds;
  if (!SetDisplaySettings(ds))
    return false;

  // Check if we are changing exclusive mode
  if (toggleFullScreen)
  {
    // Change the window style
    if (isFullScreen)
    {
      // Get the window rect
      RECT windowRect;
      GetWindowRect(hWnd, &windowRect);
      ds.PreviousWindowPosition.x = windowRect.left;
      ds.PreviousWindowPosition.y = windowRect.top;
      ds.PreviousWindowSize.cx    = windowRect.right - windowRect.left;
      ds.PreviousWindowSize.cy    = windowRect.bottom - windowRect.top;

      // Get the client rect
      RECT clientRect;
      GetClientRect(hWnd, &clientRect);
      ds.PreviousClientPosition.x = clientRect.left;
      ds.PreviousClientPosition.y = clientRect.top;
      ds.PreviousClientSize.cx    = clientRect.right - clientRect.left;
      ds.PreviousClientSize.cy    = clientRect.bottom - clientRect.top;

      // Set the new window params
      SetMenu(hWnd, NULL);
      SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | ds.FullScreenStyle);
      SetWindowPos(hWnd, NULL, 0, 0, ds.FullScreenParams.BackBufferWidth, 
        ds.FullScreenParams.BackBufferHeight, SWP_NOZORDER);
    } // if
    else
    {
      // Set the new window params
      SetWindowLong(hWnd, GWL_STYLE, ds.WindowStyle);

      // Windows has a problem with restoring a window from fullscreen to window mode
      // if the extents of the window are a fullscreen resulution (like 800x600). So first
      // we restore the window to 1 pixel bigger then we need so windows can change the
      // mode correctly, then we restore the actual right size.
      SetWindowPos(hWnd, HWND_NOTOPMOST, ds.PreviousWindowPosition.x, ds.PreviousWindowPosition.y, 
        1 + ds.PreviousWindowSize.cx, 1 + ds.PreviousWindowSize.cy, SWP_NOACTIVATE | SWP_SHOWWINDOW);
      SetWindowPos(hWnd, HWND_NOTOPMOST, ds.PreviousWindowPosition.x, ds.PreviousWindowPosition.y, 
        ds.PreviousWindowSize.cx, ds.PreviousWindowSize.cy, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    } // else
  } // if

  // Reset the device
  HRESULT hr = S_FALSE;
  if (isFullScreen)
  {
    hr = m_pDevice->Reset(&ds.FullScreenParams);
  } // if
  else
  {
    // Get the window rect
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);
    ds.PreviousWindowPosition.x = windowRect.left;
    ds.PreviousWindowPosition.y = windowRect.top;
    ds.PreviousWindowSize.cx    = windowRect.right - windowRect.left;
    ds.PreviousWindowSize.cy    = windowRect.bottom - windowRect.top;

    // Get the client rect
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    ds.PreviousClientPosition.x = clientRect.left;
    ds.PreviousClientPosition.y = clientRect.top;
    ds.PreviousClientSize.cx    = clientRect.right - clientRect.left;
    ds.PreviousClientSize.cy    = clientRect.bottom - clientRect.top;

    // Set the back buffer to the client size
    ds.WindowParams.BackBufferWidth  = ds.PreviousClientSize.cx;
    ds.WindowParams.BackBufferHeight = ds.PreviousClientSize.cy;

    // Reset the device
    hr = m_pDevice->Reset(&ds.WindowParams);
  } // else

  if (FAILED(hr))
  {
    if (hr == D3DERR_DEVICELOST)
    { LOG_ERROR << "Reset Failed: D3DERR_DEVICELOST" << ENDLOG; }
    else if (hr == D3DERR_DRIVERINTERNALERROR)
    { LOG_ERROR << "Reset Failed: D3DERR_DRIVERINTERNALERROR" << ENDLOG; }
    else if (hr == D3DERR_OUTOFVIDEOMEMORY)
    { LOG_ERROR << "Reset Failed: D3DERR_OUTOFVIDEOMEMORY" << ENDLOG; }
    else
    { LOG_ERROR << "Reset Failed: " << ConvertDxErrorToString(hr) << ENDLOG; }

    return false;
  } // if

  // Tell the module that the window size has changed
  Resize();

  return true;
} // ResetDisplay


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::StaticWndProc
// Desc: The static windows procedure that is called from the message pump
// Parm: HWND hWnd     - the window
// Parm: UINT Message  - the message
// Parm: WPARAM wParam - the first parameter
// Parm: LPARAM lParam - the second parameter
// Retn: LRESULT       - the result
// ----------------------------------------------------------------------------
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
  // If this is a create message, trap the 'this' pointer 
  // passed in and store it within the window.
  if (Message == WM_CREATE) 
    SetWindowLong(hWnd, GWL_USERDATA, (LONG)(LONGLONG)((CREATESTRUCT FAR *) lParam)->lpCreateParams);

  if (Message == WM_QUIT || Message == WM_CLOSE)
  {
    SetWindowLong(hWnd, GWL_USERDATA, NULL);
    Application.RequestExit(0);
    PostQuitMessage(0);
  } // if
  else
  {
    // Obtain the correct destination for this message
    if (Application.GetHWND())
    {
      ApplicationModule_Win32 *app = (ApplicationModule_Win32 *) (LONGLONG)GetWindowLong(hWnd, GWL_USERDATA);
      if (app)
        return app->DisplayWndProc(hWnd, Message, wParam, lParam);
    } // if
  } // else if

  // No destination found, defer to system...
  return DefWindowProc(hWnd, Message, wParam, lParam);
} // StaticWndProc


// ----------------------------------------------------------------------------
// Name: DisplayWndProc
// Desc: The windows procedure that is called as a member function
// Parm: HWND hWnd     - the window
// Parm: UINT Message  - the message
// Parm: WPARAM wParam - the first parameter
// Parm: LPARAM lParam - the second parameter
// Retn: LRESULT       - the result
// ----------------------------------------------------------------------------
LRESULT ApplicationModule_Win32::DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
  // Check any message types we care about
  switch (Message)
  {
    // Trap clicking on the [X] titlebar button
    case WM_CLOSE:
    {
      Application.RequestExit(0);
      PostQuitMessage(0);
      return 0;
    } // case WM_CLOSE

    case WM_DESTROY:
    {
      Application.RequestExit(0);
      PostQuitMessage(0);
      return 0;
    } // case WM_DESTROY

     case WM_PAINT:
     {
       ValidateRect(hWnd, NULL);
       return 0;
     } // case WM_PAINT

    case WM_SIZE:
    {
      if (wParam == SIZE_MINIMIZED)
      {
        Application.Pause();
        return 0;
      } // if
      else
      {
        Application.Resume();
        Application.ResizeDisplay();
        return 0;
      } // else
    } // case WM_SIZE

    case WM_KEYDOWN:
    {
      if (wParam == VK_RETURN && GetKeyState(VK_SHIFT) & 0xFF00)
        Application.ToggleFullScreen();
      return 0;
    } // case WM_KEYDOWN

  } // switch

  return DefWindowProc(hWnd, Message, wParam, lParam);
} // DisplayWndProc


// -- EOF



