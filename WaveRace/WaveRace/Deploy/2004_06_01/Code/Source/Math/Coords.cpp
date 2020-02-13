// ----------------------------------------------------------------------------
// File: Coords.h
// Desc: Manages a position and rotation as a vec3 and a quaternion
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Coords.h"


// ----------------------------------------------------------------------------
// Name: Coords::Identity
// Desc: Reset the coords to identity
// Retn: Coords & - a reference to this class
// ----------------------------------------------------------------------------
Coords &Coords::Identity()
{
    xyz.Set(0, 0, 0);
    quat.Identity();

    return *this;
} // Identity


// -- EOF

