// ----------------------------------------------------------------------------
// File: Camera.cpp
// Desc: Camera class
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// includes
// ----------------------------------------------------------------------------
#include "Engine/ApplicationCentral.h"
#include "Engine/Camera.h"


// ----------------------------------------------------------------------------
// Name: Camera::Camera
// Desc: Constructor
// ----------------------------------------------------------------------------
Camera::Camera()
{
  REF_COUNT_CTOR(Camera);

  // Cameras position & orientation (independant of camera)
  m_vecPos             = Vec3(0.0f, 0.0f, 0.0f);
  m_vecRight           = Vec3(1.0f, 0.0f, 0.0f);
  m_vecUp              = Vec3(0.0f, 1.0f, 0.0f);
  m_vecLook            = Vec3(0.0f, 0.0f, 1.0f);
  m_fYaw               = 0.0f;
  m_fPitch             = 0.0f;
  m_fRoll              = 0.0f;

  // Set the view matrix default
  m_view_mat = MatrixIdentity;

  // Default matricies
  SetView(m_vecLook, m_vecUp, m_vecRight);
  UpdateCombinedMatrices();
} // Camera


// ----------------------------------------------------------------------------
// Name: Camera::~Camera
// Desc: Destructor
// ----------------------------------------------------------------------------
Camera::~Camera()
{
  REF_COUNT_DTOR(Camera);
} // ~Camera


// ----------------------------------------------------------------------------
// Print the camera values
// ----------------------------------------------------------------------------
void Camera::Print() const
{
/*
  LOG_INFO << "*******************"              << ENDLOG;
  LOG_INFO << "Pos :  " << m_vecPos.ToString()   << ENDLOG;
  LOG_INFO << "Look:  " << m_vecLook.ToString()  << ENDLOG;
  LOG_INFO << "Right: " << m_vecRight.ToString() << ENDLOG;
  LOG_INFO << "Up:    " << m_vecUp.ToString()    << ENDLOG;
  LOG_INFO << "*******************"              << ENDLOG;
*/
} // Print


// ----------------------------------------------------------------------------
// Name: Camera::SetPosition
// Desc: Set the players position
// Parm: const Vec3 &Position - the position vector
// ----------------------------------------------------------------------------
void Camera::SetPosition(float x, float y, float z)
{
  D3DXVec3Set(&m_vecPos, x, y, z);

  // Set view matrix values
  m_view_mat._41 =- D3DXVec3Dot(&m_vecPos, &m_vecRight);
  m_view_mat._42 =- D3DXVec3Dot(&m_vecPos, &m_vecUp   );
  m_view_mat._43 =- D3DXVec3Dot(&m_vecPos, &m_vecLook );

  m_frustum.SetViewMatrix(m_view_mat);
  UpdateCombinedMatrices();
} // SetPosition


// ----------------------------------------------------------------------------
// Name: Camera::SetRotate
// Desc: Set the player rotation
// Parm: float x  - the x axis
// Parm: float y  - the y axis
// Parm: float z  - the z axis
// ----------------------------------------------------------------------------
void Camera::SetRotate(float x, float y, float z)
{ 
  D3DXVec3Set(&m_vecRight, 1.0f,  0.0f,  0.0f);
  D3DXVec3Set(&m_vecUp,    0.0f,  1.0f,  0.0f);
  D3DXVec3Set(&m_vecLook,  0.0f,  0.0f,  1.0f);

  Rotate(x, y, z);
} // SetRotate


// ----------------------------------------------------------------------------
// Name: Camera::SetRotate
// Desc: Rotate the player around the world axis.
// Parm: float x  - the x axis
// Parm: float y  - the y axis
// Parm: float z  - the z axis
// ----------------------------------------------------------------------------
void Camera::Rotate(float x, float y, float z)
{ 
  Matrix matRotate; 

  if (x != 0) 
  { 
    // Build rotation matrix 
    D3DXMatrixRotationAxis (&matRotate,  &m_vecRight,   D3DXToRadian(x)); 
    D3DXVec3TransformNormal(&m_vecLook,  &m_vecLook,    &matRotate);
    D3DXVec3TransformNormal(&m_vecUp,    &m_vecUp,      &matRotate);
  } // if

  if (y != 0) 
  { 
    // Build rotation matrix 
    D3DXMatrixRotationAxis (&matRotate,  &m_vecUp,      D3DXToRadian(y)); 
    D3DXVec3TransformNormal(&m_vecLook,  &m_vecLook,    &matRotate);
    D3DXVec3TransformNormal(&m_vecRight, &m_vecRight,   &matRotate);
  } // if

  if (z != 0)
  { 
    // Build rotation matrix 
    D3DXMatrixRotationAxis (&matRotate,  &m_vecLook,    D3DXToRadian(z));
    D3DXVec3TransformNormal(&m_vecUp,    &m_vecUp,      &matRotate);
    D3DXVec3TransformNormal(&m_vecRight, &m_vecRight,   &matRotate);
  } // if 

  // Perform vector regeneration 
  D3DXVec3Normalize(&m_vecLook, &m_vecLook); 
  D3DXVec3Cross(&m_vecRight, &m_vecUp, &m_vecLook); 
  D3DXVec3Normalize(&m_vecRight, &m_vecRight); 
  D3DXVec3Cross(&m_vecUp, &m_vecLook, &m_vecRight); 
  D3DXVec3Normalize(&m_vecUp, &m_vecUp);

  // Set view matrix values
  m_view_mat._11 = m_vecRight.x; m_view_mat._12 = m_vecUp.x; m_view_mat._13 = m_vecLook.x;
  m_view_mat._21 = m_vecRight.y; m_view_mat._22 = m_vecUp.y; m_view_mat._23 = m_vecLook.y;
  m_view_mat._31 = m_vecRight.z; m_view_mat._32 = m_vecUp.z; m_view_mat._33 = m_vecLook.z;
  m_view_mat._41 =- D3DXVec3Dot(&m_vecPos, &m_vecRight);
  m_view_mat._42 =- D3DXVec3Dot(&m_vecPos, &m_vecUp   );
  m_view_mat._43 =- D3DXVec3Dot(&m_vecPos, &m_vecLook );

  m_frustum.SetViewMatrix(m_view_mat);
  UpdateCombinedMatrices();
} // Rotate


// ----------------------------------------------------------------------------
// Name: LookAt
// Desc: Set the camera using lookat vectors
// Parm: const Vec3 &eye - the eye position
// Parm: const Vec3 &at  - the point to look at
// Parm: const Vec3 &up  - the up vector
// ----------------------------------------------------------------------------
void Camera::LookAt(const Vec3 &eye, const Vec3 &at, const Vec3 &up)
{
  Vec3 look = at - eye;
  D3DXVec3Normalize(&look, &look);

  Vec3 right;
  D3DXVec3Cross(&right, &up, &look);

  SetView(eye, look, up, right);
} // LookAt


// ----------------------------------------------------------------------------
// Name: Camera::SetView
// Desc: Set the view
// Parm: const Vec3 &look   - the look vector
// Parm: const Vec3 &up     - the up vector
// Parm: const Vec3 &right  - the right vector
// ----------------------------------------------------------------------------
void Camera::SetView(const Vec3 &look, const Vec3 &up, const Vec3 &right)
{
  // Assign the vectors
  m_vecLook   = look;
  m_vecUp     = up;
  m_vecRight  = right;

  // Perform vector regeneration 
  D3DXVec3Normalize(&m_vecLook, &m_vecLook); 
  D3DXVec3Cross(&m_vecRight, &m_vecUp, &m_vecLook); 
  D3DXVec3Normalize(&m_vecRight, &m_vecRight); 
  D3DXVec3Cross(&m_vecUp, &m_vecLook, &m_vecRight); 
  D3DXVec3Normalize(&m_vecUp, &m_vecUp);

  // Set view matrix values
  m_view_mat._11 = m_vecRight.x; m_view_mat._12 = m_vecUp.x; m_view_mat._13 = m_vecLook.x;
  m_view_mat._21 = m_vecRight.y; m_view_mat._22 = m_vecUp.y; m_view_mat._23 = m_vecLook.y;
  m_view_mat._31 = m_vecRight.z; m_view_mat._32 = m_vecUp.z; m_view_mat._33 = m_vecLook.z;
  m_view_mat._41 =- D3DXVec3Dot(&m_vecPos, &m_vecRight);
  m_view_mat._42 =- D3DXVec3Dot(&m_vecPos, &m_vecUp   );
  m_view_mat._43 =- D3DXVec3Dot(&m_vecPos, &m_vecLook );

  m_frustum.SetViewMatrix(m_view_mat);
  UpdateCombinedMatrices();
} // SetView


// ----------------------------------------------------------------------------
// Name: Camera::SetView
// Desc: Set the view
// Parm: const Vec3 &pos    - the camera position
// Parm: const Vec3 &look   - the look vector
// Parm: const Vec3 &up     - the up vector
// Parm: const Vec3 &right  - the right vector
// ----------------------------------------------------------------------------
void Camera::SetView(const Vec3 &pos, const Vec3 &look, const Vec3 &up, const Vec3 &right)
{
  // Assign the vectors
  m_vecPos    = pos;
  m_vecLook   = look;
  m_vecUp     = up;
  m_vecRight  = right;

  // Perform vector regeneration 
  D3DXVec3Normalize(&m_vecLook, &m_vecLook); 
  D3DXVec3Cross(&m_vecRight, &m_vecUp, &m_vecLook); 
  D3DXVec3Normalize(&m_vecRight, &m_vecRight); 
  D3DXVec3Cross(&m_vecUp, &m_vecLook, &m_vecRight); 
  D3DXVec3Normalize(&m_vecUp, &m_vecUp);

  // Set view matrix values
  m_view_mat._11 = m_vecRight.x; m_view_mat._12 = m_vecUp.x; m_view_mat._13 = m_vecLook.x;
  m_view_mat._21 = m_vecRight.y; m_view_mat._22 = m_vecUp.y; m_view_mat._23 = m_vecLook.y;
  m_view_mat._31 = m_vecRight.z; m_view_mat._32 = m_vecUp.z; m_view_mat._33 = m_vecLook.z;
  m_view_mat._41 =- D3DXVec3Dot(&m_vecPos, &m_vecRight);
  m_view_mat._42 =- D3DXVec3Dot(&m_vecPos, &m_vecUp   );
  m_view_mat._43 =- D3DXVec3Dot(&m_vecPos, &m_vecLook );

  m_frustum.SetViewMatrix(m_view_mat);
  UpdateCombinedMatrices();
} // SetView


// ----------------------------------------------------------------------------
// Name: Camera::UpdateCombinedMatrices
// Desc: Update the combined matrices
// ----------------------------------------------------------------------------
void Camera::UpdateCombinedMatrices()
{
  // The view proj matrix
  D3DXMatrixMultiply(&m_viewproj_mat, &m_view_mat, &m_proj_mat);

  // The inverse matrices
  D3DXMatrixInverse(&m_invproj_mat, NULL, &m_proj_mat);
  D3DXMatrixInverse(&m_invview_mat, NULL, &m_view_mat);
  D3DXMatrixInverse(&m_invviewproj_mat, NULL, &m_viewproj_mat);
} // UpdateCombinedMatrices


// ----------------------------------------------------------------------------
// Set the projection
// ----------------------------------------------------------------------------
void Camera::SetProj(const Matrix &proj)
{
  m_proj_mat = proj;
  m_frustum.SetProjMatrix(proj);
  UpdateCombinedMatrices();
} // SetProj


// ----------------------------------------------------------------------------
// Name: Camera::SetProjPerspective
// Desc: Set the left handed perspective projection
// Parm: float fov     - the field of view
// Parm: float aspect  - the aspect ratio
// Parm: float z_near  - the near plane
// Parm: float z_far   - the far plane
// ----------------------------------------------------------------------------
void Camera::SetProjPerspective(float fov, float aspect, float z_near, float z_far)
{
  D3DXMatrixPerspectiveFovLH(&m_proj_mat, D3DXToRadian(fov), aspect, z_near, z_far);
  m_frustum.SetProjMatrix(m_proj_mat);
  UpdateCombinedMatrices();
} // SetProjPerspective


// ----------------------------------------------------------------------------
// Name: Camera::SetProjOrtho
// Desc: Set the left handed orthographic projection
// Parm: float width   - the width
// Parm: float height  - the height
// Parm: float z_near  - the near plane
// Parm: float z_far   - the far plane
// ----------------------------------------------------------------------------
void Camera::SetProjOrtho(float width, float height, float z_near, float z_far)
{
  D3DXMatrixOrthoLH(&m_proj_mat, width, height, z_near, z_far);
  m_frustum.SetProjMatrix(m_proj_mat);
  UpdateCombinedMatrices();
} // SetProjOrtho


// ----------------------------------------------------------------------------
// Name: Camera::SphereInFrustum
// Desc: Test a sphere to be within the view frustum
// Parm: const Sphere &sphere - the sphere
// Retn: bool                 - true if it is within the frustum
// TODO: Should return a code to determine if it is in, out, or bit of both
//       so the application can determine how to traverse a tree of spheres,
//       in the most efficient manner.
// ----------------------------------------------------------------------------
bool Camera::SphereInFrustum(const Sphere &sphere)
{
  return (m_frustum.Intersects(sphere) == Frustum::IN_FRUSTUM);
} // SphereInFrustum


// ----------------------------------------------------------------------------
// Name: Camera::SphereInFrustum
// Desc: Test a sphere to be within the view frustum
// Parm: const Sphere &sphere - the sphere
// Parm: const MAtrix &matrix - the world matrix of the sphere
// Retn: bool                 - true if it is within the frustum
// TODO: Should return a code to determine if it is in, out, or bit of both
//       so the application can determine how to traverse a tree of spheres,
//       in the most efficient manner.
// ----------------------------------------------------------------------------
bool Camera::SphereInFrustum(const Sphere &sphere, const Matrix &world_mat)
{
  return (m_frustum.Intersects(sphere, world_mat) == Frustum::IN_FRUSTUM);
} // SphereInFrustum


// ----------------------------------------------------------------------------
// Name: Camera::Move
// Desc: Move the camera
// Parm: const Vec3 &axis - the axis to move along
// Parm: float distance   - the distance to move
// ----------------------------------------------------------------------------
void Camera::Move(const Vec3 &axis, float distance)
{
  Vec3 delta_pos = axis * distance;
  SetPosition(m_vecPos + delta_pos);
} // Move


// ----------------------------------------------------------------------------
// Name: Camera::MakeWorldView
// Desc: Make a world view matrix from the given matrix
// Parm: const Matrix &world - the world matrix
// Parm: Matrix &world_view  - the input matrix to turn into a world view 
//       matrix
// Retn: Matrix & - the modified world view matrix
// ----------------------------------------------------------------------------
Matrix &Camera::MakeWorldView(const Matrix &world, Matrix &world_view) const
{
  D3DXMatrixMultiply(&world_view, &world, &m_view_mat);
  return world_view;
} // MakeWorldView


// ----------------------------------------------------------------------------
// Name: Camera::MakeWorldViewProj
// Desc: Make a world view proj matrix from the given matrix
// Parm: const Matrix &world      - the world matrix
// Parm: Matrix &world_view_proj  - the input matrix to turn into a world view 
//       projection matrix
// Retn: Matrix & - the modified world view projection matrix
// ----------------------------------------------------------------------------
Matrix &Camera::MakeWorldViewProj(const Matrix &world, Matrix &world_view_proj) const
{
  D3DXMatrixMultiply(&world_view_proj, &world, &m_viewproj_mat);
  return world_view_proj;
} // MakeWorldViewProj



// --------------------------------------------------------------------------
// Name: ScreenToWorld
// Desc: Unproject a screen vector to a world vector
// Parm: const Vec3 &screen - the screen vector
// --------------------------------------------------------------------------
Vec3 Camera::ScreenToWorld(const Vec3 &screen, const Matrix &world_mat)
{
  D3DVIEWPORT9 viewport;
  ApplicationCentral.GetDevice()->GetViewport(&viewport);
  Vec3 world;
  D3DXVec3Unproject(&world, &screen, &viewport, &m_proj_mat, &m_view_mat, &world_mat);
  return world;
} // ScreenToWorld


// --------------------------------------------------------------------------
// Name: WorldToScreen
// Desc: Project a world vector to a screen vector
// Parm: const Vec3 &world - the world vector
// --------------------------------------------------------------------------
Vec3 Camera::WorldToScreen(const Vec3 &world, const Matrix &world_mat)
{
  D3DVIEWPORT9 viewport;
  ApplicationCentral.GetDevice()->GetViewport(&viewport);
  Vec3 screen;
  D3DXVec3Project(&screen, &world, &viewport, &m_proj_mat, &m_view_mat, &world_mat);
  return screen;
} // WorldToScreen


// ----------------------------------------------------------------------------
// Name: Camera::GetMouseRay3D
// Desc: Get the mouse ray from the eye point into the scene
// Parm: Ray &ray - the ray
// ----------------------------------------------------------------------------
Ray Camera::GetMouseRay3D()
{
  POINT ptCursor; 
  GetCursorPos(&ptCursor); 
  ScreenToClient(ApplicationCentral.GetHWND(), &ptCursor);

  D3DVIEWPORT9 viewport;
  ApplicationCentral.GetDevice()->GetViewport(&viewport);

  Ray ray;
  ray.position = m_vecPos;
  D3DXVec3Unproject(&(ray.direction), &Vec3((float) ptCursor.x, (float) ptCursor.y, 0.0f), &viewport, &m_proj_mat, 
    &m_view_mat, &MatrixIdentity);

  ray.direction = ray.direction - ray.position;
  D3DXVec3Normalize(&(ray.direction), &(ray.direction));

  return ray;
} // GetMouseRay3D

// -- EOF

