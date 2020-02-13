// ----------------------------------------------------------------------------
// File: MeshEditorMainFrame.cpp
// Desc: The main frame of the editor
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "MeshEditor/MeshEditorModule.h"
#include "MeshEditor/MeshEditorMainFrame.h"
#include "MeshEditor/Resource.h"


// ----------------------------------------------------------------------------
// The Frame Window Message Map
// ----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(MeshEditorMainFrame, CFrameWnd)
  ON_WM_CREATE()
END_MESSAGE_MAP()


// ----------------------------------------------------------------------------
// Dynamic creation
// ----------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(MeshEditorMainFrame, CFrameWnd)


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};



// ----------------------------------------------------------------------------
// Name: MeshEditorMainFrame::MeshEditorMainFrame
// Desc: Constructor
// ----------------------------------------------------------------------------
MeshEditorMainFrame::MeshEditorMainFrame()
: CFrameWnd()
{
  MFCDisplay::SetWnd(this);
} // MeshEditorMainFrame


// ----------------------------------------------------------------------------
// Name: MeshEditorMainFrame::~MeshEditorMainFrame
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshEditorMainFrame::~MeshEditorMainFrame()
{
} // ~MeshEditorMainFrame


// ----------------------------------------------------------------------------
// Create the frame's resources
// ----------------------------------------------------------------------------
int MeshEditorMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
    | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
  {
    TRACE0("Failed to create toolbar\n");
    return -1;
  }

  if (!m_wndStatusBar.Create(this) ||
    !m_wndStatusBar.SetIndicators(indicators,
    sizeof(indicators)/sizeof(UINT)))
  {
    TRACE0("Failed to create status bar\n");
    return -1;
  }

  // TODO: Delete these three lines if you don't want the toolbar to be dockable
  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndToolBar);

  return 0;
} // OnCreate


// ----------------------------------------------------------------------------
// Set the window style
// ----------------------------------------------------------------------------
BOOL MeshEditorMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  if(!CFrameWnd::PreCreateWindow(cs))
    return FALSE;

  return TRUE;
} // PreCreateWindow


// -- EOF

