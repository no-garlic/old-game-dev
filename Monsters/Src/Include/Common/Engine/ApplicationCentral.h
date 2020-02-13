// ----------------------------------------------------------------------------
// File: Application.h
// Desc: The central system for the D3D application, all other systems branch 
//       out from this singleton.
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __APPLICATION_CENTRAL_H_
#define __APPLICATION_CENTRAL_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Engine/MemoryManager.h"
#include "Engine/DisplaySettings.h"
#include "Engine/ApplicationModule.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/EngineTypes.h"


// ----------------------------------------------------------------------------
// Process Modes
// ----------------------------------------------------------------------------
#define PMODE_ONE         1 // App + Cull + Draw
#define PMODE_TWO         2 // App + Cull : Draw
#define PMODE_THREE       3 // App : Cull : Draw


// ----------------------------------------------------------------------------
// DataFlux index accessors
// ----------------------------------------------------------------------------
#define APP  Application::APP_ID
#define CULL Application::CULL_ID
#define DRAW Application::DRAW_ID


// ----------------------------------------------------------------------------
// Singelton accessor
// ----------------------------------------------------------------------------
#define ApplicationCentral Application::GetInstance()


// ----------------------------------------------------------------------------
// Name: Application (class)
// Desc: The central system for the D3D application, all other systems branch 
//       out from this singleton.
// ----------------------------------------------------------------------------
class Application
{
public:
  // --------------------------------------------------------------------------
  // Static singleton accessor
  // --------------------------------------------------------------------------
  static Application &GetInstance();
  static void DestroyInstance();

  // --------------------------------------------------------------------------
  // Public accessors for indexing data fluxes
  // --------------------------------------------------------------------------
  static unsigned int APP_ID;
  static unsigned int CULL_ID;
  static unsigned int DRAW_ID;

private:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Application();
  ~Application();

public:
  // --------------------------------------------------------------------------
  // Initialise the application
  // --------------------------------------------------------------------------
  bool Init(HWND hWnd, ApplicationModule *pModule);
  bool IsInitialised() const { return m_Initialised; }

  // --------------------------------------------------------------------------
  // Run one frame
  // --------------------------------------------------------------------------
  bool RunFrame();

  // --------------------------------------------------------------------------
  // Set the display settings
  // --------------------------------------------------------------------------
  void ResizeDisplay();
  void ToggleFullScreen();

  // --------------------------------------------------------------------------
  // Request to exit the application
  // --------------------------------------------------------------------------
  inline void SetDeviceLost();
  inline void RequestExit(int exitCode);
  inline int  GetExitCode() { return m_ExitCode; }

  // --------------------------------------------------------------------------
  // Get the devices
  // --------------------------------------------------------------------------
  inline LPDIRECT3DDEVICE9  GetDevice();
  inline LPDIRECT3D9        GetD3D();
  inline HWND               GetHWND();
  inline Input             &GetInput();
  inline Camera            &GetCamera();

  // --------------------------------------------------------------------------
  // Lights and fog
  // --------------------------------------------------------------------------
  inline Fog               &GetFog();
  inline Color             &GetGlobalAmbient();
  inline DirectionalLight  &GetDirectionalLight();
  inline OmniLight         &GetOmniLight0();
  inline OmniLight         &GetOmniLight1();
  inline OmniLight         &GetOmniLight2();
  inline OmniLight         &GetOmniLight3();

  // --------------------------------------------------------------------------
  // Pausing functions
  // --------------------------------------------------------------------------
  inline bool IsPaused();
  inline void Pause();
  inline void Resume();

  // --------------------------------------------------------------------------
  // Timing functions
  // --------------------------------------------------------------------------
  inline float GetRunningTime();
  inline float GetFrameTime();
  inline unsigned int GetFrameRate();
  inline uqword GetFrameCount();

private:
  // --------------------------------------------------------------------------
  // Private functions
  // --------------------------------------------------------------------------
  void RunOneProcess();
  void RunTwoProcess();
  void RunThreeProcess();

  // --------------------------------------------------------------------------
  // Thread functions
  // --------------------------------------------------------------------------
  friend unsigned long CullThreadFunc(void *ptr);
  friend unsigned long DrawThreadFunc(void *ptr);

  // --------------------------------------------------------------------------
  // Rotate the data flux memory and indexes
  // --------------------------------------------------------------------------
  void RotateMemory();

  // --------------------------------------------------------------------------
  // Reset the device
  // --------------------------------------------------------------------------
  bool ResetDevice();

  // --------------------------------------------------------------------------
  // Destruct the resources
  // --------------------------------------------------------------------------
  void DestructResources();

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  static Application   *s_pInstance;
  bool                  m_Initialised;
  bool                  m_Destructed;
  LPDIRECT3D9           m_pDirect3D;
  LPDIRECT3DDEVICE9     m_pDevice;
  bool                  m_ResetDeviceNextFrame;
  bool                  m_ToggleFullScreenNextFrame;
  bool                  m_IsFullScreen;
  bool                  m_DeviceLost;
  ApplicationModule    *m_pModule;
  HWND                  m_hWnd;
  Input                 m_Input;
  Camera                m_Camera;
  int                   m_ProcessMode;
  bool                  m_RequestExit;
  bool                  m_RequestExitNextFrame;
  int                   m_ExitCode;
  HANDLE                m_CullThread;
  HANDLE                m_DrawThread;
  HANDLE                m_StartEvents[2];
  HANDLE                m_EndEvents[2];
  Timer                 m_Timer;
  bool                  m_Paused;
  float                 m_FrameTime;
  float                 m_RunTime;
  uint                  m_FrameRate;
  uqword                m_FrameCount;
  uint                  m_IntervalFrames;
  float                 m_IntervalTime;
  Fog                   m_Fog;
  DirectionalLight      m_DirectionalLight;
  OmniLight             m_OmniLight0;
  OmniLight             m_OmniLight1;
  OmniLight             m_OmniLight2;
  OmniLight             m_OmniLight3;
  Color                 m_GlobalAmbient;

}; // class Application


// ----------------------------------------------------------------------------
// Name: Application::GetDevice
// Desc: Get the D3D Device
// Retn: LPDIRECT3DDEVICE9 - the device
// ----------------------------------------------------------------------------
inline LPDIRECT3DDEVICE9 Application::GetDevice()
{
  return m_pDevice;
} // GetDevice


// ----------------------------------------------------------------------------
// Name: Application::GetD3D
// Desc: Get the D3D pointer
// Retn: LPDIRECT3D9 - the D3D pointer
// ----------------------------------------------------------------------------
inline LPDIRECT3D9 Application::GetD3D()
{
  return m_pDirect3D;
} // GetD3D


// ----------------------------------------------------------------------------
// Name: Application::GetHWND
// Desc: Get the HWND we are using
// Retn: HWND - the HWND
// ----------------------------------------------------------------------------
inline HWND Application::GetHWND()
{
  return m_hWnd;
} // GetHWND


// ----------------------------------------------------------------------------
// Name: Application::GetInput
// Desc: Get the input device
// ----------------------------------------------------------------------------
inline Input &Application::GetInput()
{
  return m_Input;
} // GetInput


// ----------------------------------------------------------------------------
// Name: Application::GetCamera
// Desc: Get the camera
// ----------------------------------------------------------------------------
inline Camera &Application::GetCamera()
{
  return m_Camera;
} // GetCamera


// ----------------------------------------------------------------------------
// Name: Application::RequestExit
// Desc: Request the application to exit
// Parm: int exitCode - the exit code of the application
// ----------------------------------------------------------------------------
inline void Application::RequestExit(int exitCode)
{
  m_RequestExitNextFrame = true;
  m_ExitCode             = exitCode;
} // RequestExit


// ----------------------------------------------------------------------------
// Name: Application::Pause
// Desc: Pause the renderer
// ----------------------------------------------------------------------------
inline void Application::Pause()
{
  m_Paused = true;
} // Pause


// ----------------------------------------------------------------------------
// Name: Application::Resume
// Desc: Resume the renderer
// ----------------------------------------------------------------------------
inline void Application::Resume()
{
  m_Paused = false;
} // Resume


// ----------------------------------------------------------------------------
// Name: Application::IsPaused
// Desc: Is the application paused
// Retn: bool - true if paused, otherwise false
// ----------------------------------------------------------------------------
inline bool Application::IsPaused()
{
  return m_Paused;
} // IsPaused


// ----------------------------------------------------------------------------
// Name: Application::GetRunningTime
// Desc: Get the total time the engine has been running (excluding paused time)
// Retn: float - the time in seconds
// ----------------------------------------------------------------------------
inline float Application::GetRunningTime()
{
  return m_RunTime;
} // GetRunningTime


// ----------------------------------------------------------------------------
// Name: Application::GetFrameTime
// Desc: Get the time of the last frame
// Retn: float - the time in seconds
// ----------------------------------------------------------------------------
inline float Application::GetFrameTime()
{
  return m_FrameTime;
} // GetFrameTime


// ----------------------------------------------------------------------------
// Name: Application::GetFrameRate
// Desc: Get the frame rate
// Retn: unsigned int - the frame rate
// ----------------------------------------------------------------------------
inline unsigned int Application::GetFrameRate()
{
  return m_FrameRate;
} // GetFrameRate


// ----------------------------------------------------------------------------
// Name: Application::GetFrameCount
// Desc: Get the total number of rendered frames
// Retn: uqword - the frame count
// ----------------------------------------------------------------------------
inline uqword Application::GetFrameCount()
{
  return m_FrameCount;
} // GetFrameCount


// ----------------------------------------------------------------------------
// Name: Application::SetDeviceLost
// Desc: Set the device lost flag
// ----------------------------------------------------------------------------
inline void Application::SetDeviceLost()
{
  m_DeviceLost = true;
} // SetDeviceLost


inline Fog &Application::GetFog()
{
  return m_Fog;
} // GetFog


inline DirectionalLight &Application::GetDirectionalLight()
{
  return m_DirectionalLight;
} // GetDirectionalLight


inline OmniLight &Application::GetOmniLight0()
{
  return m_OmniLight0;
} // GetOmniLight0


inline OmniLight &Application::GetOmniLight1()
{
  return m_OmniLight1;
} // GetOmniLight1


inline OmniLight &Application::GetOmniLight2()
{
  return m_OmniLight2;
} // GetOmniLight2


inline OmniLight &Application::GetOmniLight3()
{
  return m_OmniLight3;
} // GetOmniLight3


inline Color &Application::GetGlobalAmbient()
{
  return m_GlobalAmbient;
} // GetGlobalAmbient


#endif // __APPLICATION_CENTRAL_H_

// -- EOF

