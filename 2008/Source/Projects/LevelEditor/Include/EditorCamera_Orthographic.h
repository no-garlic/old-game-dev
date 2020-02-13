
#ifndef __EDITOR_CAMERA_ORTHOGRAPHIC_H_
#define __EDITOR_CAMERA_ORTHOGRAPHIC_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorCamera.h"


class EditorCamera_Orthographic : public EditorCamera
{
public:
  // Constructor and destructor
  EditorCamera_Orthographic(EditorCameraType type);
  virtual ~EditorCamera_Orthographic();

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

private:
  // Calculates the focus point offset based on the mouse movement and then
  // applys it to the focus point.
  void ApplyMouseOffset(int x, int y);

  // Private members
  Vec3              m_FocusPoint;
  Vec3              m_Look;
  Vec3              m_Up;
  Vec3              m_Right;
  float             m_Distance;
  float             m_NearPlane;
  float             m_FarPlane;

};



#endif // __EDITOR_CAMERA_ORTHOGRAPHIC_H_

// -- EOF


