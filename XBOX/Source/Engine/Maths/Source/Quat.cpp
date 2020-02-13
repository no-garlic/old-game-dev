// ----------------------------------------------------------------------------
// File: Quat.cpp
// Desc: Manages a quaternion
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Quat.h"
#include "Matrix.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"


// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------
Quat::Quat()                                      : D3DXQUATERNION()              {}
Quat::Quat(const float *f)                        : D3DXQUATERNION(f)             {}
Quat::Quat(float x, float y, float z, float w)    : D3DXQUATERNION(x, y, z, w)    {}


// ----------------------------------------------------------------------------
// Name: Quat::BaryCentric
// Desc: Returns a quaternion in barycentric coordinates
// Parm: const Quat &q1  - the first quaternion
// Parm: const Quat &q2  - the second quaternion
// Parm: const Quat &q3  - the third quaternion
// Parm: float f         - the first weighting factor
// Parm: float g         - the second weighting factor
// ----------------------------------------------------------------------------
Quat &Quat::BaryCentric(const Quat &q1, const Quat &q2, const Quat &q3, float f, float g)
{
  D3DXQuaternionBaryCentric(this, &q1, &q2, &q3, f, g);
  return *this;
} // BaryCentric


// ----------------------------------------------------------------------------
// Name: Quat::Conjugate
// Desc: Returns the conjugate of a quaternion
// ----------------------------------------------------------------------------
Quat &Quat::Conjugate()
{
  D3DXQuaternionConjugate(this, this);
  return *this;
} // Conjugate


// ----------------------------------------------------------------------------
// Name: Quat::Dot
// Desc: Get the dot product of this quaternion
// ----------------------------------------------------------------------------
float Quat::Dot()
{
  return D3DXQuaternionDot(this, this);
} // Dot


// ----------------------------------------------------------------------------
// Name: Quat::Exp
// Desc: Calculates the exponential
// ----------------------------------------------------------------------------
Quat &Quat::Exp()
{
  D3DXQuaternionExp(this, this);
  return *this;
} // Exp


// ----------------------------------------------------------------------------
// Name: Quat::Identity
// Desc: Sets the quaternion to 0,0,0,1
// ----------------------------------------------------------------------------
Quat &Quat::Identity()
{
  D3DXQuaternionIdentity(this);
  return *this;
} // Identity


// ----------------------------------------------------------------------------
// Name: Quat::Inverse
// Desc: Inverses the quaternion
// ----------------------------------------------------------------------------
Quat &Quat::Inverse()
{
  D3DXQuaternionInverse(this, this);
  return *this;
} // Inverse


// ----------------------------------------------------------------------------
// Name: Quat::IsIdentity
// Desc: Is this quaternion the identity quaternion
// ----------------------------------------------------------------------------
bool Quat::IsIdentity()
{
  return D3DXQuaternionIsIdentity(this) == TRUE;
} // IsIdentity


// ----------------------------------------------------------------------------
// Name: Quat::Length
// Desc: Returns the length of a quaternion
// ----------------------------------------------------------------------------
float Quat::Length()
{
  return D3DXQuaternionLength(this);
} // Length


// ----------------------------------------------------------------------------
// Name: Quat::LengthSq
// Desc: Returns the length squared of a quaternion
// ----------------------------------------------------------------------------
float Quat::LengthSq()
{
  return D3DXQuaternionLengthSq(this);
} // LengthSq


// ----------------------------------------------------------------------------
// Name: Quat::Ln
// Desc: Calculates the natural log
// ----------------------------------------------------------------------------
Quat &Quat::Ln()
{
  D3DXQuaternionLn(this, this);
  return *this;
} // Ln


// ----------------------------------------------------------------------------
// Name: Quat::Multiply
// Desc: Multiply this quaternion with another
// Parm: const Quat &q - the other quaternion
// ----------------------------------------------------------------------------
Quat &Quat::Multiply(const Quat &q)
{
  D3DXQuaternionMultiply(this, this, &q);
  return *this;
} // Multiply


// ----------------------------------------------------------------------------
// Name: Quat::Normalize
// Desc: Normalize this quaternion
// ----------------------------------------------------------------------------
Quat &Quat::Normalize()
{
  D3DXQuaternionNormalize(this, this);
  return *this;
} // Normalize


// ----------------------------------------------------------------------------
// Name: Quat::RotationAxis
// Desc: Set this quaternion to the given rotation axis
// Parm: const Vec3 &v - the axis
// Parm: float angle   - the angle
// ----------------------------------------------------------------------------
Quat &Quat::RotationAxis(const Vec3 &v, float angle)
{
  D3DXQuaternionRotationAxis(this, &v, angle);
  return *this;
} // RotationAxis


// ----------------------------------------------------------------------------
// Name: Quat::RotationMatrix
// Desc: Set this quaternion ot the rotation matrix
// Parm: const Matrix &m - the matrix
// ----------------------------------------------------------------------------
Quat &Quat::RotationMatrix(const Matrix &m)
{
  D3DXQuaternionRotationMatrix(this, &m);
  return *this;
} // RotationMatrix


// ----------------------------------------------------------------------------
// Name: Quat::RotationYawPitchRoll
// Desc: Set this quaternion to the euler angles
// Parm: float yaw    - heading
// Parm: float pitch  - pitch
// Parm: float roll   - roll
// ----------------------------------------------------------------------------
Quat &Quat::RotationYawPitchRoll(float yaw, float pitch, float roll)
{
  D3DXQuaternionRotationYawPitchRoll(this, yaw, pitch, roll);
  return *this;
} // RotationYawPitchRoll


// ----------------------------------------------------------------------------
// Name: Quat::Slerp
// Desc: Spherically interpolate between the two given quaternions
// Parm: const Quat &q1  - the first quaternion
// Parm: const Quat &q2  - the second quaternion
// Parm: float t         - the interpolant
// ----------------------------------------------------------------------------
Quat &Quat::Slerp(const Quat &q1, const Quat &q2, float t)
{
  D3DXQuaternionSlerp(this, &q1, &q2, t);
  return *this;
} // Slerp


// ----------------------------------------------------------------------------
// Name: Quat::Slerp
// Desc: Spherically interpolate between this quaternion and the given quaternion
// Parm: const Quat &q  - the other quaternion
// Parm: float t        - the interpolant
// ----------------------------------------------------------------------------
Quat &Quat::Slerp(const Quat &q, float t)
{
  D3DXQuaternionSlerp(this, this, &q, t);
  return *this;
} // Slerp


// ----------------------------------------------------------------------------
// Name: Quat::ToAxisAngle
// Desc: Extract the rotation from this quaternion
// Parm: Vec3 *axis    - the axis
// Parm: float *angle  - the angle
// ----------------------------------------------------------------------------
Quat &Quat::ToAxisAngle(Vec3 *axis, float *angle)
{
  D3DXQuaternionToAxisAngle(this, axis, angle);
  return *this;
} // ToAxisAngle


// -- EOF

