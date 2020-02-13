// ----------------------------------------------------------------------------
// File: Frustum.h
// Desc: Describes a viewing frustum
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Frustum.h"
#include "Sphere.h"
#include "Box.h"
#include "Matrix.h"


// ----------------------------------------------------------------------------
// Name: Frustum::Frustum
// Desc: Constructor
// ----------------------------------------------------------------------------
Frustum::Frustum()
{
} // Frustum


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
// Name: Frustum::GetPlanes
// Desc: Gets the frustum planes as an array of 6 planes
// Retn: Plane * - the planes array
// ----------------------------------------------------------------------------
const Plane *Frustum::GetPlanes() const
{
  // Recalculate the frustum planes if one
  // of the matricies have changed
  if (m_dirty)
    RecalculateFrustum();

  return m_planes;
} // GetPlanes


// ----------------------------------------------------------------------------
// Name: Frustum::Intersects
// Desc: Tests if the sphere supplied is in the frustum when placed at the world
//       matrix also supplied
// Parm: const Sphere &sphere        - the sphere to test
// Parm: const Matrix &world_matrix  - the world matrix where the sphere is
// ----------------------------------------------------------------------------
int Frustum::Intersects(const Sphere &sphere, const Matrix &world_matrix) const
{
  Sphere s = sphere;
  s.TransformAndScale(world_matrix);
  return Intersects(s);
} // Intersects


// ----------------------------------------------------------------------------
// Name: Frustum::Intersects
// Desc: Test if the sphere supplied is in the frustum
// Parm: const Sphere &sphere - the sphere to test against the frustum
// Retn: int                  - the intersection type - either IN, OUT, or 
//       PARTIAL
// ----------------------------------------------------------------------------
int Frustum::Intersects(const Sphere &sphere) const
{
  // Recalculate the frustum planes if one
  // of the matricies have changed
  if (m_dirty)
    RecalculateFrustum();

  int val = Frustum::IN_FRUSTUM;
  for (int i = 0; i < 6; i++)
  {
    float distance = (m_planes[i].a * sphere.center.x + m_planes[i].b * sphere.center.y +
       m_planes[i].c * sphere.center.z) - m_planes[i].d;

    bool front = (distance + sphere.radius >= 0.0f);
    bool back  = (distance - sphere.radius <= 0.0f);

    if (front && back)
      val = Frustum::PARTIAL;
    else if (back)
      return Frustum::OUT_FRUSTUM;
  } // for

  return val;
} // Intersects


// ----------------------------------------------------------------------------
// Name: Frustum::Intersects
// Desc: Test if the sphere supplied is in the frustum
// Parm: const Box &box - the sphere to test against the frustum
// Retn: int            - the intersection type - either IN, OUT, or PARTIAL
// ----------------------------------------------------------------------------
int Frustum::Intersects(const Box &box) const 
{
  // Recalculate the frustum planes if one
  // of the matricies have changed
  if (m_dirty)
    RecalculateFrustum();

  // Go through all the sides of the frustum
  bool is_partial = false;
  for (int i = 0; i < 6; i++) 
  {
    Plane::Classification pc = m_planes[i].WhichSide(box);

    if (pc == Plane::BACK)
      return Frustum::OUT_FRUSTUM;

    if (pc == Plane::FRONT)
      continue;

    is_partial = true;
  } // for

  return (is_partial ? Frustum::PARTIAL : Frustum::IN_FRUSTUM);
} // Intersects


// ----------------------------------------------------------------------------
// Name: Frustum::Intersects
// Desc: tests if the box is in the frustum
// Parm: const Box &box              - the box
// Parm: const Matrix &world_matrix  - the world matrix of the box
// Retn: int                         - the intersectin type - either IN, OUT, or PARTIAL
// ----------------------------------------------------------------------------
int Frustum::Intersects(const Box &box, const Matrix &world_matrix) const
{
  // Recalculate the frustum planes if one
  // of the matricies have changed
  if (m_dirty)
    RecalculateFrustum();

  // Transform the box
  Box transformedBox(box);
  transformedBox.MinPt.TransformCoord(box.MinPt, world_matrix);
  transformedBox.MaxPt.TransformCoord(box.MaxPt, world_matrix);

  // Now test the transformed box
  return Intersects(transformedBox);
} // Intersects


// ----------------------------------------------------------------------------
// Name: Frustum::ToString
// Desc: Create a string debugging the frustum planes
// Retn: String - the string
// ----------------------------------------------------------------------------
String Frustum::ToString() const
{
  if (m_dirty)
    RecalculateFrustum();

  StringStream ss;

  ss << "LEFT:    " << m_planes[Frustum::LEFT].ToString() << std::endl;
  ss << "RIGHT:   " << m_planes[Frustum::RIGHT].ToString() << std::endl;
  ss << "TOP:     " << m_planes[Frustum::TOP].ToString() << std::endl;
  ss << "BOTTOM:  " << m_planes[Frustum::BOTTOM].ToString() << std::endl;
  ss << "FRONT:   " << m_planes[Frustum::FRONT].ToString() << std::endl;
  ss << "BACK:    " << m_planes[Frustum::BACK].ToString() << std::endl;

  return ss.str();
} // ToString


// -- EOF

