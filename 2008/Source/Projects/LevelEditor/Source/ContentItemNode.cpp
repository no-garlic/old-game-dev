
#include "ContentItemNode.h"
#include "Editor.h"


ContentItemNode::ContentItemNode(wxTreeItemId id)
: TreeNode(id, "ContentItemNode")
{
}


ContentItemNode::~ContentItemNode()
{
}


void ContentItemNode::OnEnter()
{
  // Called when the node is selected
}


void ContentItemNode::OnLeave()
{
  // Called when the node is de-selected
}


void ContentItemNode::Create(const String &meshName, const String &fileName)
{
  m_MeshName = meshName;
  m_FileName = fileName;

  ImageList *pImageList = Editor.GetImageList();
  SetIconId(pImageList->GetIndex("icon_package_open"), wxTreeItemIcon_Normal);
  SetIconId(pImageList->GetIndex("icon_package_get"),  wxTreeItemIcon_Selected);
}


// -- EOF

