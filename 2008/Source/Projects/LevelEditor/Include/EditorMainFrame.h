
#ifndef __EDITOR_MENU_H_
#define __EDITOR_MENU_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorResource.h"


// ----------------------------------------------------------------------------
// The main application frame
// ----------------------------------------------------------------------------
class EditorMainFrame : public WxDisplayFrame
{
public:
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  EditorMainFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
    const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);

  // --------------------------------------------------------------------------
  // Initialise the controls
  // --------------------------------------------------------------------------
  virtual void InitControls();
  void UpdateControls();

  // --------------------------------------------------------------------------
  // Destructor
  // --------------------------------------------------------------------------
  virtual ~EditorMainFrame();

  // --------------------------------------------------------------------------
  // Event functions
  // --------------------------------------------------------------------------
  void OnMove(wxMoveEvent &event);
  void OnSize(wxSizeEvent &event);

  // --------------------------------------------------------------------------
  // Manage the menu options
  // --------------------------------------------------------------------------
  void SetMenuOptionEnabled(EditorResource option, bool isEnabled);
  void SetMenuOptionLabel(EditorResource option, const String &label);

  // --------------------------------------------------------------------------
  // Menu functions
  // --------------------------------------------------------------------------
  void OnFileNew(wxCommandEvent& event);
  void OnFileOpen(wxCommandEvent& event);
  void OnFileSave(wxCommandEvent& event);
  void OnFileSaveAs(wxCommandEvent& event);
  void OnFileClose(wxCommandEvent& event);
  void OnFileExit(wxCommandEvent& event);
  void OnEditUndo(wxCommandEvent& event);
  void OnEditRedo(wxCommandEvent& event);
  void OnEditCut(wxCommandEvent& event);
  void OnEditCopy(wxCommandEvent& event);
  void OnEditPaste(wxCommandEvent& event);
  void OnEditDelete(wxCommandEvent& event);
  void OnViewModeSolid(wxCommandEvent& event);
  void OnViewModeWire(wxCommandEvent& event);
  void OnViewModeSolidWire(wxCommandEvent& event);
  void OnViewModeUnlit(wxCommandEvent& event);
  void OnViewModeUntex(wxCommandEvent& event);
  void OnViewCameraPerspective(wxCommandEvent& event);
  void OnViewCameraFront(wxCommandEvent& event);
  void OnViewCameraBack(wxCommandEvent& event);
  void OnViewCameraTop(wxCommandEvent& event);
  void OnViewCameraBottom(wxCommandEvent& event);
  void OnViewCameraLeft(wxCommandEvent& event);
  void OnViewCameraRight(wxCommandEvent& event);

protected:
  // --------------------------------------------------------------------------
  // Declare the event table
  // --------------------------------------------------------------------------
  DECLARE_EVENT_TABLE()

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  wxMenuBar  *m_pMenuBar;
  wxMenu     *m_pFileMenu;
  wxMenu     *m_pEditMenu;
  wxMenu     *m_pViewMenu;
  wxMenu     *m_pHelpMenu;

  wxMenu     *m_pCameraMenu;
  wxMenu     *m_pViewModeMenu;

}; // class EditorMainFrame


#endif // __EDITOR_MENU_H_

// -- EOF

