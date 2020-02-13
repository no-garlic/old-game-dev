
#ifndef __EDITOR_PANEL_H_
#define __EDITOR_PANEL_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "wxWindows/wxDisplay.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class EditorFrame;


// ----------------------------------------------------------------------------
// The base class for an editor panel. Override this class and add controls
// to make a panel that can be parented on an EditorFrame.
// ----------------------------------------------------------------------------
class EditorPanel : public wxPanel
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  EditorPanel(EditorFrame *pParent, UINT id, const String &name);
  virtual ~EditorPanel();

  // --------------------------------------------------------------------------
  // Override the set position and size event functions
  // --------------------------------------------------------------------------
  virtual void SetPosition(wxPoint pos);
  virtual void SetSize(wxSize size);

protected:
  // --------------------------------------------------------------------------
  // Friend class
  // --------------------------------------------------------------------------
  friend class EditorFrame;

  // --------------------------------------------------------------------------
  // Virtual function to update the layout of the controls if the parent frame's
  // dimensions are changed.
  // --------------------------------------------------------------------------
  virtual void UpdateControlLayout() = 0;

};


#endif // __EDITOR_PANEL_H_

// -- EOF


