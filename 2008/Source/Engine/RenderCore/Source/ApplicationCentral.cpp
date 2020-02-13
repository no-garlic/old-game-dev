// ----------------------------------------------------------------------------
// File: ApplicationCentral.cpp
// Desc: The central system for the D3D application, all other systems branch 
//       out from this singleton.
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "ApplicationCentral.h"
#include "RenderState.h"
#include "Input.h"


// ----------------------------------------------------------------------------
// Static initialisers
// ----------------------------------------------------------------------------
ApplicationCentral *ApplicationCentral::s_pInstance = NULL;


// ----------------------------------------------------------------------------
// All creation functors
// ----------------------------------------------------------------------------
Array<ApplicationCentral::CreationFunctor *> ApplicationCentral::s_CreationFunctors;


// ----------------------------------------------------------------------------
// Globals
// ----------------------------------------------------------------------------
FileStream g_LogFile;


// ----------------------------------------------------------------------------
// Possible engine config file locations
// ----------------------------------------------------------------------------
#if PC
String g_EngineConfig[6][2] = 
{
  { "Data\\Config\\Engine.cfg",                     "" },
  { "..\\Data\\Config\\Engine.cfg",                 "..\\" },
  { "..\\..\\Data\\Config\\Engine.cfg",             "..\\..\\" },
  { "..\\..\\..\\Data\\Config\\Engine.cfg",         "..\\..\\..\\" },
  { "..\\..\\..\\..\\Data\\Config\\Engine.cfg",     "..\\..\\..\\..\\" },
  { "..\\..\\..\\..\\..\\Data\\Config\\Engine.cfg", "..\\..\\..\\..\\..\\" }
};
#endif


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::ApplicationCentral
// Desc: Constructor
// ----------------------------------------------------------------------------
ApplicationCentral::ApplicationCentral()
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
  m_Antialias                 (false),
  m_ExitCode                  (0),
  m_FrameTime                 (0.0f),
  m_RunTime                   (0.0f),
  m_FrameRate                 (0),
  m_FrameCount                (0),
  m_IntervalFrames            (0),
  m_IntervalTime              (0.0f),
  m_pTextureDatabase          (0),
  m_pMaterialDatabase         (0),
  m_pModelDatabase            (0),
  m_pUIDatabase               (0),
  m_pLevelDatabase            (0),
  m_pImportDatabase           (0),
  m_pBackBufferRenderTarget   (0),
  m_pCurrentRenderTarget      (0)
{
  REF_COUNT_CTOR(ApplicationCentral);

  // Create the directx device
  m_pDirect3D = Direct3DCreate(D3D_SDK_VERSION);
  NULL_ASSERT(m_pDirect3D);
} // ApplicationCentral


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::~ApplicationCentral
// Desc: Destructor
// ----------------------------------------------------------------------------
ApplicationCentral::~ApplicationCentral()
{
  REF_COUNT_DTOR(ApplicationCentral);

  if (!m_Destructed)
    DestructResources();
} // ~ApplicationCentral


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::GetInstance
// Desc: Get the singelton instance
// Retn: ApplicationCentral & - the instance
// ----------------------------------------------------------------------------
ApplicationCentral &ApplicationCentral::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new ApplicationCentral();
    atexit(&ApplicationCentral::DestroyInstance);
  } // if

  return *s_pInstance;
} // GetInstance


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::DestroyInstance
// Desc: Destroy the singleton instance
// ----------------------------------------------------------------------------
void ApplicationCentral::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
} // DestroyInstance


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::InitDisplay
// Desc: Initialise the display for the given window
// Parm: HWND hWnd  - the window
// Retn: bool       - true if intialised sucessfully
// ----------------------------------------------------------------------------
bool ApplicationCentral::Init(HWND hWnd, ApplicationModule *pModule)
{
  if (m_Initialised)
    return false;

  // Set the member variables
  m_hWnd            = hWnd;
  m_pModule         = pModule;

  // Cehck D3D has been created
  if (!m_pDirect3D)
    return false;

#if PC
  bool configLoaded = false;
  for (uint i = 0; i < 6; i++)
  {
    if (m_config.Load(g_EngineConfig[i][0]))
    {
      configLoaded = true;
      m_DataPath = g_EngineConfig[i][1];
      break;
    }
  }

  if (!configLoaded)
  {
    LOG_ERROR << "Failed to load the engine config file" << ENDLOG;
    return false;
  } // if

#else
  // TODO: Make this relative rather than using D: - as that wont work for DVD ??
  if (!m_config.Load("D:\\Data\\Config\\XboxEngine.cfg"))
  {
    LOG_ERROR << "Failed to load the engine config file" << ENDLOG;
    return false;
  } // if

  ConfigSection &section = m_config("FilePath");
  m_DataPath = section("BasePath");
#endif

  String moduleConfigName = "..\\Data\\Config\\";
  moduleConfigName += pModule->GetName();
  moduleConfigName += ".cfg";

  // Create the module config
  ConfigFile cfg;
  if (cfg.Load(moduleConfigName))
  {
    if (!m_config.Append(cfg))
    {
       LOG_ERROR << "Failed to process the module config file" << ENDLOG;
       return false;
    }
  }

  if (!CreateLogFile(pModule))
  {
    LOG_ERROR << "Failed to create the log file" << ENDLOG;
    return false;
  }

  if (!CreateFileDatabases(pModule))
  {
    LOG_ERROR << "Failed to create the resource databases" << ENDLOG;
    return false;
  }

  // Get the module to set the display settings
  DisplaySettings ds;
  if (!pModule->SetDisplaySettings(ds))
    return false;

#if XBOX
  // Create the device
  HRESULT hr = m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
    D3DCREATE_HARDWARE_VERTEXPROCESSING, &ds.FullScreenParams, &m_pDevice);

  // Check that the device is ok
  if (FAILED(hr))
    return false;

  m_IsFullScreen = true;
#else
  HRESULT hr = S_FALSE;
  if (ds.StartFullScreen)
  {
    hr = m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
      D3DCREATE_HARDWARE_VERTEXPROCESSING, &ds.FullScreenParams, &m_pDevice);

    m_IsFullScreen = true;
  } // if
  else
  {
    // Check antialias support
    if (SUCCEEDED(m_pDirect3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, 
					D3DDEVTYPE_HAL ,ds.WindowParams.BackBufferFormat, FALSE, D3DMULTISAMPLE_4_SAMPLES, NULL)))
    {
      ds.WindowParams.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
      m_Antialias = true;
    }

    hr = m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
      D3DCREATE_HARDWARE_VERTEXPROCESSING, &ds.WindowParams, &m_pDevice);

    m_IsFullScreen = false;
  } // else

  // Check that the device is ok, if not attempt to get the next 
  // display settings from the module
  if (FAILED(hr))
    return false;

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
#endif

  // Set the render states to the default values
  if (!RenderState.ResetToDefault())
    return false;

  // Register the engine types
  if (!m_pModule->RegisterTypes())
    return false;

  // Create all vertex types, materials, etc.
  if (!CreateAllCreationFunctors())
    return false;

  // Set the module's device
  m_pModule->m_pDevice = m_pDevice;

  // Create the default render target
  if (!InitialiseRenderTarget())
    return false;

  // Initialise the module
  if (!m_pModule->Init())
    return false;

#if PC
  if (!pModule->IsNullRender())
  {
    // Initialise the input
    if (!Input.Init())
      return false;
  } // if
#else
  // Initialise the input
  Input.Init();
#endif

  // Start the timer
  m_Timer.Reset();
  m_Timer.Start();

  // Done
  m_Initialised = true;
  return true;
} // Init


// ----------------------------------------------------------------------------
// Initialsie the back buffer render target
// ----------------------------------------------------------------------------
bool ApplicationCentral::InitialiseRenderTarget()
{
  BackBufferRenderTargetFunctor func;
  m_pBackBufferRenderTarget = func(0, 0);

  if (!m_pBackBufferRenderTarget)
    return false;

  return true;
}


// ----------------------------------------------------------------------------
// Create a new render target
// ----------------------------------------------------------------------------
RenderTarget *ApplicationCentral::CreateRenderTarget(uint width, uint height, const BaseRenderTargetFunctor &type)
{
  RenderTarget *pRenderTarget = type(width, height);
  if (!pRenderTarget)
    return NULL;

  m_RenderTargetArray.push_back(pRenderTarget);
  return pRenderTarget;
}


// ----------------------------------------------------------------------------
// Get the default (back buffer) render target
// ----------------------------------------------------------------------------
RenderTarget *ApplicationCentral::GetDefaultRenderTarget()
{
  return m_pBackBufferRenderTarget;
}


// ----------------------------------------------------------------------------
// Set the current render target
// ----------------------------------------------------------------------------
void ApplicationCentral::SetRenderTarget(RenderTarget *pRenderTarget)
{
  if (!pRenderTarget)
  {
    m_pBackBufferRenderTarget->Apply();
    m_pCurrentRenderTarget = m_pBackBufferRenderTarget;
  }
  else
  {
    pRenderTarget->Apply();
    m_pCurrentRenderTarget = pRenderTarget;
  }
}


RenderTarget *ApplicationCentral::GetCurrentRenderTarget()
{
  return m_pCurrentRenderTarget;
}


bool ApplicationCentral::CreateFileDatabases(ApplicationModule *pModule)
{
  // Get the file path section
  ConfigSection &section = m_config("FilePath");
  if (!section.IsValid())
  {
    LOG_ERROR << "The config file does not contain a FilePath section" << ENDLOG;
    return false;
  }

  // Set the base path
#if XBOX
  FileSystem.SetBasePath(m_DataPath, false);
#else
  FileSystem.SetBasePath(m_DataPath);
#endif

  // See if any of the databases have been overridden from the command line
  String databaseNames[] = { "Model", "Texture", "Material", "UI", "Level", "Import" };
  for (uint i = 0; i < 6; i++)
  {
    String optionName = "-" + databaseNames[i];
    String inDir = section(databaseNames[i]);
    if (AppArgs.HasOption(optionName.c_str()))
    {
      const StringArray &optionArgs = AppArgs.GetOptionArgs(optionName.c_str());
      if (!optionArgs.empty())
      {
        inDir = optionArgs[0];
      }
    }

    // Create the databases
    switch (i)
    {
      case 0: m_pModelDatabase    = FileSystem.AddDatabase(databaseNames[i], inDir); break;
      case 1: m_pTextureDatabase  = FileSystem.AddDatabase(databaseNames[i], inDir); break;
      case 2: m_pMaterialDatabase = FileSystem.AddDatabase(databaseNames[i], inDir); break;
      case 3: m_pUIDatabase       = FileSystem.AddDatabase(databaseNames[i], inDir); break;
      case 4: m_pLevelDatabase    = FileSystem.AddDatabase(databaseNames[i], inDir); break;
      case 5: m_pImportDatabase   = FileSystem.AddDatabase(databaseNames[i], inDir); break;
    }
  }

  if (m_pModelDatabase && m_pTextureDatabase && m_pMaterialDatabase && m_pUIDatabase && m_pLevelDatabase && m_pImportDatabase)
    return true;

  return false;
}


// ----------------------------------------------------------------------------
// Callback function for the logger
// ----------------------------------------------------------------------------
void LogFileCallbackFunction(const char *pMsg)
{
  g_LogFile << pMsg << std::endl;
}


// ----------------------------------------------------------------------------
// Create the logger file for the application module based on the config options
// ----------------------------------------------------------------------------
bool ApplicationCentral::CreateLogFile(ApplicationModule *pModule)
{
  bool isLogging = true;
  String logFilename = "";

  // Get the configuration items
  ConfigSection &section = m_config("LogFile");
  ConfigValue enabled    = section("Enabled");
  ConfigValue filename   = section("Filename");

  if ((enabled.IsValid() && enabled == false) || AppArgs.HasOption("-nolog"))
    isLogging = false;
  
  if (filename.IsValid())
    logFilename = filename.Value;

  if (AppArgs.HasOption("-log"))
  {
    isLogging = true;
    const StringArray &optionArgs = AppArgs.GetOptionArgs("-log");
    if (!optionArgs.empty())
    {
      logFilename = optionArgs[0];
    }
  }

  if (logFilename.empty())
    return true;

  if (isLogging)
  {
    g_LogFile.open(logFilename.c_str(), std::ios_base::out);
    if (!g_LogFile.is_open())
      return false;

    LOG_CALLBACK(LogFileCallbackFunction);
  } // if

  return true;
}


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::SetWindowTitle
// Desc: Set the title of the main window
// Parm: const String &str - the title
// ----------------------------------------------------------------------------
void ApplicationCentral::SetWindowTitle(const String &str)
{
#if PC
  if (m_WindowTitle == str)
    return;

  m_WindowTitle = str;

  if (m_pModule)
    m_pModule->SetWindowTitle(str);
#endif
} // SetWindowTitle


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::ResizeDisplay
// Desc: Resize the back buffer because the window has been resized
// Retn: bool - true if the resize suceeded
// ----------------------------------------------------------------------------
void ApplicationCentral::ResizeDisplay()
{
  m_ResetDeviceNextFrame = true;
} // ReesizeDisplay


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::ToggleFullScreen
// Desc: Toggle between fullscreen and a window
// ----------------------------------------------------------------------------
void ApplicationCentral::ToggleFullScreen()
{
  m_ResetDeviceNextFrame      = true;
  m_ToggleFullScreenNextFrame = true;
} // ToggleFullScreen


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::ResetDevice
// Desc: Reset the device
// ----------------------------------------------------------------------------
bool ApplicationCentral::ResetDevice()
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
    bool resetOk = true;
    if (m_FrameCount > 0)
    {
      resetOk |= ReleaseDeviceObjects();
      resetOk |= m_pModule->ResetDisplay(toggleFullscreen, m_IsFullScreen);
      resetOk |= AllocateDeviceObjects();
      m_pModule->SetRenderState();
    } // if
    else
    {
      m_pBackBufferRenderTarget->ReleaseDeviceMemory();
      resetOk = m_pModule->ResetDisplay(toggleFullscreen, m_IsFullScreen);
      if (resetOk)
        m_pBackBufferRenderTarget->AllocateDeviceMemory();
    } // else

    return resetOk;
  } // if

  return false;
} // ResetDevice


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::RegisterDeviceObject
// Desc: Register a device object
// Parm: DeviceObject *pObject - the device object to register
// ----------------------------------------------------------------------------
void ApplicationCentral::RegisterDeviceObject(DeviceObject *pObject)
{
  ulong id = reinterpret_cast<ulong>(pObject);
  m_DeviceObjects.insert(std::make_pair<ulong, DeviceObject *>(id, pObject));
} // RegisterDeviceObject


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::UnregisterDeviceObject
// Desc: Unregister a device object
// Parm: DeviceObject *pObject - the device object to unregister
// ----------------------------------------------------------------------------
void ApplicationCentral::UnregisterDeviceObject(DeviceObject *pObject)
{
  ulong id = reinterpret_cast<ulong>(pObject);
  ApplicationCentral::DeviceObjectMap::iterator iter(m_DeviceObjects.find(id));
  m_DeviceObjects.erase(iter);
} // UnregisterDeviceObject


// ----------------------------------------------------------------------------
// Calculates the aspect ratio of the main window
// ----------------------------------------------------------------------------
float ApplicationCentral::CalculateAspectRatio()
{
  VIEWPORT viewport;
  m_pDevice->GetViewport(&viewport);

  // Check for div by 0
  if (viewport.Height == 0)
    return 1.0f;

  // Return the aspect ratio
  return ((float) viewport.Width / (float) viewport.Height);
}


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::AllocateDeviceObjects
// Desc: Allocate the device objects memory
// ----------------------------------------------------------------------------
bool ApplicationCentral::AllocateDeviceObjects()
{
  bool result = true;

  ApplicationCentral::DeviceObjectMap::iterator iter(m_DeviceObjects.begin()), end(m_DeviceObjects.end());
  for (; iter != end; ++iter)
  {
    result |= iter->second->AllocateDeviceMemory();
  } // for

  return result;
} // AllocateDeviceObjects


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::ReleaseDeviceObjects
// Desc: Release the device objects memory
// ----------------------------------------------------------------------------
bool ApplicationCentral::ReleaseDeviceObjects()
{
  bool result = true;

  ApplicationCentral::DeviceObjectMap::iterator iter(m_DeviceObjects.begin()), end(m_DeviceObjects.end());
  for (; iter != end; ++iter)
  {
    result |= iter->second->ReleaseDeviceMemory();
  } // for

  return result;
} // ReleaseDeviceObjects


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::Run
// Desc: Run the application module given in the specified processing mode
// Parm: stage - the frame stage to run
// Retn: bool - false means that we want to exit
// ----------------------------------------------------------------------------
bool ApplicationCentral::RunFrame(FrameStage stage)
{
  // Check that we are initialised
  if (!m_Initialised)
    return false;

  if (stage & ApplicationCentral::FS_INPUT)
  {
    // Read the input devices
    if (!Input.ReadData())
      return false;

    // Assign the request exit flag now
    m_RequestExit = m_RequestExitNextFrame;

    // If we are exiting, thens stop the threads
    if (m_RequestExit)
    {
      m_hWnd = NULL;
      DestructResources();
      return false;
    } // if

#if XBOX
    // Call Reset once at start on xbox
    if (m_FrameCount == 0)
      m_pModule->ResetDisplay(false, true);
#endif

#if PC
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
#endif

    // Reset the device if we need to
    if (m_ResetDeviceNextFrame)
    {
      if (!ResetDevice())
        return false;
    } // if
  } // if

  if (stage & ApplicationCentral::FS_RENDER)
  {
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

    // Setup the render state
    if (m_FrameCount == 0)
      m_pModule->SetRenderState();

    RunOneProcess();

    // Increment the frame count
    m_FrameCount++;

#if PC
    // Check for a lost device
    if (m_pDevice->TestCooperativeLevel() == D3DERR_DEVICELOST)
      SetDeviceLost();
#endif
  } // if

  // Return true if we want to continue
  return !m_RequestExit;
} // Run


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::DestructResources
// Desc: Destruct the allocated resources
// ----------------------------------------------------------------------------
void ApplicationCentral::DestructResources()
{
  if (!m_Initialised)
    return;

  if (!m_Destructed)
  {
    // We are now in the destructed state
    m_Destructed = true;

    // Shutdown the module
    if (m_pModule)
    {
      m_pModule->Shutdown();

      // Delete the module
      delete m_pModule;
    } // if

    // Shutdown the input
    Input.Shutdown();
  } // if

  if (m_pBackBufferRenderTarget)
    delete m_pBackBufferRenderTarget;

  DestroyAllCreationFunctors();
} // DestructResources


// ----------------------------------------------------------------------------
// Name: ApplicationCentral::RunOneProcess
// Desc: Run the module using a single process
// Retn: int - the application return code
// ----------------------------------------------------------------------------
void ApplicationCentral::RunOneProcess()
{
  PROFILE_START(PROFILE_FRAME);

  PROFILE_START(PROFILE_APP);
  m_pModule->App();
  PROFILE_STOP(PROFILE_APP);

  PROFILE_START(PROFILE_CULL);
  m_pModule->Cull();
  PROFILE_STOP(PROFILE_CULL);

  PROFILE_START(PROFILE_DRAW);
  m_pModule->Draw();
  m_pDevice->SetTexture(0, NULL);
  m_pDevice->SetTexture(1, NULL);
  m_pDevice->SetTexture(2, NULL);
  m_pDevice->SetTexture(3, NULL);
#if PC
  m_pDevice->SetVertexDeclaration(NULL); // Causes a D3D warning
  m_pDevice->SetFVF(0);
#endif
  m_pDevice->SetVertexShader(NULL);
  m_pDevice->SetPixelShader(NULL);
  PROFILE_STOP(PROFILE_DRAW);

  PROFILE_STOP(PROFILE_FRAME);

  PROFILE_RESET_ALL;
} // RunOneProcess


void ApplicationCentral::AddCreationFunctor(CreationFunctor *pFunc)
{
  s_CreationFunctors.push_back(pFunc);
}


bool ApplicationCentral::CreateAllCreationFunctors()
{
  bool result = true;
  for (uint i = 0; i < s_CreationFunctors.size(); i++)
  {
    ApplicationCentral::CreationFunctor *pFunc = s_CreationFunctors[i];

    if (!pFunc->Create())
    {
      LOG_ERROR << "Failed to create: " << pFunc->Name << ENDLOG;
      result = false;
    }
  }

  return result;
}


bool ApplicationCentral::DestroyAllCreationFunctors()
{
  bool result = true;
  for (uint i = 0; i < s_CreationFunctors.size(); i++)
  {
    ApplicationCentral::CreationFunctor *pFunc = s_CreationFunctors[i];

    if (!pFunc->Destroy())
    {
      LOG_ERROR << "Failed to destroy: " << pFunc->Name << ENDLOG;
      result = false;
    }
  }

  s_CreationFunctors.clear();  
  return result;
}


// -- EOF

