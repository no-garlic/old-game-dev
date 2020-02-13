// ----------------------------------------------------------------------------
// File: Player.h
// Desc: This file stores the player object class. This class performs tasks 
//       such as player movement, some minor physics as well as rendering.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _PLAYER_H
#define _PLAYER_H


// ----------------------------------------------------------------------------
// Player specific includes
// ----------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <D3DX9.h>

#include "Math/Types.h"
#include "Math/Matrix.h"
#include "Math/Vec3.h"


// ----------------------------------------------------------------------------
// Name: Player (class)
// Desc: Player class handles all player manipulation, update and management.
// ----------------------------------------------------------------------------
class Player
{
public:
    // ------------------------------------------------------------------------
    // Name: DIRECTION  (enum)
    // Desc: Player direction control
    // ------------------------------------------------------------------------
    enum DIRECTION 
    { 
        DIR_FORWARD     = 1, 
        DIR_BACKWARD    = 2, 
        DIR_LEFT        = 4, 
        DIR_RIGHT       = 8, 
        DIR_UP          = 16, 
        DIR_DOWN        = 32,

        DIR_FORCE_32BIT = 0x7FFFFFFF
    };


    // ------------------------------------------------------------------------
    // Constructors & destructors for this class.
    // ------------------------------------------------------------------------
             Player();
    virtual ~Player();


    // ------------------------------------------------------------------------
    // Public functions for this class.
    // ------------------------------------------------------------------------
    void                SetPosition        (float x, float y, float z);
    void                SetRotate          (float x, float y, float z);

    void                Move               (ULONG Direction, float Distance);
    void                Move               (const Vec3& vecShift);
    void                Rotate             (float x, float y, float z);

private:
    // ------------------------------------------------------------------------
    // Private member functions
    // ------------------------------------------------------------------------
    void                UpdateCamera();


    // ------------------------------------------------------------------------
    // Players position and orientation values
    // ------------------------------------------------------------------------
    Vec3                m_vecPos;           // Player Position
    Vec3                m_vecUp;            // Player Up Vector
    Vec3                m_vecRight;         // Player Right Vector
    Vec3                m_vecLook;          // Player Look Vector
}; // class Player


#endif // _PLAYER_H

// -- EOF

