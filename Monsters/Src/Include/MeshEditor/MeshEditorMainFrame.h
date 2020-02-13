// ----------------------------------------------------------------------------
// File: MeshEditorMainFrame.h
// Desc: The main frame of the editor
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MESH_EDITOR_MAIN_FRAME_H_
#define __MESH_EDITOR_MAIN_FRAME_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"


// ----------------------------------------------------------------------------
// Name: MeshEditorMainFrame  (class)
// Desc: The MFC Main Frame
// ----------------------------------------------------------------------------
class MeshEditorMainFrame : public CFrameWnd
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MeshEditorMainFrame();
  virtual ~MeshEditorMainFrame();

  // --------------------------------------------------------------------------
  // Allow this class to be created through reflection
  // --------------------------------------------------------------------------
  DECLARE_DYNCREATE(MeshEditorMainFrame);

  // --------------------------------------------------------------------------
  // Public functions
  // --------------------------------------------------------------------------
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  CStatusBar  m_wndStatusBar;
  CToolBar    m_wndToolBar;

protected:
  // --------------------------------------------------------------------------
  // Protected functions
  // --------------------------------------------------------------------------
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

  // --------------------------------------------------------------------------
  // Message map
  // --------------------------------------------------------------------------
  DECLARE_MESSAGE_MAP()

}; // class MeshEditorMainFrame


#endif // __MESH_EDITOR_MAIN_FRAME_H_

// -- EOF

