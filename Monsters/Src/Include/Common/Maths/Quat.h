// ----------------------------------------------------------------------------
// File: Quat.h
// Desc: Class to manage a quaternion
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _QUAT_H
#define _QUAT_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Matrix;
class Vec2;
class Vec3;
class Vec4;


// ----------------------------------------------------------------------------
// Name: Quat  (class)
// Desc: class Quat : public D3DXQUATERNION
// ----------------------------------------------------------------------------
class Quat : public D3DXQUATERNION
{
public:
  // ------------------------------------------------------------------------
  // Constructors
  // ------------------------------------------------------------------------
  Quat();
  Quat(const float *f);
  Quat(const D3DXFLOAT16 *f);
  Quat(float x, float y, float z, float w);

  // ------------------------------------------------------------------------
  // Makes this quaternion from bary centric coordinates
  // ------------------------------------------------------------------------
  Quat &BaryCentric(const Quat &q1, const Quat &q2, const Quat &q3, float f, float g);

  // --------------------------------------------------------------------------
  // Sets this quaternion to the conjugate of it's self
  // --------------------------------------------------------------------------
  Quat &Conjugate();

  // --------------------------------------------------------------------------
  // Get the dot product of this quaternion
  // --------------------------------------------------------------------------
  float Dot();
  
  // --------------------------------------------------------------------------
  // Calculates the exponential
  // --------------------------------------------------------------------------
  Quat &Exp();
  
  // --------------------------------------------------------------------------
  // Sets the quaternion to 0,0,0,1
  // --------------------------------------------------------------------------
  Quat &Identity();
  bool IsIdentity();

  // --------------------------------------------------------------------------
  // Inverses the quaternion
  // --------------------------------------------------------------------------
  Quat &Inverse();

  // --------------------------------------------------------------------------
  // Gets the length of the quaternion
  // --------------------------------------------------------------------------
  float Length();
  float LengthSq();
  
  // --------------------------------------------------------------------------
  // Calculates the natural log
  // --------------------------------------------------------------------------
  Quat &Ln();

  // --------------------------------------------------------------------------
  // Multiply this quaternion with another
  // --------------------------------------------------------------------------
  Quat &Multiply(const Quat &q);

  // --------------------------------------------------------------------------
  // Normalizes this quaternion
  // --------------------------------------------------------------------------
  Quat &Normalize();
  
  // --------------------------------------------------------------------------
  // Sets the quaternion to the rotation
  // --------------------------------------------------------------------------
  Quat &RotationAxis(const Vec3 &v, float angle);
  Quat &RotationMatrix(const Matrix &m);
  Quat &RotationYawPitchRoll(float yaw, float pitch, float roll);

  // --------------------------------------------------------------------------
  // Gets the rotation from the quaternion
  // --------------------------------------------------------------------------
  Quat &ToAxisAngle(Vec3 *axis, float *angle);
  
  // --------------------------------------------------------------------------
  // Spheically interpolate between the two given quaternions
  // --------------------------------------------------------------------------
  Quat &Slerp(const Quat &q1, const Quat &q2, float t);
  Quat &Slerp(const Quat &q, float t);
  
  // ------------------------------------------------------------------------
  // Sets up control points for spherical quadrangle interpolation
  // ------------------------------------------------------------------------
  static void SquadSetup(Quat &qa_out, Quat &qb_out, Quat &qc_out, 
      const Quat &q0, const Quat &q1, const Quat &q2, const Quat &q3);

  // --------------------------------------------------------------------------
  // Interpolates between quaternions, using spherical quadrangle interpolation
  // --------------------------------------------------------------------------
  Quat &Squad(const Quat &q1, const Quat &qa, const Quat &qb, const Quat &qc, float t);

}; // class Quat


#endif //_QUAT_H

// -- EOF

