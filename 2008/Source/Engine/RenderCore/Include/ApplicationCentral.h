// ----------------------------------------------------------------------------
// File: ApplicationCentral.h
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
#include "libStandard.h"
#include "libMaths.h"
#include "DisplaySettings.h"
#include "ApplicationModule.h"
#include "DeviceObject.h"
#include "RenderTarget.h"


// ----------------------------------------------------------------------------
// Singelton accessor
// ----------------------------------------------------------------------------
#define Application ApplicationCentral::GetInstance()
#define Device      Application.GetDevice()


// ----------------------------------------------------------------------------
// Name: ApplicationCentral (class)
// Desc: The central system for the D3D application, all other systems branch 
//       out from this singleton.
// ----------------------------------------------------------------------------
class ApplicationCentral
{
public:
  // --------------------------------------------------------------------------
  // Static singleton accessor
  // --------------------------------------------------------------------------
  static ApplicationCentral &GetInstance();
  static void DestroyInstance();

private:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ApplicationCentral();
  ~ApplicationCentral();

public:
  // --------------------------------------------------------------------------
  // Initialise the application
  // --------------------------------------------------------------------------
  bool Init(HWND hWnd, ApplicationModule *pModule);
  bool IsInitialised() const { return m_Initialised; }

  // --------------------------------------------------------------------------
  // Get the filesystem databases
  // --------------------------------------------------------------------------
  FileDatabase *GetTextureDatabase()  { return m_pTextureDatabase;  }
  FileDatabase *GetMaterialDatabase() { return m_pMaterialDatabase; }
  FileDatabase *GetModelDatabase()    { return m_pModelDatabase;    }
  FileDatabase *GetUIDatabase()       { return m_pUIDatabase;       }
  FileDatabase *GetLevelDatabase()    { return m_pLevelDatabase;    }
  FileDatabase *GetImportDatabase()   { return m_pImportDatabase;   }

  // --------------------------------------------------------------------------
  // The stages of the frame
  // --------------------------------------------------------------------------
  enum FrameStage
  {
    FS_INPUT  = 0x0001,
    FS_RENDER = 0x0010,
    FS_ALL    = 0x0011
  };

  // --------------------------------------------------------------------------
  // Run one frame
  // --------------------------------------------------------------------------
  bool RunFrame(FrameStage stage = FS_ALL);

  // --------------------------------------------------------------------------
  // Set the display settings
  // --------------------------------------------------------------------------
  void ResizeDisplay();
  void ToggleFullScreen();
  void SetWindowTitle(const String &str);
  bool IsAntialias() const { return m_Antialias; }

  // --------------------------------------------------------------------------
  // Request to exit the application
  // --------------------------------------------------------------------------
  inline void SetDeviceLost();
  inline void RequestExit(int exitCode);
  inline int  GetExitCode() { return m_ExitCode; }

  // --------------------------------------------------------------------------
  // Manage render targets
  // --------------------------------------------------------------------------
  RenderTarget *CreateRenderTarget(uint width, uint height, const BaseRenderTargetFunctor &type);
  RenderTarget *GetDefaultRenderTarget();
  RenderTarget *GetCurrentRenderTarget();
  void SetRenderTarget(RenderTarget *pRenderTarget);

  // --------------------------------------------------------------------------
  // Get the devices
  // --------------------------------------------------------------------------
  inline DEVICE             GetDevice();
  inline DIRECT3D           GetD3D();
  inline HWND               GetHWND();

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

  // --------------------------------------------------------------------------
  // Calculate the aspect ratio of the main window
  // --------------------------------------------------------------------------
  float CalculateAspectRatio();
  
  // --------------------------------------------------------------------------
  // Device objects
  // --------------------------------------------------------------------------
  void RegisterDeviceObject(DeviceObject *pObject);
  void UnregisterDeviceObject(DeviceObject *pObject);

  // --------------------------------------------------------------------------
  // Config
  // --------------------------------------------------------------------------
  const ConfigFile &GetConfig() { return m_config; }
  const ConfigSection &GetConfig(const String &sectionName) { return m_config(sectionName); }

  // --------------------------------------------------------------------------
  // Delayed object creation
  // --------------------------------------------------------------------------
  struct CreationFunctor
  {
    CreationFunctor(const String &name) : Name(name) {}
    virtual bool Create()  = 0;
    virtual bool Destroy() = 0;
    String Name;
  };

  // --------------------------------------------------------------------------
  // Queue an object for creation after the device has been created
  // --------------------------------------------------------------------------
  static void AddCreationFunctor(CreationFunctor *pFunc);
  static bool CreateAllCreationFunctors();
  static bool DestroyAllCreationFunctors();

private:
  // --------------------------------------------------------------------------
  // Private functions
  // --------------------------------------------------------------------------
  void RunOneProcess();
  bool InitialiseRenderTarget();

  // --------------------------------------------------------------------------
  // Reset the device
  // --------------------------------------------------------------------------
  bool ResetDevice();
  bool AllocateDeviceObjects();
  bool ReleaseDeviceObjects();

  // --------------------------------------------------------------------------
  // Destruct the resources
  // --------------------------------------------------------------------------
  void DestructResources();

  // --------------------------------------------------------------------------
  // Create the file databases
  // --------------------------------------------------------------------------
  bool CreateFileDatabases(ApplicationModule *pModule);
  bool CreateLogFile(ApplicationModule *pModule);

  // --------------------------------------------------------------------------
  // Typedefs
  // --------------------------------------------------------------------------
  typedef Map<ulong, DeviceObject *> DeviceObjectMap;

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  static ApplicationCentral   *s_pInstance;                  // The singleton instance
  bool                  m_Initialised;                // Is the app initialised
  bool                  m_Destructed;                 // Has the app been destructed
  DIRECT3D              m_pDirect3D;                  // The directX device
  DEVICE                m_pDevice;                    // The d3d graphics device
  bool                  m_ResetDeviceNextFrame;       // Request to reset the device 
  bool                  m_ToggleFullScreenNextFrame;  // Reqest to toggle to fullscreen
  bool                  m_IsFullScreen;               // Are we fullscreen
  bool                  m_DeviceLost;                 // Has teh device been lost
  ApplicationModule    *m_pModule;                    // The module that is being executed
  HWND                  m_hWnd;                       // The window handle
  bool                  m_RequestExit;                // Request to exit the game
  bool                  m_RequestExitNextFrame;       // Request to exit the game next frame
  int                   m_ExitCode;                   // The exit code
  Timer                 m_Timer;                      // The game timer
  bool                  m_Paused;                     // Is the game paused
  bool                  m_Antialias;                  // IS the application multisample antialiased
  float                 m_FrameTime;                  // The current frame time
  float                 m_RunTime;                    // The total running time
  uint                  m_FrameRate;                  // The current frame rate
  uqword                m_FrameCount;                 // Total number of frames
  uint                  m_IntervalFrames;             // Frames counted since last frame rate update
  float                 m_IntervalTime;               // Time since last frame rate update
  DeviceObjectMap       m_DeviceObjects;              // The device objects to be managed when the device is reset
  String                m_WindowTitle;                // The window title
  String                m_DataPath;                   // The base path to the data
  FileDatabase         *m_pTextureDatabase;           // The resource database for textures
  FileDatabase         *m_pMaterialDatabase;          // The resource database for materials
  FileDatabase         *m_pModelDatabase;             // The resource database for models
  FileDatabase         *m_pLevelDatabase;             // The resource database for levels
  FileDatabase         *m_pUIDatabase;                // The resource database for user interface
  FileDatabase         *m_pImportDatabase;            // The resource database for importing data
  ConfigFile            m_config;                     // The engine config file
  RenderTarget         *m_pBackBufferRenderTarget;    // The back buffer render target
  RenderTarget         *m_pCurrentRenderTarget;       // The current render target
  Array<RenderTarget *> m_RenderTargetArray;          // All render targets

  static Array<CreationFunctor *> s_CreationFunctors; // All creation functors
}; // class ApplicationCentral


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::GetDevice
// Desc: Get the D3D Device
// Retn: DEVICE - the device
// ----------------------------------------------------------------------------
inline DEVICE ApplicationCentral::GetDevice()
{
  return m_pDevice;
} // GetDevice


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::GetD3D
// Desc: Get the D3D pointer
// Retn: LPDIRECT3D9 - the D3D pointer
// ----------------------------------------------------------------------------
inline DIRECT3D ApplicationCentral::GetD3D()
{
  return m_pDirect3D;
} // GetD3D


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::GetHWND
// Desc: Get the HWND we are using
// Retn: HWND - the HWND
// ----------------------------------------------------------------------------
inline HWND ApplicationCentral::GetHWND()
{
  return m_hWnd;
} // GetHWND


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::RequestExit
// Desc: Request the application to exit
// Parm: int exitCode - the exit code of the application
// ----------------------------------------------------------------------------
inline void ApplicationCentral::RequestExit(int exitCode)
{
  m_RequestExitNextFrame = true;
  m_ExitCode             = exitCode;
} // RequestExit


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::Pause
// Desc: Pause the renderer
// ----------------------------------------------------------------------------
inline void ApplicationCentral::Pause()
{
  m_Paused = true;
} // Pause


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::Resume
// Desc: Resume the renderer
// ----------------------------------------------------------------------------
inline void ApplicationCentral::Resume()
{
  m_Paused = false;
} // Resume


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::IsPaused
// Desc: Is the application paused
// Retn: bool - true if paused, otherwise false
// ----------------------------------------------------------------------------
inline bool ApplicationCentral::IsPaused()
{
  return m_Paused;
} // IsPaused


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::GetRunningTime
// Desc: Get the total time the engine has been running (excluding paused time)
// Retn: float - the time in seconds
// ----------------------------------------------------------------------------
inline float ApplicationCentral::GetRunningTime()
{
  return m_RunTime;
} // GetRunningTime


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::GetFrameTime
// Desc: Get the time of the last frame
// Retn: float - the time in seconds
// ----------------------------------------------------------------------------
inline float ApplicationCentral::GetFrameTime()
{
  return m_FrameTime;
} // GetFrameTime


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::GetFrameRate
// Desc: Get the frame rate
// Retn: unsigned int - the frame rate
// ----------------------------------------------------------------------------
inline unsigned int ApplicationCentral::GetFrameRate()
{
  return m_FrameRate;
} // GetFrameRate


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::GetFrameCount
// Desc: Get the total number of rendered frames
// Retn: uqword - the frame count
// ----------------------------------------------------------------------------
inline uqword ApplicationCentral::GetFrameCount()
{
  return m_FrameCount;
} // GetFrameCount


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::SetDeviceLost
// Desc: Set the device lost flag
// ----------------------------------------------------------------------------
inline void ApplicationCentral::SetDeviceLost()
{
  m_DeviceLost = true;
} // SetDeviceLost


#endif // __APPLICATION_CENTRAL_H_

// -- EOF

