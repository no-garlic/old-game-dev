
#include "UndoAction_StaticMesh_Relocate.h"
#include "Editor.h"
#include "StaticMeshUtils.h"


UndoAction_StaticMesh_Relocate::UndoAction_StaticMesh_Relocate()
{
}


UndoAction_StaticMesh_Relocate::~UndoAction_StaticMesh_Relocate()
{
}


void UndoAction_StaticMesh_Relocate::SetSrcPath(const String &path)
{
  m_SrcPath = path;
}


void UndoAction_StaticMesh_Relocate::SetDstPath(const String &path)
{
  m_DstPath = path;
}


void UndoAction_StaticMesh_Relocate::Undo()
{
  if (!StaticMeshUtils::RelocateNode(m_DstPath, m_SrcPath))
  {
    DEBUG_BREAK;
  }

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();
}


void UndoAction_StaticMesh_Relocate::Redo()
{
  if (!StaticMeshUtils::RelocateNode(m_SrcPath, m_DstPath))
  {
    DEBUG_BREAK;
  }

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();
}


// -- EOF

