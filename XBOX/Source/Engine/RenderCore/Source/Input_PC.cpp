
#include "Input_PC.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// The buffer size for the direct input device
// ----------------------------------------------------------------------------
#define DI_BUFFER_SIZE 256

Input_PC *Input_PC::s_pInstance = NULL;


Input_PC &Input_PC::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new Input_PC;
    atexit(Input_PC::DestroyInstance);
  }
  return *s_pInstance;
}


void Input_PC::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
}


// ----------------------------------------------------------------------------
// Name: Input_PC::Input_PC
// Desc: Constructor
// ----------------------------------------------------------------------------
Input_PC::Input_PC()
: BaseInput               (),
  m_pDirectInput          (0),
  m_pMouse                (0),
  m_pKeyboard             (0),
  m_GamePadDeadZone       (0.3f)

{
  REF_COUNT_CTOR(Input_PC);

  // Initialise the memory
  ZeroMemory(&m_MouseState, sizeof(m_MouseState));
  ZeroMemory(&m_GamepadData, sizeof(XINPUT_GAMEPAD));
  ZeroMemory(&m_GamepadAxisValue, sizeof(float) * 6);
  ZeroMemory(&m_GamepadButtonState, sizeof(BYTE) * 24);
  ZeroMemory(&m_KeyState, sizeof(BYTE) * 256);  
} // Input_PC


// ----------------------------------------------------------------------------
// Name: Input_PC::~Input_PC
// Desc: Destructor
// ----------------------------------------------------------------------------
Input_PC::~Input_PC()
{
  REF_COUNT_DTOR(Input_PC);

  // Make sure the devices are shutdown
  Shutdown();
} // ~Input_PC


// ----------------------------------------------------------------------------
// Name: Input_PC::Init
// Desc: Iniitialise the input system
// Retn: bool - true if the devices were initialised
// ----------------------------------------------------------------------------
bool Input_PC::Init()
{
  DWORD dwCoopFlags = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND;

  // Create a DInput object
  HRESULT hr;
  if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
    IID_IDirectInput8, (VOID**)&m_pDirectInput, NULL)))
    return false;

  // Obtain an interface to the system mouse device
  if (FAILED(hr = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
    return false;

  // Obtain an interface to the system keyboard device
  if (FAILED(hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL)))
    return false;

  // Set the data format of the mouse device
  if (FAILED(hr = m_pMouse->SetDataFormat(&c_dfDIMouse2)))
    return false;

  // Set the data format of the keyboard device
  if (FAILED(hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard)))
    return false;

  // Set the cooperative level of the mouse device
  hr = m_pMouse->SetCooperativeLevel(Application.GetHWND(), FALSE);
  if (hr == DIERR_UNSUPPORTED)
    return false;

  // Set the cooperative level of the keyboard device
  hr = m_pKeyboard->SetCooperativeLevel(Application.GetHWND(), FALSE);
  if (hr == DIERR_UNSUPPORTED)
    return false;

  // Create the mouse input buffer
  DIPROPDWORD dipdw_mouse;
  dipdw_mouse.diph.dwSize       = sizeof(DIPROPDWORD);
  dipdw_mouse.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw_mouse.diph.dwObj        = 0;
  dipdw_mouse.diph.dwHow        = DIPH_DEVICE;
  dipdw_mouse.dwData            = DI_BUFFER_SIZE; // buffer size

  // Set the mouse input buffer
  if (FAILED(hr = m_pMouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw_mouse.diph)))
    return false;

  // Create the keyboard input buffer
  DIPROPDWORD dipdw_keyboard;
  dipdw_keyboard.diph.dwSize       = sizeof(DIPROPDWORD);
  dipdw_keyboard.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw_keyboard.diph.dwObj        = 0;
  dipdw_keyboard.diph.dwHow        = DIPH_DEVICE;
  dipdw_keyboard.dwData            = DI_BUFFER_SIZE; // buffer size

  // Set the keyboard input buffer
  if (FAILED(hr = m_pKeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw_keyboard.diph)))
    return false;

  // Acquire the newly created devices
  m_pMouse->Acquire();
  m_pKeyboard->Acquire();

  // Done
  return true;
} // Init


// ----------------------------------------------------------------------------
// Name: Input_PC::Shutdown
// Desc: Shutdown the input system
// ----------------------------------------------------------------------------
void Input_PC::Shutdown()
{
  if (m_pMouse) 
    m_pMouse->Unacquire();

  if (m_pKeyboard) 
    m_pKeyboard->Unacquire();

  if (m_pMouse)
  {
    m_pMouse->Release();
    m_pMouse = NULL;
  } // if

  if (m_pKeyboard)
  {
    m_pKeyboard->Release();
    m_pKeyboard = NULL;
  } // if

  if (m_pDirectInput)
  {
    m_pDirectInput->Release();
    m_pDirectInput = NULL;
  } // if
} // Shutdown


// ----------------------------------------------------------------------------
// Name: Input_PC::ReadData
// Desc: read teh mouse and keyboard data
// Retn: bool - true if the devices were read
// ----------------------------------------------------------------------------
bool Input_PC::ReadData()
{
  // Cleanup any events we didnt collect last frame
  while (!m_KeyboardMessageQueue.empty())
    m_KeyboardMessageQueue.pop();
  while (!m_MouseMessageQueue.empty())
    m_MouseMessageQueue.pop();
  while (!m_GamepadMessageQueue.empty())
    m_GamepadMessageQueue.pop();

  // Collect the new input events
  return ReadMouseData() & ReadKeyboardData() & ReadGamepadData(); 
} // ReadData


//-----------------------------------------------------------------------------
// Name: ReadMouseData
// Desc: Read the input device's state when in buffered mode and display it.
//-----------------------------------------------------------------------------
bool Input_PC::ReadMouseData()
{
  // Make sure we have created the mouse device
  if (!m_pMouse)
    return false;

  // Remove any events we did not get last frame
  while (!m_MouseMessageQueue.empty())
    m_MouseMessageQueue.pop();

  // Read the device data
  DWORD dwElements = 256;
  DIDEVICEOBJECTDATA didod[DI_BUFFER_SIZE];
  HRESULT hr = m_pMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), didod, &dwElements, 0);

  // If the read failed, try to acquire the device again
  if (hr != DI_OK) 
  {
    hr = m_pMouse->Acquire();
    while (hr == DIERR_INPUTLOST)
      hr = m_pMouse->Acquire();

    return true; 
  } // if
  else if (FAILED(hr))  
  {
    return false;
  } // else if

  // Get the current mouse state
  m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &m_MouseState);

  // Read each message in the buffer
  for (unsigned int i = 0; i < dwElements; i++)
  {
    // The new mouse message
    MouseMessage message;

    // Determine the message type
    bool found = true;
    switch (didod[i].dwOfs)
    {
      case DIMOFS_BUTTON0:    message.param = MOUSEPARAM_BUTTON_0;   break;
      case DIMOFS_BUTTON1:    message.param = MOUSEPARAM_BUTTON_1;   break;
      case DIMOFS_BUTTON2:    message.param = MOUSEPARAM_BUTTON_2;   break;
      case DIMOFS_BUTTON3:    message.param = MOUSEPARAM_BUTTON_3;   break;
      case DIMOFS_BUTTON4:    message.param = MOUSEPARAM_BUTTON_4;   break;
      case DIMOFS_BUTTON5:    message.param = MOUSEPARAM_BUTTON_5;   break;
      case DIMOFS_BUTTON6:    message.param = MOUSEPARAM_BUTTON_6;   break;
      case DIMOFS_BUTTON7:    message.param = MOUSEPARAM_BUTTON_7;   break;
      case DIMOFS_X:          message.param = MOUSEPARAM_MOVE_X;     break;
      case DIMOFS_Y:          message.param = MOUSEPARAM_MOVE_Y;     break;
      case DIMOFS_Z:          message.param = MOUSEPARAM_MOVE_Z;     break;
      default:                found = false;                         break;
    } // switch

    // Discard the messgage if not found
    if (!found)
      continue;

    // Get the message value
    switch (didod[ i ].dwOfs)
    {
      case DIMOFS_BUTTON0:
      case DIMOFS_BUTTON1:
      case DIMOFS_BUTTON2:
      case DIMOFS_BUTTON3:
      case DIMOFS_BUTTON4:
      case DIMOFS_BUTTON5:
      case DIMOFS_BUTTON6:
      case DIMOFS_BUTTON7:
      {
        if (didod[i].dwData & 0x80)
          message.value = MOUSEVAL_BUTTON_DOWN;
        else
          message.value = MOUSEVAL_BUTTON_UP;
        break;
      } // case

      case DIMOFS_X:
      case DIMOFS_Y:
      case DIMOFS_Z:
      {
        message.value = (int) didod[i].dwData;
        break;
      } // case
    } // switch

    // Send the message
    m_MouseMessageQueue.push(message);
  } // for

  // Done
  return true;
} // ReadMouseData


//-----------------------------------------------------------------------------
// Name: ReadKeyboardData
// Desc: Read the input device's state when in buffered mode and display it.
//-----------------------------------------------------------------------------
bool Input_PC::ReadKeyboardData()
{
  // Make sure we have created the mouse device
  if (!m_pKeyboard)
    return false;

  // Remove any events we did not get last frame
  while (!m_KeyboardMessageQueue.empty())
    m_KeyboardMessageQueue.pop();

  // Read the device data
  DWORD dwElements = 256;
  DIDEVICEOBJECTDATA didod[DI_BUFFER_SIZE];
  HRESULT hr = m_pKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), didod, &dwElements, 0);

  // If the read failed, try to acquire the device again
  if (hr != DI_OK) 
  {
    hr = m_pKeyboard->Acquire();
    while (hr == DIERR_INPUTLOST)
      hr = m_pKeyboard->Acquire();

    return true; 
  } // if
  else if (FAILED(hr))  
  {
    return false;
  } // else if

  // Get the current keyboard state
  m_pKeyboard->GetDeviceState(sizeof(m_KeyState), &m_KeyState);

  // Read each message in the buffer
  for (unsigned int i = 0; i < dwElements; i++)
  {
    // The new keyboard message
    KeyboardMessage message;

    // Set the message data
    message.param = (KeyParam) didod[i].dwOfs;
    message.value = (didod[i].dwData & 0x80) ? KEYVAL_DOWN : KEYVAL_UP;

    // Send the message
    m_KeyboardMessageQueue.push(message);
  } // for

  // Done
  return true;
} // ReadKeyboardData


//-----------------------------------------------------------------------------
// Name: operator==
// Desc: Comparison operator for the XINPUT_GAMEPAD structure
//-----------------------------------------------------------------------------
inline bool operator==(const XINPUT_GAMEPAD &a, const XINPUT_GAMEPAD &b)
{
  return (a.wButtons      == b.wButtons       &&
          a.bLeftTrigger  == b.bLeftTrigger   && 
          a.bRightTrigger == b.bRightTrigger  &&
          a.sThumbLX      == b.sThumbLX       &&
          a.sThumbLY      == b.sThumbLY       &&
          a.sThumbRX      == b.sThumbRX       &&
          a.sThumbRY      == b.sThumbRY);
} // operator==


//-----------------------------------------------------------------------------
// Name: GetGamepadParamName
// Desc: Get the gamepad parameter name
//-----------------------------------------------------------------------------
String Input_PC::GetGamepadParamName(GamepadParam param)
{
  switch (param)
  {
  case GAMEPAD_BUTTON_DPAD_UP:    return "GAMEPAD_BUTTON_DPAD_UP";
  case GAMEPAD_BUTTON_DPAD_DOWN:  return "GAMEPAD_BUTTON_DPAD_DOWN";
  case GAMEPAD_BUTTON_DPAD_LEFT:  return "GAMEPAD_BUTTON_DPAD_LEFT";
  case GAMEPAD_BUTTON_DPAD_RIGHT: return "GAMEPAD_BUTTON_DPAD_RIGHT";
  case GAMEPAD_BUTTON_START:      return "GAMEPAD_BUTTON_START";
  case GAMEPAD_BUTTON_BACK:       return "GAMEPAD_BUTTON_BACK";
  case GAMEPAD_BUTTON_LCLICK:     return "GAMEPAD_BUTTON_LCLICK";
  case GAMEPAD_BUTTON_RCLICK:     return "GAMEPAD_BUTTON_RCLICK";
  case GAMEPAD_BUTTON_L1:         return "GAMEPAD_BUTTON_L1";
  case GAMEPAD_BUTTON_R1:         return "GAMEPAD_BUTTON_R1";
  case GAMEPAD_BUTTON_A:          return "GAMEPAD_BUTTON_A";
  case GAMEPAD_BUTTON_B:          return "GAMEPAD_BUTTON_B";
  case GAMEPAD_BUTTON_X:          return "GAMEPAD_BUTTON_X";
  case GAMEPAD_BUTTON_Y:          return "GAMEPAD_BUTTON_Y";
  case GAMEPAD_BUTTON_L2:         return "GAMEPAD_BUTTON_L2";
  case GAMEPAD_BUTTON_R2:         return "GAMEPAD_BUTTON_R2";
  case GAMEPAD_AXIS_LEFT_UP:      return "GAMEPAD_AXIS_LEFT_UP";
  case GAMEPAD_AXIS_LEFT_DOWN:    return "GAMEPAD_AXIS_LEFT_DOWN";
  case GAMEPAD_AXIS_LEFT_LEFT:    return "GAMEPAD_AXIS_LEFT_LEFT";
  case GAMEPAD_AXIS_LEFT_RIGHT:   return "GAMEPAD_AXIS_LEFT_RIGHT";
  case GAMEPAD_AXIS_RIGHT_UP:     return "GAMEPAD_AXIS_RIGHT_UP";
  case GAMEPAD_AXIS_RIGHT_DOWN:   return "GAMEPAD_AXIS_RIGHT_DOWN";
  case GAMEPAD_AXIS_RIGHT_LEFT:   return "GAMEPAD_AXIS_RIGHT_LEFT";
  case GAMEPAD_AXIS_RIGHT_RIGHT:  return "GAMEPAD_AXIS_RIGHT_RIGHT";
  default:                        return "Unknown";
  }
}


//-----------------------------------------------------------------------------
// Name: ReadGamepadData
// Desc: Read the input device's state when in buffered mode and display it.
//-----------------------------------------------------------------------------
bool Input_PC::ReadGamepadData()
{
  // Remove any events we did not get last frame
  while (!m_GamepadMessageQueue.empty())
    m_GamepadMessageQueue.pop();

  XINPUT_STATE gamepadState;
  ZeroMemory(&gamepadState, sizeof(XINPUT_STATE));

  // Get the current gamepad state
  if (XInputGetState(0, &gamepadState) == ERROR_SUCCESS)
  {
    // Get the gamepad data
    XINPUT_GAMEPAD &data = gamepadState.Gamepad;

    // Check for no change
//    if (data == m_GamepadData)
//      return true;

    // Check for button changes
    if (data.wButtons != m_GamepadData.wButtons)
    {
      // An array of the buttons we want to test
      static INT buttons[14] = 
      {
        GAMEPAD_BUTTON_DPAD_UP,
        GAMEPAD_BUTTON_DPAD_DOWN,
        GAMEPAD_BUTTON_DPAD_LEFT,
        GAMEPAD_BUTTON_DPAD_RIGHT,
        GAMEPAD_BUTTON_START,
        GAMEPAD_BUTTON_BACK,
        GAMEPAD_BUTTON_LCLICK,
        GAMEPAD_BUTTON_RCLICK,
        GAMEPAD_BUTTON_L1,
        GAMEPAD_BUTTON_R1,
        GAMEPAD_BUTTON_A,
        GAMEPAD_BUTTON_B,
        GAMEPAD_BUTTON_X,
        GAMEPAD_BUTTON_Y,
      };

      // Test all 14 buttons
      for (uint i = 0; i < 14; i++)
      {
        if ((data.wButtons & buttons[i]) != (m_GamepadData.wButtons & buttons[i]))
        {
          GamepadMessage msg;
          msg.param = (GamepadParam) buttons[i];
          msg.value = (data.wButtons & buttons[i]) ? GAMEPADVAL_DOWN : GAMEPADVAL_UP;
          
          m_GamepadMessageQueue.push(msg);

          m_GamepadButtonState[i] = msg.value;

          //LOG_INFO << "Button: " << GetGamepadParamName(msg.param) << " = " << msg.value << ENDLOG;
        }
      }
    }

    // Get the left and right trigger values (as digital)
    BYTE leftTrigger  = (data.bLeftTrigger  > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? 1 : 0;
    BYTE rightTrigger = (data.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? 1 : 0;

    // Convert the previous values
    BYTE oldLeftTrigger  = (m_GamepadData.bLeftTrigger  > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? 1 : 0;
    BYTE oldRightTrigger = (m_GamepadData.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? 1 : 0;

    // Test the left trigger
    if (leftTrigger != oldLeftTrigger)
    {
      GamepadMessage msg;
      msg.param = GAMEPAD_BUTTON_L2;
      msg.value = (leftTrigger) ? GAMEPADVAL_DOWN : GAMEPADVAL_UP;

      m_GamepadMessageQueue.push(msg);

      m_GamepadButtonState[14] = msg.value;

      //LOG_INFO << "Button: " << GetGamepadParamName(msg.param) << " = " << msg.value << ENDLOG;
    }

    // Test the right trigger
    if (rightTrigger != oldRightTrigger)
    {
      GamepadMessage msg;
      msg.param = GAMEPAD_BUTTON_R2;
      msg.value = (rightTrigger) ? GAMEPADVAL_DOWN : GAMEPADVAL_UP;
      
      m_GamepadMessageQueue.push(msg);

      m_GamepadButtonState[15] = msg.value;

      //LOG_INFO << "Button: " << GetGamepadParamName(msg.param) << " = " << msg.value << ENDLOG;
    }

    // Get the stick values in the range of -1.0f to 1.0f.
    m_GamepadAxisValue[0] = (static_cast<int>(data.sThumbLX))       / 32768.0f;
    m_GamepadAxisValue[1] = (static_cast<int>(data.sThumbLY))       / 32768.0f;
    m_GamepadAxisValue[2] = (static_cast<int>(data.sThumbRX))       / 32768.0f;
    m_GamepadAxisValue[3] = (static_cast<int>(data.sThumbRY))       / 32768.0f;
    m_GamepadAxisValue[4] = (static_cast<int>(data.bLeftTrigger))   / 256.0f;
    m_GamepadAxisValue[5] = (static_cast<int>(data.bRightTrigger))  / 256.0f;

    for (uint i = 0; i < 4; i++)
      if (m_GamepadAxisValue[i] > -0.2f && m_GamepadAxisValue[i] < 0.2f)
        m_GamepadAxisValue[i] = 0.0f;
      else
        m_GamepadAxisValue[i] = (m_GamepadAxisValue[i] - 0.2f) * 1.2f;

    float lAxisU = (m_GamepadAxisValue[0] - m_GamePadDeadZone);
    float lAxisD = (m_GamepadAxisValue[0] + m_GamePadDeadZone);
    float lAxisL = (m_GamepadAxisValue[1] + m_GamePadDeadZone);
    float lAxisR = (m_GamepadAxisValue[1] - m_GamePadDeadZone);
    float rAxisU = (m_GamepadAxisValue[2] - m_GamePadDeadZone);
    float rAxisD = (m_GamepadAxisValue[2] + m_GamePadDeadZone);
    float rAxisL = (m_GamepadAxisValue[3] + m_GamePadDeadZone);
    float rAxisR = (m_GamepadAxisValue[3] - m_GamePadDeadZone);

    // Make an array of axis values
    BYTE axisValues[8] = 
    {
      lAxisU > 0.0f ? 1 : 0,
      lAxisD < 0.0f ? 1 : 0,
      lAxisL < 0.0f ? 1 : 0,
      lAxisR > 0.0f ? 1 : 0,
      rAxisU > 0.0f ? 1 : 0,
      rAxisD < 0.0f ? 1 : 0,
      rAxisL < 0.0f ? 1 : 0,
      rAxisR > 0.0f ? 1 : 0
    };

    // An array of the buttons we want to test
    static INT axisButtons[8] = 
    {
      GAMEPAD_AXIS_LEFT_RIGHT,
      GAMEPAD_AXIS_LEFT_LEFT,
      GAMEPAD_AXIS_LEFT_DOWN,
      GAMEPAD_AXIS_LEFT_UP,
      GAMEPAD_AXIS_RIGHT_RIGHT,
      GAMEPAD_AXIS_RIGHT_LEFT,
      GAMEPAD_AXIS_RIGHT_DOWN,
      GAMEPAD_AXIS_RIGHT_UP
    };

    for (uint i = 0; i < 8; i++)
    {
      if (axisValues[i] != m_GamepadButtonState[i + 16])
      {

        GamepadMessage msg;
        msg.param = (GamepadParam) axisButtons[i];
        msg.value = axisValues[i] ? GAMEPADVAL_DOWN : GAMEPADVAL_UP;
        m_GamepadMessageQueue.push(msg);

        m_GamepadButtonState[i + 16] = msg.value;

        //LOG_INFO << "Button: " << GetGamepadParamName(msg.param) << " = " << msg.value << ENDLOG;
      }
    }

    // Set the gamepad data for next frame
    m_GamepadData = data;
  }
  else
  {
    //LOG_INFO << "Failed to get the XInput data from the controller" << ENDLOG;
  }

  // Done
  return true;
} // ReadGamepadData


// ----------------------------------------------------------------------------
// Name: Input_PC::GetMouseState
// Desc: Get the mouse state
// Parm: MouseParam btn - the parameter
// Retn: int            - the parameter value
// ----------------------------------------------------------------------------
int Input_PC::GetMouseState(MouseParam btn)
{
  switch (btn)
  {
    case MOUSEPARAM_BUTTON_0:  return (int) (m_MouseState.rgbButtons[0] & 0x80) ? MOUSEVAL_BUTTON_DOWN : MOUSEVAL_BUTTON_UP;
    case MOUSEPARAM_BUTTON_1:  return (int) (m_MouseState.rgbButtons[1] & 0x80) ? MOUSEVAL_BUTTON_DOWN : MOUSEVAL_BUTTON_UP;
    case MOUSEPARAM_BUTTON_2:  return (int) (m_MouseState.rgbButtons[2] & 0x80) ? MOUSEVAL_BUTTON_DOWN : MOUSEVAL_BUTTON_UP;
    case MOUSEPARAM_BUTTON_3:  return (int) (m_MouseState.rgbButtons[3] & 0x80) ? MOUSEVAL_BUTTON_DOWN : MOUSEVAL_BUTTON_UP;
    case MOUSEPARAM_BUTTON_4:  return (int) (m_MouseState.rgbButtons[4] & 0x80) ? MOUSEVAL_BUTTON_DOWN : MOUSEVAL_BUTTON_UP;
    case MOUSEPARAM_BUTTON_5:  return (int) (m_MouseState.rgbButtons[5] & 0x80) ? MOUSEVAL_BUTTON_DOWN : MOUSEVAL_BUTTON_UP;
    case MOUSEPARAM_BUTTON_6:  return (int) (m_MouseState.rgbButtons[6] & 0x80) ? MOUSEVAL_BUTTON_DOWN : MOUSEVAL_BUTTON_UP;
    case MOUSEPARAM_BUTTON_7:  return (int) (m_MouseState.rgbButtons[7] & 0x80) ? MOUSEVAL_BUTTON_DOWN : MOUSEVAL_BUTTON_UP;
    case MOUSEPARAM_MOVE_X:    return (int) m_MouseState.lX;
    case MOUSEPARAM_MOVE_Y:    return (int) m_MouseState.lY;
    case MOUSEPARAM_MOVE_Z:    return (int) m_MouseState.lZ;
  }; // switch

  return 0;
} // GetMouseState


// ----------------------------------------------------------------------------
// Name: Input_PC::GetKeyboardState
// Desc: Get the current state of a keyboard key
// Parm: DWORD key - the key
// Retn: int       - the state
// ----------------------------------------------------------------------------
int Input_PC::GetKeyboardState(DWORD key)
{
  return (m_KeyState[key] & 0x80) ? KEYVAL_DOWN : KEYVAL_UP;
} // GetKeyboardState


// ----------------------------------------------------------------------------
// Name: Input_PC::GetGamepadButtonState
// Desc: Get the current state of a keyboard key
// Parm: GamepadParam button - the button
// Retn: GamepadValue        - the state
// ----------------------------------------------------------------------------
GamepadValue Input_PC::GetGamepadButtonState(GamepadParam button)
{
  return (GamepadValue) (m_GamepadButtonState[GetButtonIndex(button)]);
}


// ----------------------------------------------------------------------------
// Name: Input_PC::GetGamepadAxisValue
// Desc: Get an axis value of the gamepad
// Retn: float - the value
// ----------------------------------------------------------------------------
float Input_PC::GetGamepadAxisValue(GamepadAxis axis)
{
  return m_GamepadAxisValue[axis];
}


// ----------------------------------------------------------------------------
// Name: Input_PC::PopMouseMessage
// Desc: Get the next mouse message from the queue
// Retn: Input_PC::MouseMessage - the message
// ----------------------------------------------------------------------------
MouseMessage Input_PC::PopMouseMessage()
{
  MouseMessage msg = m_MouseMessageQueue.front();
  m_MouseMessageQueue.pop();
  return msg;
} // PopMouseMessage


// ----------------------------------------------------------------------------
// Name: Input_PC::PopKeyboardMessage
// Desc: Get the next keyboard message from the queue
// Retn: Input_PC::KeyboardMessage - the message
// ----------------------------------------------------------------------------
KeyboardMessage Input_PC::PopKeyboardMessage()
{
  KeyboardMessage msg = m_KeyboardMessageQueue.front();
  m_KeyboardMessageQueue.pop();
  return msg;
} // PopKeyboardMessage


// ----------------------------------------------------------------------------
// Name: Input_PC::PopGamepadMessage
// Desc: Get the next gamepad message from the queue
// Retn: Input_PC::GamepadMessage - the message
// ----------------------------------------------------------------------------
GamepadMessage Input_PC::PopGamepadMessage()
{
  GamepadMessage msg = m_GamepadMessageQueue.front();
  m_GamepadMessageQueue.pop();
  return msg;
} // PopGamepadMessage


// ----------------------------------------------------------------------------
// Name: Input_PC::HasMouseMessage
// Desc: Are there any mouse messages in the queue
// ----------------------------------------------------------------------------
bool Input_PC::HasMouseMessage()
{
  return (!m_MouseMessageQueue.empty());
} // HasMouseMessage


// ----------------------------------------------------------------------------
// Name: Input_PC::HasKeyboardMessage
// Desc: Are there any keyboard messages in the queue
// ----------------------------------------------------------------------------
bool Input_PC::HasKeyboardMessage()
{
  return (!m_KeyboardMessageQueue.empty());
} // HasKeyboardMessage


// ----------------------------------------------------------------------------
// Name: Input_PC::HasGamepadMessage
// Desc: Are there any gamepad messages in the queue
// ----------------------------------------------------------------------------
bool Input_PC::HasGamepadMessage()
{
  return (!m_GamepadMessageQueue.empty());
} // HasGamepadMessage


// ----------------------------------------------------------------------------
// Name: Input_PC::SetGamepadAxisDeadZone
// Desc: Sets the threashold for determing when the axis movement should 
//       trigger digital state changes.
// ----------------------------------------------------------------------------
void Input_PC::SetGamepadAxisDeadZone(float deadZone)
{
  m_GamePadDeadZone = deadZone;
}


// ----------------------------------------------------------------------------
// Get the button index for a gamepad button
// ----------------------------------------------------------------------------
int Input_PC::GetButtonIndex(GamepadParam button)
{
  switch (button)
  {
    case GAMEPAD_BUTTON_DPAD_UP:     return 0;
    case GAMEPAD_BUTTON_DPAD_DOWN:   return 1;
    case GAMEPAD_BUTTON_DPAD_LEFT:   return 2;
    case GAMEPAD_BUTTON_DPAD_RIGHT:  return 3;
    case GAMEPAD_BUTTON_START:       return 4;
    case GAMEPAD_BUTTON_BACK:        return 5;
    case GAMEPAD_BUTTON_LCLICK:      return 6;
    case GAMEPAD_BUTTON_RCLICK:      return 7;
    case GAMEPAD_BUTTON_L1:          return 8;
    case GAMEPAD_BUTTON_R1:          return 9;
    case GAMEPAD_BUTTON_A:           return 10;
    case GAMEPAD_BUTTON_B:           return 11;
    case GAMEPAD_BUTTON_X:           return 12;
    case GAMEPAD_BUTTON_Y:           return 13;
    case GAMEPAD_BUTTON_L2:          return 14;
    case GAMEPAD_BUTTON_R2:          return 15;
    case GAMEPAD_AXIS_LEFT_UP:       return 16;
    case GAMEPAD_AXIS_LEFT_DOWN:     return 17;
    case GAMEPAD_AXIS_LEFT_LEFT:     return 18;
    case GAMEPAD_AXIS_LEFT_RIGHT:    return 19;
    case GAMEPAD_AXIS_RIGHT_UP:      return 20;
    case GAMEPAD_AXIS_RIGHT_DOWN:    return 21;
    case GAMEPAD_AXIS_RIGHT_LEFT:    return 22;
    case GAMEPAD_AXIS_RIGHT_RIGHT:   return 23;
  };

  ASSERT(0, "Not a valid button");
  return 0;
}


// ----------------------------------------------------------------------------
// Check if the key is a number key
// ----------------------------------------------------------------------------
bool Input_PC::IsNumber(KeyParam key)
{
  switch (key)
  {
  case KEYPARAM_0:  case KEYPARAM_NUMPAD0:
  case KEYPARAM_1:  case KEYPARAM_NUMPAD1:
  case KEYPARAM_2:  case KEYPARAM_NUMPAD2:
  case KEYPARAM_3:  case KEYPARAM_NUMPAD3:
  case KEYPARAM_4:  case KEYPARAM_NUMPAD4:
  case KEYPARAM_5:  case KEYPARAM_NUMPAD5:
  case KEYPARAM_6:  case KEYPARAM_NUMPAD6:
  case KEYPARAM_7:  case KEYPARAM_NUMPAD7:
  case KEYPARAM_8:  case KEYPARAM_NUMPAD8:
  case KEYPARAM_9:  case KEYPARAM_NUMPAD9:
    return true;
  };

  return false;
}


// ----------------------------------------------------------------------------
// Check if the key is a text key
// ----------------------------------------------------------------------------
bool Input_PC::IsText(KeyParam key)
{
  switch (key)
  {
  case KEYPARAM_A:
  case KEYPARAM_B:
  case KEYPARAM_C:
  case KEYPARAM_D:
  case KEYPARAM_E:
  case KEYPARAM_F:
  case KEYPARAM_G:
  case KEYPARAM_H:
  case KEYPARAM_I:
  case KEYPARAM_J:
  case KEYPARAM_K:
  case KEYPARAM_L:
  case KEYPARAM_M:
  case KEYPARAM_N:
  case KEYPARAM_O:
  case KEYPARAM_P:
  case KEYPARAM_Q:
  case KEYPARAM_R:
  case KEYPARAM_S:
  case KEYPARAM_T:
  case KEYPARAM_U:
  case KEYPARAM_V:
  case KEYPARAM_W:
  case KEYPARAM_X:
  case KEYPARAM_Y:
  case KEYPARAM_Z:
    return true;
  };

  return false;
}


// ----------------------------------------------------------------------------
// Check if the key is a symbol key
// ----------------------------------------------------------------------------
bool Input_PC::IsSymbol(KeyParam key)
{
  switch (key)
  {
  case KEYPARAM_MINUS:
  case KEYPARAM_EQUALS:
  case KEYPARAM_LBRACKET:
  case KEYPARAM_RBRACKET:
  case KEYPARAM_SEMICOLON:
  case KEYPARAM_APOSTROPHE:
  case KEYPARAM_GRAVE:
  case KEYPARAM_BACKSLASH:
  case KEYPARAM_COMMA:
  case KEYPARAM_PERIOD:
  case KEYPARAM_SLASH:
  case KEYPARAM_MULTIPLY:
  case KEYPARAM_SPACE:
  case KEYPARAM_SUBTRACT:
  case KEYPARAM_ADD:
  case KEYPARAM_DECIMAL:
  case KEYPARAM_NUMPADEQUALS:
  case KEYPARAM_COLON:
  case KEYPARAM_UNDERLINE:
  case KEYPARAM_NUMPADCOMMA:
  case KEYPARAM_DIVIDE:
//  case KEYPARAM_NUMPADSTAR:
//  case KEYPARAM_NUMPADMINUS:
//  case KEYPARAM_NUMPADPLUS:
//  case KEYPARAM_NUMPADPERIOD:
//  case KEYPARAM_NUMPADSLASH:
    return true;
  };

  return false;
}


// ----------------------------------------------------------------------------
// Check if the key is a printable key
// ----------------------------------------------------------------------------
bool Input_PC::IsPrintable(KeyParam key)
{
  return (IsText(key) || IsNumber(key) || IsSymbol(key));
}


// ----------------------------------------------------------------------------
// Convert the key to it's char value
// ----------------------------------------------------------------------------
char Input_PC::ToChar(KeyParam key)
{
  switch (key)
  {
  case KEYPARAM_0:  case KEYPARAM_NUMPAD0:  return '0';
  case KEYPARAM_1:  case KEYPARAM_NUMPAD1:  return '1'; 
  case KEYPARAM_2:  case KEYPARAM_NUMPAD2:  return '2';
  case KEYPARAM_3:  case KEYPARAM_NUMPAD3:  return '3';
  case KEYPARAM_4:  case KEYPARAM_NUMPAD4:  return '4';
  case KEYPARAM_5:  case KEYPARAM_NUMPAD5:  return '5';
  case KEYPARAM_6:  case KEYPARAM_NUMPAD6:  return '6';
  case KEYPARAM_7:  case KEYPARAM_NUMPAD7:  return '7';
  case KEYPARAM_8:  case KEYPARAM_NUMPAD8:  return '8';
  case KEYPARAM_9:  case KEYPARAM_NUMPAD9:  return '9';
  case KEYPARAM_A:                          return 'a';
  case KEYPARAM_B:                          return 'b';
  case KEYPARAM_C:                          return 'c';
  case KEYPARAM_D:                          return 'd';
  case KEYPARAM_E:                          return 'e';
  case KEYPARAM_F:                          return 'f';
  case KEYPARAM_G:                          return 'g';
  case KEYPARAM_H:                          return 'h';
  case KEYPARAM_I:                          return 'i';
  case KEYPARAM_J:                          return 'j';
  case KEYPARAM_K:                          return 'k';
  case KEYPARAM_L:                          return 'l';
  case KEYPARAM_M:                          return 'm';
  case KEYPARAM_N:                          return 'n';
  case KEYPARAM_O:                          return 'o';
  case KEYPARAM_P:                          return 'p';
  case KEYPARAM_Q:                          return 'q';
  case KEYPARAM_R:                          return 'r';
  case KEYPARAM_S:                          return 's';
  case KEYPARAM_T:                          return 't';
  case KEYPARAM_U:                          return 'u';
  case KEYPARAM_V:                          return 'v';
  case KEYPARAM_W:                          return 'w';
  case KEYPARAM_X:                          return 'x';
  case KEYPARAM_Y:                          return 'y';
  case KEYPARAM_Z:                          return 'z';
  case KEYPARAM_MINUS:                      return '-';
  case KEYPARAM_EQUALS:                     return '=';
  case KEYPARAM_LBRACKET:                   return '[';
  case KEYPARAM_RBRACKET:                   return ']';
  case KEYPARAM_SEMICOLON:                  return ':';
  case KEYPARAM_APOSTROPHE:                 return '\'';
  case KEYPARAM_GRAVE:                      return '`';
  case KEYPARAM_BACKSLASH:                  return '\\';
  case KEYPARAM_COMMA:                      return ',';
  case KEYPARAM_PERIOD:                     return '.';
  case KEYPARAM_SLASH:                      return '/';
  case KEYPARAM_MULTIPLY:                   return '*';
  case KEYPARAM_SPACE:                      return ' ';
  case KEYPARAM_SUBTRACT:                   return '-';
  case KEYPARAM_ADD:                        return '+';
  case KEYPARAM_DECIMAL:                    return '.';
  case KEYPARAM_NUMPADEQUALS:               return '=';
  case KEYPARAM_COLON:                      return ':';
  case KEYPARAM_UNDERLINE:                  return '_';
  case KEYPARAM_NUMPADCOMMA:                return ',';
  case KEYPARAM_DIVIDE:                     return '/';
//  case KEYPARAM_NUMPADSTAR:                 return '*';
//  case KEYPARAM_NUMPADMINUS:                return '-';
//  case KEYPARAM_NUMPADPLUS:                 return '+';
//  case KEYPARAM_NUMPADPERIOD:               return '.';
//  case KEYPARAM_NUMPADSLASH:                return '/';
  };

  return '\0';
}









// -- EOF

