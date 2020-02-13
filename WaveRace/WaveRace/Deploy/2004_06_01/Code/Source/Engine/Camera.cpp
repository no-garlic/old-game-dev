// ----------------------------------------------------------------------------
// File: Camera.cpp
// Desc: This file stores the player object class. This class performs tasks 
//       such as player movement, some minor physics as well as rendering.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Camera specific includes
// ----------------------------------------------------------------------------
#include "Engine/Camera.h"


// ----------------------------------------------------------------------------
// Name: Camera::Camera
// Desc: Constructor
// ----------------------------------------------------------------------------
Camera::Camera()
{
    // Cameras position & orientation (independant of camera)
    m_vecPos             = Vec3(0.0f, 0.0f, 0.0f);
    m_vecRight           = Vec3(1.0f, 0.0f, 0.0f);
    m_vecUp              = Vec3(0.0f, 1.0f, 0.0f);
    m_vecLook            = Vec3(0.0f, 0.0f, 1.0f);
    m_fYaw               = 0.0f;
    m_fPitch             = 0.0f;
    m_fRoll              = 0.0f;
    m_device             = 0;

    // Default projection and view matricies
    m_mtxProj.PerspectiveFovLH(D3DXToRadian(45.0f), 4.0f / 3.0f, 1.0f, 10000.0f);
    m_mtxView.Identity();
} // Camera


// ----------------------------------------------------------------------------
// Name: Camera::~Camera
// Desc: Destructor
// ----------------------------------------------------------------------------
Camera::~Camera()
{
} // ~Camera


// ----------------------------------------------------------------------------
// Name: Camera::Create
// Desc: Create the camera for this device
// Parm: LPDIRECT3DDEVICE9 device - the device
// Retn: bool                     - true if created successfully
// ----------------------------------------------------------------------------
bool Camera::Create(LPDIRECT3DDEVICE9 device)
{
    Release();

    m_device = device;

    if (m_device)
    {
        m_device->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
        m_device->SetTransform(D3DTS_VIEW,       &m_mtxView);
        m_frustum.SetViewMatrix(m_mtxView);
        m_frustum.SetProjMatrix(m_mtxProj);
    } // if

    return (m_device != 0);
} // Create


// ----------------------------------------------------------------------------
// Name: Camera::Release
// Desc: Release the device
// ----------------------------------------------------------------------------
void Camera::Release()
{
    m_device = 0;
} // Release


// ----------------------------------------------------------------------------
// Name: Camera::SetPosition
// Desc: Set the players position
// Parm: const Vec3 &Position - the position vector
// ----------------------------------------------------------------------------
void Camera::SetPosition(float x, float y, float z)
{
    m_vecPos.Set(x, y, z);

    // Set view matrix values
	m_mtxView._41 =- D3DXVec3Dot(&m_vecPos, &m_vecRight);
	m_mtxView._42 =- D3DXVec3Dot(&m_vecPos, &m_vecUp   );
	m_mtxView._43 =- D3DXVec3Dot(&m_vecPos, &m_vecLook );

    if (m_device)
        m_device->SetTransform(D3DTS_VIEW, &m_mtxView);
    m_frustum.SetViewMatrix(m_mtxView);
} // SetPosition


// ----------------------------------------------------------------------------
// Name: Camera::SetRotate
// Desc: Rotate the player around the world axis.
// Parm: float x  - the x axis
// Parm: float y  - the y axis
// Parm: float z  - the z axis
// ----------------------------------------------------------------------------
void Camera::SetRotate(float x , float y , float z)
{ 
    m_vecRight.Set(1.0f,  0.0f,  0.0f);
    m_vecUp.Set   (0.0f,  1.0f,  0.0f);
    m_vecLook.Set (0.0f,  0.0f,  1.0f);

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
    m_mtxView._11 = m_vecRight.x; m_mtxView._12 = m_vecUp.x; m_mtxView._13 = m_vecLook.x;
	m_mtxView._21 = m_vecRight.y; m_mtxView._22 = m_vecUp.y; m_mtxView._23 = m_vecLook.y;
	m_mtxView._31 = m_vecRight.z; m_mtxView._32 = m_vecUp.z; m_mtxView._33 = m_vecLook.z;
	m_mtxView._41 =- D3DXVec3Dot(&m_vecPos, &m_vecRight);
	m_mtxView._42 =- D3DXVec3Dot(&m_vecPos, &m_vecUp   );
	m_mtxView._43 =- D3DXVec3Dot(&m_vecPos, &m_vecLook );

    if (m_device)
        m_device->SetTransform(D3DTS_VIEW, &m_mtxView);
    m_frustum.SetViewMatrix(m_mtxView);
} // Rotate


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
    m_mtxView._11 = m_vecRight.x; m_mtxView._12 = m_vecUp.x; m_mtxView._13 = m_vecLook.x;
	m_mtxView._21 = m_vecRight.y; m_mtxView._22 = m_vecUp.y; m_mtxView._23 = m_vecLook.y;
	m_mtxView._31 = m_vecRight.z; m_mtxView._32 = m_vecUp.z; m_mtxView._33 = m_vecLook.z;
	m_mtxView._41 =- D3DXVec3Dot(&m_vecPos, &m_vecRight);
	m_mtxView._42 =- D3DXVec3Dot(&m_vecPos, &m_vecUp   );
	m_mtxView._43 =- D3DXVec3Dot(&m_vecPos, &m_vecLook );

    if (m_device)
        m_device->SetTransform(D3DTS_VIEW, &m_mtxView);
    m_frustum.SetViewMatrix(m_mtxView);
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
    m_mtxView._11 = m_vecRight.x; m_mtxView._12 = m_vecUp.x; m_mtxView._13 = m_vecLook.x;
	m_mtxView._21 = m_vecRight.y; m_mtxView._22 = m_vecUp.y; m_mtxView._23 = m_vecLook.y;
	m_mtxView._31 = m_vecRight.z; m_mtxView._32 = m_vecUp.z; m_mtxView._33 = m_vecLook.z;
	m_mtxView._41 =- D3DXVec3Dot(&m_vecPos, &m_vecRight);
	m_mtxView._42 =- D3DXVec3Dot(&m_vecPos, &m_vecUp   );
	m_mtxView._43 =- D3DXVec3Dot(&m_vecPos, &m_vecLook );

    if (m_device)
        m_device->SetTransform(D3DTS_VIEW, &m_mtxView);
    m_frustum.SetViewMatrix(m_mtxView);
} // SetView


// ----------------------------------------------------------------------------
// Name: Camera::SetProjPerspectiveLH
// Desc: Set the left handed perspective projection
// Parm: float fov     - the field of view
// Parm: float aspect  - the aspect ratio
// Parm: float z_near  - the near plane
// Parm: float z_far   - the far plane
// ----------------------------------------------------------------------------
void Camera::SetProjPerspectiveLH(float fov, float aspect, float z_near, float z_far)
{
    m_mtxProj.PerspectiveFovLH(D3DXToRadian(fov), aspect, z_near, z_far);
    if (m_device)
        m_device->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
    m_frustum.SetProjMatrix(m_mtxProj);
} // SetProjPerspectiveLH


// ----------------------------------------------------------------------------
// Name: Camera::SetProjPerspectiveRH
// Desc: Set the right handed perspective projection
// Parm: float fov     - the field of view
// Parm: float aspect  - the aspect ratio
// Parm: float z_near  - the near plane
// Parm: float z_far   - the far plane
// ----------------------------------------------------------------------------
void Camera::SetProjPerspectiveRH(float fov, float aspect, float z_near, float z_far)
{
    m_mtxProj.PerspectiveFovRH(D3DXToRadian(fov), aspect, z_near, z_far);
    if (m_device)
        m_device->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
    m_frustum.SetProjMatrix(m_mtxProj);
} // SetProjPerspectiveRH


// ----------------------------------------------------------------------------
// Name: Camera::SetProjOrthoLH
// Desc: Set the left handed orthographic projection
// Parm: float width   - the width
// Parm: float height  - the height
// Parm: float z_near  - the near plane
// Parm: float z_far   - the far plane
// ----------------------------------------------------------------------------
void Camera::SetProjOrthoLH(float width, float height, float z_near, float z_far)
{
    m_mtxProj.OrthoLH(width, height, z_near, z_far);
    if (m_device)
        m_device->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
    m_frustum.SetProjMatrix(m_mtxProj);
} // SetProjOrthoLH


// ----------------------------------------------------------------------------
// Name: Camera::SetProjOrthoRH
// Desc: Set the right handed orthographic projection
// Parm: float width   - the width
// Parm: float height  - the height
// Parm: float z_near  - the near plane
// Parm: float z_far   - the far plane
// ----------------------------------------------------------------------------
void Camera::SetProjOrthoRH(float width, float height, float z_near, float z_far)
{
    m_mtxProj.OrthoLH(width, height, z_near, z_far);
    if (m_device)
        m_device->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
    m_frustum.SetProjMatrix(m_mtxProj);
} // SetProjOrthoRH


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
bool Camera::SphereInFrustum(const Sphere &sphere, const Matrix &matrix)
{
    return (m_frustum.Intersects(sphere, matrix) == Frustum::IN_FRUSTUM);
} // SphereInFrustum


// -- EOF
