
#ifndef __EDITOR_FRAME_H_
#define __EDITOR_FRAME_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "EditorPanel.h"


// ----------------------------------------------------------------------------
// An editor frame, which is a seeprate window that appears within the editor
// that the modes can use to parent their user interface components on.
// ----------------------------------------------------------------------------
class EditorFrame : public wxFrame
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  EditorFrame(const wxPoint &pos, const wxSize &size, UINT id, bool showBorder = false);
  virtual ~EditorFrame();

  // --------------------------------------------------------------------------
  // Override the set position and size event functions
  // --------------------------------------------------------------------------
  virtual void SetPosition(wxPoint pos);
  virtual void SetSize(wxSize size);

  // --------------------------------------------------------------------------
  // Add panels to the frame
  // --------------------------------------------------------------------------
  bool AddPanel(EditorPanel *pPanel);

  // --------------------------------------------------------------------------
  // Show a particualr panel - only one panel is shown at a time, so if a
  // panel is currently shown, it will first be hidden.
  // --------------------------------------------------------------------------
  bool ShowPanel(const String &name);

  // --------------------------------------------------------------------------
  // Hide the currently shown panel
  // --------------------------------------------------------------------------
  void HidePanel();

  // --------------------------------------------------------------------------
  // Get a panel by name
  // --------------------------------------------------------------------------
  EditorPanel *FindPanel(const String &name);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Map<String, EditorPanel *>  m_Panels;
  EditorPanel                *m_pShowing;

};


#endif // __EDITOR_FRAME_H_

// -- EOF

