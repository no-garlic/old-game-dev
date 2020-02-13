
#ifndef __INPUT_XBOX_H_
#define __INPUT_XBOX_H_


// ----------------------------------------------------------------------------
// Define the direct input version
// ----------------------------------------------------------------------------
#define DIRECTINPUT_VERSION  0x0800


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "Input.h"


// ----------------------------------------------------------------------------
// Name: Input  (class)
// Desc: Input system for handling mouse and keyboard
// ----------------------------------------------------------------------------
class Input_Xbox : public BaseInput
{
public:
  // --------------------------------------------------------------------------
  // Singleton
  // --------------------------------------------------------------------------
  static Input_Xbox &GetInstance();
  static void DestroyInstance();

  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Input_Xbox();
  virtual ~Input_Xbox();

  // --------------------------------------------------------------------------
  // Init and shutdown the input system
  // --------------------------------------------------------------------------
  virtual bool Init();
  virtual void Shutdown();

  // --------------------------------------------------------------------------
  // Read the data from the device
  // --------------------------------------------------------------------------
  virtual bool ReadData();

  // --------------------------------------------------------------------------
  // Get the current state of the gamepad
  // --------------------------------------------------------------------------
  virtual void SetGamepadAxisDeadZone(float deadZone);
  virtual GamepadValue GetGamepadButtonState(GamepadParam button);
  virtual float GetGamepadAxisValue(GamepadAxis axis);

  // --------------------------------------------------------------------------
  // See if the message queue's are empty
  // --------------------------------------------------------------------------
  virtual bool HasGamepadMessage();

  // --------------------------------------------------------------------------
  // Pop one message from the top of the message queue's.
  // --------------------------------------------------------------------------
  virtual GamepadMessage PopGamepadMessage();

  // --------------------------------------------------------------------------
  // Key conversions
  // --------------------------------------------------------------------------
  virtual int GetButtonIndex(GamepadParam button);
  virtual String GetGamepadParamName(GamepadParam param);

private:
  // --------------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------------
  bool ReadGamepadData();

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  HANDLE                  m_GamePadHandle;          // The gamepad handle
  XINPUT_STATE            m_GamepadData;            // The current state
  float                   m_GamePadDeadZone;        // The gamepad axis dead zone
  float                   m_GamepadAxisValue[6];    // The gamepad axis values
  BYTE                    m_GamepadButtonState[24]; // The gamepad button state
  Queue<GamepadMessage>   m_GamepadMessageQueue;    // Queue of gamepad messages
  static Input_Xbox      *s_pInstance;              // Singelton instance

}; // class Input_Xbox


#endif //__INPUT_XBOX_H_

// -- EOF


