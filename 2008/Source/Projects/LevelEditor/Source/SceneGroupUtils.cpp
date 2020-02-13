
#include "SceneGroupUtils.h"
#include "Editor.h"
#include "SceneGroupNode.h"


bool SceneGroupUtils::AddNode(const String &path)
{
  String parent, name;
  SplitPath(path, parent, name);

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pParentNode = pTreeView->FindTreeNode(parent);

  if (!pParentNode || pParentNode->GetType() != "SceneGroupNode")
  {
    return false;
  }

  SceneGroupNode *pParentGroupNode = (SceneGroupNode *) pParentNode;

  SceneGroupNode *pGroupNode = pParentGroupNode->AddChild<SceneGroupNode>(name);
  pGroupNode->Create();

  pParentGroupNode->Expand();
  pGroupNode->Select();

  return true;
}


bool SceneGroupUtils::DeleteNode(const String &path)
{
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();

  TreeNode *pNode = NULL;
  if (path.empty())
  {
    pNode = pTreeView->GetSelectedNode();
  }
  else
  {
    pNode = pTreeView->FindTreeNode(path);
  }

  if (pNode && pNode->GetParentNode())
  {
    if (pNode->GetChildrenCount() != 0)
    {
      return false;
    }

    if (pNode->GetType() == "SceneGroupNode")
    {
      pNode->GetParentNode()->DeleteChild(pNode);
      return true;
    }
  }

  return false;
}


// -- EOF

