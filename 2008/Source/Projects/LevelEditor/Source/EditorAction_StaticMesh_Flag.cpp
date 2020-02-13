
#include "EditorAction_StaticMesh_Flag.h"
#include "Editor.h"
#include "ContentItemNode.h"
#include "StaticMeshUtils.h"
#include "UndoAction_Flag.h"


EditorAction_StaticMesh_Flag::EditorAction_StaticMesh_Flag()
: EditorAction  ()
{
  m_Flag  = 0;
  m_Value = 0;
  m_Add   = true;
}


EditorAction_StaticMesh_Flag::~EditorAction_StaticMesh_Flag()
{
}


bool EditorAction_StaticMesh_Flag::Init(const String &nodePath)
{
  m_Node = nodePath;
  return true;
}


void EditorAction_StaticMesh_Flag::SetParameter(const String &paramName, bool paramValue)
{
  if (StrICmp(paramName, "Add"))
  {
    m_Add = paramValue;
  }
}


void EditorAction_StaticMesh_Flag::SetParameter(const String &paramName, uint paramValue)
{
  if (StrICmp(paramName, "Flag"))
  {
    m_Flag = paramValue;
  }
}


bool EditorAction_StaticMesh_Flag::Complete()
{
  if (m_Flag == 0)
  {
    return false;
  }

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pTreeNode = pTreeView->FindTreeNode(m_Node);

  if (!pTreeNode || pTreeNode->GetType() != "StaticMeshNode")
  {
    return false;
  }

#if _DEBUG
  // Check that we are definately changing the value
  bool testVal = pTreeNode->GetBitField().Test(m_Flag);
  ASSERT(testVal != m_Add, "Changing a flag to the same value it already is");
#endif

  if (m_Add)
  {
    pTreeNode->GetBitField().Add(m_Flag);
  }
  else
  {
    pTreeNode->GetBitField().Remove(m_Flag);
  }

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();

  if (Editor.GetUndoManager()->IsActive())
  {
    UndoAction_Flag *pUndoAction = new UndoAction_Flag();

    pUndoAction->AddFlag(m_Node, m_Add, m_Flag);
    
    Editor.GetUndoManager()->Add(pUndoAction);
  }

  return true;
}


void EditorAction_StaticMesh_Flag::Discard()
{
}


void EditorAction_StaticMesh_Flag::Update()
{
}


// -- EOF

