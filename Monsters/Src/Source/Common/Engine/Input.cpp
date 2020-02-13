
#include "Engine/Input.h"
#include "Engine/ApplicationCentral.h"


// ----------------------------------------------------------------------------
// The buffer size for the direct input device
// ----------------------------------------------------------------------------
#define DI_BUFFER_SIZE 256


// ----------------------------------------------------------------------------
// Name: Input::Input
// Desc: Constructor
// ----------------------------------------------------------------------------
Input::Input()
: m_pDirectInput    (0),
  m_pMouse          (0),
  m_pKeyboard       (0)
{
  REF_COUNT_CTOR(Input);

  ZeroMemory(&m_MouseState, sizeof(m_MouseState));
} // Input


// ----------------------------------------------------------------------------
// Name: Input::~Input
// Desc: Destructor
// ----------------------------------------------------------------------------
Input::~Input()
{
  REF_COUNT_DTOR(Input);

  // Make sure the devices are shutdown
  Shutdown();
} // ~Input


// ----------------------------------------------------------------------------
// Name: Input::Init
// Desc: Iniitialise the input system
// Retn: bool - true if the devices were initialised
// ----------------------------------------------------------------------------
bool Input::Init()
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
  hr = m_pMouse->SetCooperativeLevel(ApplicationCentral.GetHWND(), FALSE);
  if (hr == DIERR_UNSUPPORTED)
    return false;

  // Set the cooperative level of the keyboard device
  hr = m_pKeyboard->SetCooperativeLevel(ApplicationCentral.GetHWND(), FALSE);
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
// Name: Input::Shutdown
// Desc: Shutdown the input system
// ----------------------------------------------------------------------------
void Input::Shutdown()
{
  // Unacquire the device
  if (m_pMouse) 
    m_pMouse->Unacquire();

  // Release any DirectInput objects
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
// Name: Input::ReadData
// Desc: read teh mouse and keyboard data
// Retn: bool - true if the devices were read
// ----------------------------------------------------------------------------
bool Input::ReadData()
{
  return ReadMouseData() & ReadKeyboardData(); 
} // ReadData


//-----------------------------------------------------------------------------
// Name: ReadMouseData()
// Desc: Read the input device's state when in buffered mode and display it.
//-----------------------------------------------------------------------------
bool Input::ReadMouseData()
{
  // Make sure we have created the mouse device
  if (!m_pMouse)
    return false;

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
      default:                found = false;                break;
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
// Name: ReadKeyboardData()
// Desc: Read the input device's state when in buffered mode and display it.
//-----------------------------------------------------------------------------
bool Input::ReadKeyboardData()
{
  // Make sure we have created the mouse device
  if (!m_pKeyboard)
    return false;

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


// ----------------------------------------------------------------------------
// Name: Input::GetMouseState
// Desc: Get the mouse state
// Parm: MouseParam btn - the parameter
// Retn: int            - the parameter value
// ----------------------------------------------------------------------------
int Input::GetMouseState(MouseParam btn)
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
// Name: Input::GetKeyboardState
// Desc: Get the current state of a keyboard key
// Parm: DWORD key - the key
// Retn: int       - the state
// ----------------------------------------------------------------------------
int Input::GetKeyboardState(DWORD key)
{
  return (m_KeyState[key] & 0x80) ? KEYVAL_DOWN : KEYVAL_UP;
} // GetKeyboardState


// ----------------------------------------------------------------------------
// Name: Input::PopMouseMessage
// Desc: Get the next mouse message from the queue
// Retn: Input::MouseMessage - the message
// ----------------------------------------------------------------------------
Input::MouseMessage Input::PopMouseMessage()
{
  Input::MouseMessage msg = m_MouseMessageQueue.front();
  m_MouseMessageQueue.pop();
  return msg;
} // PopMouseMessage


// ----------------------------------------------------------------------------
// Name: Input::PopKeyboardMessage
// Desc: Get the next keyboard message from the queue
// Retn: Input::KeyboardMessage - the message
// ----------------------------------------------------------------------------
Input::KeyboardMessage Input::PopKeyboardMessage()
{
  Input::KeyboardMessage msg = m_KeyboardMessageQueue.front();
  m_KeyboardMessageQueue.pop();
  return msg;
} // PopKeyboardMessage


// ----------------------------------------------------------------------------
// Name: Input::HasMouseMessage
// Desc: Are there any mouse messages in the queue
// ----------------------------------------------------------------------------
bool Input::HasMouseMessage()
{
  return (!m_MouseMessageQueue.empty());
} // HasMouseMessage


// ----------------------------------------------------------------------------
// Name: Input::HasKeyboardMessage
// Desc: Are there any keyboard messages in the queue
// ----------------------------------------------------------------------------
bool Input::HasKeyboardMessage()
{
  return (!m_KeyboardMessageQueue.empty());
} // HasKeyboardMessage


// -- EOF

