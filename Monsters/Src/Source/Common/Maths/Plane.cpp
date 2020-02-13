// ----------------------------------------------------------------------------
// File: Plane.cpp
// Desc: Manages a plane
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Maths/Plane.h"
#include "Maths/Matrix.h"
#include "Maths/Vec3.h"
#include "Maths/Vec4.h"
#include "Maths/Ray.h"
#include "Maths/Line.h"
#include "Maths/Sphere.h"
#include "Maths/Box.h"


// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------
Plane::Plane()                                      : D3DXPLANE()           {}
Plane::Plane(const float *f)                        : D3DXPLANE(f)          {}
Plane::Plane(const D3DXFLOAT16 *f)                  : D3DXPLANE(f)          {}
Plane::Plane(float a, float b, float c, float d)    : D3DXPLANE(a, b, c, d) {}


// ----------------------------------------------------------------------------
// Name: Plane::Plane
// Desc: Constructor
// Parm: const Vec3 &normal - the normal
// Parm: float d            - the distance
// ----------------------------------------------------------------------------
Plane::Plane(const Vec3 &normal, float d)
: D3DXPLANE(normal[0], normal[1], normal[2], d)
{
} // Plane


// ----------------------------------------------------------------------------
// Name: Plane::Plane
// Desc: Constructor that builds a plane based on 3 posints
// Parm: const Vec3 &v1  - the first point
// Parm: const Vec3 &v2  - the second point
// Parm: const Vec3 &v3  - the third point
// ----------------------------------------------------------------------------
Plane::Plane(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
{
  FromPoints(v1, v2, v3);
} // Plane


// ----------------------------------------------------------------------------
// Name: Plane::Set
// Desc: Set the plane
// Parm: const Vec3 &normal - the normal
// Parm: float distance     - the distance
// ----------------------------------------------------------------------------
Plane &Plane::Set(const Vec3 &normal, float distance)
{
  a = normal[0];
  b = normal[1];
  c = normal[2];
  d = distance;

  return *this;
} // Set


// ----------------------------------------------------------------------------
// Name: Plane::GetNormal
// Desc: Get the normal
// ----------------------------------------------------------------------------
const Vec3 &Plane::GetNormal() const
{
  return (*((Vec3 *) (&a)));
} // GetNormal


// ----------------------------------------------------------------------------
// Name: Plane::SetNormal
// Desc: set the normal
// Parm: const Vec3 &normal - the normal
// ----------------------------------------------------------------------------
void Plane::SetNormal(const Vec3 &normal)
{
  a = normal[0];
  b = normal[1];
  c = normal[2];
} // SetNormal


// ----------------------------------------------------------------------------
// Name: Plane::GetDistance
// Desc: Get the distance
// Retn: float - the distance
// ----------------------------------------------------------------------------
float Plane::GetDistance() const
{
  return d;
} // GetDistance


// ----------------------------------------------------------------------------
// Name: Plane::SetDistance
// Desc: Set the distance
// Parm: float distance - the distance
// ----------------------------------------------------------------------------
void Plane::SetDistance(float distance)
{
  d = distance;
} // SetDistance


// ----------------------------------------------------------------------------
// Name: Plane::GetPoint
// Desc: Get the point on this plane that is the closest to the origin.
// ----------------------------------------------------------------------------
Vec3 Plane::GetPoint() const
{
  return GetNormal() * d;
} // GetPoint


// ----------------------------------------------------------------------------
// Name: Plane::WhichSide
// Desc: Classify the point
// Parm: const Vec3 &p         - the point
// ----------------------------------------------------------------------------
Plane::Classification Plane::WhichSide(const Vec3 &p) const
{
  float test = GetNormal().Dot(p) - d;
  if (test > EPSILON)
    return FRONT;
  else if (test < -EPSILON)
    return BACK;
  else
    return COPLANAR;
} // WhichSide


// ----------------------------------------------------------------------------
// Name: Plane::WhichSide
// Desc: Classify the point with the given threashold
// Parm: const Vec3 &p         - the point
// Parm: float threshold       - the threashold
// ----------------------------------------------------------------------------
Plane::Classification Plane::WhichSide(const Vec3 &p, float threshold) const
{
  float test = GetNormal().Dot(p) - d;
  if (test > threshold)
    return FRONT;
  else if (test < -threshold)
    return BACK;
  else
    return COPLANAR;
} // WhichSide

// ----------------------------------------------------------------------------
// Name: Plane::WhichSide
// Desc: classify the box
// Parm: const Box &box        - the box
// ----------------------------------------------------------------------------
Plane::Classification Plane::WhichSide(const Box &box) const
{
  Vec3 box_corners[8];
  box.CalcCorners(box_corners);

  return WhichSide(8, box_corners);
} // WhichSide


// ----------------------------------------------------------------------------
// Name: Plane::WhichSide
// Desc: Classify the array of points
// Parm: int num_points        - the number of points in the array
// Parm: const Vec3 *points    - the points array
// ----------------------------------------------------------------------------
Plane::Classification Plane::WhichSide(int num_points, const Vec3 *points) const
{
  bool front = false, back = false;

  for (int i = 0; i < num_points; i++)
  {
    switch (WhichSide(points[i]))
    {
    case FRONT: front = true; break;
    case BACK:  back  = true; break;
    } // switch
  } // for

  if (front)
    return back ? COINCIDENT : FRONT;
  else
    return back ? BACK : COPLANAR;
} // WhichSide


// ----------------------------------------------------------------------------
// Name: Plane::WhichSide
// Desc: Classify the sphere
// Parm: const Sphere &sphere  - the sphere
// ----------------------------------------------------------------------------
Plane::Classification Plane::WhichSide(const Sphere &sphere) const
{
  float test = GetNormal().Dot(sphere.center) - d;
  if (test >= 0)
    return (test > sphere.radius) ? FRONT : COINCIDENT;
  else
    return (-test > sphere.radius) ? BACK : COINCIDENT;
} // WhichSide


// ----------------------------------------------------------------------------
// Name: Plane::IsBehind
// Desc: Test if the spehre is behind the plane
// Parm: const Sphere &sphere - the sphere
// ----------------------------------------------------------------------------
bool Plane::IsBehind(const Sphere &sphere) const
{
  return (d - GetNormal().Dot(sphere.center)) > sphere.radius;
} // IsBehind


// ----------------------------------------------------------------------------
// Name: Plane::IsInFront
// Desc: test if the sphere is infornt of the plane
// Parm: const Sphere &sphere - the sphere
// ----------------------------------------------------------------------------
bool Plane::IsInFront(const Sphere &sphere) const
{
  return (GetNormal().Dot(sphere.center) - d) > sphere.radius;
} // IsInFront


// ----------------------------------------------------------------------------
// Name: Plane::Intersect
// Desc: Get the line intersecting the two planes
// Parm: const Plane &plane - the other plane
// Retn: Line               - the line
// ----------------------------------------------------------------------------
Line Plane::Intersect(const Plane &plane) const
{
  Line intercept, temp;
  Vec3 normal(*((Vec3 *) (&a)));

  intercept.SetDirection(normal.Cross(plane.GetNormal()));

  Vec3 interceptDir(intercept.GetDirection());
  temp.SetDirection(interceptDir.Cross(plane.GetNormal()));

  temp.SetPosition(plane.GetPoint());
  intercept.SetPosition(Intersect(temp));
  return intercept;
} // Intersect


// ----------------------------------------------------------------------------
// Name: Plane::Intersect
// Desc: Get the point that the line intersects the plane
// Parm: const Line &line - the line
// Retn: Vec3             - the point of intersection
// ----------------------------------------------------------------------------
Vec3 Plane::Intersect(const Line &line) const
{
  float t = (d - line.GetPosition().Dot(GetNormal())) / GetNormal().Dot(line.GetDirection());
  return (line.GetPosition() + t * line.GetDirection());
} // Intersect


// ----------------------------------------------------------------------------
// Name: Plane::Intersect
// Desc: Does the line intersect the plane
// Parm: bool twoSided            - if true then consider intersections from 
//                                  behind
// Parm: const Line &line         - the line
// Parm: Vec3 &intersectionPoint  - the intersection point
// Retn: bool                     - true if the line intersects
// ----------------------------------------------------------------------------
bool Plane::Intersect(bool twoSided, const Line &line, Vec3 &intersectionPoint) const
{
  float t;
  return Intersect(twoSided, line, intersectionPoint, t);
} // Intersect


// ----------------------------------------------------------------------------
// Name: Plane::Intersect
// Desc: Does the ray intersect the plane
// Parm: bool twoSided            - if true then consider intersections from 
//                                  behind
// Parm: const Ray &ray           - the ray
// Parm: Vec3 &intersectionPoint  - the intersection point
// Retn: bool                     - true if the ray intersects
// ----------------------------------------------------------------------------
bool Plane::Intersect(bool twoSided, const Ray &ray, Vec3 &intersectionPoint) const
{
  float t;
  return Intersect(twoSided, ray, intersectionPoint, t);
} // Intersect


// ----------------------------------------------------------------------------
// Name: Plane::Intersect
// Desc: Does the line intersect the plane
// Parm: bool twoSided            - if true then consider intersections from 
//                                  behind
// Parm: const Line &line         - the line
// Parm: Vec3 &intersectionPoint  - the intersection point
// Parm: float t                  - the distance along the line where the 
//                                  intesection occurred
// Retn: bool                     - true if the line intersects
// ----------------------------------------------------------------------------
bool Plane::Intersect(bool twoSided, const Line &line, Vec3 &intersectionPoint, float &t) const
{
  // Check if line does not parallel to plane
  float planeDotNorm = GetNormal().Dot(line.GetDirection());
  if (planeDotNorm <= -EPSILON || twoSided && planeDotNorm >= EPSILON)
  {
    // find the point of intersection
    t = (d - line.GetPosition().Dot(GetNormal())) / planeDotNorm;
    intersectionPoint = (line.GetPosition() + t * line.GetDirection());
    return true;
  } // if

  return false;
} // Intersect


// ----------------------------------------------------------------------------
// Name: Plane::Intersect
// Desc: Does the ray intersect the plane
// Parm: bool twoSided            - if true then consider intersections from 
//                                  behind
// Parm: const Ray &ray           - the ray
// Parm: Vec3 &intersectionPoint  - the intersection point
// Parm: float t                  - the distance along the ray where the 
//                                  intesection occurred
// Retn: bool                     - true if the ray intersects
// ----------------------------------------------------------------------------
bool Plane::Intersect(bool twoSided, const Ray &ray, Vec3 &intersectionPoint, float &t) const
{
  // Check if ray is not parallel to plane
  float planeDotNorm = GetNormal().Dot(ray.GetDirection());
  if (planeDotNorm <= -EPSILON || (twoSided && planeDotNorm >= EPSILON))
  {
    // Find the point of intersection
    t = (d - ray.GetPosition().Dot(GetNormal())) / planeDotNorm;
    if (t >= 0.0f)
    {
      intersectionPoint = (ray.GetPosition() + t * ray.GetDirection());
      return true;
    } // if
  } // if

  return false;
} // Intersect


// ----------------------------------------------------------------------------
// Name: Plane::Intersect
// Desc: Does the line intersect the plane
// Parm: bool twoSided            - if true then consider intersections from 
//                                  behind
// Parm: const Line &line         - the line
// Parm: float t                  - the distance along the line where the 
//                                  intesection occurred
// Retn: bool                     - true if the line intersects
// ----------------------------------------------------------------------------
Vec3 Plane::Intersect(const Line &line, float &t) const
{
  // find the point of intersection
  t = (d - line.GetPosition().Dot(GetNormal())) / GetNormal().Dot(line.GetDirection());
  return (line.GetPosition() + t * line.GetDirection());
} // Intersect


// ----------------------------------------------------------------------------
// Name: Plane::Distance
// Desc: Get the nearest distance from the given point to the plane
// Parm: const Vec3 &point - the point
// Retn: float             - the distance
// ----------------------------------------------------------------------------
float Plane::Distance(const Vec3 &point) const
{
  return (point.Dot(GetNormal()) - d);
} // Distance


// ----------------------------------------------------------------------------
// Name: Plane::Project
// Desc: Project \ point onto the plane
// Parm: const Vec3 &point - the point
// Retn: Vec3              - the projected point
// ----------------------------------------------------------------------------
Vec3 Plane::Project(const Vec3 &point) const
{
  // Create a line from the point and the planes normal.
  Line line(GetNormal(), point);

  // Return the intersection between that line and the plane.
  return Intersect(line);
} // Project


// ----------------------------------------------------------------------------
// Name: Plane::Dot
// Desc: Computes the dot product of a plane and a 4D vector.
// Parm: const Vec4 &v - the vector
// Retn: float         - the dot product
// ----------------------------------------------------------------------------
float Plane::Dot(const Vec4 &v) const
{
  return D3DXPlaneDot(this, &v);
} // Dot


// ----------------------------------------------------------------------------
// Name: Plane::DotCoord
// Desc: Computes the dot product of a plane and a 3D vector. The w parameter of
//       the vector is assumed to be 1.
// Parm: const Vec3 &v - the vector
// Retn: float         - the dot product
// ----------------------------------------------------------------------------
float Plane::DotCoord(const Vec3 &v) const
{
  return D3DXPlaneDotCoord(this, &v);
} // DotCoord


// ----------------------------------------------------------------------------
// Name: Plane::DotNormal
// Desc: Computes the dot product of a plane and a 3D vector. The w parameter of
//       the vector is assumed to be 0.
// Parm: const Vec3 &v - the normal
// Retn: float         - the dot product
// ----------------------------------------------------------------------------
float Plane::DotNormal(const Vec3 &v) const
{
  return D3DXPlaneDotNormal(this, &v);
} // DotNormal


// ----------------------------------------------------------------------------
// Name: Plane::FromPointNormal
// Desc: Build a plane from a point and a normal
// Parm: const Vec3 &point   - the point
// Parm: const Vec3 &normal  - the normal
// Retn: Plane &             - the plane
// ----------------------------------------------------------------------------
Plane &Plane::FromPointNormal(const Vec3 &point, const Vec3 &normal)
{
  D3DXPlaneFromPointNormal(this, &point, &normal);
  return *this;
} // FromPointNormal


// ----------------------------------------------------------------------------
// Name: Plane::FromPoints
// Desc: Build a plane from 3 points
// Parm: const Vec3 &v1  - the first point
// Parm: const Vec3 &v2  - the second point
// Parm: const Vec3 &v3  - the third point
// Retn: Plane &         - the plane
// ----------------------------------------------------------------------------
Plane &Plane::FromPoints(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
{
  D3DXPlaneFromPoints(this, &v1, &v2, &v3);
  return *this;
} // FromPoints


// ----------------------------------------------------------------------------
// Name: Plane::Normalize
// Desc: Normalize the plane's normal
// Parm: const Plane &p - 
// ----------------------------------------------------------------------------
Plane &Plane::Normalize()
{
  D3DXPlaneNormalize(this, this);
  return *this;
} // Normalize


// ----------------------------------------------------------------------------
// Name: Plane::Scale
// Desc: Scale the plane
// Parm: float s - the scale
// ----------------------------------------------------------------------------
Plane &Plane::Scale(float s)
{
  D3DXPlaneScale(this, this, s);
  return *this;
} // Scale


// ----------------------------------------------------------------------------
// Name: Plane::Transform
// Desc: Transforms a plane by a matrix. The input matrix is the inverse 
//       transpose of the actual transformation.
// Parm: const Matrix &m - the matrix
// ----------------------------------------------------------------------------
Plane &Plane::Transform(const Matrix &m)
{
  D3DXPlaneTransform(this, this, &m);
  return *this;
} // Transform


// ----------------------------------------------------------------------------
// Name: Plane::TransformArray
// Desc: Transforms an array of planes by a matrix. The vectors that describe 
//       each plane must be normalized
// Parm: uint out_stride     - the stride of each input pane
// Parm: Plane *plane_array  - the array of planes
// Parm: uint p_stride       - the stride of each output plane
// Parm: const Matrix &m     - the matrix
// Parm: uint n              - the number of planes to transform
// ----------------------------------------------------------------------------
Plane &Plane::TransformArray(uint out_stride, Plane *plane_array, uint p_stride, const Matrix &m, uint n)
{
  D3DXPlaneTransformArray(this, out_stride, plane_array, p_stride, &m, n);
  return *this;
} // TransformArray


// -- EOF
