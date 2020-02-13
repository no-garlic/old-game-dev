// ----------------------------------------------------------------------------
// File: Frustum.h
// Desc: Describes a viewing frustum
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Frustum.h"
#include "Math/Sphere.h"
#include "Math/Box.h"
#include "Math/Matrix.h"


// ----------------------------------------------------------------------------
// Name: Frustum::Frustum
// Desc: Constructor
// ----------------------------------------------------------------------------
Frustum::Frustum()
{
    m_dirty     = true;
    m_view_mat.Identity();
    m_proj_mat.Identity();
} // Frustum


// ----------------------------------------------------------------------------
// Name: Frustum::SetViewMatrix
// Desc: Sets the view matrix
// Parm: const Matrix &m - the matrix
// ----------------------------------------------------------------------------
void Frustum::SetViewMatrix(const Matrix &m)
{
    m_view_mat  = m;
    m_dirty     = true;
} // SetViewMatrix


// ----------------------------------------------------------------------------
// Name: Frustum::SetProjMatrix
// Desc: Sets the projection matrix
// Parm: const Matrix &m - the matrix
// ----------------------------------------------------------------------------
void Frustum::SetProjMatrix(const Matrix &m)
{
    m_proj_mat  = m;
    m_dirty     = true;
} // SetViewMatrix


// ----------------------------------------------------------------------------
// Name: Frustum::GetPlanes
// Desc: Gets the frustum planes as an array of 6 planes
// Retn: Plane * - the planes array
// ----------------------------------------------------------------------------
Plane *Frustum::GetPlanes()
{
    // Recalculate the frustum planes if one
    // of the matricies have changed
    if (m_dirty)
        RecalculateFrustum();

    return m_planes;
} // GetPlanes


// ----------------------------------------------------------------------------
// Name: Frustum::Intersects
// Desc: Tests if the sphere supplied is in the frustum when placed at teh world
//       matrix also supplied
// Parm: const Sphere &sphere        - the sphere to test
// Parm: const Matrix &world_matrix  - the world matrix where the sphere is
// ----------------------------------------------------------------------------
int Frustum::Intersects(const Sphere &sphere, const Matrix &world_matrix)
{
    Sphere s = sphere;
    s.center.TransformCoord(s.center, world_matrix);
    // s.center.Add(s.center, Vec3(world_matrix._41, world_matrix._42, world_matrix._43));
    return Intersects(s);
} // Intersects


// ----------------------------------------------------------------------------
// Name: Frustum::Intersects
// Desc: Test if the sphere supplied is in the frustum
// Parm: const Sphere &sphere - the sphere to test against the frustum
// Retn: int                  - the intersection type - either IN, OUT, or 
//       PARTIAL
// ----------------------------------------------------------------------------
int Frustum::Intersects(const Sphere &sphere)
{
    // TODO
    // Need to make this return IN, OUT, PARTIAL

    // Recalculate the frustum planes if one
    // of the matricies have changed
    if (m_dirty)
        RecalculateFrustum();

    // Go through all the sides of the frustum
    for (int i = 0; i < 6; i++) 
    {
        // If the center of the sphere is farther away 
        // from the plane than the radius
        if (m_planes[i].a * sphere.center[0] + 
            m_planes[i].b * sphere.center[1] + 
            m_planes[i].c * sphere.center[2] + 
            m_planes[i].d <= -sphere.radius)
        {
            // The distance was greater than the radius so the 
            // sphere is outside of the frustum
            return Frustum::OUT_FRUSTUM;
        } // if
    } // for
    
    // The sphere is totally in the frustum
    return Frustum::IN_FRUSTUM;
} // Intersects


// ----------------------------------------------------------------------------
// Name: Frustum::Intersects
// Desc: Test if the sphere supplied is in the frustum
// Parm: const Box &box - the sphere to test against the frustum
// Retn: int            - the intersection type - either IN, OUT, or PARTIAL
// ----------------------------------------------------------------------------
int Frustum::Intersects(const Box &box)
{
    // TODO
    // Need to make this return IN, OUT, PARTIAL

    // Recalculate the frustum planes if one
    // of the matricies have changed
    if (m_dirty)
        RecalculateFrustum();

    return Frustum::IN_FRUSTUM;
} // Intersects


// ----------------------------------------------------------------------------
// Name: Frustum::RecalculateFrustum
// Desc: Recalculate the frustum planes from the supplied projection and view 
//       matricies
// ----------------------------------------------------------------------------
void Frustum::RecalculateFrustum()
{
    // Proceed if one of the matricies have changed
    if (!m_dirty)
        return;

    // Create the clipping matrix
    Matrix clip_matrix;
    D3DXMatrixMultiply(&clip_matrix, &m_view_mat, &m_proj_mat);

    // Get the right plane
    m_planes[Frustum::RIGHT].a = clip_matrix[ 3] - clip_matrix[ 0];
    m_planes[Frustum::RIGHT].b = clip_matrix[ 7] - clip_matrix[ 4];
    m_planes[Frustum::RIGHT].c = clip_matrix[11] - clip_matrix[ 8];
    m_planes[Frustum::RIGHT].d = clip_matrix[15] - clip_matrix[12];

    // Get the left plane
    m_planes[Frustum::LEFT].a = clip_matrix[ 3] + clip_matrix[ 0];
    m_planes[Frustum::LEFT].b = clip_matrix[ 7] + clip_matrix[ 4];
    m_planes[Frustum::LEFT].c = clip_matrix[11] + clip_matrix[ 8];
    m_planes[Frustum::LEFT].d = clip_matrix[15] + clip_matrix[12];

    // Get the botom plane
    m_planes[Frustum::BOTTOM].a = clip_matrix[ 3] + clip_matrix[ 1];
    m_planes[Frustum::BOTTOM].b = clip_matrix[ 7] + clip_matrix[ 5];
    m_planes[Frustum::BOTTOM].c = clip_matrix[11] + clip_matrix[ 9];
    m_planes[Frustum::BOTTOM].d = clip_matrix[15] + clip_matrix[13];

    // Get the top plane
    m_planes[Frustum::TOP].a = clip_matrix[ 3] - clip_matrix[ 1];
    m_planes[Frustum::TOP].b = clip_matrix[ 7] - clip_matrix[ 5];
    m_planes[Frustum::TOP].c = clip_matrix[11] - clip_matrix[ 9];
    m_planes[Frustum::TOP].d = clip_matrix[15] - clip_matrix[13];

    // Get the back plane
    m_planes[Frustum::BACK].a = clip_matrix[ 3] - clip_matrix[ 2];
    m_planes[Frustum::BACK].b = clip_matrix[ 7] - clip_matrix[ 6];
    m_planes[Frustum::BACK].c = clip_matrix[11] - clip_matrix[10];
    m_planes[Frustum::BACK].d = clip_matrix[15] - clip_matrix[14];

    // Get the front plane
    m_planes[Frustum::FRONT].a = clip_matrix[ 3] + clip_matrix[ 2];
    m_planes[Frustum::FRONT].b = clip_matrix[ 7] + clip_matrix[ 6];
    m_planes[Frustum::FRONT].c = clip_matrix[11] + clip_matrix[10];
    m_planes[Frustum::FRONT].d = clip_matrix[15] + clip_matrix[14];

    // Normalize the 6 planes
    for (int i = 0; i < 6; i++)
        m_planes[i].Normalize(m_planes[i]);

    m_dirty = false;
} // RecalculateFrustum


// -- EOF

