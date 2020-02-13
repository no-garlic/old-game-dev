
#include "EditorAction_StaticMesh_SetTransform.h"
#include "Editor.h"
#include "ContentItemNode.h"
#include "StaticMeshUtils.h"
#include "UndoAction_StaticMesh_Transform.h"


EditorAction_StaticMesh_SetTransform::EditorAction_StaticMesh_SetTransform()
: EditorAction  ()
{
  m_Pos   = Vec3(0.0f, 0.0f, 0.f);
  m_Rot   = Vec3(0.0f, 0.0f, 0.f);
  m_Scale = Vec3(1.0f, 1.0f, 1.f);
}


EditorAction_StaticMesh_SetTransform::~EditorAction_StaticMesh_SetTransform()
{
}


bool EditorAction_StaticMesh_SetTransform::Init(const String &nodePath)
{
  m_Node = nodePath;

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pNode = pTreeView->FindTreeNode(nodePath);

  if (pNode && pNode->GetType() == "StaticMeshNode")
  {
    StaticMeshNode *pStaticMeshNode = (StaticMeshNode *) pNode;

    m_Pos = pStaticMeshNode->GetPos();
    m_Rot = pStaticMeshNode->GetRot();
    m_Scale = pStaticMeshNode->GetScale();

    m_OldPos   = m_Pos;
    m_OldRot   = m_Rot;
    m_OldScale = m_Scale;
  }

  return true;
}


void EditorAction_StaticMesh_SetTransform::SetParameter(const String &paramName, const Vec3 &paramValue)
{
  if (StrICmp(paramName, "Pos"))
  {
    m_Pos = paramValue;
  }
  else if (StrICmp(paramName, "Rot"))
  {
    m_Rot = paramValue;
  }
  else if (StrICmp(paramName, "Scale"))
  {
    m_Scale = paramValue;
  }
}


bool EditorAction_StaticMesh_SetTransform::Complete()
{
  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();

  if (StaticMeshUtils::MoveNode(m_Node, m_Pos, m_Rot, m_Scale))
  {
    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_StaticMesh_Transform *pAction = new UndoAction_StaticMesh_Transform();
      
      pAction->SetNode(m_Node);
      pAction->SetFrom(m_OldPos, m_OldRot, m_OldScale);
      pAction->SetTo(m_Pos, m_Rot, m_Scale);

      Editor.GetUndoManager()->Add(pAction);
    }

    return true;
  }

  return false;
}


void EditorAction_StaticMesh_SetTransform::Discard()
{
}


void EditorAction_StaticMesh_SetTransform::Update()
{
}


// -- EOF

