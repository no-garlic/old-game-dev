
#include "TreeView.h"
#include "TreeNode.h"
#include "EditorFrame.h"


TreeNode::TreeNode(TreeNodeId id, const String &type)
: m_pTreeView       (NULL),
  m_pParent         (NULL),
  m_Id              (id),
  m_Type            (type)
{
}


TreeNode::~TreeNode()
{
  DeleteAllChildren();
}


void TreeNode::SetTreeView(TreeView *pTreeView)
{
  m_pTreeView = pTreeView;
}


void TreeNode::SetParentNode(TreeNode *pNode)
{
  m_pParent = pNode;
}


void TreeNode::PopupMenu(wxMenu *pMenu, const wxPoint &pos)
{
  m_pTreeView->m_pTreeCtrl->PopupMenu(pMenu, pos);
}


void TreeNode::SetText(const String &text)
{
  m_pTreeView->m_pTreeCtrl->SetItemText(m_Id, text.c_str());
}


String TreeNode::GetText() const
{
  return m_pTreeView->m_pTreeCtrl->GetItemText(m_Id).wx_str();
}


void TreeNode::SetIconId(int id, wxTreeItemIcon which)
{
  m_pTreeView->m_pTreeCtrl->SetItemImage(m_Id, id, which);
}


void TreeNode::SetHasChildren(bool showHasChildrentrue)
{
  m_pTreeView->m_pTreeCtrl->SetItemHasChildren(m_Id, showHasChildrentrue);
}


bool TreeNode::HasChildren()
{
  return m_pTreeView->m_pTreeCtrl->ItemHasChildren(m_Id);
}


bool TreeNode::IsVisible()
{
  return m_pTreeView->m_pTreeCtrl->IsVisible(m_Id);
}


uint TreeNode::GetChildrenCount()
{
  return m_pTreeView->m_pTreeCtrl->GetChildrenCount(m_Id, false);
}


TreeNode *TreeNode::GetChild(uint index)
{
  if (index >= GetChildrenCount())
    return NULL;

  wxTreeItemIdValue cookie;
  TreeNodeId childId = m_pTreeView->m_pTreeCtrl->GetFirstChild(m_Id, cookie);

  for (uint i = 0; i < index; i++)
  {
    childId = m_pTreeView->m_pTreeCtrl->GetNextChild(m_Id, cookie);
  }

  return m_pTreeView->FindTreeNode(childId);
}


TreeNode *TreeNode::GetParentNode()
{
  return m_pParent;
}


void TreeNode::DeleteChild(TreeNode *pNode)
{
  TreeNodeId id = pNode->m_Id;

  //delete pNode;

  m_pTreeView->m_pTreeCtrl->Delete(id);
}


void TreeNode::DeleteAllChildren()
{
  //for (uint i = 0; i < GetChildrenCount(); i++)
  //{
    //delete GetChild(i); 
  //}

  m_pTreeView->m_pTreeCtrl->DeleteChildren(m_Id);
}


TreeNode *TreeNode::FindTreeNode(const String &path)
{
  if (path.empty())
    return this;

  String node, nextPath;
  SplitString(path, '/', node, nextPath);

  if (node.empty())
    return NULL;

  for (uint i = 0; i < GetChildrenCount(); i++)
  {
    TreeNode *pChildNode = GetChild(i);

    if (StrICmp(pChildNode->GetText(), node))
    {
      return pChildNode->FindTreeNode(nextPath);
    }
  }

  return NULL;
}


void TreeNode::GetPath(String &path) const
{
  if (m_pParent)
  {
    m_pParent->GetPath(path);
    path += "/";
  }

  path += GetText();
}


void TreeNode::Expand()
{
  m_pTreeView->m_pTreeCtrl->Expand(m_Id);
}


void TreeNode::Collapse()
{
  m_pTreeView->m_pTreeCtrl->Collapse(m_Id);
}


bool TreeNode::IsExpanded()
{
  return m_pTreeView->m_pTreeCtrl->IsExpanded(m_Id);
}


void TreeNode::Select(bool select)
{
  m_pTreeView->m_pTreeCtrl->SelectItem(m_Id, select);
}


bool TreeNode::IsSelected()
{
  return m_pTreeView->m_pTreeCtrl->IsSelected(m_Id);
}


void TreeNode::ToggleSelection()
{
  m_pTreeView->m_pTreeCtrl->ToggleItemSelection(m_Id);
}


void TreeNode::EnsureVisible()
{
  m_pTreeView->m_pTreeCtrl->EnsureVisible(m_Id);
}


void TreeNode::ScrollTo()
{
  m_pTreeView->m_pTreeCtrl->ScrollTo(m_Id);
}


void TreeNode::SortChildren()
{
  m_pTreeView->m_pTreeCtrl->SortChildren(m_Id);
}


void TreeNode::OnEnter()
{
}


void TreeNode::OnLeave()
{
}


void TreeNode::OnRightClick(const wxPoint &pos)
{
}


void TreeNode::Edit()
{
  m_pTreeView->m_pTreeCtrl->EditLabel(m_Id);
}

// -- EOF

