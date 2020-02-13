
// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "EditorPanel.h"
#include "EditorFrame.h"


// ----------------------------------------------------------------------------
// The base class for an editor panel. Override this class and add controls
// to make a panel that can be parented on an EditorFrame.
// ----------------------------------------------------------------------------
EditorPanel::EditorPanel(EditorFrame *pParent, UINT id, const String &name)
: wxPanel(pParent, id, wxPoint(0, 0))
{
  SetName(name.c_str());
  pParent->AddPanel(this);
  Show(false);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
EditorPanel::~EditorPanel()
{
}


// ----------------------------------------------------------------------------
// Override the SetPosition function
// ----------------------------------------------------------------------------
void EditorPanel::SetPosition(wxPoint pos)
{
  wxPanel::SetPosition(pos);
  UpdateControlLayout();
}


// ----------------------------------------------------------------------------
// Override the SetSize function
// ----------------------------------------------------------------------------
void EditorPanel::SetSize(wxSize size)
{
  wxPanel::SetSize(size);
  UpdateControlLayout();
}


// -- EOF

