// ----------------------------------------------------------------------------
// File: AnimationModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "AnimationModule.h"
#include "Material_PNT_ANIM.h"


#if USE_VIEWER
#include "Viewer.h"
#endif


// ----------------------------------------------------------------------------
// Name: AnimationModule::AnimationModule
// Desc: Constructor
// ----------------------------------------------------------------------------
AnimationModule::AnimationModule(const String &name)
: BaseModuleType(name)
{
  REF_COUNT_CTOR(AnimationModule);
}


// ----------------------------------------------------------------------------
// Name: AnimationModule::~AnimationModule
// Desc: Destructor
// ----------------------------------------------------------------------------
AnimationModule::~AnimationModule() 
{
  REF_COUNT_DTOR(AnimationModule);
}


// ----------------------------------------------------------------------------
// Name: AnimationModule::RegisterTypes
// Desc: Register any types used by the module
// Retn: bool - true if the types were registered
// ----------------------------------------------------------------------------
bool AnimationModule::RegisterTypes()
{
  if (!BaseModuleType::RegisterTypes())
    return false;

#if !USE_VIEWER
//  REGISTER_MATERIAL(Material_PNT_ANIM);
#endif

  return true;
}


// ----------------------------------------------------------------------------
// Name: AnimationModule::SetDisplaySettings
// Desc: Set the module's display settings
// Retn: bool - true if the settings were set
// ----------------------------------------------------------------------------
bool AnimationModule::SetDisplaySettings(DisplaySettings &settings)
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
// Name: AnimationModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool AnimationModule::Init()
{
  LOG_INFO << "Initialised the application" << ENDLOG;

#if !USE_VIEWER
  m_pScene = new GameScene();
  if (!m_pScene->Init())
    return false;
#endif

  return true;
}


// ----------------------------------------------------------------------------
// Name: AnimationModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void AnimationModule::Shutdown()
{
#if USE_VIEWER
  theViewer.onShutdown();
#else

#endif
}


// ----------------------------------------------------------------------------
// Name: AnimationModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void AnimationModule::App()
{
#if PC
  while (Input.HasKeyboardMessage())
  {
    KeyboardMessage msg = Input.PopKeyboardMessage();

    if (msg.param == KEYPARAM_ESCAPE && msg.value == KEYVAL_DOWN)
      Application.RequestExit(0);
  }
#endif

#if USE_VIEWER
  static int i = 0;
  if (i == 0)
  {
    //if (!theViewer.onCreate("paladin.cfg"))
    if (!theViewer.onCreate("skeleton.cfg"))
    {
      exit(-1);
    }

    if (!theViewer.onInit())
    {
      exit(-1);
    }
    i = 1;
  }

  theViewer.onIdle();
#else

  m_pScene->Update(Application.GetFrameTime());

#endif
}


// ----------------------------------------------------------------------------
// Name: AnimationModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void AnimationModule::Cull()
{
}


// ----------------------------------------------------------------------------
// Name: AnimationModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void AnimationModule::Draw()
{
#if USE_VIEWER
  Device->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,77), 1.0f, 0 );
  Device->BeginScene();

  theViewer.onRender();

  Device->EndScene();
  Device->Present( NULL, NULL, NULL, NULL );  
#else
  Device->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(127,127,127), 1.0f, 0 );
  Device->BeginScene();

  m_pScene->Render();

  Device->EndScene();
  Device->Present( NULL, NULL, NULL, NULL );  
#endif

}


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void AnimationModule::Resize()
{
#if !USE_VIEWER
  m_pScene->SetRenderState();
#endif
}


// ----------------------------------------------------------------------------
// Name: AnimationModule::SetRenderState
// Desc: Set the render state for the module
// ----------------------------------------------------------------------------
void AnimationModule::SetRenderState()
{
#if USE_VIEWER
  RenderState.Set(D3DRS_LIGHTING, FALSE);
#else
  m_pScene->SetRenderState();
#endif
}


// -- EOF


