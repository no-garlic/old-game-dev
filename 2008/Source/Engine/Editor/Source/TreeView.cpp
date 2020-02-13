
#include "TreeView.h"


TreeView::TreeView(wxWindow *pParent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
{
  m_pParentWindow = pParent;
  m_pTreeCtrl     = new wxTreeCtrl(pParent, id, pos, size, style);
}


TreeView::~TreeView()
{
  // TODO: Memory leak / delete all nodes
}


void TreeView::SetImageList(ImageList *pImageList)
{
  m_pTreeCtrl->SetImageList(pImageList);
}


TreeNode *TreeView::FindTreeNode(const TreeNodeId &id)
{
  if (id.IsOk())
  {
    wxTreeItemData *pData = m_pTreeCtrl->GetItemData(id);
    if (pData)
    {
      return static_cast<TreeNode *>(pData);
    }
  }

  return NULL;
}


TreeNode *TreeView::FindTreeNode(const String &path)
{
  String trimmedPath = path;

  if (StartsWith(trimmedPath, "/"))
  {
    trimmedPath = trimmedPath.substr(1);
  }

  String node, nextPath;
  SplitString(trimmedPath, '/', node, nextPath);

  if (node.empty())
    return NULL;

  TreeNode *pRootNode = GetRootNode();
  if (!pRootNode)
    return NULL;

  if (!StrICmp(pRootNode->GetText(), node))
    return NULL;

  if (nextPath.empty())
    return pRootNode;

  return pRootNode->FindTreeNode(nextPath);
}


bool TreeView::CheckUniqueAndValid(const String &path, const String &name)
{
  // Check that the nbase path exists
  TreeNode *pTreeNode = FindTreeNode(path);
  if (!pTreeNode)
  {
    return false;
  }

  // Check that the name is unique for the base path
  if (pTreeNode->FindTreeNode(name))
  {
    return false;
  }
  
  return true;
}


void TreeView::SetVisible(bool IsVisible)
{
  // TODO: Check this is correct
  m_pTreeCtrl->Enable(false);
}


bool TreeView::IsVisible()
{
  // TODO: Check this is correct
  return m_pTreeCtrl->IsEnabled();
}


void TreeView::SetPosition(const wxPoint &pos)
{
  m_pTreeCtrl->SetPosition(pos);
}


void TreeView::SetSize(const wxSize &size)
{
  m_pTreeCtrl->SetSize(size);
}


uint TreeView::GetCount()
{
  return m_pTreeCtrl->GetCount();
}


uint TreeView::GetIndent()
{
  return m_pTreeCtrl->GetIndent();
}


void TreeView::SetIndent(uint indent)
{
  m_pTreeCtrl->SetIndent(indent);
}


TreeNode *TreeView::GetRootNode()
{
  TreeNodeId id = m_pTreeCtrl->GetRootItem();
  return FindTreeNode(id);
}


TreeNode *TreeView::GetSelectedNode()
{
  TreeNodeId id = m_pTreeCtrl->GetSelection();
  return FindTreeNode(id);
}


void TreeView::UnSelect()
{
  m_pTreeCtrl->Unselect();
}


void TreeView::Expand()
{
  TreeNodeId id = m_pTreeCtrl->GetRootItem();

  if (id.IsOk())
    m_pTreeCtrl->Expand(id);
}


void TreeView::Collapse()
{
  TreeNodeId id = m_pTreeCtrl->GetRootItem();

  if (id.IsOk())
    m_pTreeCtrl->Collapse(id);
}


void TreeView::DeleteAllNodes()
{
  TreeNode *pSelectedNode = GetSelectedNode();
  if (pSelectedNode)
    pSelectedNode->OnLeave();

  TreeNode *pRootNode = GetRootNode();
  if (pRootNode)
  {
    delete pRootNode;
  }

  m_pTreeCtrl->DeleteAllItems();
}


void TreeView::DeleteAllNodes(Callback<void, TreeNode *> &cb)
{
  AddressAllNodes(cb);
  DeleteAllNodes();
}


void TreeView::AddressAllNodes(Callback<void, TreeNode *> &cb)
{
  TreeNode *pRootNode = GetRootNode();

  if (pRootNode)
  {
    AddressNode(pRootNode, cb);
  }
}


void TreeView::AddressNode(TreeNode *pNode, Callback<void, TreeNode *> &cb)
{
  cb(pNode);

  for (uint i = 0; i < pNode->GetChildrenCount(); i++)
  {
    AddressNode(pNode->GetChild(i), cb);
  }
}

// -- EOF

