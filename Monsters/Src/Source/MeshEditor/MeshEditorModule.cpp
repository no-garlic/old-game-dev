// ----------------------------------------------------------------------------
// File: MeshEditorModule.cpp
// Desc: The module that runs the game editor
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "MeshEditor/MeshEditorModule.h"
#include "MeshEditor/MeshEditorApp.h"
#include "MeshEditor/Resource.h"


// ----------------------------------------------------------------------------
// Register this module
// ----------------------------------------------------------------------------
REGISTER_MODULE(MeshEditorModule);


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::MeshEditorModule
// Desc: Constructor
// ----------------------------------------------------------------------------
MeshEditorModule::MeshEditorModule()
: m_Visible               (false),
  m_pMesh                 (NULL),
  m_pMaterialDialog       (NULL),
  m_pLightDialog          (NULL),
  m_MouseEnabled          (true),
  m_MouseOverMaterialDlg  (false),
  m_MaterialDlgShowing    (false),
  m_LightDlgShowing       (false)
{
  REF_COUNT_CTOR(MeshEditorModule);

  // Load the config file
  ConfigFile cfg;
  if (cfg.Load("..\\Data\\Config\\MeshEditor.cfg"))
  {
    // Get the section
    ConfigSection &section = cfg("FilePath");

    // Set the base path
    FileSystem.SetBasePath(section("BasePath"));

    // Set the file databases
    FileSystem.AddDatabase("Model",     section("Model"));
    FileSystem.AddDatabase("Texture",   section("Texture"));
    FileSystem.AddDatabase("Material",  section("Material"));
  } // if

  // Set teh MFC module
  MFCDisplay::SetModule(this);

  // Initialise the camera
  ResetCamera();

  // Initialise the model matrix
  m_ModelMatrix.Identity();
} // MeshEditorModule


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::~MeshEditorModule
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshEditorModule::~MeshEditorModule() 
{
  REF_COUNT_DTOR(MeshEditorModule);
  
  SafeUnRef(m_pMesh);

  if (m_pMaterialDialog)
    delete m_pMaterialDialog;

  if (m_pLightDialog)
    delete m_pLightDialog;
} // ~MeshEditorModule


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::ResetCamera
// Desc: Reset the camera
// ----------------------------------------------------------------------------
void MeshEditorModule::ResetCamera()
{
  m_CameraLook.Set(0.0f, 0.0f, -1.0f);
  m_CameraRight.Set(1.0f, 0.0f, 0.0f);
  m_CameraUp.Set(0.0f, 1.0f, 0.0f);
  m_CameraPos.Set(0.0f, 0.0f, 0.0f);

  if (m_pMesh)
  {
    float radius = m_pMesh->GetBSphere().GetRadius();
    m_CameraPos.Set(0.0f, 0.0f, radius * 2.5f);
  } // if

  ApplicationCentral.GetCamera().SetView(m_CameraPos, m_CameraLook, m_CameraUp, m_CameraRight);
} // ResetCamera


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::CreateApp
// Desc: Create the application
// Parm: DisplaySettings ds  - the display settings
// Retn: CWinApp *           - the application
// ----------------------------------------------------------------------------
CWinApp *MeshEditorModule::CreateApp(DisplaySettings ds)
{
  MFCDisplay::GetDisplaySettings() = ds;

  return new MeshEditorApp;
} // CreateApp


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::Init
// Desc: Initialise the module
// Retn: bool - true if all went ok
// ----------------------------------------------------------------------------
bool MeshEditorModule::Init()
{
  // Set the display state
  SetDisplayState();

  // Done
  return true;
} // Init


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::CreateSafeObjects
// Desc: Create the safe objects
// ----------------------------------------------------------------------------
bool MeshEditorModule::CreateSafeObjects()
{
  return true;
} // CreateSafeObjects


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::CreateDeviceObjects
// Desc: Create the device objects
// ----------------------------------------------------------------------------
bool MeshEditorModule::CreateDeviceObjects()
{
  if (m_OpenFile.empty())
    return true;

  String filename;
  String extension;
  String path;
  String name;
  SplitFilename(m_OpenFile, filename, extension);
  SplitPath(filename, path, name);

  if (m_pMesh)
    SafeUnRef(m_pMesh);

  if (extension == "X" || extension == "x")
  {
    m_pMesh = new IndexedMesh(name);
    if (!m_pMesh->ImportFromX(m_OpenFile))
    {
      delete m_pMesh;
      m_pMesh = NULL;
      return false;
    } // if

    String windowTitle = name + " - Monster MeshEditor";
    SetWindowText(AfxGetMainWnd()->GetSafeHwnd(), windowTitle.c_str());

    m_pMesh->Ref();

    if (m_pMaterialDialog)
      m_pMaterialDialog->Init(m_pMesh);
  } // if
  else
  {
    m_pMesh = new IndexedMesh(name);

    FileDatabase *pModelDB = FileSystem("Model");
    if (!pModelDB)
      return false;

    FileHandle handle = pModelDB->MakeFileHandle(m_OpenFile);

    if (!m_pMesh->Load(handle))
    {
      delete m_pMesh;
      m_pMesh = NULL;
      return false;
    } // if

    String windowTitle = name + " - Monster MeshEditor";
    SetWindowText(AfxGetMainWnd()->GetSafeHwnd(), windowTitle.c_str());

    m_pMesh->Ref();

    if (m_pMaterialDialog)
      m_pMaterialDialog->Init(m_pMesh);
  } // else

  ResetCamera();

  return true;
} // CreateDeviceObjects


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::ReleaseSafeObjects
// Desc: Release the safe objects
// ----------------------------------------------------------------------------
bool MeshEditorModule::ReleaseSafeObjects()
{
  return true;
} // ReleaseSafeObjects


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::ReleaseDeviceObjects
// Desc: Release the device objects
// ----------------------------------------------------------------------------
bool MeshEditorModule::ReleaseDeviceObjects()
{
  SafeUnRef(m_pMesh);
  m_pMesh = NULL;

  String windowTitle = "Untitled - Monster MeshEditor";
  SetWindowText(AfxGetMainWnd()->GetSafeHwnd(), windowTitle.c_str());

  TextureLoader::GarbageCollect();
  MaterialLoader::GarbageCollect();

  if (m_pMaterialDialog)
    m_pMaterialDialog->Release();

  return true;
} // ReleaseDeviceObjects


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::Shutdown
// Desc: Shutdown the module
// ----------------------------------------------------------------------------
void MeshEditorModule::Shutdown()
{
} // Shutdown


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::App
// Desc: App Process
// ----------------------------------------------------------------------------
void MeshEditorModule::App()
{
  Input &input   = ApplicationCentral.GetInput();
  Camera &camera = ApplicationCentral.GetCamera();

  // Update the view matrix based on the mouse input
  while (input.HasMouseMessage())
  {
    // Get the next mouse message
    Input::MouseMessage msg = input.PopMouseMessage();

    // Check mouse is in the window
    if (!m_MouseEnabled || !IsMouseOverGfx())
      continue;

    // If the mouse has moved in the X axis
    if (msg.param == Input::MOUSEPARAM_MOVE_X)
    {
      // If the left button is down
      if (input.GetMouseState(Input::MOUSEPARAM_BUTTON_0) == Input::MOUSEVAL_BUTTON_DOWN)
      {
        if (m_pMesh)
        {
          Matrix rotationMatrix = Matrix::MakeNewRotationYawPitchRoll(D3DXToRadian(static_cast<float>(-msg.value) * 0.5f), 0.0f, 0.0f);
          m_ModelMatrix.Multiply(rotationMatrix);
        } // if
      } // if

      // If the right button is down
      else if (input.GetMouseState(Input::MOUSEPARAM_BUTTON_1) == Input::MOUSEVAL_BUTTON_DOWN)
      {
        if (m_pMesh)
        {
        } // if
      } // else if
    } // if

    // If the mouse has moved in the Y axis
    else if (msg.param == Input::MOUSEPARAM_MOVE_Y)
    {
      // If the left button is down
      if (input.GetMouseState(Input::MOUSEPARAM_BUTTON_0) == Input::MOUSEVAL_BUTTON_DOWN)
      {
        if (m_pMesh)
        {
          Matrix rotationMatrix = Matrix::MakeNewRotationYawPitchRoll(0.0f, D3DXToRadian(static_cast<float>(msg.value) * 0.5f), 0.0f);
          m_ModelMatrix.Multiply(rotationMatrix);
        } // if
      } // if

      // If the right button is down
      else if (input.GetMouseState(Input::MOUSEPARAM_BUTTON_1) == Input::MOUSEVAL_BUTTON_DOWN)
      {
        if (m_pMesh)
        {
        } // if
      } // else if
    } // if

    // If the mouse wheel has been scrolled
    if (msg.param == Input::MOUSEPARAM_MOVE_Z)
    {
        m_CameraPos = camera.GetPosition();
        m_CameraPos += (camera.GetLook() * 0.25f * static_cast<float>(msg.value));
        camera.SetPosition(m_CameraPos);
    } // if

    // Perform vector regeneration to stop the camera from rolling
    m_CameraUp      = camera.GetUp();
    m_CameraLook    = camera.GetLook();
    m_CameraRight   = camera.GetRight();
    m_CameraRight.y = 0.0f;
    m_CameraRight.Normalize();
    m_CameraUp.Set(0, 1, 0);

    // Set the camera vectors
    camera.SetView(m_CameraPos, m_CameraLook, m_CameraUp, m_CameraRight);
  } // while

  while (input.HasKeyboardMessage())
  {
    Input::KeyboardMessage msg = input.PopKeyboardMessage();

    if (msg.value == Input::KEYVAL_DOWN)
    {
      switch (msg.param)
      {
      case Input::KEYPARAM_ESCAPE:
        {
          if (m_MaterialDlgShowing)
            ShowMaterialDialog(false);
          else if (m_LightDlgShowing)
            ShowLightDialog(false);
          else
            ApplicationCentral.RequestExit(0);
          break;
        } // case

      case Input::KEYPARAM_M:
        {
          ShowMaterialDialog(!m_MaterialDlgShowing);
          break;
        } // case

      case Input::KEYPARAM_L:
        {
          ShowLightDialog(!m_LightDlgShowing);
          break;
        } // case

      case Input::KEYPARAM_R:
        {
          ResetCamera();
          break;
        } // case
      } // switch
    } // if
  } // while
} // App


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::Cull
// Desc: Cull Process
// ----------------------------------------------------------------------------
void MeshEditorModule::Cull()
{
  m_Visible = (m_pMesh && m_pMesh->IsVisible(m_ModelMatrix, ApplicationCentral.GetCamera().GetFrustum()));
} // Cull


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::Draw
// Desc: Draw Process
// ----------------------------------------------------------------------------
void MeshEditorModule::Draw()
{
  m_pDevice->BeginScene();
  m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFF4F4F4F, 1.0f, 0);

  if (m_Visible)
  {
    uint numSubsets = m_pMesh->GetNumSubsets();
    for (uint id = 0; id < numSubsets; id++)
    {
      const MeshSubset *pSubset = m_pMesh->GetSubset(id);
      const Material *pMaterial = pSubset->GetMaterial();
      pMaterial->Prepare(m_ModelMatrix, pSubset->GetColorMaterial(), pSubset->GetTextureArray());

      uint numPasses = pMaterial->Begin();
      for (uint i = 0; i < numPasses; i++)
      {
        pMaterial->BeginPass(i);

        m_pMesh->RenderSubset(id, i);

        pMaterial->EndPass();
      } // for
      pMaterial->End();
    } // for
  } // if

  m_pDevice->EndScene();
  m_pDevice->Present(0, 0, 0, 0);
} // Draw


// ----------------------------------------------------------------------------
// The window has been resized
// ----------------------------------------------------------------------------
void MeshEditorModule::Resize()
{
  SetDisplayState();
} // Resize


// ----------------------------------------------------------------------------
// Name: TeapotModule::SetDisplayState
// Desc: Set the displays tate
// ----------------------------------------------------------------------------
void MeshEditorModule::SetDisplayState()
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
  ApplicationCentral.GetCamera().SetView(m_CameraPos, m_CameraLook, m_CameraUp, m_CameraRight);

  // Set the projection
  ApplicationCentral.GetCamera().SetProjPerspective(45.0f, aspect, 1.0f, 2000.0f);

  // Set the global ambient
  ApplicationCentral.GetGlobalAmbient() = Color(0.1f, 0.1f, 0.1f, 1.0f);

  // Set the directional light
  ApplicationCentral.GetDirectionalLight().ambient    = Color(0.1f, 0.1f, 0.1f, 1.0f);
  ApplicationCentral.GetDirectionalLight().diffuse    = Color(0.6f, 0.6f, 0.8f, 1.0f);
  ApplicationCentral.GetDirectionalLight().direction  = Vec3(-1.0f, -1.0f, -1.0f).Normalize();
  ApplicationCentral.GetDirectionalLight().enabled    = true;
  ApplicationCentral.GetDirectionalLight().specular   = Color(0.9f, 0.9f, 0.9f, 1.0f);
  ApplicationCentral.GetDirectionalLight().power      = 64;
} // SetDisplayState


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::IsMouseOverWindow
// Desc: Check if the mouse is over the window
// Parm: HWND window - the window
// ----------------------------------------------------------------------------
bool MeshEditorModule::IsMouseOverWindow(HWND window)
{
  // Get the mouse position
  POINT pos;
  GetCursorPos(&pos);

  // Get the window rect
  RECT rect;
  GetWindowRect(window, &rect);

  // If the mouse is out of the window return false
  if (pos.x > rect.right || pos.x < rect.left || pos.y < rect.top || pos.y > rect.bottom)
    return false;

  return true;
} // IsMouseOverWindow


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::MouseIsOverGfx
// Desc: See if the mouse is over the graphics
// ----------------------------------------------------------------------------
bool MeshEditorModule::IsMouseOverGfx()
{
  // Check the main window
  if (!IsMouseOverWindow(ApplicationCentral.GetHWND()))
    return false;

  // Check the material dialog
  if (m_MaterialDlgShowing)
  {
    if (IsMouseOverWindow(m_pMaterialDialog->GetSafeHwnd()))
    {
      if (!m_MouseOverMaterialDlg)
      {
        // Set the material dialog as the focus window
        m_pMaterialDialog->SetFocus();
        m_MouseOverMaterialDlg = true;
        m_MouseOverLightDlg = false;
      } // if

      return false;
    } // if
  } // if

  // Check the light dialog
  if (m_LightDlgShowing)
  {
    if (IsMouseOverWindow(m_pLightDialog->GetSafeHwnd()))
    {
      if (!m_MouseOverLightDlg)
      {
        // Set the material dialog as the focus window
        m_pLightDialog->SetFocus();
        m_MouseOverLightDlg = true;
        m_MouseOverMaterialDlg = false;
      } // if

      return false;
    } // if
  } // if

  // Set focus to the main window
  if (m_MouseOverMaterialDlg || m_MouseOverLightDlg)
  {
    // Set the main windos as the focus window
    AfxGetMainWnd()->SetFocus();
    m_MouseOverMaterialDlg = false;
    m_MouseOverLightDlg    = false;
  } // if

  return true;
} // MouseIsOverGfx


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::OpenFile
// Desc: Open the given file
// Parm: const String &filename - the filename of the file to open
// ----------------------------------------------------------------------------
bool MeshEditorModule::OpenFile(const String &filename)
{
  DisableMouseScope disableMouse;

  if (m_pMesh)
  {
    if (!ReleaseDeviceObjects())
      return false;
  } // if

  m_OpenFile = filename;

  String path;
  SplitPath(m_OpenFile, path, m_SaveFile);
  
  ResetCamera();

  return CreateDeviceObjects();
} // OpenFile


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::ImportFile
// Desc: Import a file from the given DirectX file
// Parm: const String &filename - the filename
// ----------------------------------------------------------------------------
bool MeshEditorModule::ImportFile(const String &filename)
{
  DisableMouseScope disableMouse;

  if (m_pMesh)
  {
    if (!ReleaseDeviceObjects())
      return false;
  } // if

  m_OpenFile = filename;
  m_SaveFile.clear();

  ResetCamera();

  return CreateDeviceObjects();
} // ImportFile


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::SaveFileAs
// Desc: Save the file to a mesh file with the given filename
// Parm: const String &filename - the filename
// ----------------------------------------------------------------------------
bool MeshEditorModule::SaveFileAs(const String &filename)
{
  if (m_pMesh)
  {
    m_SaveFile = filename;
    return SaveFile();
  } // if

  return false;
} // SaveFileAs


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::SaveFile
// Desc: Save the file to a mesh file
// ----------------------------------------------------------------------------
bool MeshEditorModule::SaveFile()
{
  if (m_pMesh)
  {
    if (m_SaveFile.length())
    {
      FileDatabase *pModelDB = FileSystem("Model");
      if (!pModelDB)
        return false;

      FileHandle handle = pModelDB->MakeFileHandle(m_SaveFile);

      return m_pMesh->Save(handle);
    } // if
  } // if

  return false;
} // SaveFile


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::CloseFile
// Desc: Close the open file
// ----------------------------------------------------------------------------
bool MeshEditorModule::CloseFile()
{
  m_OpenFile.clear();
  m_SaveFile.clear();

  return ReleaseDeviceObjects();
} // CloseFile


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::ShowMaterialDialog
// Desc: Show the material dialog
// Parm: bool enabled - true to show it, false to hide
// ----------------------------------------------------------------------------
void MeshEditorModule::ShowMaterialDialog(bool enabled)
{
  if (!m_pMaterialDialog)
  {
    m_pMaterialDialog = new MeshMaterialDialog();
    m_pMaterialDialog->Create(IDD_MATERIAL_EDITOR);
    m_pMaterialDialog->Init(m_pMesh);
  } // if

  if (enabled)
  {
    m_MaterialDlgShowing = true;
    m_LightDlgShowing    = false;

    m_pMaterialDialog->ShowWindow(SW_SHOW);

    if (m_pLightDialog)
      m_pLightDialog->ShowWindow(SW_HIDE);
  } // if
  else
  {
    m_MaterialDlgShowing = false;
    m_pMaterialDialog->ShowWindow(SW_HIDE);
  } // else
} // ShowMaterialDialog


// ----------------------------------------------------------------------------
// Name: MeshEditorModule::ShowLightDialog
// Desc: Show the light dialog
// Parm: bool enabled - true to show it, false to hide it
// ----------------------------------------------------------------------------
void MeshEditorModule::ShowLightDialog(bool enabled)
{
  if (!m_pLightDialog)
  {
    m_pLightDialog = new MeshLightDialog();
    m_pLightDialog->Create(IDD_LIGHT_EDITOR);
    m_pLightDialog->Init();
  } // if

  if (enabled)
  {
    m_LightDlgShowing    = true;
    m_MaterialDlgShowing = false;

    m_pLightDialog->ShowWindow(SW_SHOW);

    if (m_pMaterialDialog)
      m_pMaterialDialog->ShowWindow(SW_HIDE);
  } // if
  else
  {
    m_LightDlgShowing = false;
    m_pLightDialog->ShowWindow(SW_HIDE);
  } // else
} // ShowLightDialog


// -- EOF


