// ----------------------------------------------------------------------------
// File: WxDisplay.h
// Desc: Wrapper for a single view Wx application
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __WX_DISPLAY_H_
#define __WX_DISPLAY_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "wxWindows/wxDirectXCanvas.h"
#include "wxWindows/wxDirectXContext.h"
#include "wxWindows/wxDirectXModule.h"
#include "wxWindows/wxDirectX.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class WxDisplayFrame;
class WxDisplayCanvas;
class WxDisplayApp;
class ApplicationModule_Wx;


// ----------------------------------------------------------------------------
// Name: WxDisplay (class)
// Desc: Wrapper for a single view Wx application
// ----------------------------------------------------------------------------
class WxDisplay
{
public:
  // --------------------------------------------------------------------------
  // Get the Wx handles
  // --------------------------------------------------------------------------
  static WxDisplayApp           *GetApp()     { return s_pApplication; }
  static WxDisplayFrame         *GetFrame()   { return s_pFrame;       }
  static HWND                    GetHWND()    { return s_hWnd;         }
  static ApplicationModule_Wx   *GetModule()  { return s_pModule;      }

  // --------------------------------------------------------------------------
  // Get and set the module
  // --------------------------------------------------------------------------
  static void SetModule(ApplicationModule_Wx *pModule) { s_pModule = pModule; }
  static void SetHWND(HWND hWnd) { s_hWnd = hWnd; }
  static void SetApp(WxDisplayApp *pApp);
  static void SetFrame(WxDisplayFrame *pFrame) { s_pFrame = pFrame; }

  // --------------------------------------------------------------------------
  // Get the settings
  // --------------------------------------------------------------------------
  static DisplaySettings &GetDisplaySettings() { return s_DisplaySettings; }

  // --------------------------------------------------------------------------
  // Destroy the application
  // --------------------------------------------------------------------------
  static void DestroyApp();
  
private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  static WxDisplayApp           *s_pApplication;
  static WxDisplayFrame         *s_pFrame;
  static ApplicationModule_Wx   *s_pModule;
  static HWND                    s_hWnd;
  static DisplaySettings         s_DisplaySettings;

}; // class WxDisplay


// ----------------------------------------------------------------------------
// The canvas class for rendering to
// ----------------------------------------------------------------------------
class WxDisplayCanvas : public wxDirectXCanvas
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  WxDisplayCanvas(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = _T("DirectXCanvas"));
  virtual ~WxDisplayCanvas();

  // --------------------------------------------------------------------------
  // Callback functions
  // --------------------------------------------------------------------------
  void OnPaint(wxPaintEvent& event);
  void OnSize(wxSizeEvent& event);
  void OnEraseBackground(wxEraseEvent& event);
  void OnChar(wxKeyEvent& event);
  void OnMouseEvent(wxMouseEvent& event);

  // --------------------------------------------------------------------------
  // The event table
  // --------------------------------------------------------------------------
  DECLARE_EVENT_TABLE()

}; // class WxDisplayCanvas


// ----------------------------------------------------------------------------
// The base frame class for modules to inherit from
// ----------------------------------------------------------------------------
class WxDisplayFrame : public wxFrame
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  WxDisplayFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
    const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);
  virtual ~WxDisplayFrame();

  // --------------------------------------------------------------------------
  // Initialise the controls
  // --------------------------------------------------------------------------
  virtual void InitControls() {}

  // --------------------------------------------------------------------------
  // Get the canvas
  // --------------------------------------------------------------------------
  WxDisplayCanvas *GetCanvas() { return m_pCanvas; }

protected:
  // --------------------------------------------------------------------------
  // Callback functions
  // --------------------------------------------------------------------------
  virtual void OnInternalIdle();

  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  WxDisplayCanvas *m_pCanvas;

  // --------------------------------------------------------------------------
  // The event table
  // --------------------------------------------------------------------------
  DECLARE_EVENT_TABLE()

}; // class WxDisplayFrame


// ----------------------------------------------------------------------------
// The base application class for modules to inherit from
// ----------------------------------------------------------------------------
class WxDisplayApp : public wxApp
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  WxDisplayApp();

  // --------------------------------------------------------------------------
  // Public functions
  // --------------------------------------------------------------------------
  virtual bool OnInit();
  WxDisplayFrame *GetFrame() { return m_pFrame; }

protected:
  // --------------------------------------------------------------------------
  // Protected functions
  // --------------------------------------------------------------------------
  virtual WxDisplayFrame *CreateFrame();

  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  WxDisplayFrame *m_pFrame;

}; // WxDisplayApp


#endif // __WX_DISPLAY_H_

// -- EOF


