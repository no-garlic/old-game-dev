
#include "UndoAction_Rename.h"
#include "Editor.h"


UndoAction_Rename::UndoAction_Rename()
{
}


UndoAction_Rename::~UndoAction_Rename()
{
}


void UndoAction_Rename::SetPath(const String &path)
{
  m_Path = path;
}


void UndoAction_Rename::SetOldName(const String &name)
{
  m_OldName = name;
}


void UndoAction_Rename::SetNewName(const String &name)
{
  m_NewName = name;
}


void UndoAction_Rename::Undo()
{
  String nodePath = m_Path + "/" + m_NewName;

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pTreeNode = pTreeView->FindTreeNode(nodePath);

  if (pTreeNode)
  {
    ASSERT(m_OldName.length() > 0, "Name not set");
    pTreeNode->SetText(m_OldName);
  }
  else
  {
    DEBUG_BREAK;
  }
}


void UndoAction_Rename::Redo()
{
  String nodePath = m_Path + "/" + m_OldName;

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pTreeNode = pTreeView->FindTreeNode(nodePath);

  if (pTreeNode)
  {
    ASSERT(m_NewName.length() > 0, "Name not set");
    pTreeNode->SetText(m_NewName);
  }
  else
  {
    DEBUG_BREAK;
  }
}


// -- EOf

