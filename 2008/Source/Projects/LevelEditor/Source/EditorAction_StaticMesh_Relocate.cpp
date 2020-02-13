
#include "EditorAction_StaticMesh_Relocate.h"
#include "Editor.h"
#include "ContentItemNode.h"
#include "StaticMeshUtils.h"
#include "UndoAction_StaticMesh_Relocate.h"


EditorAction_StaticMesh_Relocate::EditorAction_StaticMesh_Relocate()
: EditorAction  ()
{
}


EditorAction_StaticMesh_Relocate::~EditorAction_StaticMesh_Relocate()
{
}


bool EditorAction_StaticMesh_Relocate::Init(const String &nodePath)
{
  m_SrcPath = nodePath;
  return true;
}


void EditorAction_StaticMesh_Relocate::SetParameter(const String &paramName, const String &paramValue)
{
  if (StrICmp(paramName, "Path"))
  {
    m_DstPath = paramValue;
  }
}


bool EditorAction_StaticMesh_Relocate::Complete()
{
  if (m_DstPath.empty())
  {
    return false;
  }

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();

  if (StaticMeshUtils::RelocateNode(m_SrcPath, m_DstPath))
  {
    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_StaticMesh_Relocate *pUndoAction = new UndoAction_StaticMesh_Relocate();

      pUndoAction->SetSrcPath(m_SrcPath);
      pUndoAction->SetDstPath(m_DstPath);
      
      Editor.GetUndoManager()->Add(pUndoAction);
    }

    return true;
  }

  return false;
}


void EditorAction_StaticMesh_Relocate::Discard()
{
}


void EditorAction_StaticMesh_Relocate::Update()
{
}


// -- EOF

