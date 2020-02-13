
#ifndef __TREE_NODE_H_
#define __TREE_NODE_H_


#include "libRenderExt.h"
#include "wx/treectrl.h"
#include "wx/image.h"


class TreeView;


typedef wxTreeItemId TreeNodeId;


class TreeNode : public wxTreeItemData, private Unique
{
protected:
  // The tree view manager can construct and destruct nodes
  friend class TreeView;

  // Constructor and destructor
  explicit TreeNode(TreeNodeId id, const String &type);
  virtual ~TreeNode();

  // Set the parent and the tree view
  void SetTreeView(TreeView *pTreeView);
  void SetParentNode(TreeNode *pNode);

public:
  // Get the tree node id
  TreeNodeId GetId() const { return m_Id; }

  // Get the bitfield
  BitField &GetBitField() { return m_BitField; }

  // Called when the node is selected and deselected
  virtual void OnEnter();
  virtual void OnLeave();

  // Called when the node is right clicked
  virtual void OnRightClick(const wxPoint &pos);

  // Set the node text
  void SetText(const String &text);
  String GetText() const;

  // Find the child node for the given path
  TreeNode *FindTreeNode(const String &path);
  void GetPath(String &path) const;

  // Set the icon Id
  void SetIconId(int id, wxTreeItemIcon which);

  // Force the [+] to appear on the node
  void SetHasChildren(bool showHasChildren = true);
  bool HasChildren();

  // The node children
  uint GetChildrenCount();
  TreeNode *GetChild(uint index);

  // Get the parent node
  TreeNode *GetParentNode();

  // Add children
  template <class T>
  T *AddChild(const String &text);

  // Delete children
  void DeleteChild(TreeNode *pNode);
  void DeleteAllChildren();

  // Expand and collapse
  void Expand();
  void Collapse();
  bool IsExpanded();

  // Is the node visible on the screen
  bool IsVisible();

  // Select the item
  void Select(bool select = true);
  bool IsSelected();
  void ToggleSelection();

  // Ensure this item is visible
  void EnsureVisible();

  // Scroll the tree view so this item is visible
  void ScrollTo();

  // Sort the children alphabetically
  void SortChildren();

  // Popup a menu
  void PopupMenu(wxMenu *pMenu, const wxPoint &pos);

  // Get the type name
  const String &GetType() const { return m_Type; }

  // Edit the label
  void Edit();

protected:
  TreeNodeId      m_Id;
  String          m_Type;
  TreeView       *m_pTreeView;
  TreeNode       *m_pParent;
  BitField        m_BitField;

};


template <class T>
T *TreeNode::AddChild(const String &text)
{
  TreeNodeId id = m_pTreeView->m_pTreeCtrl->AppendItem(m_Id, text.c_str());

  if (!id.IsOk())
    return NULL;

  TreeNode *pNode = new T(id);

  pNode->SetTreeView(m_pTreeView);
  pNode->SetParentNode(this);
  pNode->SetText(text);

  m_pTreeView->m_pTreeCtrl->SetItemData(id, pNode);
  m_pTreeView->m_pTreeCtrl->Refresh();

  return (T *) pNode;
}


#endif // __TREE_NODE_H_

// -- EOF


