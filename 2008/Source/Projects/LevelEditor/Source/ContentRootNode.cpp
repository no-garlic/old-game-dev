
#include "ContentRootNode.h"
#include "ContentGroupNode.h"
#include "Editor.h"


ContentRootNode::ContentRootNode(wxTreeItemId id)
: TreeNode(id, "ContentRootNode")
{
}


ContentRootNode::~ContentRootNode()
{
}


void ContentRootNode::OnEnter()
{
  // Called when the node is selected
}


void ContentRootNode::OnLeave()
{
  // Called when the node is de-selected
}


void ContentRootNode::Create()
{
  StringArray groupNames;
  Editor.GetContent()->EnumerateMeshGroups(groupNames);

  for (uint i = 0; i < groupNames.size(); i++)
  {
    ContentGroupNode *pGroupNode = AddChild<ContentGroupNode>(groupNames[i]);
    pGroupNode->Create(groupNames[i]);
  }

  ImageList *pImageList = Editor.GetImageList();
  SetIconId(pImageList->GetIndex("folder"), wxTreeItemIcon_Normal);
}


// -- EOF

