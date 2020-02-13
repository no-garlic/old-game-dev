
#include "EditorCamera_Orthographic.h"
#include "Editor.h"


// Constructor
EditorCamera_Orthographic::EditorCamera_Orthographic(EditorCameraType type)
: EditorCamera(type)
{
  ResetView();
}


// Destructor
EditorCamera_Orthographic::~EditorCamera_Orthographic()
{
}


// Activate the camera
void EditorCamera_Orthographic::Activate()
{
  if (Application.IsInitialised())
  {
    VIEWPORT viewport;
    Device->GetViewport(&viewport);

    Camera.SetProjOrtho(viewport.Width, viewport.Height, m_NearPlane, m_FarPlane);
  }
  else
  {
    Camera.SetProjOrtho(800, 600, m_NearPlane, m_FarPlane);
  }

  Vec3 pos = m_FocusPoint - (m_Look * m_Distance);
  Camera.SetView(pos, m_Look, m_Up, m_Right);
}


// Process a mouse message
void EditorCamera_Orthographic::OnMouseMessage(const MouseMessage &msg)
{
  // Get the camera x, y, z (wheel) delta values
  int x = 0;  if (msg.param == MOUSEPARAM_MOVE_X) { x = msg.value; }
  int y = 0;  if (msg.param == MOUSEPARAM_MOVE_Y) { y = msg.value; }
  int z = 0;  if (msg.param == MOUSEPARAM_MOVE_Z) { z = msg.value; }

  // Did the mouse wheel scroll?
  if (z)
  {
    m_Distance -= (z * m_FarPlane * 0.00025f);
    Activate();
  }

  // Did the mouse pointer move?
  else if (x || y)
  {
    // ----------------------
    // Pan the camera
    if (Input.GetMouseState(MOUSEPARAM_BUTTON_0) == MOUSEVAL_BUTTON_DOWN)
    {
      ApplyMouseOffset(-x, y);
      Activate();
    }
  }
}


// Apply the offset fom the mouse to the focus point
void EditorCamera_Orthographic::ApplyMouseOffset(int x, int y)
{
  VIEWPORT viewport;
  Device->GetViewport(&viewport);

  if (x)
  {
    m_FocusPoint.x += m_Distance * (static_cast<float>(x) / static_cast<float>(viewport.Width));
  }
  if (y)
  {
    m_FocusPoint.y += m_Distance * (static_cast<float>(y) / static_cast<float>(viewport.Height));
  }
}


// Reset the camera view
void EditorCamera_Orthographic::ResetView()
{
  m_NearPlane   = 1.0f;
  m_FarPlane    = 5000.0f;

  m_Distance    = 1.0f;
  m_FocusPoint  = Vec3(0.0f, 0.0f, 0.0f);

  Vec3 xVec(1.0f, 0.0f, 0.0f);
  Vec3 yVec(0.0f, 1.0f, 0.0f);
  Vec3 zVec(0.0f, 0.0f, 1.0f);

  switch (GetType())
  {
  case CAM_LEFT:
    m_Look  = -xVec;
    m_Up    = yVec;
    m_Right = zVec;
    break;

  case CAM_RIGHT:
    m_Look  = xVec;
    m_Up    = yVec;
    m_Right = -zVec;
    break;

  case CAM_TOP:
    m_Look  = -yVec;
    m_Up    = zVec;
    m_Right = xVec;
    break;

  case CAM_BOTTOM:
    m_Look  = yVec;
    m_Up    = zVec;
    m_Right = -xVec;
    break;

  case CAM_FRONT:
    m_Look  = zVec;
    m_Up    = yVec;
    m_Right = xVec;
    break;

  case CAM_BACK:
    m_Look  = -zVec;
    m_Up    = yVec;
    m_Right = -xVec;
    break;
  };

  Activate();
}


// Focus on the selected node of the entire scene
void EditorCamera_Orthographic::Focus()
{
  TreeNode *pNode = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView()->GetSelectedNode();
  if (pNode && pNode->GetType() == "StaticMeshNode")
  {
    StaticMeshNode *pStaticMeshNode = (StaticMeshNode *) pNode;

    Sphere sphere = pStaticMeshNode->GetMesh()->GetBSphere();
    sphere.TransformAndScale(pStaticMeshNode->GetMatrix());

    m_FocusPoint = sphere.center;
    m_Distance   = sphere.radius * 2.0f;

    // Set the near and far plane ot match the world
    const Sphere &worldSphere = Editor.GetDocument()->GetCachedSceneBounds();

    m_NearPlane = worldSphere.radius * 0.004f;
    m_FarPlane  = worldSphere.radius * 4.0f;
  }
  else
  {
    Sphere sphere = Editor.GetDocument()->GetCachedSceneBounds();

    m_FocusPoint = sphere.center;
    m_Distance   = sphere.radius * 2.0f;

    m_NearPlane = sphere.radius * 0.004f;
    m_FarPlane  = sphere.radius * 4.0f;
  }

  Activate();
}


// Update each frame
void EditorCamera_Orthographic::Update()
{
}


// -- EOF

