
#include "EditorMainFrame.h"
#include "Editor.h"
#include "EditorModule.h"
#include "wx/menu.h"
#include "wx/menuitem.h"


// ----------------------------------------------------------------------------
// Define the event table
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(EditorMainFrame, WxDisplayFrame)
  EVT_MENU(MNU_FILE_NEW, EditorMainFrame::OnFileNew)
  EVT_MENU(MNU_FILE_OPEN, EditorMainFrame::OnFileOpen)
  EVT_MENU(MNU_FILE_CLOSE, EditorMainFrame::OnFileClose)
  EVT_MENU(MNU_FILE_SAVE, EditorMainFrame::OnFileSave)
  EVT_MENU(MNU_FILE_SAVEAS, EditorMainFrame::OnFileSaveAs)
  EVT_MENU(MNU_FILE_EXIT, EditorMainFrame::OnFileExit)  
  EVT_MENU(MNU_EDIT_UNDO, EditorMainFrame::OnEditUndo)  
  EVT_MENU(MNU_EDIT_REDO, EditorMainFrame::OnEditRedo)  
  EVT_MENU(MNU_EDIT_CUT, EditorMainFrame::OnEditCut)
  EVT_MENU(MNU_EDIT_COPY, EditorMainFrame::OnEditCopy)
  EVT_MENU(MNU_EDIT_PASTE, EditorMainFrame::OnEditPaste)
  EVT_MENU(MNU_EDIT_DELETE, EditorMainFrame::OnEditDelete)
  EVT_MENU(MNU_VIEW_MODE_SOLID, EditorMainFrame::OnViewModeSolid)
  EVT_MENU(MNU_VIEW_MODE_WIRE, EditorMainFrame::OnViewModeWire)
  EVT_MENU(MNU_VIEW_MODE_SOLID_WIRE, EditorMainFrame::OnViewModeSolidWire)
  EVT_MENU(MNU_VIEW_MODE_UNLIT, EditorMainFrame::OnViewModeUnlit)
  EVT_MENU(MNU_VIEW_MODE_UNTEX, EditorMainFrame::OnViewModeUntex)
  EVT_MENU(MNU_VIEW_CAM_PERSPECTIVE, EditorMainFrame::OnViewCameraPerspective)
  EVT_MENU(MNU_VIEW_CAM_FRONT, EditorMainFrame::OnViewCameraFront)
  EVT_MENU(MNU_VIEW_CAM_BACK, EditorMainFrame::OnViewCameraBack)
  EVT_MENU(MNU_VIEW_CAM_LEFT, EditorMainFrame::OnViewCameraLeft)
  EVT_MENU(MNU_VIEW_CAM_RIGHT, EditorMainFrame::OnViewCameraRight)
  EVT_MENU(MNU_VIEW_CAM_TOP, EditorMainFrame::OnViewCameraTop)
  EVT_MENU(MNU_VIEW_CAM_BOTTOM, EditorMainFrame::OnViewCameraBottom)
  EVT_MOVE(EditorMainFrame::OnMove)
  EVT_SIZE(EditorMainFrame::OnSize)
END_EVENT_TABLE()


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
EditorMainFrame::EditorMainFrame(wxFrame *frame, 
                     const wxString& title, 
                     const wxPoint& pos,
                     const wxSize& size, 
                     long style)
: WxDisplayFrame(frame, title, pos, size, style)
{
  m_pMenuBar          = NULL;
  m_pFileMenu         = NULL;
  m_pEditMenu         = NULL;
  m_pViewMenu         = NULL;
  m_pHelpMenu         = NULL;
  m_pCameraMenu       = NULL;
  m_pViewModeMenu     = NULL;
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
EditorMainFrame::~EditorMainFrame()
{
  // HACK
  exit(0);
}


// --------------------------------------------------------------------------
// Toggle enabled of a menu option
// --------------------------------------------------------------------------
void EditorMainFrame::SetMenuOptionEnabled(EditorResource option, bool isEnabled)
{
  if (option > MNU_FILE_INDEX_START && option < MNU_FILE_INDEX_END)
  {
    m_pFileMenu->Enable(option, isEnabled);
  }
  else if (option > MNU_EDIT_INDEX_START && option < MNU_EDIT_INDEX_END)
  {
    m_pEditMenu->Enable(option, isEnabled);
  }
}


// --------------------------------------------------------------------------
// Change a menu option label
// --------------------------------------------------------------------------
void EditorMainFrame::SetMenuOptionLabel(EditorResource option, const String &label)
{
  if (option > MNU_FILE_INDEX_START && option < MNU_FILE_INDEX_END)
  {
    m_pFileMenu->SetLabel(option, label.c_str());
  }
  else if (option > MNU_EDIT_INDEX_START && option < MNU_EDIT_INDEX_END)
  {
    m_pEditMenu->SetLabel(option, label.c_str());
  }
}


// ----------------------------------------------------------------------------
// Initialise the controls
// ----------------------------------------------------------------------------
void EditorMainFrame::InitControls()
{
  // Create the menu bar
  m_pMenuBar = new wxMenuBar();

  // Create the main menus
  m_pFileMenu = new wxMenu();
  m_pEditMenu = new wxMenu();
  m_pViewMenu = new wxMenu();
  m_pHelpMenu = new wxMenu();

  // Create the file menu items
  m_pFileMenu->Append(MNU_FILE_NEW, "&New");
  m_pFileMenu->Append(MNU_FILE_OPEN, "&Open");
  m_pFileMenu->AppendSeparator();
  m_pFileMenu->Append(MNU_FILE_SAVE, "&Save");
  m_pFileMenu->Append(MNU_FILE_SAVEAS, "Save &As");
  m_pFileMenu->AppendSeparator();
  m_pFileMenu->Append(MNU_FILE_CLOSE, "&Close");
  m_pFileMenu->AppendSeparator();
  m_pFileMenu->Append(MNU_FILE_EXIT, "E&xit");

  // Create the edit menu items
  m_pEditMenu->Append(MNU_EDIT_UNDO, "&Undo");
  m_pEditMenu->Append(MNU_EDIT_REDO, "&Redo");
  m_pEditMenu->AppendSeparator();
  m_pEditMenu->Append(MNU_EDIT_CUT, "&Cut");
  m_pEditMenu->Append(MNU_EDIT_COPY, "&Copy");
  m_pEditMenu->Append(MNU_EDIT_PASTE, "&Paste");
  m_pEditMenu->AppendSeparator();
  m_pEditMenu->Append(MNU_EDIT_DELETE, "&Delete");

  // Create the camera menu
  m_pCameraMenu = new wxMenu();
  m_pCameraMenu->AppendRadioItem(MNU_VIEW_CAM_PERSPECTIVE, "Perspective");
  m_pCameraMenu->AppendRadioItem(MNU_VIEW_CAM_TOP, "Top");
  m_pCameraMenu->AppendRadioItem(MNU_VIEW_CAM_FRONT, "Front");
  m_pCameraMenu->AppendRadioItem(MNU_VIEW_CAM_LEFT, "Left");
  m_pCameraMenu->AppendRadioItem(MNU_VIEW_CAM_BOTTOM, "Bottom");
  m_pCameraMenu->AppendRadioItem(MNU_VIEW_CAM_BACK, "Back");
  m_pCameraMenu->AppendRadioItem(MNU_VIEW_CAM_RIGHT, "Right");

  // Create the view mode menu
  m_pViewModeMenu = new wxMenu();
  m_pViewModeMenu->AppendRadioItem(MNU_VIEW_MODE_SOLID, "Solid");
  m_pViewModeMenu->AppendRadioItem(MNU_VIEW_MODE_WIRE, "Wireframe");
  m_pViewModeMenu->AppendRadioItem(MNU_VIEW_MODE_SOLID_WIRE, "Solid + Wireframe");
  m_pViewModeMenu->AppendRadioItem(MNU_VIEW_MODE_UNLIT, "Unlit");
  m_pViewModeMenu->AppendRadioItem(MNU_VIEW_MODE_UNTEX, "Untextured");

  // Create the view menu items
  m_pViewMenu->Append(-1, "View Mode", m_pViewModeMenu);
  m_pViewMenu->AppendSeparator();
  m_pViewMenu->Append(-1, "Camera", m_pCameraMenu);
  m_pViewMenu->AppendSeparator();
  m_pViewMenu->Append(-1, "Zoom Extents");
  m_pViewMenu->Append(-1, "Zoom Selected");
  m_pViewMenu->AppendSeparator();
  m_pViewMenu->AppendCheckItem(-1, "Show Grid");
  m_pViewMenu->AppendCheckItem(-1, "Snap To Grid");

  // Create the help menu items
  m_pHelpMenu->Append(-1, "About");

  // Add the menus to the menu bar
  m_pMenuBar->Append(m_pFileMenu, "&File");
  m_pMenuBar->Append(m_pEditMenu, "&Edit");
  m_pMenuBar->Append(m_pViewMenu, "&View");
  m_pMenuBar->Append(m_pHelpMenu, "&Help");

  // Add the menu bar to the frame
  SetMenuBar(m_pMenuBar);

  // Create a status bar
  CreateStatusBar(2);
}


// ----------------------------------------------------------------------------
// Update the controls 
// ----------------------------------------------------------------------------
void EditorMainFrame::UpdateControls()
{
  // The items in this map must match the order of the items in the 
  // EditorDocument::ViewMode enumeration.
  static int viewModeMap[] = 
  { 
    MNU_VIEW_MODE_SOLID, 
    MNU_VIEW_MODE_SOLID_WIRE, 
    MNU_VIEW_MODE_UNTEX, 
    MNU_VIEW_MODE_UNLIT, 
    MNU_VIEW_MODE_WIRE
  };

  // Get the selected view mode
  int viewMode = Editor.GetDocument()->GetViewMode();

  // If the menu's slected item is different, select the correct item
  if (!m_pViewModeMenu->IsChecked(viewModeMap[viewMode]))
  {
    m_pViewModeMenu->Check(viewModeMap[viewMode], true);
  }

  // The items in this map must match the order of the items in the 
  // EditorCameraType enumeration.
  static int viewCameraMap[] = 
  { 
    MNU_VIEW_CAM_PERSPECTIVE,
    MNU_VIEW_CAM_TOP,
    MNU_VIEW_CAM_BOTTOM,
    MNU_VIEW_CAM_LEFT,
    MNU_VIEW_CAM_RIGHT,
    MNU_VIEW_CAM_FRONT,
    MNU_VIEW_CAM_BACK
  };

  // Get the current camera
  EditorCamera *camera = Editor.GetCameraManager()->GetCurrentCamera();
  if (camera)
  {
    // Get the camera type
    int cameraType = camera->GetType();

    // If the menu's slected item is different, select the correct item
    if (!m_pCameraMenu->IsChecked(viewCameraMap[cameraType]))
    {
      m_pCameraMenu->Check(viewCameraMap[cameraType], true);
    }
  }
}


// ----------------------------------------------------------------------------
// Event callback when the frame is moved
// ----------------------------------------------------------------------------
void EditorMainFrame::OnMove(wxMoveEvent &event)
{
  // Notify the module that the frame has moved
  static_cast<EditorModule *>(WxDisplay::GetModule())->Move();
}


// ----------------------------------------------------------------------------
// Event callback when the frame is resized
// ----------------------------------------------------------------------------
void EditorMainFrame::OnSize(wxSizeEvent &event)
{
  wxFrame::OnSize(event);

  // Notify the module that the frame has been resized
  static_cast<EditorModule *>(WxDisplay::GetModule())->Resize();
}


// ----------------------------------------------------------------------------
// Event callback when the exit command is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnFileExit(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_EXIT);
}


// ----------------------------------------------------------------------------
// Event callback when the new command is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnFileNew(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_NEW);
}


// ----------------------------------------------------------------------------
// Event callback when the open command is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnFileOpen(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_OPEN);
}


// ----------------------------------------------------------------------------
// Event callback when the close command is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnFileClose(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_CLOSE);
}


// ----------------------------------------------------------------------------
// Event callback when the save command is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnFileSave(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_SAVE);
}


// ----------------------------------------------------------------------------
// Event callback when the save as command is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnFileSaveAs(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DOCUMENT_SAVEAS);
}


// ----------------------------------------------------------------------------
// Event callback when the undo command is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnEditUndo(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_UNDO);
}


// ----------------------------------------------------------------------------
// Event callback when copy is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnEditRedo(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_REDO);
}


// ----------------------------------------------------------------------------
// Event callback when cut is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnEditCut(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_CUT);
}


// ----------------------------------------------------------------------------
// Event callback when the redo command is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnEditCopy(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_COPY);
}


// ----------------------------------------------------------------------------
// Event callback when paste is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnEditPaste(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_CLIPBOARD_PASTE);
}


// ----------------------------------------------------------------------------
// Event callback when delete is selected from the menu
// ----------------------------------------------------------------------------
void EditorMainFrame::OnEditDelete(wxCommandEvent& event)
{
  Editor.GetActionManager()->CreateAndCompleteAction(ActionManager::ACTION_DELETE_SELECTED);
}


// ----------------------------------------------------------------------------
// Event callback when view mode is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewModeSolid(wxCommandEvent& event)
{
  Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_NORMAL);
}


// ----------------------------------------------------------------------------
// Event callback when view mode is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewModeWire(wxCommandEvent& event)
{
  Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_WIREFRAME);
}


// ----------------------------------------------------------------------------
// Event callback when view mode is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewModeSolidWire(wxCommandEvent& event)
{
  Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_NORMAL_WIREOVER);
}


// ----------------------------------------------------------------------------
// Event callback when view mode is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewModeUnlit(wxCommandEvent& event)
{
  Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_UNLIT);
}


// ----------------------------------------------------------------------------
// Event callback when view mode is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewModeUntex(wxCommandEvent& event)
{
  Editor.GetDocument()->SetViewMode(EditorDocument::VIEW_NOTEX);
}


// ----------------------------------------------------------------------------
// Event callback when view camera is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewCameraPerspective(wxCommandEvent& event)
{
  Editor.GetCameraManager()->SetCurrentCamera(CAM_PERSPECTIVE);
}


// ----------------------------------------------------------------------------
// Event callback when view camera is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewCameraFront(wxCommandEvent& event)
{
  Editor.GetCameraManager()->SetCurrentCamera(CAM_FRONT);
}


// ----------------------------------------------------------------------------
// Event callback when view camera is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewCameraBack(wxCommandEvent& event)
{
  Editor.GetCameraManager()->SetCurrentCamera(CAM_BACK);
}


// ----------------------------------------------------------------------------
// Event callback when view camera is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewCameraTop(wxCommandEvent& event)
{
  Editor.GetCameraManager()->SetCurrentCamera(CAM_TOP);
}


// ----------------------------------------------------------------------------
// Event callback when view camera is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewCameraBottom(wxCommandEvent& event)
{
  Editor.GetCameraManager()->SetCurrentCamera(CAM_BOTTOM);
}


// ----------------------------------------------------------------------------
// Event callback when view camera is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewCameraLeft(wxCommandEvent& event)
{
  Editor.GetCameraManager()->SetCurrentCamera(CAM_LEFT);
}


// ----------------------------------------------------------------------------
// Event callback when view camera is set
// ----------------------------------------------------------------------------
void EditorMainFrame::OnViewCameraRight(wxCommandEvent& event)
{
  Editor.GetCameraManager()->SetCurrentCamera(CAM_RIGHT);
}


// -- EOF
