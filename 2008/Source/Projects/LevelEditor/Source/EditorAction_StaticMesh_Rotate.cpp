
#include "EditorAction_StaticMesh_Rotate.h"
#include "UndoAction_StaticMesh_Transform.h"
#include "Editor.h"


/*
    if (Editor.GetUndoManager()->IsActive())
    {
      UndoAction_StaticMeshMove *pAction = new UndoAction_StaticMeshMove();
      
      String path;
      GetPath(path);

      pAction->SetNode(path);
      pAction->SetFrom(m_Pos, m_Rot, m_Scale);
      pAction->SetTo(Vec3(x, y, z), m_Rot, m_Scale);

      Editor.GetUndoManager()->Add(pAction);
    }
*/


EditorAction_StaticMesh_Rotate::EditorAction_StaticMesh_Rotate()
: EditorAction  (),
  m_pNode       (NULL)
{
}


EditorAction_StaticMesh_Rotate::~EditorAction_StaticMesh_Rotate()
{
}


bool EditorAction_StaticMesh_Rotate::Init(const String &nodePath)
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

  m_pNode = (StaticMeshNode *) pNode;
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


bool EditorAction_StaticMesh_Rotate::Complete()
{
  Editor.GetDocument()->SetDirty();
  Editor.GetDocument()->PreCacheSceneBounds();

  NULL_ASSERT(m_pNode);

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
  return true;
}


void EditorAction_StaticMesh_Rotate::Discard()
{
  NULL_ASSERT(m_pNode);

  bool active = Editor.GetUndoManager()->IsActive();
  Editor.GetUndoManager()->SetActive(false);

  m_pNode->SetPos(m_Pos.x, m_Pos.y, m_Pos.z);
  m_pNode->SetRot(m_Rot.x, m_Rot.y, m_Rot.z);
  m_pNode->SetScale(m_Scale.x, m_Scale.y, m_Scale.z);

  Editor.GetUndoManager()->SetActive(active);
}


void EditorAction_StaticMesh_Rotate::Update()
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

    float length = (Camera.GetFov() / 360.0f) * Vec3(hitPt - Camera.GetPosition()).Length();
    delta /= (length * 0.01f);

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

    Vec3 gridRot(m_Rot.x - delta.x, m_Rot.y + delta.y, m_Rot.z + delta.z);
    Editor.GetGrid()->Snap(0, &gridRot, 0);
    m_pNode->SetRot(gridRot.x, gridRot.y, gridRot.z);
  }

  Editor.GetUndoManager()->SetActive(active);
}


// -- EOF

