
#include "EditorCamera_Perspective.h"
#include "Editor.h"


// Constructor
EditorCamera_Perspective::EditorCamera_Perspective(EditorCameraType type)
: EditorCamera(type)
{
  ResetView();
}


// Destructor
EditorCamera_Perspective::~EditorCamera_Perspective()
{
}


// Set the near, far, and FOV
void EditorCamera_Perspective::SetNearFarFOV(float nearPlane, float farPlane, float fov)
{
  m_NearPlane   = nearPlane;
  m_FarPlane    = farPlane;
  m_FieldOfView = fov;
}


// Activate the camera
void EditorCamera_Perspective::Activate()
{
  Camera.SetProjPerspective(m_FieldOfView, m_AspectRatio, m_NearPlane, m_FarPlane);

  m_QuaternionCamera.SetYawPitch(m_Yaw, m_Pitch);
  m_QuaternionCamera.SetDistance(m_Distance);
  m_QuaternionCamera.SetFocusPoint(m_FocusPoint);

  m_QuaternionCamera.ApplyCameraToScene();
}


// Process a mouse message
void EditorCamera_Perspective::OnMouseMessage(const MouseMessage &msg)
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

    // ----------------------
    // Rotate the camera
    else if (Input.GetMouseState(MOUSEPARAM_BUTTON_1) == MOUSEVAL_BUTTON_DOWN)
    {
      if (x)
      {
        m_Yaw += D3DXToRadian(x * 2.0f);
        Activate();
      }
      else if (y)
      {
        m_Pitch += D3DXToRadian(y * 2.0f);
        Activate();
      }
    }
  }
}


// Apply the offset fom the mouse to the focus point
void EditorCamera_Perspective::ApplyMouseOffset(int x, int y)
{
  VIEWPORT viewport;
  Device->GetViewport(&viewport);

  if (x)
  {
    float xTheta    = x * (D3DXToRadian(m_FieldOfView) / static_cast<float>(viewport.Width));
    float deltaX    = m_Distance * tanf(xTheta);
    m_FocusPoint.x += deltaX;
  }
  if (y)
  {
    float yTheta    = y * (D3DXToRadian(m_FieldOfView) / static_cast<float>(viewport.Height));
    float deltaY    = m_Distance * tanf(yTheta);
    m_FocusPoint.y += deltaY;
  }
}


// Reset the camera view
void EditorCamera_Perspective::ResetView()
{
  m_FieldOfView = 45.0f;
  m_NearPlane   = 1.0;
  m_FarPlane    = 5000.0f;

  if (Application.IsInitialised())
  {
    m_AspectRatio = Application.CalculateAspectRatio();
  }
  else
  {
    m_AspectRatio = 3.0f / 4.0f;
  }

  m_Yaw         = 0.0f;
  m_Pitch       = 0.0f;
  m_Distance    = 1.0f;
  m_FocusPoint  = Vec3(0.0f, 0.0f, 0.0f);

  Activate();
}


// Focus on the selected node of the entire scene
void EditorCamera_Perspective::Focus()
{
  TreeNode *pNode = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView()->GetSelectedNode();
  if (pNode && pNode->GetType() == "StaticMeshNode")
  {
    StaticMeshNode *pStaticMeshNode = (StaticMeshNode *) pNode;

    Sphere sphere = pStaticMeshNode->GetMesh()->GetBSphere();
    sphere.TransformAndScale(pStaticMeshNode->GetMatrix());

    float theta = D3DXToRadian(m_FieldOfView / 2.0f);
    float d = 1.5f * (sphere.radius / atan(theta));

    m_FocusPoint = sphere.center;
    m_Distance   = d;
    m_Pitch      = D3DXToRadian(30.0f);

    // Set the near and far plane ot match the world
//    const Sphere &worldSphere = Editor.GetDocument()->GetCachedSceneBounds();
//    float d2 = 1.05f * (worldSphere.radius / atan(theta));

//    m_NearPlane = d2 * 0.004f;
//    m_FarPlane  = d2 * 4.0f;
  }
  else
  {
    Sphere sphere = Editor.GetDocument()->GetCachedSceneBounds();

    float theta = D3DXToRadian(m_FieldOfView / 2.0f);
    float d = 1.5f * (sphere.radius / atan(theta));

    m_FocusPoint = sphere.center;
    m_Distance   = d;
    m_Pitch      = D3DXToRadian(30.0f);

//    m_NearPlane = d * 0.004f;
//    m_FarPlane  = d * 4.0f;
  }

  Activate();
}


// Update each frame
void EditorCamera_Perspective::Update()
{
}


// -- EOF

