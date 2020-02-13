
#ifndef __TREE_VIEW_H_
#define __TREE_VIEW_H_


#include "libRenderExt.h"
#include "TreeNode.h"
#include "ImageList.h"
#include "wx/treectrl.h"
#include "wx/image.h"


class TreeView : private Unique
{
public:
  // Constructor and destructor
  TreeView(wxWindow *pParent, 
           wxWindowID id = wxID_ANY, 
           const wxPoint& pos = wxDefaultPosition, 
           const wxSize& size = wxDefaultSize, 
           long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT);
  virtual ~TreeView();

  // Manage the visibliity
  void SetVisible(bool IsVisible);
  bool IsVisible();

  // Set the image list
  void SetImageList(ImageList *pImageList);

  // Set the position and size
  void SetPosition(const wxPoint &pos);
  void SetSize(const wxSize &size);

  // Get the total number nodes in the tree
  uint GetCount();

  // Number of pixels to indnt children
  uint GetIndent();
  void SetIndent(uint indent);

  // Add the root node
  template <class T>
  T *AddRootNode(const String &text);

  // Get the root node
  TreeNode *GetRootNode();

  // Get the selected node
  TreeNode *GetSelectedNode();

  // Remove the current selection
  void UnSelect();

  // Expand or collapse the entire tree
  void Expand();
  void Collapse();

  // Delete all items from the tree
  void DeleteAllNodes();
  void DeleteAllNodes(Callback<void, TreeNode *> &cb);

  // Call the callback on all nodes in the tree
  void AddressAllNodes(Callback<void, TreeNode *> &cb);

  // Find the node in the tree from the item id
  TreeNode *FindTreeNode(const TreeNodeId &id);
  TreeNode *FindTreeNode(const String &path);

  // Check that the path exists and the name is unique
  bool CheckUniqueAndValid(const String &path, const String &name);

protected:
  friend class TreeNode;

  void AddressNode(TreeNode *pNode, Callback<void, TreeNode *> &cb);

  wxWindow     *m_pParentWindow;
  wxTreeCtrl   *m_pTreeCtrl;

};


template <class T>
T *TreeView::AddRootNode(const String &text)
{
  TreeNodeId id = m_pTreeCtrl->AddRoot(text.c_str());

  if (!id.IsOk())
    return NULL;

  TreeNode *pNode = new T(id);

  pNode->SetTreeView(this);
  pNode->SetParentNode(NULL);
  pNode->SetText(text);

  m_pTreeCtrl->SetItemData(id, pNode);
  Expand();

  return (T *) pNode;
}


#endif // __TREE_VIEW_H_

// -- EOF

