
// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/MFCDisplay.h"
#include "MeshEditor/MeshEditorModule.h"
#include "MeshEditor/MeshEditorApp.h"
#include "MeshEditor/MeshEditorMainFrame.h"
#include "MeshEditor/MeshEditorMainView.h"
#include "MeshEditor/MeshEditorMainDoc.h"
#include "MeshEditor/Resource.h"


// ----------------------------------------------------------------------------
// The Aplication Message Map
// ----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(MeshEditorApp, CWinApp)
  ON_COMMAND(ID_APP_EXIT,           OnAppExit)
  ON_COMMAND(ID_FILE_NEW,           CWinApp::OnFileNew)
  ON_COMMAND(ID_FILE_OPEN,          OnFileOpen)
  ON_COMMAND(ID_FILE_IMPORTFROMX,   OnImportFromX)
  ON_COMMAND(ID_FILE_CLOSE_MESH,    OnFileClose)
  ON_COMMAND(ID_FILE_SAVE_MESH,     OnFileSave)
  ON_COMMAND(ID_FILE_SAVE_MESH_AS,  OnFileSaveAs)
END_MESSAGE_MAP()


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::MeshEditorApp
// Desc: Constructor
// ----------------------------------------------------------------------------
MeshEditorApp::MeshEditorApp()
: CWinApp()
{
  REF_COUNT_CTOR(MeshEditorApp);
} // MeshEditorApp


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::~MeshEditorApp
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshEditorApp::~MeshEditorApp()
{
  delete m_pMainWnd;
  REF_COUNT_DTOR(MeshEditorApp);
} // ~MeshEditorApp


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::InitInstance
// Desc: Initialise the application instance
// Retn: BOOL - true if successful
// ----------------------------------------------------------------------------
BOOL MeshEditorApp::InitInstance()
{
  InitCommonControls();

  CWinApp::InitInstance();

  if (!AfxOleInit())
  {
    return FALSE;
  }
  AfxEnableControlContainer();

  SetRegistryKey(_T("Monsters MeshEditor"));
  LoadStdProfileSettings(4);

  CSingleDocTemplate *pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME,
    RUNTIME_CLASS(MeshEditorMainDoc),
    RUNTIME_CLASS(MeshEditorMainFrame),
    RUNTIME_CLASS(MeshEditorMainView));
  AddDocTemplate(pDocTemplate);

  CCommandLineInfo cmdInfo;
  ParseCommandLine(cmdInfo);
  cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;

  if (!ProcessShellCommand(cmdInfo))
    return FALSE;

  m_pMainWnd->ShowWindow(SW_SHOW);
  m_pMainWnd->UpdateWindow();

  return TRUE;
} // InitInstance


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::OnIdle
// Desc: Called for each frame
// ----------------------------------------------------------------------------
BOOL MeshEditorApp::OnIdle(LONG lCount)
{
  CWinApp::OnIdle(lCount);

  if (ApplicationCentral.IsInitialised())
  {
    if (ApplicationCentral.RunFrame())
      return TRUE;
    else
    {
      CWnd* pMainFrame = AfxGetMainWnd();
      if (pMainFrame)
        SendMessage(pMainFrame->GetSafeHwnd(), WM_QUIT, 0, 0);
      PostQuitMessage(0);
      return FALSE;
    } // else
  } // if

  return FALSE;
} // OnIdle


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::OnAppExit
// Desc: Callback for application exit
// ----------------------------------------------------------------------------
void MeshEditorApp::OnAppExit()
{
  MeshEditorModule::DisableMouseScope disableMouse;

  ApplicationCentral.RequestExit(0);
  CWinApp::OnAppExit();
} // OnAppExit


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::OnImportFromX
// Desc: Callback to import an x file
// ----------------------------------------------------------------------------
void MeshEditorApp::OnImportFromX()
{
  MeshEditorModule::DisableMouseScope disableMouse;
  
  CFileDialog dlg(TRUE, "*.X", 0, OFN_HIDEREADONLY|OFN_NOCHANGEDIR, "DirectX Files (*.x)|*.x|All Files (*.*)|*.*||", AfxGetMainWnd());
  if (dlg.DoModal() == IDCANCEL)
    return;

  String filename = dlg.GetPathName();
  {
    MeshEditorModule *pModule = reinterpret_cast<MeshEditorModule *>(MFCDisplay::GetModule());
    if (pModule)
    {
      if (!pModule->ImportFile(filename))
      {
        MessageBox(AfxGetMainWnd()->GetSafeHwnd(), "Import file failed", "Error", MB_ICONERROR | MB_OK);
      } // if
    } // if
  } // if
} // OnImportFromX


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::OnFileOpen
// Desc: Callback to open a file
// ----------------------------------------------------------------------------
void MeshEditorApp::OnFileOpen()
{
  MeshEditorModule::DisableMouseScope disableMouse;
  
  CFileDialog dlg(TRUE, "*.msh", 0, OFN_HIDEREADONLY|OFN_NOCHANGEDIR, "Mesh Files (*.msh)|*.msh|All Files (*.*)|*.*||", AfxGetMainWnd());
  if (dlg.DoModal() == IDCANCEL)
    return;

  String filename = dlg.GetFileName();
  //if (FilePath.LocateFile(filename))
  {
    MeshEditorModule *pModule = reinterpret_cast<MeshEditorModule *>(MFCDisplay::GetModule());
    if (pModule)
    {
      if (!pModule->OpenFile(filename))
      {
        MessageBox(AfxGetMainWnd()->GetSafeHwnd(), "Open file failed", "Error", MB_ICONERROR | MB_OK);
      } // if
    } // if
  } // if
} // OnFileOpen


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::OnFileClose
// Desc: Callback to close the open file
// ----------------------------------------------------------------------------
void MeshEditorApp::OnFileClose()
{
  MeshEditorModule::DisableMouseScope disableMouse;

  MeshEditorModule *pModule = reinterpret_cast<MeshEditorModule *>(MFCDisplay::GetModule());
  if (pModule)
  {
    if (!pModule->CloseFile())
    {
      MessageBox(AfxGetMainWnd()->GetSafeHwnd(), "Close file failed", "Error", MB_ICONERROR | MB_OK);
    } // if
  } // if
} // OnFileClose


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::OnFileSave
// Desc: Callback to save a file
// ----------------------------------------------------------------------------
void MeshEditorApp::OnFileSave()
{
  MeshEditorModule::DisableMouseScope disableMouse;

  MeshEditorModule *pModule = reinterpret_cast<MeshEditorModule *>(MFCDisplay::GetModule());
  if (pModule)
  {
    if (pModule->CanSave())
    {
      if (!pModule->SaveFile())
      {
        MessageBox(AfxGetMainWnd()->GetSafeHwnd(), "Save file failed", "Error", MB_ICONERROR | MB_OK);
      } // if
    } // if
    else
    {
      OnFileSaveAs();
    } // else
  } // if  
} // OnFileSave


// ----------------------------------------------------------------------------
// Name: MeshEditorApp::OnFileSaveAs
// Desc: Callback to save a file
// ----------------------------------------------------------------------------
void MeshEditorApp::OnFileSaveAs()
{
  MeshEditorModule::DisableMouseScope disableMouse;
   
  CFileDialog dlg(FALSE, "*.msh", 0, OFN_HIDEREADONLY|OFN_NOCHANGEDIR, "Mesh Files (*.msh)|*.msh|All Files (*.*)|*.*||", AfxGetMainWnd());
  if (dlg.DoModal() == IDCANCEL)
    return;

  String filename = dlg.GetFileName();

  MeshEditorModule *pModule = reinterpret_cast<MeshEditorModule *>(MFCDisplay::GetModule());
  if (pModule)
  {
    if (!pModule->SaveFileAs(filename))
    {
      MessageBox(AfxGetMainWnd()->GetSafeHwnd(), "Save file failed", "Error", MB_ICONERROR | MB_OK);
    } // if
  } // if
} // OnFileSaveAs


// -- EOF

