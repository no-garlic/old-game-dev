
#include "EditorCameraManager.h"
#include "EditorCamera_Perspective.h"
#include "EditorCamera_Orthographic.h"
#include "Editor.h"


EditorCameraManager::EditorCameraManager()
{
  m_pCameraArray[CAM_PERSPECTIVE] = new EditorCamera_Perspective(CAM_PERSPECTIVE);
  m_pCameraArray[CAM_TOP]         = new EditorCamera_Orthographic(CAM_TOP);
  m_pCameraArray[CAM_BOTTOM]      = new EditorCamera_Orthographic(CAM_BOTTOM);
  m_pCameraArray[CAM_LEFT]        = new EditorCamera_Orthographic(CAM_LEFT);
  m_pCameraArray[CAM_RIGHT]       = new EditorCamera_Orthographic(CAM_RIGHT);
  m_pCameraArray[CAM_FRONT]       = new EditorCamera_Orthographic(CAM_FRONT);
  m_pCameraArray[CAM_BACK]        = new EditorCamera_Orthographic(CAM_BACK);

  m_Current = CAM_PERSPECTIVE;
}


EditorCameraManager::~EditorCameraManager()
{
  for (uint i = 0; i < CAM_MAX; i++)
  {
    delete m_pCameraArray[i];
  }
}


void EditorCameraManager::Init()
{
  SetCurrentCamera(CAM_PERSPECTIVE);
}


void EditorCameraManager::SetCurrentCamera(EditorCameraType type)
{
  m_Current = type;
  m_pCameraArray[type]->Activate();
}


EditorCamera *EditorCameraManager::GetCurrentCamera()
{
  return m_pCameraArray[m_Current];
}


void EditorCameraManager::Update()
{
  GetCurrentCamera()->Update();
}


void EditorCameraManager::OnMouseMessage(const MouseMessage &msg)
{
  GetCurrentCamera()->OnMouseMessage(msg);
}


void EditorCameraManager::ResetView()
{
  GetCurrentCamera()->ResetView();
}


void EditorCameraManager::Focus()
{
  GetCurrentCamera()->Focus();
}


void EditorCameraManager::SetNearFarFOV(float nearPlane, float farPlane, float fov)
{
  static_cast<EditorCamera_Perspective *>(m_pCameraArray[CAM_PERSPECTIVE])->SetNearFarFOV(nearPlane, farPlane, fov);

  if (m_Current == CAM_PERSPECTIVE)
  {
    m_pCameraArray[CAM_PERSPECTIVE]->Activate();
  }
}


// -- EOF

