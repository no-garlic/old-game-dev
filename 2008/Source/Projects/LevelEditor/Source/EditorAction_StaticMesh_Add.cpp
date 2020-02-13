
#include "EditorAction_StaticMesh_Add.h"
#include "Editor.h"
#include "ContentItemNode.h"
#include "StaticMeshUtils.h"
#include "UndoAction_StaticMesh_Add_Delete.h"


EditorAction_StaticMesh_Add::EditorAction_StaticMesh_Add()
: EditorAction  ()
{
  m_Pos   = Vec3(0.0f, 0.0f, 0.f);
  m_Rot   = Vec3(0.0f, 0.0f, 0.f);
  m_Scale = Vec3(1.0f, 1.0f, 1.f);
}


EditorAction_StaticMesh_Add::~EditorAction_StaticMesh_Add()
{
}


bool EditorAction_StaticMesh_Add::Init(const String &nodePath)
{
  EditorContentPanel *pContentPanel = Editor.GetLeftPanel()->GetContentPanel();
  TreeNode *pNode = pContentPanel->GetTreeView()->GetSelectedNode();

  if (pNode && pNode->GetType() == "ContentItemNode")
  {
    ContentItemNode *pContentItemNode = (ContentItemNode *) pNode;

    m_Node = nodePath;
    m_Filename = pContentItemNode->GetFileName();

    return true;
   
  }

  return false;
}


void EditorAction_StaticMesh_Add::SetParameter(const String &paramName, const Vec3 &paramValue)
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


bool EditorAction_StaticMesh_Add::Complete()
{
  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();

  if (StaticMeshUtils::AddNode(m_Node, m_Filename))
  {
    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_StaticMesh_Add_Delete *pUndoAction = new UndoAction_StaticMesh_Add_Delete();

      pUndoAction->SetAddNode(m_Node);
      pUndoAction->SetAddMesh(m_Filename);
      pUndoAction->SetAddTransform(m_Pos, m_Rot, m_Scale);
      
      Editor.GetUndoManager()->Add(pUndoAction);
    }

    return true;
  }

  return false;
}


void EditorAction_StaticMesh_Add::Discard()
{
}


void EditorAction_StaticMesh_Add::Update()
{
}


// -- EOF

