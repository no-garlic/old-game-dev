// ----------------------------------------------------------------------------
// File: wxDirectXCanvas.cpp
// Desc: The WX canvas base class for directX
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "wxWindows/wxDirectXCanvas.h"
#include "wxWindows/wxDirectXContext.h"
#include "wxWindows/wxDirectXModule.h"
#include "wx/bitmap.h"


// ----------------------------------------------------------------------------
// Implement the class
// ----------------------------------------------------------------------------
IMPLEMENT_CLASS(wxDirectXCanvas, wxWindow)


// ----------------------------------------------------------------------------
// Define the event table
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(wxDirectXCanvas, wxWindow)
EVT_ERASE_BACKGROUND(wxDirectXCanvas::OnEraseBackground)
END_EVENT_TABLE()


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
wxDirectXCanvas::wxDirectXCanvas(wxWindow        *parent, 
                                 wxWindowID       id, 
                                 const wxPoint   &pos,
                                 const wxSize    &size, 
                                 long             style, 
                                 const wxString  &name)
{
  REF_COUNT_CTOR(wxDirectXCanvas);

  m_Context = NULL;

  bool ret = Create(parent, id, pos, size, style, name);

  if (ret)
    SetBackgroundColour(wxColor(0x7F, 0x7F, 0x7F));

  m_hDC = (WXHDC) ::GetDC((HWND) GetHWND());
  m_Context = new wxDirectXContext(this);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
wxDirectXCanvas::~wxDirectXCanvas()
{
  REF_COUNT_DTOR(wxDirectXCanvas);

  delete m_Context;

  ::ReleaseDC((HWND) GetHWND(), (HDC) m_hDC);
}


// ----------------------------------------------------------------------------
// Create the canvas
// ----------------------------------------------------------------------------
bool wxDirectXCanvas::Create(wxWindow *parent,
                             wxWindowID id,
                             const wxPoint& pos,
                             const wxSize& size,
                             long style,
                             const wxString& name)
{
  wxCHECK_MSG( parent, false, wxT("can't create wxWindow without parent") );

  if (! wxDirectXModule::RegisterClasses())
  {
    wxLogError(_("Failed to register DirectX window class."));
    return false;
  }

  if (!CreateBase(parent, id, pos, size, style, wxDefaultValidator, name))
    return false;

  parent->AddChild(this);
  DWORD msflags = 0;

  WXDWORD exStyle = 0;
  msflags |= WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CS_BYTEALIGNCLIENT;
  msflags |= MSWGetStyle(style, &exStyle) ;

  return MSWCreate(wxDirectXCanvasClassName, NULL, pos, size, msflags, exStyle);
}


// ----------------------------------------------------------------------------
// Erase background event callback
// ----------------------------------------------------------------------------
void wxDirectXCanvas::OnEraseBackground(wxEraseEvent &event)
{
  static bool once = true;
  if (once)
  {
    once = false;

    if (event.GetDC())
    {
      event.GetDC()->SetBackground(wxBrush(GetBackgroundColour(), wxSOLID));
      event.GetDC()->Clear();
    }
    else
    {
      wxClientDC dc(this);
      dc.SetBackground(wxBrush(GetBackgroundColour(), wxSOLID));
      dc.Clear();
    }
  }
}


// -- EOF

