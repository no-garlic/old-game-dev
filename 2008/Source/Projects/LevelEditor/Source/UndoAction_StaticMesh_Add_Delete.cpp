
#include "UndoAction_StaticMesh_Add_Delete.h"
#include "Editor.h"
#include "StaticMeshUtils.h"


UndoAction_StaticMesh_Add_Delete::UndoAction_StaticMesh_Add_Delete()
{
}


UndoAction_StaticMesh_Add_Delete::~UndoAction_StaticMesh_Add_Delete()
{
}


void UndoAction_StaticMesh_Add_Delete::SetAddNode(const String &path)
{
  m_AddPath = path;
}


void UndoAction_StaticMesh_Add_Delete::SetAddMesh(const String &filename)
{
  m_AddFilename = filename;
}


void UndoAction_StaticMesh_Add_Delete::SetAddTransform(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale)
{
  m_AddPos = pos;
  m_AddRot = rot;
  m_AddScale = scale;
}


void UndoAction_StaticMesh_Add_Delete::SetDeleteNode(const String &path)
{
  m_DeletePath = path;
}


void UndoAction_StaticMesh_Add_Delete::SetDeleteMesh(const String &filename)
{
  m_DeleteFilename = filename;
}


void UndoAction_StaticMesh_Add_Delete::SetDeleteTransform(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale)
{
  m_DeletePos = pos;
  m_DeleteRot = rot;
  m_DeleteScale = scale;
}


void UndoAction_StaticMesh_Add_Delete::Undo()
{
  if (!m_AddPath.empty())
  {
    if (!StaticMeshUtils::DeleteNode(m_AddPath))
    {
      DEBUG_BREAK;
    }
  }
  if (!m_DeletePath.empty())
  {
    if (!StaticMeshUtils::AddNode(m_DeletePath, m_DeleteFilename, m_DeletePos, m_DeleteRot, m_DeleteScale))
    {
      DEBUG_BREAK;
    }
  }

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();
}


void UndoAction_StaticMesh_Add_Delete::Redo()
{
  if (!m_DeletePath.empty())
  {
    if (!StaticMeshUtils::DeleteNode(m_DeletePath))
    {
      DEBUG_BREAK;
    }
  }
  if (!m_AddPath.empty())
  {
    if (!StaticMeshUtils::AddNode(m_AddPath, m_AddFilename, m_AddPos, m_AddRot, m_AddScale))
    {
      DEBUG_BREAK;
    }
  }

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();
}


// -- EOF


