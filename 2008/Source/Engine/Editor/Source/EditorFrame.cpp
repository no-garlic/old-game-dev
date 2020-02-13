
// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "EditorFrame.h"


// ----------------------------------------------------------------------------
// An editor frame, which is a seeprate window that appears within the editor
// that the modes can use to parent their user interface components on.
// ----------------------------------------------------------------------------
EditorFrame::EditorFrame(const wxPoint &pos, const wxSize &size, UINT id, bool showBorder)
: wxFrame(WxDisplay::GetFrame(), id, "", pos, size, wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR | wxNO_BORDER),
  m_pShowing (NULL)
{
  if (showBorder)
    SetWindowStyleFlag(wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
EditorFrame::~EditorFrame()
{
} 


// ----------------------------------------------------------------------------
// Override the SetPosition function
// ----------------------------------------------------------------------------
void EditorFrame::SetPosition(wxPoint pos)
{
  wxFrame::SetPosition(pos);
}


// ----------------------------------------------------------------------------
// Override the SetSize function
// ----------------------------------------------------------------------------
void EditorFrame::SetSize(wxSize size)
{
  wxFrame::SetSize(size);

  Map<String, EditorPanel *>::iterator iter(m_Panels.begin()), end(m_Panels.end());
  for (; iter != end; ++iter)
  {
    iter->second->SetSize(size);
  }
}


// ----------------------------------------------------------------------------
// Add panels to the frame
// ----------------------------------------------------------------------------
bool EditorFrame::AddPanel(EditorPanel *pPanel)
{
  String panelName = String((const char *) pPanel->GetName());
  Map<String, EditorPanel *>::iterator iter = m_Panels.find(panelName);
  if (iter != m_Panels.end())
  {
    LOG_ERROR << "Cannot add duplicate named panel: " << pPanel->GetName() << ENDLOG;
    return false;
  }

  m_Panels.insert(MakePair(panelName, pPanel));
  return true;
}


// --------------------------------------------------------------------------
// Get a panel by name
// --------------------------------------------------------------------------
EditorPanel *EditorFrame::FindPanel(const String &name)
{
  Map<String, EditorPanel *>::iterator iter = m_Panels.find(name);
  if (iter == m_Panels.end())
  {
    return NULL;
  }

  return iter->second;
}


// ----------------------------------------------------------------------------
// Show a particualr panel - only one panel is shown at a time, so if a
// panel is currently shown, it will first be hidden.
// ----------------------------------------------------------------------------
bool EditorFrame::ShowPanel(const String &name)
{
  Map<String, EditorPanel *>::iterator iter = m_Panels.find(name);
  if (iter == m_Panels.end())
  {
    LOG_ERROR << "Cannot find the panel: " << name << ENDLOG;
    return false;
  }

  if (m_pShowing)
    m_pShowing->Show(false);

  m_pShowing = iter->second;
  m_pShowing->UpdateControlLayout();
  m_pShowing->Show(true);

  return true;
}


// ----------------------------------------------------------------------------
// Hide the currently shown panel
// ----------------------------------------------------------------------------
void EditorFrame::HidePanel()
{
  if (m_pShowing)
    m_pShowing->Show(false);
}


// -- EOF


