// ----------------------------------------------------------------------------
// File: Quat.cpp
// Desc: Manages a quaternion
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Quat.h"
#include "Math/Matrix.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"


Quat::Quat()                                      : D3DXQUATERNION()              {}
Quat::Quat(const float *f)                        : D3DXQUATERNION(f)             {}
Quat::Quat(const D3DXFLOAT16 *f)                  : D3DXQUATERNION(f)             {}
Quat::Quat(float x, float y, float z, float w)    : D3DXQUATERNION(x, y, z, w)    {}


Quat &Quat::BaryCentric(const Quat &q1, const Quat &q2, 
                        const Quat &q3, float f, float g)
{
    D3DXQuaternionBaryCentric(this, &q1, &q2, &q3, f, g);
    return *this;
} // BaryCentric


Quat &Quat::Conjugate(const Quat &q)
{
    D3DXQuaternionConjugate(this, &q);
    return *this;
} // Conjugate


float Quat::Dot(const Quat &q)
{
    return D3DXQuaternionDot(this, &q);
} // Dot


Quat &Quat::Exp(const Quat &q)
{
    D3DXQuaternionExp(this, &q);
    return *this;
} // Exp


Quat &Quat::Identity()
{
    D3DXQuaternionIdentity(this);
    return *this;
} // Identity


Quat &Quat::Inverse(const Quat &q)
{
    D3DXQuaternionInverse(this, &q);
    return *this;
} // Inverse


bool Quat::IsIdentity()
{
    return D3DXQuaternionIsIdentity(this) == TRUE;
} // IsIdentity


float Quat::Length()
{
    return D3DXQuaternionLength(this);
} // Length


float Quat::LengthSq()
{
    return D3DXQuaternionLengthSq(this);
} // LengthSq


Quat &Quat::Ln(const Quat &q)
{
    D3DXQuaternionLn(this, &q);
    return *this;
} // Ln


Quat &Quat::Multiply(const Quat &q1, const Quat &q2)
{
    D3DXQuaternionMultiply(this, &q1, &q2);
    return *this;
} // Multiply


Quat &Quat::Normalize(const Quat &q)
{
    D3DXQuaternionNormalize(this, &q);
    return *this;
} // Normalize


Quat &Quat::RotationAxis(const Vec3 &v, float angle)
{
    D3DXQuaternionRotationAxis(this, &v, angle);
    return *this;
} // RotationAxis


Quat &Quat::RotationMatrix(const Matrix &m)
{
    D3DXQuaternionRotationMatrix(this, &m);
    return *this;
} // RotationMatrix


Quat &Quat::RotationYawPitchRoll(float yaw, float pitch, float roll)
{
    D3DXQuaternionRotationYawPitchRoll(this, yaw, pitch, roll);
    return *this;
} // RotationYawPitchRoll


Quat &Quat::Slerp(const Quat &q1, const Quat &q2, float t)
{
    D3DXQuaternionSlerp(this, &q1, &q2, t);
    return *this;
} // Slerp


Quat &Quat::Squad(const Quat &q1, const Quat &qa, const Quat &qb, 
                  const Quat &qc, float t)
{
    D3DXQuaternionSquad(this, &q1, &qa, &qb, &qc, t);
    return *this;
} // Squad


Quat &Quat::ToAxisAngle(Vec3 *axis, float *angle)
{
    D3DXQuaternionToAxisAngle(this, axis, angle);
    return *this;
} // ToAxisAngle


void  Quat::SquadSetup(Quat &qa_out, Quat &qb_out, Quat &qc_out, const Quat &q0, 
                       const Quat &q1, const Quat &q2, const Quat &q3)
{
    D3DXQuaternionSquadSetup(&qa_out, &qb_out, &qc_out, &q0, &q1, &q2, &q3);
} // SquadSetup




// -- EOF

