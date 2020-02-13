
#ifndef __EDITOR_CAMERA_MANAGER_H_
#define __EDITOR_CAMERA_MANAGER_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorCamera.h"


class EditorCameraManager : private Unique
{
public:
  // Constructor and destructor
  EditorCameraManager();
  virtual ~EditorCameraManager();

  // Initialise the camera manager
  void Init();

  // Update each frame
  void Update();

  // Process a mouse message
  void OnMouseMessage(const MouseMessage &msg);

  // Reset the camera view
  virtual void ResetView();

  // Focus on the selected node of the entire scene
  virtual void Focus();

  // Manage the current camera
  void SetCurrentCamera(EditorCameraType type);
  EditorCamera *GetCurrentCamera();

  // Set the near, far, and FOV
  void SetNearFarFOV(float nearPlane, float farPlane, float fov);

private:
  EditorCamera     *m_pCameraArray[CAM_MAX];
  EditorCameraType  m_Current;

};


#endif // __EDITOR_CAMERA_MANAGER_H_

// -- EOF


