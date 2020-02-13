
#include "EditorAction_DeleteSelected.h"
#include "Editor.h"
#include "UndoAction_SceneGroup_Add_Delete.h"
#include "UndoAction_StaticMesh_Add_Delete.h"


EditorAction_DeleteSelected::EditorAction_DeleteSelected()
: EditorAction  ()
{
}


EditorAction_DeleteSelected::~EditorAction_DeleteSelected()
{
}


bool EditorAction_DeleteSelected::Init(const String &nodePath)
{
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();

  TreeNode *pNode = NULL;
  if (nodePath.empty())
  {
    pNode = pTreeView->GetSelectedNode();
  }
  else
  {
    pNode = pTreeView->FindTreeNode(nodePath);
  }

  if (pNode && pNode->GetParentNode())
  {
    if (pNode->GetChildrenCount() != 0)
    {
      return false;
    }

    Editor.GetDocument()->SetDirty();

    if (Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode() == pNode)
    {
      Editor.GetLeftPanel()->GetScenePanel()->SetSelectedStaticMeshNode(NULL);
    }

    if (Editor.GetUndoManager()->IsActive())
    {
      String path;
      pNode->GetPath(path);

      if (pNode->GetType() == "StaticMeshNode")
      {
        StaticMeshNode *pStaticMeshNode = (StaticMeshNode *) pNode;

        UndoAction_StaticMesh_Add_Delete *pUndoAction = new UndoAction_StaticMesh_Add_Delete();

        pUndoAction->SetDeleteNode(path);
        pUndoAction->SetDeleteMesh(pStaticMeshNode->GetMesh()->GetFileHandle().GetFilename());
        pUndoAction->SetDeleteTransform(pStaticMeshNode->GetPos(), pStaticMeshNode->GetRot(), pStaticMeshNode->GetScale());

        Editor.GetUndoManager()->Add(pUndoAction);
      }
      else if (pNode->GetType() == "SceneGroupNode")
      {
        SceneGroupNode *pSceneGroupNode = (SceneGroupNode *) pNode;

        UndoAction_SceneGroup_Add_Delete *pUndoAction = new UndoAction_SceneGroup_Add_Delete();
        pUndoAction->SetDeleteNode(path);

        Editor.GetUndoManager()->Add(pUndoAction);
      }
      else
      {
        DEBUG_BREAK;
      }
    }

    pNode->GetParentNode()->DeleteChild(pNode);

    Editor.GetDocument()->SetDirty();
    Editor.GetDocument()->PreCacheSceneBounds();
    return true;
  }

  return false;
}


bool EditorAction_DeleteSelected::Complete()
{
  return true;
}


void EditorAction_DeleteSelected::Discard()
{
}


void EditorAction_DeleteSelected::Update()
{
}


// -- EOF

