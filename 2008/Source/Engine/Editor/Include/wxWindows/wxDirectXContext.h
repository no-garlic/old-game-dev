// ----------------------------------------------------------------------------
// File: wxDirectXContext.h
// Desc: The WX context base class for directX
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __WX_DIRECTX_CONTEXT_H_
#define __WX_DIRECTX_CONTEXT_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "wxWindows/wxDirectX.h"


// ----------------------------------------------------------------------------
// Forward declaration
// ----------------------------------------------------------------------------
class wxDirectXCanvas;


// ----------------------------------------------------------------------------
// The base context class to implement directx into wx windows
// ----------------------------------------------------------------------------
class wxDirectXContext : public wxObject
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  wxDirectXContext(wxDirectXCanvas *win);
  ~wxDirectXContext();

  // --------------------------------------------------------------------------
  // Get the window and device context
  // --------------------------------------------------------------------------
  wxWindow* GetWindow() const { return m_window; }
  WXHDC GetHDC() const { return m_hDC; }

public:
  // --------------------------------------------------------------------------
  // Public members
  // --------------------------------------------------------------------------
  WXHDC             m_hDC;
  wxWindow*         m_window;

};


#endif // __WX_DIRECTX_CONTEXT_H_

// -- EOF

