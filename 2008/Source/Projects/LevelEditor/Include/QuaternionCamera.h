
#ifndef __QUATERNION_CAMERA_H_
#define __QUATERNION_CAMERA_H_


#include "libEngine.h"
#include "libEditor.h"


class QuaternionCamera : private Unique
{
public:
  // Constructor and destructor
  QuaternionCamera();
  virtual ~QuaternionCamera();

  // Set the point at which the camera focuses on and rotates around
  inline void SetFocusPoint(const Vec3 &point)            { m_FocusPoint = point; }
  inline const Vec3 &GetFocusPoint() const                { return m_FocusPoint;  }

  // Set the distance from the focus point wher the camera is located
  inline void SetDistance(float distance)                 { m_Distance = distance; }
  inline float GetDistance() const                        { return m_Distance; }

  // Set the camera yaw and pitch
  inline void SetYawPitch(float yaw,  float pitch)        { m_Yaw = yaw; m_Pitch = pitch; }
  inline void GetYawPitch(float &yaw, float &pitch) const { yaw = m_Yaw; pitch = m_Pitch; }

public:
  // Generate the camera vectors
  void GenerateCameraVectors(Vec3 &pos, Vec3 &look, Vec3 &up, Vec3 &right) const;

  // Apply the camera vectors to the global camera (Camera3D).
  void ApplyCameraToScene() const;

private:
  Vec3        m_FocusPoint;     // The point at which the camera is focusing on
  float       m_Distance;       // The distance from the focus point where the camera lies
  float       m_Yaw;            // The camera yaw
  float       m_Pitch;          // The camera pitch

};


#endif // __QUATERNION_CAMERA_H_

// -- EOF

