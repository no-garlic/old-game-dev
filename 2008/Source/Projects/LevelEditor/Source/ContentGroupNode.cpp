
#include "ContentGroupNode.h"
#include "ContentItemNode.h"
#include "Editor.h"


ContentGroupNode::ContentGroupNode(wxTreeItemId id)
: TreeNode(id, "ContentGroupNode")
{
}


ContentGroupNode::~ContentGroupNode()
{
}


void ContentGroupNode::OnEnter()
{
  // Called when the node is selected
}


void ContentGroupNode::OnLeave()
{
  // Called when the node is de-selected
}


void ContentGroupNode::Create(const String &groupName)
{
  m_GroupName = groupName;

  StringMap meshes;
  Editor.GetContent()->EnumerateMeshes(groupName, meshes);

  StringMap::iterator iter(meshes.begin()), end(meshes.end());
  for (; iter != end; ++iter)
  {
    ContentItemNode *pItemNode = AddChild<ContentItemNode>(iter->first);
    pItemNode->Create(iter->first, iter->second);
  }

  ImageList *pImageList = Editor.GetImageList();
  SetIconId(pImageList->GetIndex("folder"), wxTreeItemIcon_Normal);
}


// -- EOF

