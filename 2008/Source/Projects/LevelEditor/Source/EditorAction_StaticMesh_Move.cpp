
#include "EditorAction_StaticMesh_Move.h"
#include "Editor.h"
#include "StaticMeshUtils.h"
#include "UndoAction_StaticMesh_Add_Delete.h"
#include "UndoAction_StaticMesh_Transform.h"


EditorAction_StaticMesh_Move::EditorAction_StaticMesh_Move()
: EditorAction  (),
  m_pNode       (NULL),
  m_pOrigNode   (NULL),
  m_Duplicate   (false)
{
}


EditorAction_StaticMesh_Move::~EditorAction_StaticMesh_Move()
{
}


bool EditorAction_StaticMesh_Move::Init(const String &nodePath)
{
  TreeNode *pNode = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView()->FindTreeNode(nodePath);
  if (!pNode)
  {
    return false;
  }

  if (pNode->GetType() != "StaticMeshNode")
  {
    return false;
  }

  if (Input.GetKeyboardState(KEYPARAM_LSHIFT) == KEYVAL_DOWN || Input.GetKeyboardState(KEYPARAM_RSHIFT) == KEYVAL_DOWN)
  {
    m_Duplicate = true;
  }

  m_pNode = (StaticMeshNode *) pNode;
  m_pOrigNode = m_pNode;

  if (m_Duplicate)
  {
    String basePath, baseName;
    SplitPath(nodePath, basePath, baseName);

    baseName = Editor.GetNextName(baseName);

    String newPath = basePath + "/" + baseName;

    StaticMeshUtils::DuplicateNode(nodePath, newPath);
    m_pNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
  }

  m_Pos   = m_pNode->GetPos();
  m_Rot   = m_pNode->GetRot();
  m_Scale = m_pNode->GetScale();

  GetCursorPos(&m_StartPoint);
  m_LastPoint.x = ~0;
  m_LastPoint.y = ~0;

  m_PlaneInitPos = m_pNode->GetMatrix().GetTAxis();

  Plane xPlane(1.0f, 0.0f, 0.0f, m_PlaneInitPos.x);
  Plane yPlane(0.0f, 1.0f, 0.0f, m_PlaneInitPos.y);
  Plane zPlane(0.0f, 0.0f, 1.0f, m_PlaneInitPos.z);

  switch(Editor.GetToolPanel()->GetToolAxis())
  {
    case ToolPanel::TA_X:
    {
      if (fabs(yPlane.GetNormal().Dot(Camera.GetLook())) > fabs(zPlane.GetNormal().Dot(Camera.GetLook())))
        m_Plane = yPlane;
      else 
        m_Plane = zPlane;
      break;
    }

    case ToolPanel::TA_Y:
    {
      if (fabs(xPlane.GetNormal().Dot(Camera.GetLook())) > fabs(zPlane.GetNormal().Dot(Camera.GetLook())))
        m_Plane = xPlane;
      else 
        m_Plane = zPlane;
      break;
    }

    case ToolPanel::TA_Z:
    {
      if (fabs(xPlane.GetNormal().Dot(Camera.GetLook())) > fabs(yPlane.GetNormal().Dot(Camera.GetLook())))
        m_Plane = xPlane;
      else 
        m_Plane = yPlane;
      break;
    }

    case ToolPanel::TA_XY:
    {
      m_Plane = zPlane;
      break;
    }

    case ToolPanel::TA_ZX:
    {
      m_Plane = yPlane;
      break;
    }

    case ToolPanel::TA_YZ:
    {
      m_Plane = xPlane;
      break;
    }
  }

  Ray ray = Camera.GetMouseRay3D();
  m_Plane.Intersect(true, ray, m_PlaneInitPos);

  return true;
}


bool EditorAction_StaticMesh_Move::Complete()
{
  NULL_ASSERT(m_pNode);

  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();

  if (m_Duplicate)
  {
    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_StaticMesh_Add_Delete *pUndoAction = new UndoAction_StaticMesh_Add_Delete();

      String path;
      m_pNode->GetPath(path);

      pUndoAction->SetAddNode(path);
      pUndoAction->SetAddMesh(m_pNode->GetMesh()->GetFileHandle().GetFilename());

      Vec3 newPos, newRot, newScale;
      newPos    = m_pNode->GetPos();
      newRot    = m_pNode->GetRot();
      newScale  = m_pNode->GetScale();

      pUndoAction->SetAddTransform(newPos, newRot, newScale);
      
      Editor.GetUndoManager()->Add(pUndoAction);
    }
  }
  else
  {
    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_StaticMesh_Transform *pAction = new UndoAction_StaticMesh_Transform();
      
      String path;
      m_pNode->GetPath(path);

      pAction->SetNode(path);
      pAction->SetFrom(m_Pos, m_Rot, m_Scale);

      Vec3 newPos, newRot, newScale;
      newPos    = m_pNode->GetPos();
      newRot    = m_pNode->GetRot();
      newScale  = m_pNode->GetScale();

      pAction->SetTo(newPos, newRot, newScale);

      Editor.GetUndoManager()->Add(pAction);
    }
  }

  return true;
}


void EditorAction_StaticMesh_Move::Discard()
{
/*
  NULL_ASSERT(m_pNode);

  if (m_Duplicate)
  {
    bool active = Editor.GetUndoManager()->IsActive();
    Editor.GetUndoManager()->SetActive(false);

    Editor.GetLeftPanel()->GetScenePanel()->SetSelectedStaticMeshNode(m_pOrigNode);
    m_pNode->GetParentNode()->DeleteChild(m_pNode);

    Editor.GetUndoManager()->SetActive(active);
  }
  else
  {
    bool active = Editor.GetUndoManager()->IsActive();
    Editor.GetUndoManager()->SetActive(false);

    m_pNode->SetPos(m_Pos.x, m_Pos.y, m_Pos.z);
    m_pNode->SetRot(m_Rot.x, m_Rot.y, m_Rot.z);
    m_pNode->SetScale(m_Scale.x, m_Scale.y, m_Scale.z);

    Editor.GetUndoManager()->SetActive(active);
  }
*/
}


void EditorAction_StaticMesh_Move::Update()
{
  NULL_ASSERT(m_pNode);

  POINT mousePos;
  GetCursorPos(&mousePos);

  if (mousePos.x == m_LastPoint.x && mousePos.y == m_LastPoint.y)
  {
    return;
  }

  m_LastPoint.x = mousePos.x;
  m_LastPoint.y = mousePos.y;

  bool active = Editor.GetUndoManager()->IsActive();
  Editor.GetUndoManager()->SetActive(false);

  Ray ray = Camera.GetMouseRay3D();
  Vec3 hitPt;
  if (m_Plane.Intersect(true, ray, hitPt))
  {
    Vec3 delta = hitPt - m_PlaneInitPos;

    switch(Editor.GetToolPanel()->GetToolAxis())
    {
      case ToolPanel::TA_X:
        delta.y = 0.0f;
        delta.z = 0.0f;
        break;

      case ToolPanel::TA_XY:
        delta.z = 0.0f;
        break;

      case ToolPanel::TA_Z:
        delta.x = 0.0f;
        delta.y = 0.0f;
        break;

      case ToolPanel::TA_ZX:
        delta.y = 0.0f;
        break;

      case ToolPanel::TA_Y:
        delta.x = 0.0f;
        delta.z = 0.0f;
        break;

      case ToolPanel::TA_YZ:
        delta.x = 0.0f;
        break;
    }

    Vec3 gridPos(m_Pos.x + delta.x, m_Pos.y + delta.y, m_Pos.z + delta.z);
    Editor.GetGrid()->Snap(&gridPos, 0, 0);
    m_pNode->SetPos(gridPos.x, gridPos.y, gridPos.z);
  }

  Editor.GetUndoManager()->SetActive(active);
}


// -- EOF

