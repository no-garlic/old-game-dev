
#include "StaticMeshUtils.h"
#include "Editor.h"
#include "StaticMeshNode.h"
#include "SceneGroupNode.h"


// Add a new static mesh node to the scene tree
bool StaticMeshUtils::AddNode(const String &path, const String &filename, const Vec3 &pos, const Vec3 &rot, const Vec3 &scale)
{
  String parent, name;
  SplitPath(path, parent, name);

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pParentNode = pTreeView->FindTreeNode(parent);

  bool treeIsEmpty = (pTreeView->GetCount() == 1);

  if (!pParentNode || pParentNode->GetType() != "SceneGroupNode")
  {
    return false;
  }

  SceneGroupNode *pGroupNode = (SceneGroupNode *) pParentNode;
  
  StaticMeshNode *pMeshNode = pGroupNode->AddChild<StaticMeshNode>(name);
  pMeshNode->Create(name, filename);

  pMeshNode->SetPos(pos.x, pos.y, pos.z);
  pMeshNode->SetRot(rot.x, rot.y, rot.z);
  pMeshNode->SetScale(scale.x, scale.y, scale.z);

  pGroupNode->Expand();
  pMeshNode->Select(true);

  // If we are adding the first item, focus on it
  if (treeIsEmpty)
  {
    Editor.GetCameraManager()->Focus();
  }

  return true;
}


// Delete a static mesh node from the scene tree
bool StaticMeshUtils::DeleteNode(const String &path)
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

    if (pNode->GetType() == "StaticMeshNode")
    {
      if (Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode() == pNode)
      {
        Editor.GetLeftPanel()->GetScenePanel()->SetSelectedStaticMeshNode(NULL);
      }

      pNode->GetParentNode()->DeleteChild(pNode);
      return true;
    }
  }

  return false;
}


// Duplicate a static mesh node in the scene tree
bool StaticMeshUtils::DuplicateNode(const String &path, const String &destPath)
{
  String newName;
  String newPath = destPath;
  if (newPath.empty())
  {
    SplitPath(path, newPath, newName);
  }
  else
  {
    SplitPath(destPath, newPath, newName);
  }

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pTreeNode = pTreeView->FindTreeNode(path);

  if (pTreeNode && pTreeNode->GetType() == "StaticMeshNode")
  {
    if (pTreeNode->GetChildrenCount() != 0)
    {
      return false;
    }

    StaticMeshNode *pMeshNode = (StaticMeshNode *) pTreeNode;

    TreeNode *pParentNode = pTreeView->FindTreeNode(newPath);

    if (pParentNode && pParentNode->GetType() == "SceneGroupNode")
    {
      SceneGroupNode *pGroupNode = (SceneGroupNode *) pParentNode;

      String outPath = newPath + "/" + newName;

      return AddNode(outPath, pMeshNode->GetMesh()->GetFileHandle().GetFilename(), 
        pMeshNode->GetPos(), pMeshNode->GetRot(), pMeshNode->GetScale());
    }
  }

  return false;
}


// Move a static mesh in the scene
bool StaticMeshUtils::MoveNode(const String &path, const Vec3 &pos, const Vec3 &rot, const Vec3 &scale)
{
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pNode = pTreeView->FindTreeNode(path);

  if (pNode && pNode->GetType() == "StaticMeshNode")
  {
    StaticMeshNode *pMeshNode = (StaticMeshNode *) pNode;

    pMeshNode->SetPos(pos.x, pos.y, pos.z);
    pMeshNode->SetRot(rot.x, rot.y, rot.z);
    pMeshNode->SetScale(scale.x, scale.y, scale.z);

    return true;
  }
  else
  {
    return false;
  }
}


// Relocate a static mesh in the tree view
bool StaticMeshUtils::RelocateNode(const String &srcPath, const String &dstPath)
{
  if (!StaticMeshUtils::DuplicateNode(srcPath, dstPath))
  {
    return false;
  }

  if (!StaticMeshUtils::DeleteNode(srcPath))
  {
    DEBUG_BREAK;
    return false;
  }

  return true;
}


// -- EOF


