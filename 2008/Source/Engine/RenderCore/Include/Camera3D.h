// ----------------------------------------------------------------------------
// File: Camera3D.h
// Desc: Camera3D class
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __CAMERA_H_
#define __CAMERA_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libMaths.h"


#define Camera Camera3D::GetInstance()


// ----------------------------------------------------------------------------
// Name: Camera3D (class)
// Desc: Basic left handed camera
// ----------------------------------------------------------------------------
class Camera3D
{
public:
  // --------------------------------------------------------------------------
  // Singleton
  // --------------------------------------------------------------------------
  static Camera3D &GetInstance();
  static void DestroyInstance();

  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Camera3D();
  ~Camera3D();

  // ------------------------------------------------------------------------
  // Get the camera vectors
  // ------------------------------------------------------------------------
  const Vec3 &GetPosition() const { return m_vecPos; }
  const Vec3 &GetLook() const { return m_vecLook; }
  const Vec3 &GetUp() const { return m_vecUp; }
  const Vec3 &GetRight() const { return m_vecRight; }
  
  // ------------------------------------------------------------------------
  // Set the projection
  // ------------------------------------------------------------------------
  void SetProj                (const Matrix &proj);
  void SetProjPerspective     (float fov,   float aspect, float z_near, float z_far);
  void SetProjOrtho           (float width, float height, float z_near, float z_far);

  // --------------------------------------------------------------------------
  // Set the view
  // --------------------------------------------------------------------------
  void SetView(const Vec3 &look, const Vec3 &up, const Vec3 &right);
  void SetView(const Vec3 &pos, const Vec3 &look, const Vec3 &up, const Vec3 &right);
  void LookAt(const Vec3 &eye, const Vec3 &at, const Vec3 &up);

  // --------------------------------------------------------------------------
  // Set the rotation
  // --------------------------------------------------------------------------
  void Rotate(float x, float y, float z);
  void SetRotate(float x, float y, float z);

  // --------------------------------------------------------------------------
  // Set the position
  // --------------------------------------------------------------------------
  void SetPosition(float x, float y, float z);
  void SetPosition(const Vec3 &pos)  { SetPosition(pos[0], pos[1], pos[2]); }

  // --------------------------------------------------------------------------
  // Move the camera
  // --------------------------------------------------------------------------
  void Move(const Vec3 &axis, float distance);

  // --------------------------------------------------------------------------
  // Get the projection and view matricies
  // --------------------------------------------------------------------------
  const Matrix &GetProj() const { return m_proj_mat; }
  const Matrix &GetView() const { return m_view_mat; }

  // --------------------------------------------------------------------------
  // Near and far plane distances
  // --------------------------------------------------------------------------
  float GetNear() const         { return m_Near; }
  float GetFar()  const         { return m_Far;  }
  float GetFov()  const         { return m_Fov;  }

  // --------------------------------------------------------------------------
  // Get the combined matricies
  // --------------------------------------------------------------------------
  const Matrix &GetViewProj() const { return m_viewproj_mat; }
  const Matrix &GetInvView() const { return m_invview_mat; }
  const Matrix &GetInvProj() const { return m_invproj_mat; }
  const Matrix &GetInvViewProj() const { return m_invviewproj_mat; }

  // ------------------------------------------------------------------------
  // Frustum functions
  // ------------------------------------------------------------------------
  const Frustum &GetFrustum() const { return m_frustum; }
  bool SphereInFrustum(const Sphere &sphere);
  bool SphereInFrustum(const Sphere &sphere, const Matrix &world_mat);

  // --------------------------------------------------------------------------
  // Make a world view matrix
  // --------------------------------------------------------------------------
  Matrix &MakeWorldView(const Matrix &world, Matrix &world_view) const;
  Matrix &MakeWorldViewProj(const Matrix &world, Matrix &world_view_proj) const;

  // --------------------------------------------------------------------------
  // Mouse functions
  // --------------------------------------------------------------------------
#if PC
  Ray  GetMouseRay3D();
#endif

  // --------------------------------------------------------------------------
  // Viewport functions
  // --------------------------------------------------------------------------
  Vec3 WorldToScreen(const Vec3 &world, const Matrix &world_mat);
  Vec3 ScreenToWorld(const Vec3 &screen, const Matrix &world_mat);

  // --------------------------------------------------------------------------
  // Print the camera values
  // --------------------------------------------------------------------------
  void Print() const;

private:
  // --------------------------------------------------------------------------
  // Update the combined matrices
  // --------------------------------------------------------------------------
  void UpdateCombinedMatrices();

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Matrix                m_view_mat;         // The view matrix
  Matrix                m_proj_mat;         // The projection matrix
  Matrix                m_viewproj_mat;     // The view projection matrix
  Matrix                m_invview_mat;      // The inverse view matrix
  Matrix                m_invproj_mat;      // The inverse projection matrix
  Matrix                m_invviewproj_mat;  // The inverse view proj matrix
  PerspectiveFrustum    m_frustum;          // View frustum
  Vec3                  m_vecPos;           // Position
  Vec3                  m_vecUp;            // Up Vector
  Vec3                  m_vecRight;         // Right Vector
  Vec3                  m_vecLook;          // Look Vector
  float                 m_fPitch;           // Pitch
  float                 m_fRoll;            // Roll
  float                 m_fYaw;             // Yaw
  float                 m_Near;             // The near plane distance
  float                 m_Far;              // The far plane distance
  float                 m_Fov;              // The field of view
  static Camera3D *s_pInstance;        // Singelton instance

}; // class Camera3D


#endif // __CAMERA_H

// -- EOF

