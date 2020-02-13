
#include "EditorAction_Clipboard_Paste.h"
#include "StaticMeshUtils.h"
#include "UndoAction_StaticMesh_Add_Delete.h"
#include "Editor.h"


EditorAction_Clipboard_Paste::EditorAction_Clipboard_Paste()
: EditorAction  ()
{
}


EditorAction_Clipboard_Paste::~EditorAction_Clipboard_Paste()
{
}


bool EditorAction_Clipboard_Paste::Init(const String &nodePath)
{
  return true;
}


bool EditorAction_Clipboard_Paste::Complete()
{
  if (!Editor.GetActionManager()->GetClipboard().IsValid)
  {
    return false;
  }

  Editor.GetDocument()->SetDirty();

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pTreeNode = pTreeView->GetSelectedNode();

  String newPath;
  if (pTreeNode)
  {
    if (pTreeNode->GetType() == "StaticMeshNode")
    {
      pTreeNode = pTreeNode->GetParentNode();
    }
    if (pTreeNode && pTreeNode->GetType() == "SceneGroupNode")
    {
      pTreeNode->GetPath(newPath);
    }
    else
    {
      return false;
    }
  }

  String oldName, oldPath;
  SplitPath(Editor.GetActionManager()->GetClipboard().Path, oldPath, oldName);

  String outPath = newPath + "/" + Editor.GetNextName(oldName);

  if (!StaticMeshUtils::DuplicateNode(Editor.GetActionManager()->GetClipboard().Path, outPath))
  {
    return false;
  }

  if (Editor.GetActionManager()->GetClipboard().IsCut)
  {
    if (!StaticMeshUtils::DeleteNode(Editor.GetActionManager()->GetClipboard().Path))
    {
      return false;
    }
    Editor.GetActionManager()->GetClipboard().IsValid = false;
  }

  if (Editor.GetUndoManager()->IsActive())
  {
    TreeNode *pTreeNode = pTreeView->FindTreeNode(outPath);
    NULL_ASSERT(pTreeNode);
    
    if (pTreeNode && pTreeNode->GetType() == "StaticMeshNode")
    {
      StaticMeshNode *pStaticMeshNode = (StaticMeshNode *) pTreeNode;

      UndoAction_StaticMesh_Add_Delete *pUndoAction = new UndoAction_StaticMesh_Add_Delete();

      pUndoAction->SetAddNode(outPath);
      pUndoAction->SetAddMesh(pStaticMeshNode->GetMesh()->GetFileHandle().GetFilename());
      pUndoAction->SetAddTransform(pStaticMeshNode->GetPos(), pStaticMeshNode->GetRot(), pStaticMeshNode->GetScale());

      if (Editor.GetActionManager()->GetClipboard().IsCut)
      {
        pUndoAction->SetDeleteNode(Editor.GetActionManager()->GetClipboard().Path);
        pUndoAction->SetDeleteMesh(pStaticMeshNode->GetMesh()->GetFileHandle().GetFilename());
        pUndoAction->SetDeleteTransform(pStaticMeshNode->GetPos(), pStaticMeshNode->GetRot(), pStaticMeshNode->GetScale());
      }

      Editor.GetUndoManager()->Add(pUndoAction);
    }
    else
    {
      DEBUG_BREAK;
    }      
  }

  return true;
}


void EditorAction_Clipboard_Paste::Discard()
{
}


void EditorAction_Clipboard_Paste::Update()
{
}


// -- EOF

