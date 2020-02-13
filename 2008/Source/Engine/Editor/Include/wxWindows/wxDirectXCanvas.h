// ----------------------------------------------------------------------------
// File: wxDirectXCanvas.h
// Desc: The WX canvas base class for directX
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __WX_DIRECTX_CANVAS_H_
#define __WX_DIRECTX_CANVAS_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "wxWindows/wxDirectX.h"


// ----------------------------------------------------------------------------
// The base canvas class to implement directx into wx windows
// ----------------------------------------------------------------------------
class wxDirectXCanvas : public wxWindow
{
  // --------------------------------------------------------------------------
  // Declare the class
  // --------------------------------------------------------------------------
  DECLARE_CLASS(wxDirectXCanvas)

public:
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  wxDirectXCanvas(wxWindow *parent, 
    wxWindowID id             = wxID_ANY,
    const wxPoint& pos        = wxDefaultPosition,
    const wxSize& size        = wxDefaultSize, 
    long style                = 0,
    const wxString& name      = wxDirectXCanvasName);

  // --------------------------------------------------------------------------
  // Destructor
  // --------------------------------------------------------------------------
  ~wxDirectXCanvas();

  // --------------------------------------------------------------------------
  // Create the canvas
  // --------------------------------------------------------------------------
  bool Create(wxWindow *parent, wxWindowID id, const wxPoint& pos, 
    const wxSize& size, long style, const wxString& name);

  // --------------------------------------------------------------------------
  // Event to erase the canvas background
  // --------------------------------------------------------------------------
  void OnEraseBackground(wxEraseEvent &event);

  // --------------------------------------------------------------------------
  // Get the context and device handle
  // --------------------------------------------------------------------------
  wxDirectXContext *GetContext() const { return m_Context; }
  WXHDC GetHDC() const { return m_hDC; }

protected:
  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  wxDirectXContext*   m_Context;
  WXHDC               m_hDC;

  // --------------------------------------------------------------------------
  // Declare the registered event table
  // --------------------------------------------------------------------------
  DECLARE_EVENT_TABLE()

};


#endif // __WX_DIRECTX_CANVAS_H_

// -- EOF

