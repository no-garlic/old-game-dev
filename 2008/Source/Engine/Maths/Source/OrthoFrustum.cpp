// ----------------------------------------------------------------------------
// File: OrthoFrustum.cpp
// Desc: Describes an orthographic frustum
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "OrthoFrustum.h"
#include "Sphere.h"
#include "Box.h"
#include "Matrix.h"


// ----------------------------------------------------------------------------
// Name: OrthoFrustum::OrthoFrustum
// Desc: Constructor
// ----------------------------------------------------------------------------
OrthoFrustum::OrthoFrustum()
: Frustum()
{
  m_Focus.Reset();
  m_Dir.Set(0.0f, 1.0f, 0.0f);
  m_Length = 1.0f;
} // Frustum


// ----------------------------------------------------------------------------
// Set the frustum - which is an oriented box.
// ----------------------------------------------------------------------------
void OrthoFrustum::Set(const Sphere &focus, const Vec3 &dir, float length)
{
  m_Focus = focus;
  m_Dir = dir;
  m_Length = length;

  //m_Focus.radius *= 1.1f;

  m_Dir.Normalize();

  m_dirty = true;

  RecalculateFrustum();
}


// ----------------------------------------------------------------------------
// Name: OrthoFrustum::RecalculateFrustum
// Desc: Recalculate the frustum planes
// ----------------------------------------------------------------------------
void OrthoFrustum::RecalculateFrustum() const
{
  // Proceed if one of the matricies have changed
  if (!m_dirty)
    return;

  // The center point of the back frustum plane
  Vec3 nearPt = m_Focus.center - (m_Dir * (m_Focus.radius + m_Length));
  Vec3 farPt  = m_Focus.center + (m_Dir * m_Focus.radius);

  m_planes[Frustum::FRONT]  = Plane(m_Dir,  0.0f - nearPt.Length());
  m_planes[Frustum::BACK]   = Plane(-m_Dir, 0.0f - farPt.Length());
  
  Vec3 topA = nearPt        + Vec3(0.0f, m_Focus.radius, 0.0f);
  Vec3 topB = farPt         + Vec3(0.0f, m_Focus.radius, 0.0f);
  Vec3 topC = topA          + Vec3(1.0f, 0.0f, 0.0f);

  Vec3 bottomA = nearPt     - Vec3(0.0f, m_Focus.radius, 0.0f);
  Vec3 bottomB = farPt      - Vec3(0.0f, m_Focus.radius, 0.0f);
  Vec3 bottomC = bottomA    - Vec3(1.0f, 0.0f, 0.0f);

  Vec3 rightA = nearPt      - Vec3(m_Focus.radius, 0.0f, 0.0f);
  Vec3 rightB = farPt       - Vec3(m_Focus.radius, 0.0f, 0.0f);
  Vec3 rightC = rightA      - Vec3(0.0f, 1.0f, 0.0f);

  Vec3 leftA = nearPt       + Vec3(m_Focus.radius, 0.0f, 0.0f);
  Vec3 leftB = farPt        + Vec3(m_Focus.radius, 0.0f, 0.0f);
  Vec3 leftC = leftA        + Vec3(0.0f, 1.0f, 0.0f);

  m_planes[Frustum::TOP]    = Plane(topA, topC, topB);
  m_planes[Frustum::BOTTOM] = Plane(bottomA, bottomC, bottomB);
  m_planes[Frustum::LEFT]   = Plane(leftA, leftC, leftB);
  m_planes[Frustum::RIGHT]  = Plane(rightA, rightC, rightB);

  m_planes[Frustum::TOP].d    = -m_planes[Frustum::TOP].d;
  m_planes[Frustum::BOTTOM].d = -m_planes[Frustum::BOTTOM].d;

  // Normalize the 6 planes
  for (int i = 0; i < 6; i++)
    m_planes[i].Normalize();

  m_dirty = false;
} // RecalculateFrustum


// -- EOF

