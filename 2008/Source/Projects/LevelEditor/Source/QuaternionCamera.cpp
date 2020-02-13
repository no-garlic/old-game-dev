

#include "QuaternionCamera.h"


// Constructor
QuaternionCamera::QuaternionCamera()
{
  m_FocusPoint.Set(0.0f, 0.0f, 0.0f); // The point at which the camera is focusing on
  m_Distance  = 1.0f;                 // The distance from the focus point where the camera lies
  m_Yaw       = 0.0f;                 // The camera yaw
  m_Pitch     = 0.0f;                 // The camera pitch
}


// Destructor
QuaternionCamera::~QuaternionCamera()
{
}


// Generate the camera vectors
void QuaternionCamera::GenerateCameraVectors(Vec3 &pos, Vec3 &look, Vec3 &up, Vec3 &right) const
{
  Quat qRotation;
  qRotation.RotationYawPitchRoll(m_Yaw, m_Pitch, 0.0f);

  Matrix mRotation;
  mRotation.RotationQuaternion(qRotation.Conjugate());

  look  = mRotation.GetZAxis();
  up    = mRotation.GetYAxis();
  right - mRotation.GetXAxis();

  look.Normalize();
  up.Normalize();
  right.Normalize();

  pos = m_FocusPoint - (look * m_Distance);
}


// Apply the camera vectors to the global camera (Camera3D).
void QuaternionCamera::ApplyCameraToScene() const
{
  // Generate the camera vectors
  Vec3 pos, look, up, right;
  GenerateCameraVectors(pos, look, up, right);

  // Apply the camera vectors to the global scene camera
  Camera.SetView(pos, look, up, right);
}


// -- EOF

