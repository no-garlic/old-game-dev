// ----------------------------------------------------------------------------
// File: EditorModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "EditorModule.h"
#include "EditorApp.h"
#include "Editor.h"


// ----------------------------------------------------------------------------
// Name: EditorModule::EditorModule
// Desc: Constructor
// ----------------------------------------------------------------------------
EditorModule::EditorModule(const String &name)
: ApplicationModule_Wx(name)
{
  REF_COUNT_CTOR(EditorModule);
} // EditorModule


// ----------------------------------------------------------------------------
// Name: EditorModule::~EditorModule
// Desc: Destructor
// ----------------------------------------------------------------------------
EditorModule::~EditorModule() 
{
  REF_COUNT_DTOR(EditorModule);
} // ~EditorModule



// ----------------------------------------------------------------------------
// Name: LevelEditorModule::Create
// Desc: Set the module's display settings
// Parm: DisplaySettings &settings - [out] the settings to set
// Retn: bool - true if the settings were set
// ----------------------------------------------------------------------------
bool EditorModule::SetDisplaySettings(DisplaySettings &settings)
{
  // Windowed
  settings.StartFullScreen = false;

  // Initial Size
  settings.InitialWindowSize.cx = 1024;
  settings.InitialWindowSize.cy = 768;

  // Initial Position
  //settings.InitialWindowPosition.x = 300;
  //settings.InitialWindowPosition.y = 960;

  // Done
  return true;
}


// ----------------------------------------------------------------------------
// Name: EditorModule::CreateApp
// Desc: Create the application
// Parm: DisplaySettings ds  - the display settings
// Retn: CWinApp *           - the application
// ----------------------------------------------------------------------------
WxDisplayApp *EditorModule::CreateApp(DisplaySettings ds)
{
  WxDisplay::GetDisplaySettings() = ds;
  return new EditorApp;
} // CreateApp


// ----------------------------------------------------------------------------
// Name: EditorModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool EditorModule::Init()
{
  Editor.SetModule(this);
  return Editor.OnInit();
} // Init


// ----------------------------------------------------------------------------
// Name: EditorModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void EditorModule::Shutdown()
{
  Editor.OnShutdown();

  MeshLoader::GarbageCollect();
  TextureLoader::GarbageCollect();
} // Shutdown


// ----------------------------------------------------------------------------
// Name: EditorModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void EditorModule::App()
{
  Editor.App();
} // App


// ----------------------------------------------------------------------------
// Name: EditorModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void EditorModule::Cull()
{
  Editor.Cull();
} // Cull


// ----------------------------------------------------------------------------
// Name: EditorModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void EditorModule::Draw()
{
  Editor.Draw();
} // Draw


// ----------------------------------------------------------------------------
// Name: EditorModule::SetRenderState
// Desc: Set the render state
// ----------------------------------------------------------------------------
void EditorModule::SetRenderState()
{
}


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void EditorModule::Resize()
{
  Editor.OnResize();
} // Resize


// ----------------------------------------------------------------------------
// The window has moved
// ----------------------------------------------------------------------------
void EditorModule::Move()
{
  Editor.OnMove();
}


// -- EOF


