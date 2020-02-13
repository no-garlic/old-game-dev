// ----------------------------------------------------------------------------
// File: Player.cpp
// Desc: This file stores the player object class. This class performs tasks 
//       such as player movement, some minor physics as well as rendering.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Player specific includes
// ----------------------------------------------------------------------------
#include "GameObject/Player.h"
#include "Engine/Camera.h"


// ----------------------------------------------------------------------------
// Name: Player::Player
// Desc: Constructor
// ----------------------------------------------------------------------------
Player::Player()
{
    // Players position & orientation
    m_vecPos    = Vec3(0.0f, 0.0f, 0.0f);
    m_vecRight  = Vec3(1.0f, 0.0f, 0.0f);
    m_vecUp     = Vec3(0.0f, 1.0f, 0.0f);
    m_vecLook   = Vec3(0.0f, 0.0f, 1.0f);
} // Player


// ----------------------------------------------------------------------------
// Name: Player::~Player
// Desc: Destructor
// ----------------------------------------------------------------------------
Player::~Player()
{
} // ~Player


// ----------------------------------------------------------------------------
// Name: Player::SetPosition
// Desc: Set the players position
// Parm: float x  - the x axis
// Parm: float y  - the y axis
// Parm: float z  - the z axis
// ----------------------------------------------------------------------------
void Player::SetPosition(float x, float y, float z)
{
    m_vecPos.Set(x, y, z);
    UpdateCamera();
} // SetPosition


// ----------------------------------------------------------------------------
// Name: Player::Move
// Desc: Move the camera in the specified direction for the specified distance. 
//       Note : Specify 'true' to velocity if you wish the move to affect the 
//       cameras velocity rather than it's absolute position
// Parm: ULONG Direction - the direction to move
// Parm: float Distance  - the distance to move
// ----------------------------------------------------------------------------
void Player::Move(ULONG Direction, float Distance)
{
    Vec3 vecShift = Vec3(0, 0, 0);

    // Which direction are we moving ?
    if (Direction & DIR_FORWARD ) vecShift += m_vecLook  * Distance;
    if (Direction & DIR_BACKWARD) vecShift -= m_vecLook  * Distance;
    if (Direction & DIR_RIGHT   ) vecShift += m_vecRight * Distance;
    if (Direction & DIR_LEFT    ) vecShift -= m_vecRight * Distance;
    if (Direction & DIR_UP      ) vecShift += m_vecUp    * Distance;
    if (Direction & DIR_DOWN    ) vecShift -= m_vecUp    * Distance;

    // Update camera vectors
    Move(vecShift);
} // Move


// ----------------------------------------------------------------------------
// Name: Player::Move
// Desc: Move the camera by the specified amount based on the vector passed.
// Parm: const Vec3& vecShift - the vector to move the player
// ----------------------------------------------------------------------------
void Player::Move(const Vec3& vecShift)
{
    m_vecPos += vecShift;
    UpdateCamera();
} // Move


// ----------------------------------------------------------------------------
// Name: Player::SetRotate
// Desc: Rotate the player around the world axis.
// Parm: float x  - the x axis
// Parm: float y  - the y axis
// Parm: float z  - the z axis
// ----------------------------------------------------------------------------
void Player::SetRotate(float x , float y , float z)
{ 
    m_vecRight.Set(1.0f,  0.0f,  0.0f);
    m_vecUp.Set   (0.0f,  1.0f,  0.0f);
    m_vecLook.Set (0.0f,  0.0f,  1.0f);

    Rotate(x, y, z);
} // SetRotate


// ----------------------------------------------------------------------------
// Name: Player::Rotate
// Desc: Rotate the player around the players local axis.
// Parm: float x  - the x axis
// Parm: float y  - the y axis
// Parm: float z  - the z axis
// ----------------------------------------------------------------------------
void Player::Rotate(float x, float y, float z)
{
    Matrix matRotate; 

    if (x != 0) 
    { 
        // Build rotation matrix 
        D3DXMatrixRotationAxis (&matRotate,  &m_vecRight,   D3DXToRadian(x)); 
        D3DXVec3TransformNormal(&m_vecLook,  &m_vecLook,    &matRotate);
        D3DXVec3TransformNormal(&m_vecUp,    &m_vecUp,      &matRotate);
    } // if

    if (y != 0) 
    { 
        // Build rotation matrix 
        D3DXMatrixRotationAxis (&matRotate,  &m_vecUp,      D3DXToRadian(y)); 
        D3DXVec3TransformNormal(&m_vecLook,  &m_vecLook,    &matRotate);
        D3DXVec3TransformNormal(&m_vecRight, &m_vecRight,   &matRotate);
    } // if

    if (z != 0)
    { 
        // Build rotation matrix 
        D3DXMatrixRotationAxis (&matRotate,  &m_vecLook,    D3DXToRadian(z));
        D3DXVec3TransformNormal(&m_vecUp,    &m_vecUp,      &matRotate);
        D3DXVec3TransformNormal(&m_vecRight, &m_vecRight,   &matRotate);
    } // if 

    // Perform vector regeneration 
    D3DXVec3Normalize(&m_vecLook, &m_vecLook); 
    D3DXVec3Cross(&m_vecRight, &m_vecUp, &m_vecLook); 
    D3DXVec3Normalize(&m_vecRight, &m_vecRight); 
    D3DXVec3Cross(&m_vecUp, &m_vecLook, &m_vecRight); 
    D3DXVec3Normalize(&m_vecUp, &m_vecUp);

    // Update the camera
    UpdateCamera();
} // Rotate


// ----------------------------------------------------------------------------
// Name: Player::UpdateCamera
// Desc: Update the camera with the players position and look vector
// ----------------------------------------------------------------------------
void Player::UpdateCamera()
{
    CameraSingleton::Instance().SetView(m_vecPos, m_vecLook, m_vecUp, m_vecRight);
} // UpdateCamera


// -- EOF
