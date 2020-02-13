// ----------------------------------------------------------------------------
// File: WxDisplay.h
// Desc: Wrapper for a single view Wx application
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// includes
// ----------------------------------------------------------------------------
#include "wxWindows/wxDisplay.h"
#include "ApplicationModule_Wx.h"


// ----------------------------------------------------------------------------
// Static initializers
// ----------------------------------------------------------------------------
DisplaySettings         WxDisplay::s_DisplaySettings;
WxDisplayApp           *WxDisplay::s_pApplication = 0;
WxDisplayFrame         *WxDisplay::s_pFrame       = 0;
HWND                    WxDisplay::s_hWnd         = 0;
ApplicationModule_Wx   *WxDisplay::s_pModule      = 0;


// ----------------------------------------------------------------------------
// Set the application
// ----------------------------------------------------------------------------
void WxDisplay::SetApp(WxDisplayApp *pApp)
{
  if (!s_pApplication)
    atexit(&WxDisplay::DestroyApp);

  s_pApplication = pApp;
} // SetApp


// ----------------------------------------------------------------------------
// Destroy the application
// ----------------------------------------------------------------------------
void WxDisplay::DestroyApp()
{
//  delete s_pApplication;

  s_pApplication = 0;
  s_hWnd         = 0;
  s_pModule      = 0;
  s_pFrame       = 0;
} // DestroyApp



// ----------------------------------------------------------------------------
// The event table for WxDisplayFrame
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(WxDisplayFrame, wxFrame)
END_EVENT_TABLE()


// ----------------------------------------------------------------------------
// The event table for WxDisplayCanvas
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(WxDisplayCanvas, wxDirectXCanvas)
EVT_SIZE(WxDisplayCanvas::OnSize)
EVT_PAINT(WxDisplayCanvas::OnPaint)
EVT_CHAR(WxDisplayCanvas::OnChar)
EVT_MOUSE_EVENTS(WxDisplayCanvas::OnMouseEvent)
END_EVENT_TABLE()


// ----------------------------------------------------------------------------
// Constructor for WxDisplayCanvas
// ----------------------------------------------------------------------------
WxDisplayCanvas::WxDisplayCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos,
                             const wxSize &size, long style, const wxString &name)
                             : wxDirectXCanvas(parent, id, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name)
{
//  parent->Show(true);
} // WxDisplayCanvas


// ----------------------------------------------------------------------------
// Destructor for WxDisplayCanvas
// ----------------------------------------------------------------------------
WxDisplayCanvas::~WxDisplayCanvas()
{
} // ~WxDisplayCanvas


// ----------------------------------------------------------------------------
// Called to paint (render) the canvas
// ----------------------------------------------------------------------------
void WxDisplayCanvas::OnPaint(wxPaintEvent &event)
{
  if (Application.IsInitialised())
  {
    if (!Application.RunFrame(ApplicationCentral::FS_RENDER))
    {
      // TODO: Implement this
    }
  } // if

  // This must happen after we render so it's in a scope block
  {
    wxPaintDC dc(this);
  }
} // OnPaint


// ----------------------------------------------------------------------------
// Resize the display
// ----------------------------------------------------------------------------
void WxDisplayCanvas::OnSize(wxSizeEvent &event)
{
  Application.ResizeDisplay();
} // OnSize


// ----------------------------------------------------------------------------
// Key entry callback
// ----------------------------------------------------------------------------
void WxDisplayCanvas::OnChar(wxKeyEvent &event)
{
} // OnChar


// ----------------------------------------------------------------------------
// Mouse entry callback
// ----------------------------------------------------------------------------
void WxDisplayCanvas::OnMouseEvent(wxMouseEvent &event)
{
} // OnMouseEvent


// ----------------------------------------------------------------------------
// Constructor for WxDisplayFrame
// ----------------------------------------------------------------------------
WxDisplayFrame::WxDisplayFrame(wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
: wxFrame   (frame, wxID_ANY, title, pos, size, style)
{
  m_pCanvas = new WxDisplayCanvas(this, wxID_ANY, pos, size, 0, _T("WxDisplayCanvas"));
  WxDisplay::SetHWND((HWND)m_pCanvas->GetHWND());
} // WxDisplayFrame


// ----------------------------------------------------------------------------
// Destructor for WxDisplayFrame
// ----------------------------------------------------------------------------
WxDisplayFrame::~WxDisplayFrame()
{
  delete m_pCanvas;
} // ~WxDisplayFrame


// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void WxDisplayFrame::OnInternalIdle()
{
  wxFrame::OnInternalIdle();

  if (Application.IsInitialised())
  {
    if (!Application.RunFrame(ApplicationCentral::FS_INPUT))
    {
      // TODO: Implement this
    }
  }

  Refresh(false);
} // OnInternalIdle


// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
WxDisplayApp::WxDisplayApp()
: wxApp()
{
  WxDisplay::SetApp(this);
}


// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
bool WxDisplayApp::OnInit()
{
  // Create the main frame window
  m_pFrame = CreateFrame();

  // Show the frame
  m_pFrame->Show(true);

  // Create the module
  if (!WxDisplay::GetModule()->Create())
    return false;

  // Check that the application central is initialised
  if (!Application.IsInitialised())
    return false;

  // Process the input
  if (!Application.RunFrame(ApplicationCentral::FS_INPUT))
    return false;

  return true;
} // OnInit


// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
WxDisplayFrame *WxDisplayApp::CreateFrame()
{
  const DisplaySettings &settings = WxDisplay::GetDisplaySettings();

  wxPoint pos(settings.InitialWindowPosition.x, settings.InitialWindowPosition.y);
  wxSize size(settings.InitialWindowSize.cx, settings.InitialWindowSize.cy);

  WxDisplayFrame *pFrame = new WxDisplayFrame(NULL, wxT(settings.InitialWindowCaption.c_str()), pos, size);
  WxDisplay::SetFrame(pFrame);

  if (settings.StartFullScreen)
  {
    Application.ToggleFullScreen();
  }

  return pFrame;
}


// -- EOF


