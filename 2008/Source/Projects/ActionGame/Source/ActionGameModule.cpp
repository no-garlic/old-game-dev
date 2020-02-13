// ----------------------------------------------------------------------------
// File: ActionGameModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2007
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "ActionGameModule.h"
#include "GameWorld.h"
#include "GameState.h"


// ----------------------------------------------------------------------------
// Name: ActionGameModule::ActionGameModule
// Desc: Constructor
// ----------------------------------------------------------------------------
ActionGameModule::ActionGameModule(const String &name)
: BaseModuleType    (name)
{
  REF_COUNT_CTOR(ActionGameModule);
}


// ----------------------------------------------------------------------------
// Name: ActionGameModule::~ActionGameModule
// Desc: Destructor
// ----------------------------------------------------------------------------
ActionGameModule::~ActionGameModule() 
{
  REF_COUNT_DTOR(ActionGameModule);
}


// ----------------------------------------------------------------------------
// Name: ActionGameModule::Create
// Desc: Set the module's display settings
// Parm: DisplaySettings &settings - [out] the settings to set
// Retn: bool - true if the settings were set
// ----------------------------------------------------------------------------
bool ActionGameModule::SetDisplaySettings(DisplaySettings &settings)
{
#if XBOX
  // No VSYNC
  settings.FullScreenParams.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

  // 640 x 480
  settings.FullScreenParams.BackBufferWidth  = 640;
  settings.FullScreenParams.BackBufferHeight = 480;

  // Done
  return true;
#else
  // Windowed
  settings.StartFullScreen = false;

  // 640 x 480
  settings.InitialWindowSize.cx = 640;
  settings.InitialWindowSize.cy = 480;
  //settings.InitialWindowPosition.x = 300;
  //settings.InitialWindowPosition.y = 960;

  // Done
  return true;
#endif
}


// ----------------------------------------------------------------------------
// Name: ActionGameModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool ActionGameModule::Init()
{
  // Initialise the world
  if (!GameWorld.Init())
    return false;

  // Set the render state
  GameWorld.SetRenderState();

  // Initialise the game state
  if (!GameState.Init())
    return false;

  // Done
  return true;
}


// ----------------------------------------------------------------------------
// Name: ActionGameModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void ActionGameModule::Shutdown()
{  
  // Shutdown the world
  GameWorld.Shutdown();

  // Any meshes no longer used by a scene can now be deleted
  MeshLoader::GarbageCollect();

  // Any textures no longer used (by meshes) can now be deleted
  TextureLoader::GarbageCollect();
}


// ----------------------------------------------------------------------------
// Name: ActionGameModule::SetRenderState
// Desc: Set the render state for the module
// ----------------------------------------------------------------------------
void ActionGameModule::SetRenderState()
{
  GameWorld.SetRenderState();
}


// ----------------------------------------------------------------------------
// Name: ActionGameModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void ActionGameModule::App()
{
  GameWorld.App();
}


// ----------------------------------------------------------------------------
// Name: ActionGameModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void ActionGameModule::Cull()
{
  GameWorld.Cull();
}


// ----------------------------------------------------------------------------
// Name: ActionGameModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void ActionGameModule::Draw()
{
  GameWorld.Draw();
}


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void ActionGameModule::Resize()
{
  GameWorld.SetRenderState();
}


// -- EOF


