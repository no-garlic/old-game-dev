
#ifndef __EDITOR_CAMERA_H_
#define __EDITOR_CAMERA_H_


#include "libEngine.h"
#include "libEditor.h"


enum EditorCameraType
{
  CAM_PERSPECTIVE,
  CAM_TOP,
  CAM_BOTTOM,
  CAM_LEFT,
  CAM_RIGHT,
  CAM_FRONT,
  CAM_BACK,

  CAM_MAX
};


class EditorCamera : private Unique
{
public:
  // Constructor and destructor
  EditorCamera(EditorCameraType type);
  virtual ~EditorCamera();

  // Get the camera type
  EditorCameraType GetType() const { return m_Type; }

  // Initialise the camera
  virtual void Activate() = 0;

  // Process a mouse message
  virtual void OnMouseMessage(const MouseMessage &msg) = 0;

  // Reset the camera view
  virtual void ResetView() = 0;

  // Focus on the selected node of the entire scene
  virtual void Focus() = 0;

  // Update each frame
  virtual void Update() = 0;

private:
  EditorCameraType  m_Type;

};



#endif // __EDITOR_CAMERA_H_

// -- EOF


