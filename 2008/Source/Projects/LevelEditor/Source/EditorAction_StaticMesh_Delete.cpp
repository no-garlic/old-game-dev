
#include "EditorAction_StaticMesh_Delete.h"
#include "Editor.h"
#include "StaticMeshUtils.h"
#include "UndoAction_StaticMesh_Add_Delete.h"


EditorAction_StaticMesh_Delete::EditorAction_StaticMesh_Delete()
: EditorAction  ()
{
}


EditorAction_StaticMesh_Delete::~EditorAction_StaticMesh_Delete()
{
}


bool EditorAction_StaticMesh_Delete::Init(const String &nodePath)
{
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pTreeNode = pTreeView->FindTreeNode(nodePath);

  if (!pTreeNode || pTreeNode->GetType() != "StaticMeshNode")
  {
    return false;
  }

  StaticMeshNode *pStaticMeshNode = (StaticMeshNode *) pTreeNode;

  UndoAction_StaticMesh_Add_Delete *pUndoAction = new UndoAction_StaticMesh_Add_Delete();

  pUndoAction->SetDeleteNode(nodePath);
  pUndoAction->SetDeleteMesh(pStaticMeshNode->GetMesh()->GetFileHandle().GetFilename());
  pUndoAction->SetDeleteTransform(pStaticMeshNode->GetPos(), pStaticMeshNode->GetRot(), pStaticMeshNode->GetScale());

  if (StaticMeshUtils::DeleteNode(nodePath))
  {
    if (Editor.GetUndoManager()->IsActive())
    {
      Editor.GetUndoManager()->Add(pUndoAction);
      return true;
    }

    delete pUndoAction;
    return true;
  }

  delete pUndoAction;
  return false;
}


bool EditorAction_StaticMesh_Delete::Complete()
{
  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();
  return true;
}


void EditorAction_StaticMesh_Delete::Discard()
{
}


void EditorAction_StaticMesh_Delete::Update()
{
}


// -- EOF

