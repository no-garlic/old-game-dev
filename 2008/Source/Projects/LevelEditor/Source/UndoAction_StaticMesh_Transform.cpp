
#include "UndoAction_StaticMesh_Transform.h"
#include "Editor.h"
#include "StaticMeshUtils.h"


UndoAction_StaticMesh_Transform::UndoAction_StaticMesh_Transform()
{
}


UndoAction_StaticMesh_Transform::~UndoAction_StaticMesh_Transform()
{
}


void UndoAction_StaticMesh_Transform::SetNode(const String &path)
{
  m_Node = path;
}


void UndoAction_StaticMesh_Transform::SetFrom(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale)
{
  m_FromPos = pos;
  m_FromRot = rot;
  m_FromScale = scale;
}


void UndoAction_StaticMesh_Transform::SetTo(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale)
{
  m_ToPos = pos;
  m_ToRot = rot;
  m_ToScale = scale;
}


void UndoAction_StaticMesh_Transform::Undo()
{
  if (!StaticMeshUtils::MoveNode(m_Node, m_FromPos, m_FromRot, m_FromScale))
  {
    DEBUG_BREAK;
  }

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();
}


void UndoAction_StaticMesh_Transform::Redo()
{
  if (!StaticMeshUtils::MoveNode(m_Node, m_ToPos, m_ToRot, m_ToScale))
  {
    DEBUG_BREAK;
  }

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();
}


// -- EOF

