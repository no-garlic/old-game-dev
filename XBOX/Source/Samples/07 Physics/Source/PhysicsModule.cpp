// ----------------------------------------------------------------------------
// File: PhysicsModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "PhysicsModule.h"


// ----------------------------------------------------------------------------
// Name: PhysicsModule::PhysicsModule
// Desc: Constructor
// ----------------------------------------------------------------------------
PhysicsModule::PhysicsModule(const String &name)
: BaseModuleType    (name)
{
  REF_COUNT_CTOR(PhysicsModule);
}


// ----------------------------------------------------------------------------
// Name: PhysicsModule::~PhysicsModule
// Desc: Destructor
// ----------------------------------------------------------------------------
PhysicsModule::~PhysicsModule() 
{
  REF_COUNT_DTOR(PhysicsModule);
}


// ----------------------------------------------------------------------------
// Name: PhysicsModule::SetDisplaySettings
// Desc: Set the module's display settings
// Retn: bool - true if the settings were set
// ----------------------------------------------------------------------------
bool PhysicsModule::SetDisplaySettings(DisplaySettings &settings)
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
// Name: PhysicsModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool PhysicsModule::Init()
{
  if (!DebugRender.Init())
    return false;

  if (!m_Scene.Init())
    return false;

  return true;
}


// ----------------------------------------------------------------------------
// Name: PhysicsModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void PhysicsModule::Shutdown()
{
  // Any meshes no longer used by a scene can now be deleted
  MeshLoader::GarbageCollect();

  // Any textures no longer used (by meshes) can now be deleted
  TextureLoader::GarbageCollect();
}


// ----------------------------------------------------------------------------
// Name: PhysicsModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void PhysicsModule::App()
{
#if PC
  // Check keyboard input
  while (Input.HasKeyboardMessage())
  {
    KeyboardMessage msg = Input.PopKeyboardMessage();

    // Exit if the escape key was pressed
    if (msg.param == KEYPARAM_ESCAPE && msg.value == KEYVAL_DOWN)
      Application.RequestExit(0);
  }
#endif

  m_Scene.Update(Application.GetFrameTime());
}


// ----------------------------------------------------------------------------
// Name: PhysicsModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void PhysicsModule::Cull()
{
  m_Scene.Cull();
}


// ----------------------------------------------------------------------------
// Name: PhysicsModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void PhysicsModule::Draw()
{
#if XBOX
  ulong clearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
#else
  ulong clearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
#endif

  // Begin rendering and clear the buffer
  Device->BeginScene();
  Device->Clear(0, 0, clearFlags, Color::Black, 1.0f, 0);

  m_Scene.Render();

  // Render the debug geometry
  DebugRender.Render();

  // Done rendering
  Device->EndScene();
  Device->Present(0, 0, 0, 0);
}


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void PhysicsModule::Resize()
{
  m_Scene.Resize();
}


// ----------------------------------------------------------------------------
// Name: PhysicsModule::SetRenderState
// Desc: Set the render state for the module
// ----------------------------------------------------------------------------
void PhysicsModule::SetRenderState()
{
  m_Scene.SetRenderState();
}


// -- EOF


