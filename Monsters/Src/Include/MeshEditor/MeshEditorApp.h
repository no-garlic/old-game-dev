// ----------------------------------------------------------------------------
// File: MeshEditorApp.h
// Desc: The applkication main window for the editor
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MESH_EDITOR_APP_H_
#define __MESH_EDITOR_APP_H_


// ----------------------------------------------------------------------------
// includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"


// ----------------------------------------------------------------------------
// Name: MeshEditorApp  (class)
// Desc: The editor application class
// ----------------------------------------------------------------------------
class MeshEditorApp : public CWinApp
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MeshEditorApp();
  virtual ~MeshEditorApp();

  // --------------------------------------------------------------------------
  // Function overrides
  // --------------------------------------------------------------------------
  virtual BOOL InitInstance();
  virtual BOOL OnIdle(LONG lCount);
  //virtual int Run();
  

  // --------------------------------------------------------------------------
  // Message map
  // --------------------------------------------------------------------------
  DECLARE_MESSAGE_MAP()

protected:
  afx_msg void OnAppExit();
  afx_msg void OnFileOpen();
  afx_msg void OnImportFromX();
  afx_msg void OnFileClose();
  afx_msg void OnFileSave();
  afx_msg void OnFileSaveAs();

}; // class MeshEditorApp


#endif // __MESH_EDITOR_APP_H_

// -- EOF

