// ----------------------------------------------------------------------------
// File: Camera.h
// Desc: Camera class handles camera manipulation
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _CAMERA_H
#define _CAMERA_H


// ----------------------------------------------------------------------------
// Camera specific includes
// ----------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <D3DX9.h>

#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Math/Matrix.h"
#include "Math/Vec3.h"
#include "Math/Frustum.h"


// ----------------------------------------------------------------------------
// Singleton accessor
// ----------------------------------------------------------------------------
class Camera;
typedef Singleton::SingletonHolder<Camera, 
        Singleton::CreateUsingNew<Camera> > CameraSingleton;


// ----------------------------------------------------------------------------
// Name: Camera (class)
// Desc: Camera class handles camera manipulation
// ----------------------------------------------------------------------------
class Camera
{
private:
    // ------------------------------------------------------------------------
    // Friend accessor
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<Camera>;


    // ------------------------------------------------------------------------
    // Constructors & destructors for this class.
    // ------------------------------------------------------------------------
                        Camera();
    virtual            ~Camera();


public:
    // ------------------------------------------------------------------------
    // Memory functions
    // ------------------------------------------------------------------------
    bool                Create(LPDIRECT3DDEVICE9 device);
    void                Release();


    // ------------------------------------------------------------------------
    // View matrix functions
    // ------------------------------------------------------------------------
    const Vec3         &GetPosition     () const { return m_vecPos;      }
    const Vec3         &GetLook         () const { return m_vecLook;     }
    const Vec3         &GetUp           () const { return m_vecUp;       }
    const Vec3         &GetRight        () const { return m_vecRight;    }
    const Matrix       &GetViewMatrix   () const { return m_mtxView;     }
    
    void                SetView         (const Vec3 &look, const Vec3 &up, const Vec3 &right);
    void                SetView         (const Vec3 &pos, const Vec3 &look, const Vec3 &up, const Vec3 &right);

    void                SetRotate       (float x, float y, float z);
    void                SetPosition     (float x, float y, float z);

    void                SetRotate       (const Vec3 &axis) { SetRotate(axis[0], axis[1], axis[2]); }
    void                SetPosition     (const Vec3 &pos)  { SetPosition(pos[0], pos[1], pos[2]);  }


    // ------------------------------------------------------------------------
    // Projection matrix functions
    // ------------------------------------------------------------------------
    void                SetProjPerspectiveLH    (float fov,   float aspect, float z_near, float z_far);
    void                SetProjPerspectiveRH    (float fov,   float aspect, float z_near, float z_far);
    void                SetProjOrthoLH          (float width, float height, float z_near, float z_far);
    void                SetProjOrthoRH          (float width, float height, float z_near, float z_far);
    const Matrix       &GetProjMatrix()  const { return m_mtxProj; }


    // ------------------------------------------------------------------------
    // Culling functions
    // ------------------------------------------------------------------------
    bool SphereInFrustum(const Sphere &sphere);
    bool SphereInFrustum(const Sphere &sphere, const Matrix &matrix);


private:
    // ------------------------------------------------------------------------
    // Cameras position and orientation values
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9   m_device;   // The device
    Matrix              m_mtxView;  // View matrix
    Matrix              m_mtxProj;  // Projection matrix
    Frustum             m_frustum;  // View frustum
    Vec3                m_vecPos;   // Camera Position
    Vec3                m_vecUp;    // Camera Up Vector
    Vec3                m_vecRight; // Camera Right Vector
    Vec3                m_vecLook;  // Camera Look Vector
    float               m_fPitch;   // Camera pitch
    float               m_fRoll;    // Camera roll
    float               m_fYaw;     // Camera yaw
}; // class Camera


#endif // _CAMERA_H

// -- EOF

