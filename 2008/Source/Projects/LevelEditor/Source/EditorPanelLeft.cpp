
#include "EditorPanelLeft.h"
#include "EditorResource.h"


EditorPanelLeft::EditorPanelLeft(EditorFrame *pParent)
: EditorPanel (pParent, EDT_LEFT_PANEL, "LEFT")
{
  m_pBook = new wxBookCtrl(this, CTL_SIDEPANEL_BOOK, wxDefaultPosition, pParent->GetSize());

  m_pContentPanel = new EditorContentPanel(m_pBook);
  m_pScenePanel   = new EditorScenePanel(m_pBook);

  m_pBook->AddPage(m_pScenePanel,   "Scene",   true);
  m_pBook->AddPage(m_pContentPanel, "Content", false);
}


EditorPanelLeft::~EditorPanelLeft()
{
}


void EditorPanelLeft::UpdateControlLayout()
{
  const int offset = 2;

  wxSize size = GetSize();
  size.x -= (offset * 2);
  size.y -= (offset * 2);

  m_pBook->SetPosition(wxPoint(offset, offset));
  m_pBook->SetSize(size);

  m_pContentPanel->GetTreeView()->SetSize(m_pContentPanel->GetSize());
  m_pScenePanel->GetTreeView()->SetSize(m_pScenePanel->GetSize());
}


// -- EOF

