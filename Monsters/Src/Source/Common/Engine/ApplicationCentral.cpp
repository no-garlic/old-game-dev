// ----------------------------------------------------------------------------
// File: Application.cpp
// Desc: The central system for the D3D application, all other systems branch 
//       out from this singleton.
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Static initialisers
// ----------------------------------------------------------------------------
Application *Application::s_pInstance = NULL;
unsigned int Application::APP_ID         = 0;
unsigned int Application::CULL_ID        = 0;
unsigned int Application::DRAW_ID        = 0;


// ----------------------------------------------------------------------------
// Name: Application::Application
// Desc: Constructor
// ----------------------------------------------------------------------------
Application::Application()
: m_pDirect3D                 (NULL),
  m_pDevice                   (NULL),
  m_pModule                   (NULL),
  m_Initialised               (false),
  m_Destructed                (false),
  m_Paused                    (false),
  m_RequestExit               (false),
  m_RequestExitNextFrame      (false),
  m_ResetDeviceNextFrame      (false),
  m_ToggleFullScreenNextFrame (false),
  m_IsFullScreen              (false),
  m_DeviceLost                (false),
  m_ExitCode                  (0),
  m_CullThread                (0),
  m_DrawThread                (0),
  m_FrameTime                 (0.0f),
  m_RunTime                   (0.0f),
  m_FrameRate                 (0),
  m_FrameCount                (0),
  m_IntervalFrames            (0),
  m_IntervalTime              (0.0f),
  m_GlobalAmbient             (0.1f, 0.1f, 0.1f, 1.0f)
{
  REF_COUNT_CTOR(ApplicationCentral);

  m_StartEvents[0] = NULL;
  m_StartEvents[1] = NULL;
  m_EndEvents[0]   = NULL;
  m_EndEvents[1]   = NULL;
} // Application


// ----------------------------------------------------------------------------
// Name: Application::~Application
// Desc: Destructor
// ----------------------------------------------------------------------------
Application::~Application()
{
  REF_COUNT_DTOR(ApplicationCentral);

  if (!m_Destructed)
    DestructResources();
} // ~Application


// ----------------------------------------------------------------------------
// Name: Application::GetInstance
// Desc: Get the singelton instance
// Retn: Application & - the instance
// ----------------------------------------------------------------------------
Application &Application::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new Application();
    atexit(&Application::DestroyInstance);
  } // if

  return *s_pInstance;
} // GetInstance


// ----------------------------------------------------------------------------
// Name: Application::DestroyInstance
// Desc: Destroy the singleton instance
// ----------------------------------------------------------------------------
void Application::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
} // DestroyInstance


// ----------------------------------------------------------------------------
// Name: Application::InitDisplay
// Desc: Initialise the display for the given window
// Parm: HWND hWnd  - the window
// Retn: bool       - true if intialised sucessfully
// ----------------------------------------------------------------------------
bool Application::Init(HWND hWnd, ApplicationModule *pModule)
{
  if (m_Initialised)
    return false;

  // Set the member variables
  m_hWnd            = hWnd;
  m_pModule         = pModule;
  m_ProcessMode     = MemoryManager.GetNumProcesses();

  // Get the display settings from the module
  DisplaySettings &ds = pModule->m_DisplaySettings;

  // Create the directx device
  m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
  if (!m_pDirect3D)
    return false;

  // Create the d3d9 device
  HRESULT hr = S_FALSE;
  if (ds.StartFullScreen)
  {
    hr = m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
      D3DCREATE_HARDWARE_VERTEXPROCESSING, &ds.FullScreenParams, &m_pDevice);

    m_IsFullScreen = true;
  } // if
  else
  {
    hr = m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
      D3DCREATE_HARDWARE_VERTEXPROCESSING, &ds.WindowParams, &m_pDevice);

    m_IsFullScreen = false;
  } // else

  // Check that the device is ok
  if (FAILED(hr))
    return false;

  // Show the window
  ShowWindow(m_hWnd, SW_SHOW);

  // Get the window rect
  RECT windowRect;
  GetWindowRect(m_hWnd, &windowRect);
  ds.PreviousWindowPosition.x = windowRect.left;
  ds.PreviousWindowPosition.y = windowRect.top;
  ds.PreviousWindowSize.cx    = windowRect.right - windowRect.left;
  ds.PreviousWindowSize.cy    = windowRect.bottom - windowRect.top;

  // Get the client rect
  RECT clientRect;
  GetClientRect(m_hWnd, &clientRect);
  ds.PreviousClientPosition.x = clientRect.left;
  ds.PreviousClientPosition.y = clientRect.top;
  ds.PreviousClientSize.cx    = clientRect.right - clientRect.left;
  ds.PreviousClientSize.cy    = clientRect.bottom - clientRect.top;

  // Set the module's device
  m_pModule->m_pDevice = m_pDevice;

  // Set the data flux indexes
  Application::APP_ID  = 0;
  Application::CULL_ID = 0;
  Application::DRAW_ID = 0;

  // Do we have a seperate draw thread
  if (m_ProcessMode > 1)
  {
    // Create the start event
    if (!(m_StartEvents[1] = CreateEventA(0, TRUE, FALSE, "DrawStartEvent")))
      return false;

    // Create the end event
    if (!(m_EndEvents[1] = CreateEventA(0, TRUE, FALSE, "DrawEndEvent")))
      return false;

    // Create the thread
    unsigned long discard;
    if (!(m_DrawThread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DrawThreadFunc), this, 0, &discard)))
      return false;

    // Set the draw data flux index
    Application::DRAW_ID = 1;
  } // if

  // If the processing mode has a seperate CULL thread then create the
  // required events and thread.
  if (m_ProcessMode > 2)
  {
    // Create the start event
    if (!(m_StartEvents[0] = CreateEventA(0, TRUE, FALSE, "CullStartEvent")))
      return false;

    // Create the end event
    if (!(m_EndEvents[0] = CreateEventA(0, TRUE, FALSE, "CullEndEvent")))
      return false;

    // Create the thread
    unsigned long discard;
    if (!(m_CullThread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(CullThreadFunc), this, 0, &discard)))
      return false;

    // Set the cull and draw data flux indices
    Application::CULL_ID = 1;
    Application::DRAW_ID = 2;
  } // if

  // Initialise the module
  if (!m_pModule->Init())
    return false;

  // Create the safe objects
  if (!m_pModule->CreateSafeObjects())
    return false;

  // Initialise the input
  if (!m_Input.Init())
    return false;

  // Start the timer
  m_Timer.Reset();
  m_Timer.Start();

  // Done
  m_Initialised = true;
  return true;
} // Init


// ----------------------------------------------------------------------------
// Name: Application::ResizeDisplay
// Desc: Resize the back buffer because the window has been resized
// Retn: bool - true if the resize suceeded
// ----------------------------------------------------------------------------
void Application::ResizeDisplay()
{
  m_ResetDeviceNextFrame = true;
} // ReesizeDisplay


// ----------------------------------------------------------------------------
// Name: Application::ToggleFullScreen
// Desc: Toggle between fullscreen and a window
// ----------------------------------------------------------------------------
void Application::ToggleFullScreen()
{
  m_ResetDeviceNextFrame      = true;
  m_ToggleFullScreenNextFrame = true;
} // ToggleFullScreen


// ----------------------------------------------------------------------------
// Name: Application::ResetDevice
// Desc: Reset the device
// ----------------------------------------------------------------------------
bool Application::ResetDevice()
{
  if (!m_Initialised)
    return false;

  if (m_RequestExit || m_RequestExitNextFrame)
    return true;

  if (m_ResetDeviceNextFrame)
  {
    // Store the toggle fullscreen flag
    bool toggleFullscreen = m_ToggleFullScreenNextFrame;

    // Reset the flags so we dont keep doing this 
    // if we return from this function early
    m_ResetDeviceNextFrame      = false;
    m_ToggleFullScreenNextFrame = false;

    // Toggle the fullscreen mode
    if (toggleFullscreen)
      m_IsFullScreen = !m_IsFullScreen;

    // Reset the display
    return m_pModule->ResetDisplay(toggleFullscreen, m_IsFullScreen);
  } // if

  return false;
} // ResetDevice


// ----------------------------------------------------------------------------
// Name: Application::RotateMemory
// Desc: Rotate the memory in the memory manager and change the data flux 
//       indexes
// ----------------------------------------------------------------------------
void Application::RotateMemory()
{
  switch (m_ProcessMode)
  {
    // Single mode, all processes are sequentional and share
    // the same memory so no need to copy anything or change 
    // the indexes (as they are all 0).
    case PMODE_ONE:
    {
      break;      
    } // case PMODE_ONE

    // Two processes - (App + Cull) and (Draw).
    case PMODE_TWO:
    {
      // Rotate the indexes
      Application::APP_ID  = (Application::APP_ID + 1) % 2;
      Application::CULL_ID =  Application::APP_ID;
      Application::DRAW_ID = (Application::APP_ID + 1) % 2;

      // Copy the old app memory into the new app memory.
      MemoryManager.Swap(Application::DRAW_ID, Application::APP_ID);

      break;      
    } // case PMODE_TWO

    // Three processes - (App), (Cull), and (Draw).
    case PMODE_THREE:
    {
      // Get the current indexes
      unsigned int oldAppId  = Application::APP_ID;
      unsigned int oldCullId = Application::APP_ID;
      unsigned int oldDrawId = Application::APP_ID;

      // Remap the indexes
      Application::APP_ID  = oldDrawId;
      Application::CULL_ID = oldAppId;
      Application::DRAW_ID = oldCullId;

      // Copy the old app memory into the new app memory.
      MemoryManager.Swap(oldAppId, Application::APP_ID);

      break;      
    } // case PMODE_THREE

  } // switch
} // RotateMemory


// ----------------------------------------------------------------------------
// Name: Application::Run
// Desc: Run the application module given in the specified processing mode
// Retn: bool - false means that we want to exit
// ----------------------------------------------------------------------------
bool Application::RunFrame()
{
  // Check that we are initialised
  if (!m_Initialised)
    return false;

  // Read the input devices
  if (!m_Input.ReadData())
    return false;

  // Assign the request exit flag now
  m_RequestExit = m_RequestExitNextFrame;

  // If we are exiting, thens stop the threads
  if (m_RequestExit)
  {
    DestructResources();
    return false;
  } // if

  // Recover a lost device
  if (m_DeviceLost)
  {
    if (m_pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
    {
      if (!ResetDevice())
        return false;

      m_DeviceLost = false;
    } // if
    else
      return true;
  } // if

  // Reset the device if we need to
  if (m_ResetDeviceNextFrame)
  {
    if (!ResetDevice())
      return false;
  } // if

  // Calculate the timing variables
  m_RunTime = m_Timer.GetTime(&m_FrameTime);

  // Accumulate frames and time to calculate the frame rate
  m_IntervalFrames++;
  m_IntervalTime += m_FrameTime;

  // Calculate the frame rate each second
  if (m_IntervalTime > 1.0f)
  {
    m_FrameRate = static_cast<unsigned int>(static_cast<float>(m_IntervalFrames) / m_IntervalTime);

    m_IntervalFrames = 0;
    m_IntervalTime   = 0.0f;
  } // if

  // Choose the most appropriate mode to execute
  switch (m_ProcessMode)
  {
    case PMODE_ONE:   RunOneProcess();    break;
    case PMODE_TWO:   RunTwoProcess();    break;
    case PMODE_THREE: RunThreeProcess();  break;
  }; // switch

  // Increment the frame count
  m_FrameCount++;

  // Check for a lost device
  if (m_pDevice->TestCooperativeLevel() == D3DERR_DEVICELOST)
    SetDeviceLost();

  // Return true if we want to continue
  return !m_RequestExit;
} // Run


// ----------------------------------------------------------------------------
// Name: Application::DestructResources
// Desc: Destruct the allocated resources
// ----------------------------------------------------------------------------
void Application::DestructResources()
{
  if (!m_Destructed)
  {
    // We are now in the destructed state
    m_Destructed = true;

    // Stop the draw thread
    if (m_ProcessMode > 1)
    {
      // Terminate the draw thread - first setting an event so it should shutdown
      // cleanly, but if that fails then just terminate it.
      SetEvent(m_StartEvents[1]);
      if (WaitForSingleObject(m_DrawThread, 500) == WAIT_OBJECT_0)
        CloseHandle(m_DrawThread);
      else
        TerminateThread(m_DrawThread, 0);
    } // if

    // Stop the cull thread
    if (m_ProcessMode > 2)
    {
      // Terminate the cull thread - first setting an event so it should shutdown
      // cleanly, but if that fails then just terminate it.
      SetEvent(m_StartEvents[0]);
      if (WaitForSingleObject(m_CullThread, 500) == WAIT_OBJECT_0)
        CloseHandle(m_CullThread);
      else
        TerminateThread(m_CullThread, 0);
    } // if

    // Shutdown the module
    if (m_pModule)
    {
      m_pModule->ReleaseDeviceObjects();
      m_pModule->ReleaseSafeObjects();
      m_pModule->Shutdown();

      // Delete the module
      delete m_pModule;
    } // if

    // Shutdown the input
    m_Input.Shutdown();
  } // if
} // DestructResources


// ----------------------------------------------------------------------------
// Name: Application::RunOneProcess
// Desc: Run the module using a single process
// Retn: int - the application return code
// ----------------------------------------------------------------------------
void Application::RunOneProcess()
{
  // Sequentially run the App, Cull, and Draw processes
  m_pModule->App();
  m_pModule->Cull();
  m_pModule->Draw();
} // RunOneProcess


// ----------------------------------------------------------------------------
// Name: Application::RunTwoProcess
// Desc: Run the module using 2 processes
// Retn: int - the application return code
// ----------------------------------------------------------------------------
void Application::RunTwoProcess()
{
  // Start the draw thread
  SetEvent(m_StartEvents[1]);

  // Run the App and Cull processes
  m_pModule->App();
  m_pModule->Cull();

  // Wait uintil the draw thread is finished it's loop
  WaitForSingleObject(m_EndEvents[1], INFINITE);

  // Reset the end event
  ResetEvent(m_EndEvents[1]);

  // Rotate the memory before the next loop
  RotateMemory();
} // RunTwoProcess


// ----------------------------------------------------------------------------
// Name: Application::RunThreeProcess
// Desc: Run the module using 3 processes
// Retn: int - the application return code
// ----------------------------------------------------------------------------
void Application::RunThreeProcess()
{
  // Start the cull and draw threads
  SetEvent(m_StartEvents[0]);
  SetEvent(m_StartEvents[1]);

  // Run the App process
  m_pModule->App();

  // Wait for the cull and draw threads to finish their loops
  WaitForMultipleObjects(2, m_EndEvents, TRUE, INFINITE);

  // Reset the end events
  ResetEvent(m_EndEvents[0]);
  ResetEvent(m_EndEvents[1]);

  // Rotate the memory before the next loop
  RotateMemory();
} // RunThreeProcess


// ----------------------------------------------------------------------------
// Name: CullThreadFunc
// Desc: Run the cull thread
// Parm: LPVOID ptr    - the Application instance
// Retn: unsigned long - the thread return code
// ----------------------------------------------------------------------------
unsigned long CullThreadFunc(LPVOID ptr)
{
  // Get the application central and the application module
  Application *app = static_cast<Application *>(ptr);
  ApplicationModule  *mod = app->m_pModule;

  // Keep looping until we are asked to exit
  while (!app->m_RequestExit)
  {
    // Wait for the start event
    if (::WaitForSingleObject(app->m_StartEvents[0], INFINITE) == WAIT_FAILED)
    {
      assert(false);
      return -1; 
    } // if

    // Reset the start event
    ResetEvent(app->m_StartEvents[0]);

    // See if the event was to terminate
    if (app->m_RequestExit)
      return 0;

    // Run the Process
    mod->Cull();

    // Set the done event
    if (::SetEvent(app->m_EndEvents[0]) == FALSE)
    {
      assert(false);
      return -1; 
    } // if
  } // while

  return 0;
} // CullThreadFunc


// ----------------------------------------------------------------------------
// Name: DrawThreadFunc
// Desc: Run the draw thread
// Parm: LPVOID ptr    - the Application instance
// Retn: unsigned long - the thread return code
// ----------------------------------------------------------------------------
unsigned long DrawThreadFunc(LPVOID ptr)
{
  // Get the application central and the application module
  Application *app = static_cast<Application *>(ptr);
  ApplicationModule  *mod = app->m_pModule;

  // Keep looping until we are asked to exit
  while (!app->m_RequestExit)
  {
    // Wait for the start event
    if (::WaitForSingleObject(app->m_StartEvents[1], INFINITE) == WAIT_FAILED)
    {
      assert(false);
      return -1; 
    } // if

    // Reset the start event
    ResetEvent(app->m_StartEvents[1]);

    // See if the event was to terminate
    if (app->m_RequestExit)
      return 0;

    // Run the Process
    mod->Draw();

    // Set the done event
    if (::SetEvent(app->m_EndEvents[1]) == FALSE)
    {
      assert(false);
      return -1; 
    } // if
  } // while

  return 0;
} // DrawThreadFunc


// -- EOF

