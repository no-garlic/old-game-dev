// ----------------------------------------------------------------------------
// File: CreateDeviceModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "CreateDeviceModule.h"


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::CreateDeviceModule
// Desc: Constructor
// ----------------------------------------------------------------------------
CreateDeviceModule::CreateDeviceModule(const String &name)
: BaseModuleType(name)
{
  REF_COUNT_CTOR(CreateDeviceModule);
}


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::~CreateDeviceModule
// Desc: Destructor
// ----------------------------------------------------------------------------
CreateDeviceModule::~CreateDeviceModule() 
{
  REF_COUNT_DTOR(CreateDeviceModule);
}


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::SetDisplaySettings
// Desc: Set the module's display settings
// Retn: bool - true if the settings were set
// ----------------------------------------------------------------------------
bool CreateDeviceModule::SetDisplaySettings(DisplaySettings &settings)
{
#if XBOX
  // No VSYNC
  settings.FullScreenParams.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

  // 640 x 480
  settings.FullScreenParams.BackBufferWidth  = 640;
  settings.FullScreenParams.BackBufferHeight = 480;
#else
  // Windowed
  settings.StartFullScreen = false;

  // 640 x 480
  settings.InitialWindowSize.cx = 640;
  settings.InitialWindowSize.cy = 480;
#endif

  return true;
}


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool CreateDeviceModule::Init()
{
  LOG_INFO << "Initialised the application" << ENDLOG;
  return true;
}


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void CreateDeviceModule::Shutdown()
{
}


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void CreateDeviceModule::App()
{
#if PC
  while (Input.HasKeyboardMessage())
  {
    KeyboardMessage msg = Input.PopKeyboardMessage();

    if (msg.param == KEYPARAM_ESCAPE && msg.value == KEYVAL_DOWN)
      Application.RequestExit(0);
  }
#endif
}


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void CreateDeviceModule::Cull()
{
}


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void CreateDeviceModule::Draw()
{
#if XBOX
  ulong clearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
#else
  ulong clearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
#endif

  Device->BeginScene();
  Device->Clear(0, 0, clearFlags, Color::Blue, 1.0f, 0);

  Device->EndScene();
  Device->Present(0, 0, 0, 0);
}


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void CreateDeviceModule::Resize()
{
}


// ----------------------------------------------------------------------------
// Name: CreateDeviceModule::SetRenderState
// Desc: Set the render state for the module
// ----------------------------------------------------------------------------
void CreateDeviceModule::SetRenderState()
{
  RenderState.Set(D3DRS_LIGHTING, FALSE);
}


// -- EOF


