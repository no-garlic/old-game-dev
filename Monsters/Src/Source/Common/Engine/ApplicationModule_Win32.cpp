// ----------------------------------------------------------------------------
// File: ApplicationModule_Win32.cpp
// Desc: The Win32 direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/ApplicationModule_Win32.h"
#include "Engine/ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Windows proc callback
// ----------------------------------------------------------------------------
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::ApplicationModule_Win32
// Desc: Constructor
// ----------------------------------------------------------------------------
ApplicationModule_Win32::ApplicationModule_Win32()
: ApplicationModule()
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


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Win32::Create
// Desc: Set the module's display
// Retn: bool                   - true if the application was initialised
// ----------------------------------------------------------------------------
bool ApplicationModule_Win32::Create()
{
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
  wc.lpszClassName    = m_DisplaySettings.WindowClassName.c_str();

  // Register the window class
  if (RegisterClass(&wc) == 0)
    return false;

  // Create the window
  HWND hWnd = NULL;
  
  // Create the window based on the fullscreen setting
  if (m_DisplaySettings.StartFullScreen)
  {
    hWnd = CreateWindow(m_DisplaySettings.WindowClassName.c_str(), m_DisplaySettings.InitialWindowCaption.c_str(), 
      m_DisplaySettings.FullScreenStyle, 0, 0, m_DisplaySettings.FullScreenParams.BackBufferWidth, 
      m_DisplaySettings.FullScreenParams.BackBufferHeight, NULL, NULL, wc.hInstance, this);
  } // if
  else
  {
    hWnd = CreateWindow(m_DisplaySettings.WindowClassName.c_str(), m_DisplaySettings.InitialWindowCaption.c_str(), 
      m_DisplaySettings.WindowStyle, m_DisplaySettings.InitialWindowPosition.x, m_DisplaySettings.InitialWindowPosition.y, 
      m_DisplaySettings.InitialWindowSize.cx, m_DisplaySettings.InitialWindowSize.cy, NULL, NULL, wc.hInstance, this);
  } // else

  // Make sure the window was created
  if (!hWnd)
    return false;

  // Create the application
  if (!ApplicationCentral.Init(hWnd, this))
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
    run = ApplicationCentral.RunFrame();

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
        ApplicationCentral.RequestExit(0);
        PostQuitMessage(0);
        break;
      }
    }  // while
  } // while

  return ApplicationCentral.GetExitCode();
} // Run


// --------------------------------------------------------------------------
// Reset the device
// --------------------------------------------------------------------------
bool ApplicationModule_Win32::ResetDisplay(bool toggleFullScreen, bool isFullScreen)
{
  // Get the window
  HWND hWnd = ApplicationCentral.GetHWND();

  // Release our device objects if we have already
  // created them
  if (m_DeviceObjectsCreated && !ReleaseDeviceObjects())
    return false;

  // Set the device objects as released
  m_DeviceObjectsCreated = false;

  // Check if we are changing exclusive mode
  if (toggleFullScreen)
  {
    // Change the window style
    if (isFullScreen)
    {
      // Get the window rect
      RECT windowRect;
      GetWindowRect(hWnd, &windowRect);
      m_DisplaySettings.PreviousWindowPosition.x = windowRect.left;
      m_DisplaySettings.PreviousWindowPosition.y = windowRect.top;
      m_DisplaySettings.PreviousWindowSize.cx    = windowRect.right - windowRect.left;
      m_DisplaySettings.PreviousWindowSize.cy    = windowRect.bottom - windowRect.top;

      // Get the client rect
      RECT clientRect;
      GetClientRect(hWnd, &clientRect);
      m_DisplaySettings.PreviousClientPosition.x = clientRect.left;
      m_DisplaySettings.PreviousClientPosition.y = clientRect.top;
      m_DisplaySettings.PreviousClientSize.cx    = clientRect.right - clientRect.left;
      m_DisplaySettings.PreviousClientSize.cy    = clientRect.bottom - clientRect.top;

      // Set the new window params
      SetMenu(hWnd, NULL);
      SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | m_DisplaySettings.FullScreenStyle);
      SetWindowPos(hWnd, NULL, 0, 0, m_DisplaySettings.FullScreenParams.BackBufferWidth, 
        m_DisplaySettings.FullScreenParams.BackBufferHeight, SWP_NOZORDER);
    } // if
    else
    {
      // Set the new window params
      SetWindowLong(hWnd, GWL_STYLE, m_DisplaySettings.WindowStyle);

      // Windows has a problem with restoring a window from fullscreen to window mode
      // if the extents of the window are a fullscreen resulution (like 800x600). So first
      // we restore the window to 1 pixel bigger then we need so windows can change the
      // mode correctly, then we restore the actual right size.
      SetWindowPos(hWnd, HWND_NOTOPMOST, m_DisplaySettings.PreviousWindowPosition.x, m_DisplaySettings.PreviousWindowPosition.y, 
        1 + m_DisplaySettings.PreviousWindowSize.cx, 1 + m_DisplaySettings.PreviousWindowSize.cy, SWP_NOACTIVATE | SWP_SHOWWINDOW);
      SetWindowPos(hWnd, HWND_NOTOPMOST, m_DisplaySettings.PreviousWindowPosition.x, m_DisplaySettings.PreviousWindowPosition.y, 
        m_DisplaySettings.PreviousWindowSize.cx, m_DisplaySettings.PreviousWindowSize.cy, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    } // else
  } // if

  // Reset the device
  HRESULT hr = S_FALSE;
  if (isFullScreen)
  {
    hr = m_pDevice->Reset(&m_DisplaySettings.FullScreenParams);
  } // if
  else
  {
    // Set the back buffer to the previous client size
    m_DisplaySettings.WindowParams.BackBufferWidth  = m_DisplaySettings.PreviousClientSize.cx;
    m_DisplaySettings.WindowParams.BackBufferHeight = m_DisplaySettings.PreviousClientSize.cy;

    // Reset the device
    hr = m_pDevice->Reset(&m_DisplaySettings.WindowParams);

    // Get the window rect
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);
    m_DisplaySettings.PreviousWindowPosition.x = windowRect.left;
    m_DisplaySettings.PreviousWindowPosition.y = windowRect.top;
    m_DisplaySettings.PreviousWindowSize.cx    = windowRect.right - windowRect.left;
    m_DisplaySettings.PreviousWindowSize.cy    = windowRect.bottom - windowRect.top;
  } // else

  if (hr == D3DERR_DEVICELOST)
  { LOG_ERROR << "Reset Failed: D3DERR_DEVICELOST" << ENDLOG; }
  else if (hr == D3DERR_DRIVERINTERNALERROR)
  { LOG_ERROR << "Reset Failed: D3DERR_DRIVERINTERNALERROR" << ENDLOG; }
  else if (hr == D3DERR_OUTOFVIDEOMEMORY)
  { LOG_ERROR << "Reset Failed: D3DERR_OUTOFVIDEOMEMORY" << ENDLOG; }
  else
  { LOG_ERROR << "Reset Failed: " << ConvertDxErrorToString(hr) << ENDLOG; }

  // Check that the reset worked
  if (hr != D3D_OK)
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
    ApplicationCentral.RequestExit(0);
    PostQuitMessage(0);
  } // if
  else
  {
    // Obtain the correct destination for this message
    ApplicationModule_Win32 *app = (ApplicationModule_Win32 *) (LONGLONG)GetWindowLong(hWnd, GWL_USERDATA);
    if (app)
      return app->DisplayWndProc(hWnd, Message, wParam, lParam);
  } // else if

  // No destination found, defer to system...
  return DefWindowProc(hWnd, Message, wParam, lParam);
} // StaticWndProc


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::DisplayWndProc
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
      ApplicationCentral.RequestExit(0);
      PostQuitMessage(0);
      return 0;
    } // case WM_CLOSE

    case WM_DESTROY:
    {
      ApplicationCentral.RequestExit(0);
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
        ApplicationCentral.Pause();
        return 0;
      } // if
      else
      {
        ApplicationCentral.Resume();
        ApplicationCentral.ResizeDisplay();
        return 0;
      } // else
    } // case WM_SIZE

    case WM_KEYDOWN:
    {
      if (wParam == VK_RETURN && GetKeyState(VK_SHIFT) & 0xFF00)
        ApplicationCentral.ToggleFullScreen();
      return 0;
    } // case WM_KEYDOWN

  } // switch

  return DefWindowProc(hWnd, Message, wParam, lParam);
} // DisplayWndProc


// -- EOF



