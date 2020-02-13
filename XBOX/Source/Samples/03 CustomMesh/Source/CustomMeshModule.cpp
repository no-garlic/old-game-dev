// ----------------------------------------------------------------------------
// File: CustomMeshModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "CustomMeshModule.h"


// ----------------------------------------------------------------------------
// Name: CustomMeshModule::CustomMeshModule
// Desc: Constructor
// ----------------------------------------------------------------------------
CustomMeshModule::CustomMeshModule(const String &name)
: BaseModuleType    (name),
  m_pSceneNode      (NULL),
  m_pTransformNode  (NULL),
  m_pMeshNode       (NULL)
{
  REF_COUNT_CTOR(CustomMeshModule);
}


// ----------------------------------------------------------------------------
// Name: CustomMeshModule::~CustomMeshModule
// Desc: Destructor
// ----------------------------------------------------------------------------
CustomMeshModule::~CustomMeshModule() 
{
  REF_COUNT_DTOR(CustomMeshModule);
}


// ----------------------------------------------------------------------------
// Name: CustomMeshModule::SetDisplaySettings
// Desc: Set the module's display settings
// Retn: bool - true if the settings were set
// ----------------------------------------------------------------------------
bool CustomMeshModule::SetDisplaySettings(DisplaySettings &settings)
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
// Name: CustomMeshModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool CustomMeshModule::Init()
{
  // Get the vertex type we want to use for our mesh (Position + Color)
  const VertexType *pVertexType = VertexTypeCache::GetVertexType("VertexType_PC");
  NULL_ASSERT(pVertexType);

  // Create the mesh (it will be deleted (de-referenced) when the scenegraph is deleted).
  IndexedMesh *pMesh = new IndexedMesh("MyMesh", pVertexType);

  // The number of segments in our color wheel
  const uint numSegments = 32;

  // Allocate some faces and vertices in the mesh
  pMesh->SetNumFaces(numSegments);
  pMesh->SetNumVerts(numSegments + 1);

  // Assign the faces
  IndexedMesh::Face *pFaces = pMesh->GetFaceData();
  for (uint i = 0; i < numSegments; i++)
  {
    uint a = ((i + 1) > numSegments ? 1 : (i + 1));
    uint b = ((a + 1) > numSegments ? 1 : (a + 1));
    pFaces[i].Assign(0, a, b);
  }

  // Color index array
  Color cols[] = { Color(1,1,1), Color(1,0,0), Color(1,1,0), Color(0,1,0), Color(0,1,1), Color(0,0,1), Color(1,0,1), Color(1,0,0) };

  // Get the vertex data (cast to the Position + Color vertex type)
  VT_PC *pVertexData = (VT_PC *) pMesh->GetVertexData();

  // Assign the center vertex
  pVertexData[0].pos = Vec3(0.0f, 0.0f, 0.0f);
  pVertexData[0].col = cols[0];

  // Assign the edge vertices
  for (uint i = 1; i < numSegments + 1; i++)
  {
    uint numVerts = numSegments + 1;
    float index = (float) i;
    float theta = 2.0f * PI * ((index - 1.0f) / numVerts);

    // Set the vertex position
    pVertexData[i].pos = Vec3(100.0f * sinf(theta), 100.0f * cosf(theta), 0.0f);

    // Which sixth is the point in?
    float segment = 6.0f * (index / numVerts);
    int a = 1 + (int) segment;
    int b = a + 1;

    // Interpolate between the two colors
    float lerp = segment - (int) segment;
    Color col;
    col.Lerp(cols[a], cols[b], lerp);

    // Set the vertex color
    pVertexData[i].col = col;
  }

  // Mark the vertex buffer and index buffer data dirty
  pMesh->SetDirty(true, true);

  // Get the fixed function material to use
  const Material *pMaterial = MaterialCache::GetMaterial("FixedFunctionMaterial_PC");
  NULL_ASSERT(pMaterial);

  // Set the color material
  D3DMATERIAL colorMaterial;
  colorMaterial.Ambient = Color(0.1f, 0.1f, 0.1f);
  colorMaterial.Diffuse = Color(0.9f, 0.9f, 0.9f);

  // Create a mesh subset (a render call) for the mesh
  MeshSubset *pSubset = pMesh->AddSubset();
  pSubset->SetFaceStart(0);
  pSubset->SetFaceCount(numSegments);
  pSubset->SetMaterial(pMaterial);
  pSubset->SetColorMaterial(colorMaterial);

  // Set the camera to look at the mesh
  Sphere sphere = pMesh->GetBSphere();

  // Get the aspect ratio of the main window
  float aspect = Application.CalculateAspectRatio();
  float fov = 45.0f;

  // Get the distance from the sphere center (*1.05) where the entire sphere
  // is visible within the frustum fov.
  float theta = D3DXToRadian(fov * 0.5f);
  float d = 1.05 * (sphere.radius / atan(theta));

  // Set the global camera perspective projection (proj matrix)
  Camera.SetProjPerspective(fov, aspect, d * 0.001f, d);

  // Set the global camera lookat vectors (view matrix)
  Vec3 eye = sphere.center + Vec3(0.0f, 0.0f, -d);
  Vec3  at = sphere.center;
  Vec3  up(0.0f, 1.0f, 0.0f);
  Camera.LookAt(eye, at, up);

  // Create the scenegraph nodes
  m_pSceneNode     = new SceneNode();
  m_pTransformNode = new TransformNode();
  m_pMeshNode      = new MeshNode();

  // Link the scene nodes
  m_pSceneNode->AddChild(m_pTransformNode);
  m_pTransformNode->AddChild(m_pMeshNode);

  // Add the mesh to the scene
  m_pMeshNode->AddMesh(pMesh);
  return true;
}


// ----------------------------------------------------------------------------
// Name: CustomMeshModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void CustomMeshModule::Shutdown()
{
  // Deleting the root node of a scene will delete all child nodes aswell, and
  // release the references on any meshes.
  delete m_pSceneNode;

  // Any meshes no longer used by a scene can now be deleted
  MeshLoader::GarbageCollect();

  // Any textures no longer used (by meshes) can now be deleted
  TextureLoader::GarbageCollect();
}


// ----------------------------------------------------------------------------
// Name: CustomMeshModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void CustomMeshModule::App()
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
  // rotate once per second).
  float runTime = Application.GetRunningTime();
  Matrix rotationMatrix = Matrix::MakeNewRotationYawPitchRoll(0.0f, 0.0f, runTime * PI * 2.0f);

  // Set the transform node's matrix
  m_pTransformNode->SetTransform(rotationMatrix);
}


// ----------------------------------------------------------------------------
// Name: CustomMeshModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void CustomMeshModule::Cull()
{
  // Cull the scene and add the visible meshes to the render list
  m_pSceneNode->Cull(m_RenderList, Camera.GetFrustum());
}


// ----------------------------------------------------------------------------
// Name: CustomMeshModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void CustomMeshModule::Draw()
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
void CustomMeshModule::Resize()
{
}


// ----------------------------------------------------------------------------
// Name: CustomMeshModule::SetRenderState
// Desc: Set the render state for the module
// ----------------------------------------------------------------------------
void CustomMeshModule::SetRenderState()
{
  RenderState.Set(D3DRS_LIGHTING, FALSE);
}


// -- EOF


