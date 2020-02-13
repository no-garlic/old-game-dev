// ----------------------------------------------------------------------------
// File: Box.h
// Desc: Bounding box class
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Box.h"
#include "Math/Vec3.h"


// ----------------------------------------------------------------------------
// Name: Box::Calculate
// Desc: Calculate the bounding box around the two supplied boxes
// Parm: const Box &box1  - the first box
// Parm: const Box &box2  - the second box
// ----------------------------------------------------------------------------
void Box::Calculate(const Box &box1, const Box &box2)
{
    Min.Minimize(box1.Min, box2.Min);
    Max.Maximize(box1.Max, box2.Max);
} // Calculate


// -- EOF

