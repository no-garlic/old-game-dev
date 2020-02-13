
#ifndef __EDITOR_H_
#define __EDITOR_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libEngine.h"
#include "libEditor.h"
#include "EditorResource.h"
#include "EditorMainFrame.h"
#include "EditorPanelBottom.h"
#include "EditorPanelLeft.h"
#include "ToolPanel.h"
#include "ToolBar.h"
#include "EditorDocument.h"
#include "EditorContent.h"
#include "UndoManager.h"
#include "ActionManager.h"
#include "EditorCameraManager.h"
#include "EditorInput_Keyboard.h"
#include "EditorInput_Mouse.h"
#include "Grid.h"


// ----------------------------------------------------------------------------
// Singelton accessor
// ----------------------------------------------------------------------------
#define Editor EditorCentral::GetInstance()


// ----------------------------------------------------------------------------
// Name: EditorCentral (class)
// Desc: The central global game class.
// ----------------------------------------------------------------------------
class EditorCentral
{
public:
  // --------------------------------------------------------------------------
  // Static singleton accessor
  // --------------------------------------------------------------------------
  static EditorCentral &GetInstance();
  static void DestroyInstance();

  // --------------------------------------------------------------------------
  // Get the main frame
  // --------------------------------------------------------------------------
  EditorMainFrame *GetMainFrame();

  // --------------------------------------------------------------------------
  // Get the file database
  // --------------------------------------------------------------------------
  FileDatabase *GetDatabase()             { return m_pDatabase; }

  // --------------------------------------------------------------------------
  // Get the undo manager
  // --------------------------------------------------------------------------
  UndoManager *GetUndoManager()           { return m_pUndoManager; }

  // --------------------------------------------------------------------------
  // Get the action manager
  // --------------------------------------------------------------------------
  ActionManager *GetActionManager()       { return m_pActionManager; }

  // --------------------------------------------------------------------------
  // Get the camera manager
  // --------------------------------------------------------------------------
  EditorCameraManager *GetCameraManager() { return m_pCameraManager; }

  // --------------------------------------------------------------------------
  // Get the camera manager
  // --------------------------------------------------------------------------
  Grid *GetGrid()                         { return m_pGrid; }

  // --------------------------------------------------------------------------
  // Get the input managers
  // --------------------------------------------------------------------------
  EditorInput_Keyboard *GetKeyboardManager()  { return m_pKeyboardInput; }
  EditorInput_Mouse    *GetMouseManager()     { return m_pMouseInput;    }

  // --------------------------------------------------------------------------
  // Test if the mouse is over the viewport
  // --------------------------------------------------------------------------
  bool IsMouseOverViewport();

  // --------------------------------------------------------------------------
  // Get the document and the content
  // --------------------------------------------------------------------------
  EditorDocument *GetDocument()         { return m_pDocument; }
  EditorContent  *GetContent()          { return m_pContent;  }

  // --------------------------------------------------------------------------
  // Get the panels
  // --------------------------------------------------------------------------
  EditorPanelLeft   *GetLeftPanel()     { return m_pLeftPanel;   }
  ToolBar           *GetToolBar()       { return m_pToolBar;  }
  ToolPanel         *GetToolPanel()     { return m_pToolPanel;    }
  EditorPanelBottom *GetBottomPanel()   { return m_pBottomPanel; }

  // --------------------------------------------------------------------------
  // Get the image list
  // --------------------------------------------------------------------------
  ImageList *GetImageList() { return m_pImageList; }

  // --------------------------------------------------------------------------
  // Manage the menu options
  // --------------------------------------------------------------------------
  void SetMenuOptionEnabled(EditorResource option, bool isEnabled);

  // --------------------------------------------------------------------------
  // Get unique names
  // --------------------------------------------------------------------------
  String GetNextName(const String &baseName);

  // --------------------------------------------------------------------------
  // Manage unique name counters
  // --------------------------------------------------------------------------
  void LoadNameCountersFromConfig(const ConfigSection &config);
  void SaveNameCountersToConfig(ConfigSection &config);
  void ResetNameCounters();

private:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  EditorCentral();
  ~EditorCentral();

  // --------------------------------------------------------------------------
  // Private static members
  // --------------------------------------------------------------------------
  static EditorCentral *s_pInstance;

public:
  // --------------------------------------------------------------------------
  // Get and set the module
  // --------------------------------------------------------------------------
  inline void SetModule(ApplicationModule *pModule);
  inline ApplicationModule *GetModule();

  // --------------------------------------------------------------------------
  // Callbacks for startup and shutdown
  // --------------------------------------------------------------------------
  bool OnInit();
  void OnShutdown();
  void OnResize();
  void OnMove();

  // --------------------------------------------------------------------------
  // Callbacks for running a frame
  // --------------------------------------------------------------------------
  void App();
  void Cull();
  void Draw();

  void SetRenderState();

private:
  // --------------------------------------------------------------------------
  // Private functions
  // --------------------------------------------------------------------------
  void SetViewport();
  void UpdateFrameDimensions();

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  bool                  m_Initialised;          // Is the editor initialised
  ApplicationModule    *m_pModule;              // The module
  ImageList            *m_pImageList;           // The image list
  EditorFrame          *m_pLeftFrame;           // The side frame
  EditorFrame          *m_pBottomFrame;         // The bottom frame
  EditorPanelLeft      *m_pLeftPanel;           // The left panel
  ToolBar              *m_pToolBar;             // The right panel
  ToolPanel            *m_pToolPanel;           // The top panel
  EditorPanelBottom    *m_pBottomPanel;         // The bottom panel
  EditorDocument       *m_pDocument;            // The editor document
  EditorContent        *m_pContent;             // The editor content
  FileDatabase         *m_pDatabase;            // The editor file database
  UndoManager          *m_pUndoManager;         // The undo manager
  ActionManager        *m_pActionManager;       // The action manager
  EditorCameraManager  *m_pCameraManager;       // The camera manager
  EditorInput_Keyboard *m_pKeyboardInput;       // The keyboard input
  EditorInput_Mouse    *m_pMouseInput;          // The mouse input
  Grid                 *m_pGrid;                // The grid
  Map<String, uint>     m_Names;                // Map of names and id's

};


// ----------------------------------------------------------------------------
// Name: EditorCentral::SetModule
// Desc: Set the module
// ----------------------------------------------------------------------------
inline void EditorCentral::SetModule(ApplicationModule *pModule)
{
  m_pModule = pModule;
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::GetModule
// Desc: Get the module
// ----------------------------------------------------------------------------
inline ApplicationModule *EditorCentral::GetModule()
{
  return m_pModule;
}


#endif // __EDITOR_H_

// -- EOF

