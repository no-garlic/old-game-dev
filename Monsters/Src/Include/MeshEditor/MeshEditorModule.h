// ----------------------------------------------------------------------------
// File: MeshEditorModule.h
// Desc: The module that runs the game editor
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MESH_EDITOR_MODULE_H_
#define __MESH_EDITOR_MODULE_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"
#include "Render/RenderInc.h"
#include "MeshEditor/MeshMaterialDialog.h"
#include "MeshEditor/MeshLightDialog.h"


// ----------------------------------------------------------------------------
// Name: MeshEditorModule  (class)
// Desc: Test Module
// ----------------------------------------------------------------------------
class MeshEditorModule : public ApplicationModule_MFC
{
public:
  // --------------------------------------------------------------------------
  // Constructor and Destructor
  // --------------------------------------------------------------------------
  MeshEditorModule();
  virtual ~MeshEditorModule();

  // --------------------------------------------------------------------------
  // Process Functions
  // --------------------------------------------------------------------------
  virtual bool Init();
  virtual bool CreateSafeObjects();
  virtual bool CreateDeviceObjects();
  virtual bool ReleaseSafeObjects();
  virtual bool ReleaseDeviceObjects();
  virtual void Shutdown();
  virtual void App();
  virtual void Cull();
  virtual void Draw();
  virtual void Resize();
  virtual CWinApp *CreateApp(DisplaySettings ds);

public:
  bool ImportFile(const String &filename);
  bool OpenFile(const String &filename);
  bool SaveFileAs(const String &filename);
  bool SaveFile();
  bool CloseFile();
  bool CanSave() { return m_SaveFile.length() > 0; }

  void EnableMouse()  { m_MouseEnabled = true;  }
  void DisableMouse() { m_MouseEnabled = false; }

  void ShowMaterialDialog(bool enabled);
  void ShowLightDialog(bool enabled);

  // ----------------------------------------------------------------------------
  // Name: DisableMouseScope (struct)
  // Desc: Simple struct to disable the mouse and re-enable it.  This is used as a
  //       scope object.
  // ----------------------------------------------------------------------------
  struct DisableMouseScope
  {
    // --------------------------------------------------------------------------
    // Constructor
    // --------------------------------------------------------------------------
    DisableMouseScope()
    {
      MeshEditorModule *pModule = reinterpret_cast<MeshEditorModule *>(MFCDisplay::GetModule());
      if (pModule)
        pModule->DisableMouse();
    } // DisableMouseScope

    // --------------------------------------------------------------------------
    // Destructor
    // --------------------------------------------------------------------------
    ~DisableMouseScope()
    {
      MeshEditorModule *pModule = reinterpret_cast<MeshEditorModule *>(MFCDisplay::GetModule());
      if (pModule)
        pModule->EnableMouse();

      // Clear all mouse messages
      ApplicationCentral.GetInput().ReadData();
      while (ApplicationCentral.GetInput().HasMouseMessage())
        ApplicationCentral.GetInput().PopMouseMessage();
    } // ~DisableMouseScope
  }; // struct DisableMouseScope

private:
  // --------------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------------
  void SetDisplayState();
  bool IsMouseOverWindow(HWND window);
  bool IsMouseOverGfx();
  void ResetCamera();

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  bool            m_Visible;              // Is the mesh visible
  IndexedMesh    *m_pMesh;                // The mesh
  String          m_OpenFile;             // The filename to open
  String          m_SaveFile;             // The filename to save

  Vec3            m_CameraLook;           // The camera look vector
  Vec3            m_CameraRight;          // The camera right vector
  Vec3            m_CameraUp;             // The camera up vector
  Vec3            m_CameraPos;            // The camera position

  Matrix          m_ModelMatrix;          // The model matrix

  bool            m_MouseEnabled;         // Is the mouse enabled
  bool            m_MouseOverMaterialDlg; // Is the mouse over the material dialog
  bool            m_MouseOverLightDlg;    // Is the mouse over the light dialog
  bool            m_MaterialDlgShowing;   // Is the material dialog showing
  bool            m_LightDlgShowing;      // Is the light dialog showing

  MeshMaterialDialog *m_pMaterialDialog;  // The material dialog
  MeshLightDialog    *m_pLightDialog;     // The light dialog

}; // class MeshEditorModule


#endif // __MESH_EDITOR_MODULE_H_

// -- EOF



