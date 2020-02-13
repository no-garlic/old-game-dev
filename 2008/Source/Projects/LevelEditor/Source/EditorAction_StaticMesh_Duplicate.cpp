
#include "EditorAction_StaticMesh_Duplicate.h"
#include "Editor.h"
#include "StaticMeshUtils.h"
#include "UndoAction_StaticMesh_Add_Delete.h"


EditorAction_StaticMesh_Duplicate::EditorAction_StaticMesh_Duplicate()
: EditorAction  ()
{
}


EditorAction_StaticMesh_Duplicate::~EditorAction_StaticMesh_Duplicate()
{
}


bool EditorAction_StaticMesh_Duplicate::Init(const String &nodePath)
{
  m_SrcNode = nodePath;
  return true;
}


void EditorAction_StaticMesh_Duplicate::SetParameter(const String &paramName, const String &paramValue)
{
  if (StrICmp(paramName, "Path"))
  {
    m_DstNode = paramValue;
  }
}


bool EditorAction_StaticMesh_Duplicate::Complete()
{
  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();

  if (StaticMeshUtils::DuplicateNode(m_SrcNode, m_DstNode))
  {
    StaticMeshNode *pStaticMeshNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
    NULL_ASSERT(pStaticMeshNode);

    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_StaticMesh_Add_Delete *pUndoAction = new UndoAction_StaticMesh_Add_Delete();

      String path;
      pStaticMeshNode->GetPath(path);

      pUndoAction->SetDeleteNode(path);
      pUndoAction->SetDeleteMesh(pStaticMeshNode->GetMesh()->GetFileHandle().GetFilename());
      pUndoAction->SetDeleteTransform(pStaticMeshNode->GetPos(), pStaticMeshNode->GetRot(), pStaticMeshNode->GetScale());

      Editor.GetUndoManager()->Add(pUndoAction);
    }

    return true;
  }

  return false;
}


void EditorAction_StaticMesh_Duplicate::Discard()
{
}


void EditorAction_StaticMesh_Duplicate::Update()
{
}


// -- EOF

