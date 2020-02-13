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
#include "Math/Types.h"


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
    // Static functions
    // ------------------------------------------------------------------------
    static void SquadSetup(Quat &qa_out, Quat &qb_out, Quat &qc_out, 
        const Quat &q0, const Quat &q1, const Quat &q2, const Quat &q3);


    // ------------------------------------------------------------------------
    // Member functions
    // ------------------------------------------------------------------------
    Quat    &BaryCentric(const Quat &q1, const Quat &q2, const Quat &q3, float f, float g);
    Quat    &Conjugate(const Quat &q);
    float    Dot(const Quat &q);
    Quat    &Exp(const Quat &q);
    Quat    &Identity();
    Quat    &Inverse(const Quat &q);
    bool     IsIdentity();
    float    Length();
    float    LengthSq();
    Quat    &Ln(const Quat &q);
    Quat    &Multiply(const Quat &q1, const Quat &q2);
    Quat    &Normalize(const Quat &q);
    Quat    &RotationAxis(const Vec3 &v, float angle);
    Quat    &RotationMatrix(const Matrix &m);
    Quat    &RotationYawPitchRoll(float yaw, float pitch, float roll);
    Quat    &Slerp(const Quat &q1, const Quat &q2, float t);
    Quat    &Squad(const Quat &q1, const Quat &qa, const Quat &qb, const Quat &qc, float t);
    Quat    &ToAxisAngle(Vec3 *axis, float *angle);

}; // class Quat


#endif //_QUAT_H

// -- EOF

