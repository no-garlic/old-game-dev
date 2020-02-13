// ----------------------------------------------------------------------------
// File: MFCDisplay.h
// Desc: Wrapper for a single view MFC application
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// includes
// ----------------------------------------------------------------------------
#include "Engine/MFCDisplay.h"


// ----------------------------------------------------------------------------
// Only include this file if MFC is enabled
// ----------------------------------------------------------------------------
#ifdef __MFC_ENABLED


// ----------------------------------------------------------------------------
// Static initialisers
// ----------------------------------------------------------------------------
DisplaySettings         MFCDisplay::s_DisplaySettings;
CWinApp                *MFCDisplay::s_pApplication = 0;
CWnd                   *MFCDisplay::s_pWnd         = 0;
ApplicationModule_MFC  *MFCDisplay::s_pModule      = 0;


// ----------------------------------------------------------------------------
// The application isntance
// ----------------------------------------------------------------------------
//MFC_Application theApp;


// ----------------------------------------------------------------------------
// The Aplication Message Map
// ----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(MFC_Application, CWinApp)
END_MESSAGE_MAP()


// ----------------------------------------------------------------------------
// The Frame Window Message Map
// ----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(MFC_MainFrame, CFrameWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// ----------------------------------------------------------------------------
// Dynamic creation
// ----------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(MFC_MainFrame, CFrameWnd)


// ----------------------------------------------------------------------------
// Name: MFC_Application::MFC_Application
// Desc: Constructor
// ----------------------------------------------------------------------------
MFC_Application::MFC_Application()
: CWinApp()
{
  REF_COUNT_CTOR(MFC_Application);
} // MFC_Application


// ----------------------------------------------------------------------------
// Name: MFC_Application::~MFC_Application
// Desc: Destructor
// ----------------------------------------------------------------------------
MFC_Application::~MFC_Application()
{
  REF_COUNT_DTOR(MFC_Application);
} // ~MFC_Application


// ----------------------------------------------------------------------------
// Name: MFC_Application::InitInstance
// Desc: Initialise the application instance
// Retn: BOOL - true if successful
// ----------------------------------------------------------------------------
BOOL MFC_Application::InitInstance()
{
  // Derived function
  if (CWinApp::InitInstance() == FALSE)
    return FALSE;

  // Create our main frame
  MFC_MainFrame *pFrame = new MFC_MainFrame();
  if (!pFrame->Create(NULL, "Application", FWS_ADDTOTITLE | WS_OVERLAPPEDWINDOW, CRect(0, 0, 400, 300), NULL, NULL, NULL))
    return FALSE;

  // Show the window
  pFrame->ShowWindow(SW_SHOW);
  pFrame->UpdateWindow();

  // Assign the main frame
  m_pMainWnd = pFrame;

  // Create the display
  // This needs fixing
  if (!ApplicationCentral.Init(pFrame->GetSafeHwnd(), MFCDisplay::GetModule()))
    return FALSE;

  return TRUE;
} // InitInstance


// ----------------------------------------------------------------------------
// Name: MFC_Application::OnIdle
// Desc: Called for each frame
// ----------------------------------------------------------------------------
BOOL MFC_Application::OnIdle(LONG lCount)
{
  if (ApplicationCentral.IsInitialised())
  {
    if (ApplicationCentral.RunFrame())
      return TRUE;
    else
      exit(0);
      //return FALSE;
  } // if

  return FALSE;
} // OnIdle


// ----------------------------------------------------------------------------
// Name: MFC_MainFrame::MFC_MainFrame
// Desc: Constructor
// ----------------------------------------------------------------------------
MFC_MainFrame::MFC_MainFrame()
: CFrameWnd()
{
  MFCDisplay::SetWnd(this);
} // MFC_MainFrame


// ----------------------------------------------------------------------------
// Name: MFC_MainFrame::~MFC_MainFrame
// Desc: Destructor
// ----------------------------------------------------------------------------
MFC_MainFrame::~MFC_MainFrame()
{
} // ~MFC_MainFrame


// ----------------------------------------------------------------------------
// Handle a size change
// ----------------------------------------------------------------------------
void MFC_MainFrame::OnSize(UINT nType, int cx, int cy)
{
  ApplicationCentral.ResizeDisplay();
} // OnSize


// ----------------------------------------------------------------------------
// Name: MFC_MainFrame::OnCreateClient
// Desc: Called to create the frame window
// ----------------------------------------------------------------------------
BOOL MFC_MainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
  return TRUE;
} // OnCreateClient


// ----------------------------------------------------------------------------
// Name: MFCDisplay::SetApp
// Desc: Set the application
// ----------------------------------------------------------------------------
void MFCDisplay::SetApp(CWinApp *pApp)
{
  s_pApplication = pApp;
  atexit(&MFCDisplay::DestroyApp);
} // SetApp


// ----------------------------------------------------------------------------
// Name: MFCDisplay::DestroyApp
// Desc: Destroy teh application
// ----------------------------------------------------------------------------
void MFCDisplay::DestroyApp()
{
  delete s_pApplication;

  s_pApplication = 0;
  s_pWnd         = 0;
} // DestroyApp


// ----------------------------------------------------------------------------
// Only include this file if MFC is enabled
// ----------------------------------------------------------------------------
#endif // __MFC_ENABLED


// -- EOF


