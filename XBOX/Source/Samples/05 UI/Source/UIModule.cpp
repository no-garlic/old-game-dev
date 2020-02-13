// ----------------------------------------------------------------------------
// File: UIModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "UIModule.h"


// ----------------------------------------------------------------------------
// Name: UIModule::UIModule
// Desc: Constructor
// ----------------------------------------------------------------------------
UIModule::UIModule(const String &name)
: BaseModuleType    (name),
  m_pSceneNode      (NULL),
  m_pTransformNode  (NULL),
  m_pMeshNode       (NULL),
  m_pUI             (NULL)
{
  REF_COUNT_CTOR(UIModule);
}


// ----------------------------------------------------------------------------
// Name: UIModule::~UIModule
// Desc: Destructor
// ----------------------------------------------------------------------------
UIModule::~UIModule() 
{
  REF_COUNT_DTOR(UIModule);
}


// ----------------------------------------------------------------------------
// Name: UIModule::SetDisplaySettings
// Desc: Set the module's display settings
// Retn: bool - true if the settings were set
// ----------------------------------------------------------------------------
bool UIModule::SetDisplaySettings(DisplaySettings &settings)
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
// Name: UIModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool UIModule::Init()
{
  LOG_INFO << "*** Init()" << ENDLOG;

  if (!CreateScene())
    return false;

  if (!CreateUI())
    return false;

  return true;
}


// ----------------------------------------------------------------------------
// Name: UIModule::CreateScene
// Desc: Create the scene
// ----------------------------------------------------------------------------
bool UIModule::CreateScene()
{
  // Search the model database for the mesh file
  FileHandle handle = Application.GetModelDatabase()->FindFileHandle("chest.msh");
  if (!handle.Exists())
  {
    LOG_ERROR << "Failed to find the mesh: " << handle << ENDLOG;
    return false;
  }

  // Load the mesh (and related textures, materials, etc)
  Mesh *pMesh = MeshLoader::LoadMesh(handle);
  if (pMesh)
  {
    // Create the scenegraph nodes
    m_pSceneNode     = new SceneNode();
    m_pTransformNode = new TransformNode();
    m_pMeshNode      = new MeshNode();

    // Link the scene nodes
    m_pSceneNode->AddChild(m_pTransformNode);
    m_pTransformNode->AddChild(m_pMeshNode);

    // Add the mesh to the scene
    m_pMeshNode->AddMesh(pMesh);

    // Done
    LOG_INFO << "Loaded the mesh: " << handle << ENDLOG;
    return true;
  }

  // The mesh did not load correctly
  LOG_ERROR << "Failed to load the mesh: " << handle << ENDLOG;
  return false;
}


// ----------------------------------------------------------------------------
// Name: UIModule::CreateUI
// Desc: Create the user interface
// ----------------------------------------------------------------------------
bool UIModule::CreateUI()
{
  // Create the user interface
  m_pUI = new UI(256, 256);

  // Create a default font
  UIFontID fontId = m_pUI->AddFont("Default", "Jhengh.tga", "Jhengh.dat");
  if (fontId == InvalidFont)
  {
    LOG_ERROR << "Failed to create the default font" << ENDLOG;
    return false;
  }

  // Create one layer
  UILayer *pLayer = m_pUI->AddLayer(0, "DefaultLayer");
  NULL_ASSERT(pLayer);
  pLayer->SetVisible(true);

  // Load an image texture
  FileHandle handle = Application.GetTextureDatabase()->FindFileHandle("Arial.bmp");
  Texture *pTexture = TextureLoader::LoadTexture(handle);
  if (!pTexture)
  {
    LOG_ERROR << "Failed to load the ui texture from the file: " << handle << ENDLOG;
    return false;
  }

  // Create an image component
  UIImage *pImage = new UIImage("Image");
  pImage->SetPosition(10, 10);
  pImage->SetSize(64, 64);
  pImage->SetTexture(pTexture, Rect(0, 0, 512, 512));
  pImage->SetVisible(true);
  pLayer->AddComponent(pImage);

  // Create a text component
  UIText *pText = new UIText("Text");
  pText->SetText("Hello World");
  pText->SetFont(fontId);
  pText->SetFormat(FMT_LEFT|FMT_BOTTOM);
  pText->SetColor(Color::Green);
  pText->SetHeight(10);
  pText->SetPosition(80, 10);
  pText->SetVisible(true);
  pLayer->AddComponent(pText);

  return true;
}


// ----------------------------------------------------------------------------
// Name: UIModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void UIModule::Shutdown()
{
  // Deleting the root node of a scene will delete all child nodes aswell, and
  // release the references on any meshes.
  delete m_pSceneNode;

  // Delete the user interface
  delete m_pUI;

  // Any meshes no longer used by a scene can now be deleted
  MeshLoader::GarbageCollect();

  // Any textures no longer used (by meshes) can now be deleted
  TextureLoader::GarbageCollect();
}


// ----------------------------------------------------------------------------
// Name: UIModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void UIModule::App()
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
  // Animate the transform node based on the application running time (it will 
  // rotate once per 3.142 seconds).
  float runTime = Application.GetRunningTime();
  Matrix rotationMatrix = Matrix::MakeNewRotationYawPitchRoll(runTime, 0.0f, 0.0f);

  // Set the transform node's matrix
  m_pTransformNode->SetTransform(rotationMatrix);
}


// ----------------------------------------------------------------------------
// Name: UIModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void UIModule::Cull()
{
  // Cull the scene and add the visible meshes to the render list
  m_pSceneNode->Cull(m_RenderList, Camera.GetFrustum());
}


// ----------------------------------------------------------------------------
// Name: UIModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void UIModule::Draw()
{
#if XBOX
  ulong clearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
#else
  ulong clearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
#endif

  // Begin rendering and clear the buffer
  Device->BeginScene();
  Device->Clear(0, 0, clearFlags, Color(0.3f, 0.3f, 0.3f), 1.0f, 0);

  // Render the visible meshes
  LightArray lights;
  m_RenderList.Render(lights);

  // Render the UI
  m_pUI->Render();

  // Done rendering
  Device->EndScene();
  Device->Present(0, 0, 0, 0);
}


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void UIModule::Resize()
{
  LOG_INFO << "*** Resize()" << ENDLOG;

  if (m_pSceneNode)
  {
    // Set the camera to look at the mesh
    Sphere sphere = m_pSceneNode->GetBSphere();

    // Get the aspect ratio of the main window
    float aspect = Application.CalculateAspectRatio();
    float fov = 45.0f;

    // Get the distance from the sphere center (*1.05) where the entire sphere
    // is visible within the frustum fov.
    float theta = D3DXToRadian(fov * 0.5f);
    float d = 1.05 * (sphere.radius / atan(theta));

    // Set the global camera perspective projection (proj matrix)
    Camera.SetProjPerspective(fov, aspect, d * 0.001f, d * 2.0f);

    // Set the global camera lookat vectors (view matrix)
    Vec3 eye = sphere.center + Vec3(0.0f, 0.0f, -d);
    Vec3  at = sphere.center;
    Vec3  up(0.0f, 1.0f, 0.0f);
    Camera.LookAt(eye, at, up);
  }
}


// ----------------------------------------------------------------------------
// Name: UIModule::SetRenderState
// Desc: Set the render state for the module
// ----------------------------------------------------------------------------
void UIModule::SetRenderState()
{
  LOG_INFO << "*** SetRenderState()" << ENDLOG;

  DirectionalLight light(Vec3(0.5f, -0.7f, 0.7f));
  Device->SetLight(0, &light);
  Device->LightEnable(0, TRUE);
  RenderState.Set(D3DRS_LIGHTING, TRUE);
}


// -- EOF


