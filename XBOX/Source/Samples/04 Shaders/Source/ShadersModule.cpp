// ----------------------------------------------------------------------------
// File: ShadersModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "ShadersModule.h"


// ----------------------------------------------------------------------------
// Name: ShadersModule::ShadersModule
// Desc: Constructor
// ----------------------------------------------------------------------------
ShadersModule::ShadersModule(const String &name)
: BaseModuleType    (name),
  m_pSceneNode      (NULL),
  m_pTransformNode  (NULL),
  m_pMeshNode       (NULL),
  m_pMaterial       (NULL)
{
  REF_COUNT_CTOR(ShadersModule);
}


// ----------------------------------------------------------------------------
// Name: ShadersModule::~ShadersModule
// Desc: Destructor
// ----------------------------------------------------------------------------
ShadersModule::~ShadersModule() 
{
  REF_COUNT_DTOR(ShadersModule);
}


// ----------------------------------------------------------------------------
// Name: ShadersModule::SetDisplaySettings
// Desc: Set the module's display settings
// Retn: bool - true if the settings were set
// ----------------------------------------------------------------------------
bool ShadersModule::SetDisplaySettings(DisplaySettings &settings)
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
// Name: ShadersModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool ShadersModule::Init()
{
  LOG_INFO << "*** Init()" << ENDLOG;

  // Search the model database for the mesh file
  FileHandle handle = Application.GetModelDatabase()->FindFileHandle("chest.msh");
  if (!handle.Exists())
  {
    LOG_ERROR << "Failed to find the mesh: " << handle << ENDLOG;
    return false;
  }

  // Create our material and load the shaders
  m_pMaterial = new OneTexShaderMaterial();
  if (!m_pMaterial->Load())
    return false;

  // Load the mesh (and related textures, materials, etc)
  Mesh *pMesh = MeshLoader::LoadMesh(handle);
  if (pMesh)
  {
    // Iterate through our mesh and set the one texture shader material 
    // to be the material for each.
    for (uint i = 0; i < pMesh->GetNumSubsets(); i++)
    {
      MeshSubset *pSubset = pMesh->GetSubset(i);
      pSubset->SetMaterial(m_pMaterial);
    }

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
// Name: ShadersModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void ShadersModule::Shutdown()
{
  // Deleting the root node of a scene will delete all child nodes aswell, and
  // release the references on any meshes.
  delete m_pSceneNode;

  // Delete the mateiral
  delete m_pMaterial;

  // Any meshes no longer used by a scene can now be deleted
  MeshLoader::GarbageCollect();

  // Any textures no longer used (by meshes) can now be deleted
  TextureLoader::GarbageCollect();
}


// ----------------------------------------------------------------------------
// Name: ShadersModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void ShadersModule::App()
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
// Name: ShadersModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void ShadersModule::Cull()
{
  // Cull the scene and add the visible meshes to the render list
  m_pSceneNode->Cull(m_RenderList, Camera.GetFrustum());
}


// ----------------------------------------------------------------------------
// Name: ShadersModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void ShadersModule::Draw()
{
#if XBOX
  ulong clearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
#else
  ulong clearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
#endif

  // Begin rendering and clear the buffer
  Device->BeginScene();
  Device->Clear(0, 0, clearFlags, Color::Black, 1.0f, 0);

  // Render the visible meshes
  LightArray lights;
  m_RenderList.Render(lights);

  // Done rendering
  Device->EndScene();
  Device->Present(0, 0, 0, 0);
}


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void ShadersModule::Resize()
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
// Name: ShadersModule::SetRenderState
// Desc: Set the render state for the module
// ----------------------------------------------------------------------------
void ShadersModule::SetRenderState()
{
  LOG_INFO << "*** SetRenderState()" << ENDLOG;

  DirectionalLight light(Vec3(0.5f, -0.7f, 0.7f));
  Device->SetLight(0, &light);
  Device->LightEnable(0, TRUE);
  RenderState.Set(D3DRS_LIGHTING, TRUE);
}


// -- EOF


