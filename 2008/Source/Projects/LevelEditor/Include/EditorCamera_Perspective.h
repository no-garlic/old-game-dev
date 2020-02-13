
#ifndef __EDITOR_CAMERA_PERSPECTIVE_H_
#define __EDITOR_CAMERA_PERSPECTIVE_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorCamera.h"
#include "QuaternionCamera.h"


class EditorCamera_Perspective : public EditorCamera
{
public:
  // Constructor and destructor
  EditorCamera_Perspective(EditorCameraType type);
  virtual ~EditorCamera_Perspective();

  // Activate the camera
  virtual void Activate();

  // Process a mouse message
  virtual void OnMouseMessage(const MouseMessage &msg);

  // Reset the camera view
  virtual void ResetView();

  // Focus on the selected node of the entire scene
  virtual void Focus();

  // Update each frame
  virtual void Update();

  // Set the near, far, and FOV
  void SetNearFarFOV(float nearPlane, float farPlane, float fov);

private:
  // Calculates the focus point offset based on the mouse movement and then
  // applys it to the focus point.
  void ApplyMouseOffset(int x, int y);

  // Private members
  QuaternionCamera  m_QuaternionCamera;
  float             m_Yaw;
  float             m_Pitch;
  float             m_Distance;
  Vec3              m_FocusPoint;
  float             m_FieldOfView;
  float             m_AspectRatio;
  float             m_NearPlane;
  float             m_FarPlane;

};



#endif // __EDITOR_CAMERA_PERSPECTIVE_H_

// -- EOF


