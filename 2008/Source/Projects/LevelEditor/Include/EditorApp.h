// ----------------------------------------------------------------------------
// File: EditorApp.h
// Desc: Editor application class
// Auth: Michael Petrou
// (C) Copyright:   2007
// ----------------------------------------------------------------------------
#ifndef _EDITOR_APP_H_
#define _EDITOR_APP_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libEngine.h"
#include "libEditor.h"


// ----------------------------------------------------------------------------
// Forward declaration
// ----------------------------------------------------------------------------
class EditorApp;
class EditorMainFrame;


// ----------------------------------------------------------------------------
// The main application for wxWindows for the editor
// ----------------------------------------------------------------------------
class EditorApp : public WxDisplayApp
{
protected:
  // --------------------------------------------------------------------------
  // Create the main application frame
  // --------------------------------------------------------------------------
  virtual WxDisplayFrame *CreateFrame();

}; // EditorApp


#endif // _EDITOR_APP_H_

// -- EOF

