// ----------------------------------------------------------------------------
// File: Input.h
// Desc: Direct Input wrapper
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef _INPUT_H
#define _INPUT_H


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"


// ----------------------------------------------------------------------------
// The input class implementation for the platform
// ----------------------------------------------------------------------------
#if XBOX
#define Input Input_Xbox::GetInstance()
#else
#define Input Input_PC::GetInstance()
#endif


// --------------------------------------------------------------------------
// Name: GamepadParam (enum)
// Desc: Gamepad parameters
// --------------------------------------------------------------------------
enum GamepadParam
{
#if XBOX
  GAMEPAD_BUTTON_DPAD_UP    = XINPUT_GAMEPAD_DPAD_UP,
  GAMEPAD_BUTTON_DPAD_DOWN  = XINPUT_GAMEPAD_DPAD_DOWN,
  GAMEPAD_BUTTON_DPAD_LEFT  = XINPUT_GAMEPAD_DPAD_LEFT,
  GAMEPAD_BUTTON_DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
  GAMEPAD_BUTTON_START      = XINPUT_GAMEPAD_START,
  GAMEPAD_BUTTON_BACK       = XINPUT_GAMEPAD_BACK,
  GAMEPAD_BUTTON_LCLICK     = XINPUT_GAMEPAD_LEFT_THUMB,
  GAMEPAD_BUTTON_RCLICK     = XINPUT_GAMEPAD_RIGHT_THUMB,
  GAMEPAD_BUTTON_L1         = 0x00001000,
  GAMEPAD_BUTTON_R1         = 0x00002000,
  GAMEPAD_BUTTON_A          = 0x00004000,
  GAMEPAD_BUTTON_B          = 0x00008000,
  GAMEPAD_BUTTON_X          = 0x00010000,
  GAMEPAD_BUTTON_Y          = 0x00020000,
  GAMEPAD_BUTTON_L2         = 0x00040000,
  GAMEPAD_BUTTON_R2         = 0x00080000,
  GAMEPAD_AXIS_LEFT_UP      = 0x00100000,
  GAMEPAD_AXIS_LEFT_DOWN    = 0x00200000,
  GAMEPAD_AXIS_LEFT_LEFT    = 0x00400000,
  GAMEPAD_AXIS_LEFT_RIGHT   = 0x00800000,
  GAMEPAD_AXIS_RIGHT_UP     = 0x01000000,
  GAMEPAD_AXIS_RIGHT_DOWN   = 0x02000000,
  GAMEPAD_AXIS_RIGHT_LEFT   = 0x04000000,
  GAMEPAD_AXIS_RIGHT_RIGHT  = 0x08000000
#else
  GAMEPAD_BUTTON_DPAD_UP    = XINPUT_GAMEPAD_DPAD_UP,
  GAMEPAD_BUTTON_DPAD_DOWN  = XINPUT_GAMEPAD_DPAD_DOWN,
  GAMEPAD_BUTTON_DPAD_LEFT  = XINPUT_GAMEPAD_DPAD_LEFT,
  GAMEPAD_BUTTON_DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
  GAMEPAD_BUTTON_START      = XINPUT_GAMEPAD_START,
  GAMEPAD_BUTTON_BACK       = XINPUT_GAMEPAD_BACK,
  GAMEPAD_BUTTON_LCLICK     = XINPUT_GAMEPAD_LEFT_THUMB,
  GAMEPAD_BUTTON_RCLICK     = XINPUT_GAMEPAD_RIGHT_THUMB,
  GAMEPAD_BUTTON_L1         = XINPUT_GAMEPAD_LEFT_SHOULDER,
  GAMEPAD_BUTTON_R1         = XINPUT_GAMEPAD_RIGHT_SHOULDER,
  GAMEPAD_BUTTON_A          = XINPUT_GAMEPAD_A,
  GAMEPAD_BUTTON_B          = XINPUT_GAMEPAD_B,
  GAMEPAD_BUTTON_X          = XINPUT_GAMEPAD_X,
  GAMEPAD_BUTTON_Y          = XINPUT_GAMEPAD_Y,
  GAMEPAD_BUTTON_L2         = 0x00010000,
  GAMEPAD_BUTTON_R2         = 0x00020000,
  GAMEPAD_AXIS_LEFT_UP      = 0x00040000,
  GAMEPAD_AXIS_LEFT_DOWN    = 0x00080000,
  GAMEPAD_AXIS_LEFT_LEFT    = 0x00100000,
  GAMEPAD_AXIS_LEFT_RIGHT   = 0x00200000,
  GAMEPAD_AXIS_RIGHT_UP     = 0x00400000,
  GAMEPAD_AXIS_RIGHT_DOWN   = 0x00800000,
  GAMEPAD_AXIS_RIGHT_LEFT   = 0x01000000,
  GAMEPAD_AXIS_RIGHT_RIGHT  = 0x02000000
#endif
}; // enum GamepadParam


// --------------------------------------------------------------------------
// Name: GamepadAxis (enum)
// Desc: Gamepad axis
// --------------------------------------------------------------------------
enum GamepadAxis
{
  GAMEPAD_AXIS_LEFT_X        = 0,
  GAMEPAD_AXIS_LEFT_Y        = 1,
  GAMEPAD_AXIS_RIGHT_X       = 2,
  GAMEPAD_AXIS_RIGHT_Y       = 3,
  GAMEPAD_AXIS_LEFT_TRIGGER  = 4,
  GAMEPAD_AXIS_RIGHT_TRIGGER = 5
};


// --------------------------------------------------------------------------
// Name: GamepadValue (enum)
// Desc: Values for the gamepad message
// --------------------------------------------------------------------------
enum GamepadValue
{
  GAMEPADVAL_UP,
  GAMEPADVAL_DOWN
}; // GamepadValue


// --------------------------------------------------------------------------
// Name: GamepadMessage (struct)
// Desc: The gamepad message
// --------------------------------------------------------------------------
struct GamepadMessage
{
  GamepadParam  param;
  GamepadValue  value;
};


// ----------------------------------------------------------------------------
// Name: Input  (class)
// Desc: Input system for handling mouse and keyboard
// ----------------------------------------------------------------------------
class BaseInput
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  BaseInput();
  virtual ~BaseInput();

  // --------------------------------------------------------------------------
  // Init and shutdown the input system
  // --------------------------------------------------------------------------
  virtual bool Init() = 0;
  virtual void Shutdown() = 0;

  // --------------------------------------------------------------------------
  // Read the data from the device
  // --------------------------------------------------------------------------
  virtual bool ReadData() = 0;

  // --------------------------------------------------------------------------
  // Get the current state of the gamepad
  // --------------------------------------------------------------------------
  virtual void SetGamepadAxisDeadZone(float deadZone) = 0;
  virtual GamepadValue GetGamepadButtonState(GamepadParam button) = 0;
  virtual float GetGamepadAxisValue(GamepadAxis axis) = 0;

  // --------------------------------------------------------------------------
  // See if the message queue's are empty
  // --------------------------------------------------------------------------
  virtual bool HasGamepadMessage() = 0;

  // --------------------------------------------------------------------------
  // Pop one message from the top of the message queue's.
  // --------------------------------------------------------------------------
  virtual GamepadMessage PopGamepadMessage() = 0;
  
  virtual int GetButtonIndex(GamepadParam button) = 0;

  virtual String GetGamepadParamName(GamepadParam param) = 0;

}; // class Input


#endif // _INPUT_H

// -- EOF

