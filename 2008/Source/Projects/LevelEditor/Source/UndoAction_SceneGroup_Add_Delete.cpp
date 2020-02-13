
#include "UndoAction_SceneGroup_Add_Delete.h"
#include "Editor.h"
#include "SceneGroupUtils.h"


UndoAction_SceneGroup_Add_Delete::UndoAction_SceneGroup_Add_Delete()
{
}


UndoAction_SceneGroup_Add_Delete::~UndoAction_SceneGroup_Add_Delete()
{
}


void UndoAction_SceneGroup_Add_Delete::SetAddNode(const String &path)
{
  m_AddPath = path;
}


void UndoAction_SceneGroup_Add_Delete::SetDeleteNode(const String &path)
{
  m_DeletePath = path;
}


void UndoAction_SceneGroup_Add_Delete::Undo()
{
  if (!m_AddPath.empty())
  {
    if (!SceneGroupUtils::DeleteNode(m_AddPath))
    {
      DEBUG_BREAK;
    }
  }
  if (!m_DeletePath.empty())
  {
    if (!SceneGroupUtils::AddNode(m_DeletePath))
    {
      DEBUG_BREAK;
    }
  }
}


void UndoAction_SceneGroup_Add_Delete::Redo()
{
  if (!m_DeletePath.empty())
  {
    if (!SceneGroupUtils::DeleteNode(m_DeletePath))
    {
      DEBUG_BREAK;
    }
  }
  if (!m_AddPath.empty())
  {
    if (!SceneGroupUtils::AddNode(m_AddPath))
    {
      DEBUG_BREAK;
    }
  }
}


// -- EOF


