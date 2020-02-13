
#include "EditorAction_StaticMesh_Rename.h"
#include "Editor.h"
#include "UndoAction_Rename.h"


EditorAction_StaticMesh_Rename::EditorAction_StaticMesh_Rename()
: EditorAction  ()
{
}


EditorAction_StaticMesh_Rename::~EditorAction_StaticMesh_Rename()
{
}


bool EditorAction_StaticMesh_Rename::Init(const String &nodePath)
{
  m_Node = nodePath;
  return true;
}


void EditorAction_StaticMesh_Rename::SetParameter(const String &paramName, const String &paramValue)
{
  if (StrICmp(paramName, "Name"))
  {
    m_Name = paramValue;
  }
}


bool EditorAction_StaticMesh_Rename::Complete()
{
  if (m_Name.empty())
  {
    return false;
  }

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pTreeNode = pTreeView->FindTreeNode(m_Node);

  if (!pTreeNode)
  {
    return false;
  }

  Editor.GetDocument()->SetDirty();

  if (Editor.GetUndoManager()->IsActive())
  {
    String path, name;
    SplitPath(m_Node, path, name);

    UndoAction_Rename *pUndoAction = new UndoAction_Rename();
    pUndoAction->SetPath(path);
    pUndoAction->SetOldName(pTreeNode->GetText());
    pUndoAction->SetNewName(m_Name);

    Editor.GetUndoManager()->Add(pUndoAction);
  }

  pTreeNode->SetText(m_Name);
  Editor.GetDocument()->SetDirty();
  return true;
}


void EditorAction_StaticMesh_Rename::Discard()
{
}


void EditorAction_StaticMesh_Rename::Update()
{
}


// -- EOF

