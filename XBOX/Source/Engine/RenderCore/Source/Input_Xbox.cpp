
#include "Input_Xbox.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// The buffer size for the direct input device
// ----------------------------------------------------------------------------
#define DI_BUFFER_SIZE 256
#define INPUT_ANALOGUE_BUTTON_THREASHOLD 30


Input_Xbox *Input_Xbox::s_pInstance = NULL;


Input_Xbox &Input_Xbox::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new Input_Xbox;
    atexit(Input_Xbox::DestroyInstance);
  }
  return *s_pInstance;
}


void Input_Xbox::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
}


// ----------------------------------------------------------------------------
// Name: Input_Xbox::Input_Xbox
// Desc: Constructor
// ----------------------------------------------------------------------------
Input_Xbox::Input_Xbox()
: BaseInput       (),
  m_GamePadHandle (0),
  m_GamePadDeadZone (0.3f)
{
  ZeroMemory(&m_GamepadData, sizeof(XINPUT_STATE));
  ZeroMemory(&m_GamepadAxisValue, sizeof(float) * 6);
  ZeroMemory(&m_GamepadButtonState, sizeof(BYTE) * 24);

  REF_COUNT_CTOR(Input_Xbox);
} // Input_Xbox


// ----------------------------------------------------------------------------
// Name: Input_Xbox::~Input_Xbox
// Desc: Destructor
// ----------------------------------------------------------------------------
Input_Xbox::~Input_Xbox()
{
  REF_COUNT_DTOR(Input_Xbox);

  // Make sure the devices are shutdown
  Shutdown();
} // ~Input_Xbox


// ----------------------------------------------------------------------------
// Name: Input_Xbox::Init
// Desc: Iniitialise the input system
// Retn: bool - true if the devices were initialised
// ----------------------------------------------------------------------------
bool Input_Xbox::Init()
{
  // Initialise the device support
  XInitDevices(0, NULL);

  // Get a mask of all currently available devices
  DWORD dwDeviceMask = XGetDevices(XDEVICE_TYPE_GAMEPAD);

  // Open the device in port 0
  if (dwDeviceMask & (1 << 0)) 
  {
    // Get a handle to the device
    m_GamePadHandle = XInputOpen(XDEVICE_TYPE_GAMEPAD, 0, XDEVICE_NO_SLOT, NULL);

    // Get the initial state
    if (m_GamePadHandle != 0)
      XInputGetState(m_GamePadHandle, &m_GamepadData);

    // Done
    return true;
  }

  // Did not find the gamepad
  m_GamePadHandle = 0;
  return false;
} // Init


// ----------------------------------------------------------------------------
// Name: Input_Xbox::Shutdown
// Desc: Shutdown the input system
// ----------------------------------------------------------------------------
void Input_Xbox::Shutdown()
{
  if (m_GamePadHandle)
    XInputClose(m_GamePadHandle);
} // Shutdown


// ----------------------------------------------------------------------------
// Name: Input_Xbox::ReadData
// Desc: read teh mouse and keyboard data
// Retn: bool - true if the devices were read
// ----------------------------------------------------------------------------
bool Input_Xbox::ReadData()
{
  return ReadGamepadData(); 
} // ReadData


//-----------------------------------------------------------------------------
// Name: GetGamepadParamName
// Desc: Get the gamepad parameter name
//-----------------------------------------------------------------------------
String Input_Xbox::GetGamepadParamName(GamepadParam param)
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
bool Input_Xbox::ReadGamepadData()
{
  // TODO: Check for insertion and removal

  if (m_GamePadHandle == 0)
    m_GamePadHandle = XInputOpen(XDEVICE_TYPE_GAMEPAD, 0, XDEVICE_NO_SLOT, NULL);

  if (m_GamePadHandle == 0)
    return true;

  // Get the current state
  XINPUT_STATE state;
  if (XInputGetState(m_GamePadHandle, &state) != ERROR_SUCCESS)
    return true;

  // Get the gamepad data
  XINPUT_GAMEPAD &data = state.Gamepad;

  // Check for button changes
  if (data.wButtons != m_GamepadData.Gamepad.wButtons)
  {
    // An array of the buttons we want to test
    static int buttons[8] = 
    {
      GAMEPAD_BUTTON_DPAD_UP,
      GAMEPAD_BUTTON_DPAD_DOWN,
      GAMEPAD_BUTTON_DPAD_LEFT,
      GAMEPAD_BUTTON_DPAD_RIGHT,
      GAMEPAD_BUTTON_START,
      GAMEPAD_BUTTON_BACK,
      GAMEPAD_BUTTON_LCLICK,
      GAMEPAD_BUTTON_RCLICK
    };

    // Test all buttons
    for (uint i = 0; i < 8; i++)
    {
      if ((data.wButtons & buttons[i]) != (m_GamepadData.Gamepad.wButtons & buttons[i]))
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

  static int analogueButtons[8][2] = 
  {
    { XINPUT_GAMEPAD_LEFT_TRIGGER,  GAMEPAD_BUTTON_L1  },
    { XINPUT_GAMEPAD_RIGHT_TRIGGER, GAMEPAD_BUTTON_R1  },
    { XINPUT_GAMEPAD_A,             GAMEPAD_BUTTON_A   },
    { XINPUT_GAMEPAD_B,             GAMEPAD_BUTTON_B   },
    { XINPUT_GAMEPAD_X,             GAMEPAD_BUTTON_X   },
    { XINPUT_GAMEPAD_Y,             GAMEPAD_BUTTON_Y   },
    { XINPUT_GAMEPAD_WHITE,         GAMEPAD_BUTTON_L2  },
    { XINPUT_GAMEPAD_BLACK,         GAMEPAD_BUTTON_R2  }
  };

  for (uint i = 0; i < 8; i++)
  {
    BYTE currVal = (data.bAnalogButtons[analogueButtons[i][0]]  > INPUT_ANALOGUE_BUTTON_THREASHOLD) ? 1 : 0;
    BYTE lastVal = (m_GamepadData.Gamepad.bAnalogButtons[analogueButtons[i][0]]  > INPUT_ANALOGUE_BUTTON_THREASHOLD) ? 1 : 0;

    // Test the left trigger
    if (currVal != lastVal)
    {
      GamepadMessage msg;
      msg.param = (GamepadParam) analogueButtons[i][1];
      msg.value = (currVal) ? GAMEPADVAL_DOWN : GAMEPADVAL_UP;

      m_GamepadMessageQueue.push(msg);
      m_GamepadButtonState[i + 8] = msg.value;

      //LOG_INFO << "Button: " << GetGamepadParamName(msg.param) << " = " << msg.value << ENDLOG;
    }
  }

  // Get the stick values in the range of -1.0f to 1.0f.
  m_GamepadAxisValue[0] = (static_cast<int>(data.sThumbLY)) / 32768.0f;
  m_GamepadAxisValue[1] = (static_cast<int>(data.sThumbLX)) / 32768.0f;
  m_GamepadAxisValue[2] = (static_cast<int>(data.sThumbRY)) / 32768.0f;
  m_GamepadAxisValue[3] = (static_cast<int>(data.sThumbRX)) / 32768.0f;
  m_GamepadAxisValue[4] = (static_cast<int>(data.bAnalogButtons[XINPUT_GAMEPAD_LEFT_TRIGGER]))  / 256.0f;
  m_GamepadAxisValue[5] = (static_cast<int>(data.bAnalogButtons[XINPUT_GAMEPAD_RIGHT_TRIGGER])) / 256.0f;

  for (uint i = 0; i < 4; i++)
  {
    if (m_GamepadAxisValue[i] > -0.1f && m_GamepadAxisValue[i] < 0.1f)
    {
      m_GamepadAxisValue[i] = 0.0f;
    }

    // TODO: else ... Filter here a bit (center dead zone)

  }

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
  static int axisButtons[8] = 
  {
    GAMEPAD_AXIS_LEFT_UP,
    GAMEPAD_AXIS_LEFT_DOWN,
    GAMEPAD_AXIS_LEFT_LEFT,
    GAMEPAD_AXIS_LEFT_RIGHT,
    GAMEPAD_AXIS_RIGHT_UP,
    GAMEPAD_AXIS_RIGHT_DOWN,
    GAMEPAD_AXIS_RIGHT_LEFT,
    GAMEPAD_AXIS_RIGHT_RIGHT
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
  m_GamepadData = state;
  return true;
} // ReadGamepadData


// ----------------------------------------------------------------------------
// Name: Input_Xbox::GetGamepadButtonState
// Desc: Get the current state of a keyboard key
// Parm: GamepadParam button - the button
// Retn: GamepadValue        - the state
// ----------------------------------------------------------------------------
GamepadValue Input_Xbox::GetGamepadButtonState(GamepadParam button)
{
  return (GamepadValue) (m_GamepadButtonState[GetButtonIndex(button)]);
}


// ----------------------------------------------------------------------------
// Name: Input_Xbox::GetGamepadAxisValue
// Desc: Get an axis value of the gamepad
// Retn: float - the value
// ----------------------------------------------------------------------------
float Input_Xbox::GetGamepadAxisValue(GamepadAxis axis)
{
  return m_GamepadAxisValue[axis];
}


// ----------------------------------------------------------------------------
// Name: Input_Xbox::PopGamepadMessage
// Desc: Get the next gamepad message from the queue
// Retn: Input_Xbox::GamepadMessage - the message
// ----------------------------------------------------------------------------
GamepadMessage Input_Xbox::PopGamepadMessage()
{
  GamepadMessage msg = m_GamepadMessageQueue.front();
  m_GamepadMessageQueue.pop();
  return msg;
} // PopGamepadMessage


// ----------------------------------------------------------------------------
// Name: Input_Xbox::HasGamepadMessage
// Desc: Are there any gamepad messages in the queue
// ----------------------------------------------------------------------------
bool Input_Xbox::HasGamepadMessage()
{
  return (!m_GamepadMessageQueue.empty());
} // HasGamepadMessage


// ----------------------------------------------------------------------------
// Name: Input_Xbox::SetGamepadAxisDeadZone
// Desc: Sets the threashold for determing when the axis movement should 
//       trigger digital state changes.
// ----------------------------------------------------------------------------
void Input_Xbox::SetGamepadAxisDeadZone(float deadZone)
{
  m_GamePadDeadZone = deadZone;
}


// ----------------------------------------------------------------------------
// Get the button index for a gamepad button
// ----------------------------------------------------------------------------
int Input_Xbox::GetButtonIndex(GamepadParam button)
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

// -- EOF

