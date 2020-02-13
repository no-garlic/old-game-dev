
#include "UndoAction_Flag.h"
#include "Editor.h"


UndoAction_Flag::UndoAction_Flag()
{
}


UndoAction_Flag::~UndoAction_Flag()
{
}


void UndoAction_Flag::AddFlag(const String &nodePath, bool add, uint flag)
{
  UndoAction_Flag::FlagData flagData;

  flagData.m_Path   = nodePath;
  flagData.m_Add    = add;
  flagData.m_Flag   = flag;

  m_Flags.push_back(flagData);
}


void UndoAction_Flag::Undo()
{
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();

  for (uint i = 0; i < m_Flags.size(); i++)
  {
    const UndoAction_Flag::FlagData &flagData = m_Flags[i];

    TreeNode *pTreeNode = pTreeView->FindTreeNode(flagData.m_Path);
    NULL_ASSERT(pTreeNode);

    if (pTreeNode)
    {
      if (flagData.m_Add)
      {
        pTreeNode->GetBitField().Remove(flagData.m_Flag);
      }
      else
      {
        pTreeNode->GetBitField().Add(flagData.m_Flag);
      }
    }
  }
}


void UndoAction_Flag::Redo()
{
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();

  for (uint i = 0; i < m_Flags.size(); i++)
  {
    const UndoAction_Flag::FlagData &flagData = m_Flags[i];

    TreeNode *pTreeNode = pTreeView->FindTreeNode(flagData.m_Path);
    NULL_ASSERT(pTreeNode);

    if (pTreeNode)
    {
      if (flagData.m_Add)
      {
        pTreeNode->GetBitField().Add(flagData.m_Flag);
      }
      else
      {
        pTreeNode->GetBitField().Remove(flagData.m_Flag);
      }
    }
  }
}


// -- EOF


