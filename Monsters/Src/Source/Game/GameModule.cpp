// ----------------------------------------------------------------------------
// File: GameModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Game/GameModule.h"
#include "MeshEditor/Resource.h"


// ----------------------------------------------------------------------------
// Register this module
// ----------------------------------------------------------------------------
REGISTER_MODULE(GameModule);


// ----------------------------------------------------------------------------
// Name: GameModule::GameModule
// Desc: Constructor
// ----------------------------------------------------------------------------
GameModule::GameModule()
{
  REF_COUNT_CTOR(GameModule);

  // Clear the existing file path
  FilePath.Clear();
  
  // Load the config file
  ConfigFile cfg;
  if (cfg.Load("..\\Data\\Config\\Game.cfg"))
  {
    // Get the section
    ConfigSection &section = cfg("FilePath");

    // Add the paths to the file path
    ConfigValueMap::iterator iter(section.Items.begin()), end(section.Items.end());
    for (; iter != end; ++iter)
      FilePath.Add((String) iter->second);
  } // if

  m_pMesh = NULL;
} // GameModule


// ----------------------------------------------------------------------------
// Name: GameModule::~GameModule
// Desc: Destructor
// ----------------------------------------------------------------------------
GameModule::~GameModule() 
{
  REF_COUNT_DTOR(GameModule);
  SafeUnRef(m_pMesh);
} // ~GameModule


// ----------------------------------------------------------------------------
// Name: GameModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool GameModule::Init()
{
  // Set the display state
  SetDisplayState();

  // Done
  return true;
} // Init


// ----------------------------------------------------------------------------
// Name: GameModule::CreateSafeObjects
// Desc: Create the safe objects
// ----------------------------------------------------------------------------
bool GameModule::CreateSafeObjects()
{
  return true;
} // CreateSafeObjects


// ----------------------------------------------------------------------------
// Name: GameModule::CreateDeviceObjects
// Desc: Create the device objects
// ----------------------------------------------------------------------------
bool GameModule::CreateDeviceObjects()
{
  m_pMesh = new IndexedMesh("Object");
  if (!m_pMesh->ImportFromX("room4.X"))
  {
    delete m_pMesh;
    m_pMesh = NULL;
    return false;
  } // if

  m_pMesh->Ref();

  const float spacing = 50.0f;
  const int rows      = 3;
  float startPos      = (spacing * rows) / -2.0f;

  for (uint x = 0; x < rows; x++)
  {
    for (uint z = 0; z < rows; z++)
    {
      CreateMeshInstance(m_pMesh, startPos + (spacing * x), 0.0f, startPos + (spacing * z));
    } // for
  } // for

  return true;
} // CreateDeviceObjects


// ----------------------------------------------------------------------------
// Name: GameModule::CreateMeshInstance
// Desc: Create a mesh instance
// Parm: Mesh *pMesh - the mesh
// Parm: float x     - the x position
// Parm: float y     - the y position
// Parm: float z     - the z position
// ----------------------------------------------------------------------------
void GameModule::CreateMeshInstance(Mesh *pMesh, float x, float y, float z)
{
  MeshInstance *pMeshInstance = pMesh->CreateInstance("", Matrix::MakeNewTranslation(x, y, z));
  m_MeshArray.push_back(pMeshInstance);
  pMeshInstance->Ref();
} // CreateMeshInstance


// ----------------------------------------------------------------------------
// Name: GameModule::ReleaseSafeObjects
// Desc: Release the safe objects
// ----------------------------------------------------------------------------
bool GameModule::ReleaseSafeObjects()
{
  return true;
} // ReleaseSafeObjects


// ----------------------------------------------------------------------------
// Name: GameModule::ReleaseDeviceObjects
// Desc: Release the device objects
// ----------------------------------------------------------------------------
bool GameModule::ReleaseDeviceObjects()
{
  UnRefArray<MeshInstance *>(m_MeshArray, true);
  m_VisibleList.clear();

  SafeUnRef(m_pMesh);
  m_pMesh = NULL;

  TextureLoader::GarbageCollect();
  MaterialLoader::GarbageCollect();

  return true;
} // ReleaseDeviceObjects


// ----------------------------------------------------------------------------
// Name: GameModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void GameModule::Shutdown()
{
} // Shutdown


// ----------------------------------------------------------------------------
// Name: GameModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void GameModule::App()
{
  Input &input   = ApplicationCentral.GetInput();
  Camera &camera = ApplicationCentral.GetCamera();

  //static bool once = true;
  //if (once && input.GetKeyboardState(Input::KEYPARAM_E) == Input::KEYVAL_DOWN)
  //{
  //  once = false;

  //  MFCDialogTest *pDialog = new MFCDialogTest();
  //  pDialog->Create(IDD_DIALOG1, MFCDisplay::GetWnd());

  //  pDialog->ShowWindow(SW_SHOW);
  //  //pDialog->DoModal();
  //} // if

  // Update the view matrix based on the mouse input
  while (input.HasMouseMessage())
  {
    // Get the next mouse message
    Input::MouseMessage msg = input.PopMouseMessage();

    // If the mouse has moved in the X axis
    if (msg.param == Input::MOUSEPARAM_MOVE_Y)
    {
      // If the left button is down
      if (input.GetMouseState(Input::MOUSEPARAM_BUTTON_0) == Input::MOUSEVAL_BUTTON_DOWN)
        camera.Rotate(D3DXToRadian(static_cast<float>(msg.value) * 8.0f), 0, 0);

      // If the right button is down
      else if (input.GetMouseState(Input::MOUSEPARAM_BUTTON_1) == Input::MOUSEVAL_BUTTON_DOWN)
      {
        Vec3 position = camera.GetPosition();
        position += (camera.GetLook() * -0.5f * static_cast<float>(msg.value));
        camera.SetPosition(position);
      } // else if
    } // if

    // If the mouse has moved in the Y axis
    else if (msg.param == Input::MOUSEPARAM_MOVE_X)
    {
      // If the left button is down
      if (input.GetMouseState(Input::MOUSEPARAM_BUTTON_0) == Input::MOUSEVAL_BUTTON_DOWN)
        camera.Rotate(0, D3DXToRadian(static_cast<float>(msg.value) * 8.0f), 0);
    } // if

    // If the mouse wheel has been scrolled
    if (msg.param == Input::MOUSEPARAM_MOVE_Z)
    {
        Vec3 position = camera.GetPosition();
        position += (camera.GetLook() * 0.25f * static_cast<float>(msg.value));
        camera.SetPosition(position);
    } // if

    // Perform vector regeneration to stop the camera from rolling
    Vec3 up    = camera.GetUp();
    Vec3 look  = camera.GetLook();
    Vec3 right = camera.GetRight();

    right.y    = 0.0f;
    right.Normalize();

    up.Set(0,1,0);

    // Set the camera vectors
    camera.SetView(look, up, right);
  } // while

  // Exit the application
  if (input.GetKeyboardState(Input::KEYPARAM_ESCAPE) == Input::KEYVAL_DOWN)
  {
    ApplicationCentral.RequestExit(0);
  } // if

  // Toggle fullscreen mode
  if (input.GetKeyboardState(Input::KEYPARAM_RETURN) == Input::KEYVAL_DOWN && 
      (input.GetKeyboardState(Input::KEYPARAM_LALT)  == Input::KEYVAL_DOWN ||
       input.GetKeyboardState(Input::KEYPARAM_RALT)  == Input::KEYVAL_DOWN))
  {
    ApplicationCentral.ToggleFullScreen();
  } // if
} // App


// ----------------------------------------------------------------------------
// Name: GameModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void GameModule::Cull()
{
  m_VisibleList.clear();

  MeshInstanceArray::iterator iter(m_MeshArray.begin()), end(m_MeshArray.end());
  for (; iter != end; ++iter)
  {
    MeshInstance *pMeshInstance = *iter;

    if (pMeshInstance->GetMesh()->IsVisible(pMeshInstance->GetMatrix(), ApplicationCentral.GetCamera().GetFrustum()))
      m_VisibleList.push_back(pMeshInstance);
  } // for
} // Cull


// ----------------------------------------------------------------------------
// Name: GameModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void GameModule::Draw()
{
  m_pDevice->BeginScene();
  m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFF7F7F7F, 1.0f, 0);

  MeshInstanceArray::iterator iter(m_VisibleList.begin()), end(m_VisibleList.end());
  for (; iter != end; ++iter)
  {
    MeshInstance *pMeshInstance = *iter;
    Mesh *pMesh   = pMeshInstance->GetMesh();
    Matrix matrix = pMeshInstance->GetMatrix();

    uint numSubsets = pMesh->GetNumSubsets();
    for (uint id = 0; id < numSubsets; id++)
    {
      const MeshSubset *pSubset = pMesh->GetSubset(id);

      const Material *pMaterial = pSubset->GetMaterial();

      pMaterial->Prepare(matrix, pSubset->GetColorMaterial(), pSubset->GetTextureArray());

      uint numPasses = pMaterial->Begin();
      for (uint i = 0; i < numPasses; i++)
      {
        pMaterial->BeginPass(i);

        if (pMesh->IsVisible(matrix, ApplicationCentral.GetCamera().GetFrustum()))
          pMesh->RenderSubset(id, i);

        pMaterial->EndPass();
      } // for
      pMaterial->End();
    } // for
  } // for

  m_pDevice->EndScene();
  m_pDevice->Present(0, 0, 0, 0);
} // Draw


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void GameModule::Resize()
{
  SetDisplayState();
} // Resize


// ----------------------------------------------------------------------------
// Name: TeapotModule::SetDisplayState
// Desc: Set the displays tate
// ----------------------------------------------------------------------------
void GameModule::SetDisplayState()
{
  // Set the render states
  m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

  // Get the new client rect
  RECT clientRect;
  ::GetClientRect(ApplicationCentral.GetHWND(), &clientRect);

  // Calculate the dimensions of the window
  int width  = clientRect.right  - clientRect.left;
  int height = clientRect.bottom - clientRect.top;

  // Calculate the aspect ratio
  float aspect = (float) width / (float) height;

  // Setup the eye and view vectors
  Vec3 eye(0.0f, 30.0f, 0.0f);
  Vec3  at(0.0f, 30.0f, 1.0f);
  Vec3  up(0.0f, 1.0f, 0.0f);
  ApplicationCentral.GetCamera().LookAt(eye, at, up);

  // Set the projection
  ApplicationCentral.GetCamera().SetProjPerspective(45.0f, aspect, 1.0f, 2000.0f);

  // Set the global ambient
  ApplicationCentral.GetGlobalAmbient() = Color(0.1f, 0.1f, 0.1f, 1.0f);

  // Set the directional light
  ApplicationCentral.GetDirectionalLight().ambient    = Color(0.1f, 0.1f, 0.1f, 1.0f);
  ApplicationCentral.GetDirectionalLight().diffuse    = Color(0.6f, 0.6f, 0.8f, 1.0f);
  ApplicationCentral.GetDirectionalLight().direction  = Vec3(-0.707f, -0.707f, 1.0f);
  ApplicationCentral.GetDirectionalLight().enabled    = true;
  ApplicationCentral.GetDirectionalLight().specular   = Color(0.9f, 0.9f, 0.9f, 1.0f);
  ApplicationCentral.GetDirectionalLight().power      = 64;
} // SetDisplayState


// -- EOF


