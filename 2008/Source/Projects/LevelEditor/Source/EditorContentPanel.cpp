
#include "EditorContentPanel.h"
#include "EditorResource.h"
#include "ContentRootNode.h"
#include "Editor.h"


BEGIN_EVENT_TABLE(EditorContentPanel, wxPanel)
  EVT_TREE_SEL_CHANGED(CTL_CONTENT_TREE, EditorContentPanel::OnItemChanged)
  EVT_TREE_ITEM_RIGHT_CLICK(CTL_CONTENT_TREE, EditorContentPanel::OnItemRightClick)
END_EVENT_TABLE()


EditorContentPanel::EditorContentPanel(wxWindow *pParent)
: wxPanel(pParent, EDT_CONTENT_PANEL)
{
  // Create the tree view
  m_pTreeView = new TreeView(this, CTL_CONTENT_TREE, wxPoint(0, 0), 
    pParent->GetSize(), wxBORDER_NONE | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT);

  // Set the image list
  m_pTreeView->SetImageList(Editor.GetImageList());
}


EditorContentPanel::~EditorContentPanel()
{
}


void EditorContentPanel::RefreshData()
{
  // Clear the tree view
  m_pTreeView->DeleteAllNodes();

  // Create the root node
  ContentRootNode *pRootNode = m_pTreeView->AddRootNode<ContentRootNode>("Content");

  // Build the tree items
  pRootNode->Create();

  // Expand the tree view
  m_pTreeView->Expand();
}


void EditorContentPanel::OnItemRightClick(wxTreeEvent &event)
{
  // Get the mouse cursor position
  POINT pt;
  ::GetCursorPos(&pt);
  ::ScreenToClient((HWND) this->GetHWND(), &pt);
  
  // Call the OnRightClick method of the node
  wxTreeItemId itemId = event.GetItem();
  TreeNode *pNode = m_pTreeView->FindTreeNode(itemId);
  if (pNode)
  {
    pNode->OnRightClick(wxPoint(pt.x, pt.y));
  }
}


void EditorContentPanel::OnItemChanged(wxTreeEvent &event)
{
  // Get the old and new items from the tree view
  TreeNode *pNewNode = m_pTreeView->FindTreeNode(event.GetItem());
  TreeNode *pOldNode = m_pTreeView->FindTreeNode(event.GetOldItem());

  // CAll OnLeave for the old item
  if (pOldNode)
  {
    pOldNode->OnLeave();
  }

  // Call OnEnter for the new item
  if (pNewNode)
  {
    pNewNode->OnEnter();
  }
}


// -- EOF

