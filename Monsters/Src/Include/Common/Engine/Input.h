// ----------------------------------------------------------------------------
// File: Input.h
// Desc: Direct Input wrapper
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef _INPUT_H
#define _INPUT_H


// ----------------------------------------------------------------------------
// Define the direct input version
// ----------------------------------------------------------------------------
#define DIRECTINPUT_VERSION  0x0800


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"


// ----------------------------------------------------------------------------
// Name: Input  (class)
// Desc: Input system for handling mouse and keyboard
// ----------------------------------------------------------------------------
class Input
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Input();
  ~Input();

  // --------------------------------------------------------------------------
  // Init and shutdown the input system
  // --------------------------------------------------------------------------
  bool Init();
  void Shutdown();

  // --------------------------------------------------------------------------
  // Read the data from the device
  // --------------------------------------------------------------------------
  bool ReadData();

  // --------------------------------------------------------------------------
  // Name: MouseParam (enum)
  // Desc: Parameters for the mouse message
  // --------------------------------------------------------------------------
  enum MouseParam
  {
    MOUSEPARAM_BUTTON_0,
    MOUSEPARAM_BUTTON_1,
    MOUSEPARAM_BUTTON_2,
    MOUSEPARAM_BUTTON_3,
    MOUSEPARAM_BUTTON_4,
    MOUSEPARAM_BUTTON_5,
    MOUSEPARAM_BUTTON_6,
    MOUSEPARAM_BUTTON_7,
    MOUSEPARAM_MOVE_X,
    MOUSEPARAM_MOVE_Y,
    MOUSEPARAM_MOVE_Z
  }; // enum MouseParam


  // --------------------------------------------------------------------------
  // Name: KeyParam (enum)
  // Desc: Key parameters
  // --------------------------------------------------------------------------
  enum KeyParam
  {
    KEYPARAM_ESCAPE          = 0x01,
    KEYPARAM_1               = 0x02,
    KEYPARAM_2               = 0x03,
    KEYPARAM_3               = 0x04,
    KEYPARAM_4               = 0x05,
    KEYPARAM_5               = 0x06,
    KEYPARAM_6               = 0x07,
    KEYPARAM_7               = 0x08,
    KEYPARAM_8               = 0x09,
    KEYPARAM_9               = 0x0A,
    KEYPARAM_0               = 0x0B,
    KEYPARAM_MINUS           = 0x0C,
    KEYPARAM_EQUALS          = 0x0D,
    KEYPARAM_BACK            = 0x0E,
    KEYPARAM_TAB             = 0x0F,
    KEYPARAM_Q               = 0x10,
    KEYPARAM_W               = 0x11,
    KEYPARAM_E               = 0x12,
    KEYPARAM_R               = 0x13,
    KEYPARAM_T               = 0x14,
    KEYPARAM_Y               = 0x15,
    KEYPARAM_U               = 0x16,
    KEYPARAM_I               = 0x17,
    KEYPARAM_O               = 0x18,
    KEYPARAM_P               = 0x19,
    KEYPARAM_LBRACKET        = 0x1A,
    KEYPARAM_RBRACKET        = 0x1B,
    KEYPARAM_RETURN          = 0x1C,
    KEYPARAM_LCONTROL        = 0x1D,
    KEYPARAM_A               = 0x1E,
    KEYPARAM_S               = 0x1F,
    KEYPARAM_D               = 0x20,
    KEYPARAM_F               = 0x21,
    KEYPARAM_G               = 0x22,
    KEYPARAM_H               = 0x23,
    KEYPARAM_J               = 0x24,
    KEYPARAM_K               = 0x25,
    KEYPARAM_L               = 0x26,
    KEYPARAM_SEMICOLON       = 0x27,
    KEYPARAM_APOSTROPHE      = 0x28,
    KEYPARAM_GRAVE           = 0x29,
    KEYPARAM_LSHIFT          = 0x2A,
    KEYPARAM_BACKSLASH       = 0x2B,
    KEYPARAM_Z               = 0x2C,
    KEYPARAM_X               = 0x2D,
    KEYPARAM_C               = 0x2E,
    KEYPARAM_V               = 0x2F,
    KEYPARAM_B               = 0x30,
    KEYPARAM_N               = 0x31,
    KEYPARAM_M               = 0x32,
    KEYPARAM_COMMA           = 0x33,
    KEYPARAM_PERIOD          = 0x34,
    KEYPARAM_SLASH           = 0x35,
    KEYPARAM_RSHIFT          = 0x36,
    KEYPARAM_MULTIPLY        = 0x37,
    KEYPARAM_LMENU           = 0x38,
    KEYPARAM_SPACE           = 0x39,
    KEYPARAM_CAPITAL         = 0x3A,
    KEYPARAM_F1              = 0x3B,
    KEYPARAM_F2              = 0x3C,
    KEYPARAM_F3              = 0x3D,
    KEYPARAM_F4              = 0x3E,
    KEYPARAM_F5              = 0x3F,
    KEYPARAM_F6              = 0x40,
    KEYPARAM_F7              = 0x41,
    KEYPARAM_F8              = 0x42,
    KEYPARAM_F9              = 0x43,
    KEYPARAM_F10             = 0x44,
    KEYPARAM_NUMLOCK         = 0x45,
    KEYPARAM_SCROLL          = 0x46,
    KEYPARAM_NUMPAD7         = 0x47,
    KEYPARAM_NUMPAD8         = 0x48,
    KEYPARAM_NUMPAD9         = 0x49,
    KEYPARAM_SUBTRACT        = 0x4A,
    KEYPARAM_NUMPAD4         = 0x4B,
    KEYPARAM_NUMPAD5         = 0x4C,
    KEYPARAM_NUMPAD6         = 0x4D,
    KEYPARAM_ADD             = 0x4E,
    KEYPARAM_NUMPAD1         = 0x4F,
    KEYPARAM_NUMPAD2         = 0x50,
    KEYPARAM_NUMPAD3         = 0x51,
    KEYPARAM_NUMPAD0         = 0x52,
    KEYPARAM_DECIMAL         = 0x53,
    KEYPARAM_OEM_102         = 0x56,
    KEYPARAM_F11             = 0x57,
    KEYPARAM_F12             = 0x58,
    KEYPARAM_F13             = 0x64,
    KEYPARAM_F14             = 0x65,
    KEYPARAM_F15             = 0x66,
    KEYPARAM_KANA            = 0x70,
    KEYPARAM_ABNT_C1         = 0x73,
    KEYPARAM_CONVERT         = 0x79,
    KEYPARAM_NOCONVERT       = 0x7B,
    KEYPARAM_YEN             = 0x7D,
    KEYPARAM_ABNT_C2         = 0x7E,
    KEYPARAM_NUMPADEQUALS    = 0x8D,
    KEYPARAM_PREVTRACK       = 0x90,
    KEYPARAM_AT              = 0x91,
    KEYPARAM_COLON           = 0x92,
    KEYPARAM_UNDERLINE       = 0x93,
    KEYPARAM_KANJI           = 0x94,
    KEYPARAM_STOP            = 0x95,
    KEYPARAM_AX              = 0x96,
    KEYPARAM_UNLABELED       = 0x97,
    KEYPARAM_NEXTTRACK       = 0x99,
    KEYPARAM_NUMPADENTER     = 0x9C,
    KEYPARAM_RCONTROL        = 0x9D,
    KEYPARAM_MUTE            = 0xA0,
    KEYPARAM_CALCULATOR      = 0xA1,
    KEYPARAM_PLAYPAUSE       = 0xA2,
    KEYPARAM_MEDIASTOP       = 0xA4,
    KEYPARAM_VOLUMEDOWN      = 0xAE,
    KEYPARAM_VOLUMEUP        = 0xB0,
    KEYPARAM_WEBHOME         = 0xB2,
    KEYPARAM_NUMPADCOMMA     = 0xB3,
    KEYPARAM_DIVIDE          = 0xB5,
    KEYPARAM_SYSRQ           = 0xB7,
    KEYPARAM_RMENU           = 0xB8,
    KEYPARAM_PAUSE           = 0xC5,
    KEYPARAM_HOME            = 0xC7,
    KEYPARAM_UP              = 0xC8,
    KEYPARAM_PRIOR           = 0xC9,
    KEYPARAM_LEFT            = 0xCB,
    KEYPARAM_RIGHT           = 0xCD,
    KEYPARAM_END             = 0xCF,
    KEYPARAM_DOWN            = 0xD0,
    KEYPARAM_NEXT            = 0xD1,
    KEYPARAM_INSERT          = 0xD2,
    KEYPARAM_DELETE          = 0xD3,
    KEYPARAM_LWIN            = 0xDB,
    KEYPARAM_RWIN            = 0xDC,
    KEYPARAM_APPS            = 0xDD,
    KEYPARAM_POWER           = 0xDE,
    KEYPARAM_SLEEP           = 0xDF,
    KEYPARAM_WAKE            = 0xE3,
    KEYPARAM_WEBSEARCH       = 0xE5,
    KEYPARAM_WEBFAVORITES    = 0xE6,
    KEYPARAM_WEBREFRESH      = 0xE7,
    KEYPARAM_WEBSTOP         = 0xE8,
    KEYPARAM_WEBFORWARD      = 0xE9,
    KEYPARAM_WEBBACK         = 0xEA,
    KEYPARAM_MYCOMPUTER      = 0xEB,
    KEYPARAM_MAIL            = 0xEC,
    KEYPARAM_MEDIASELECT     = 0xED,
    KEYPARAM_BACKSPACE       = KEYPARAM_BACK,        
    KEYPARAM_NUMPADSTAR      = KEYPARAM_MULTIPLY,    
    KEYPARAM_LALT            = KEYPARAM_LMENU,       
    KEYPARAM_CAPSLOCK        = KEYPARAM_CAPITAL,     
    KEYPARAM_NUMPADMINUS     = KEYPARAM_SUBTRACT,    
    KEYPARAM_NUMPADPLUS      = KEYPARAM_ADD,         
    KEYPARAM_NUMPADPERIOD    = KEYPARAM_DECIMAL,     
    KEYPARAM_NUMPADSLASH     = KEYPARAM_DIVIDE,      
    KEYPARAM_RALT            = KEYPARAM_RMENU,       
    KEYPARAM_UPARROW         = KEYPARAM_UP,          
    KEYPARAM_PGUP            = KEYPARAM_PRIOR,       
    KEYPARAM_LEFTARROW       = KEYPARAM_LEFT,        
    KEYPARAM_RIGHTARROW      = KEYPARAM_RIGHT,       
    KEYPARAM_DOWNARROW       = KEYPARAM_DOWN,        
    KEYPARAM_PGDN            = KEYPARAM_NEXT         
  }; // enum KeyParam


  // --------------------------------------------------------------------------
  // Name: MouseValue (enum)
  // Desc: Values for hte mouse message
  // --------------------------------------------------------------------------
  enum MouseValue
  {
    MOUSEVAL_BUTTON_UP,
    MOUSEVAL_BUTTON_DOWN
  }; // MouseValue

  // --------------------------------------------------------------------------
  // Name: KeyValue (enum)
  // Desc: Values for the key message
  // --------------------------------------------------------------------------
  enum KeyValue
  {
    KEYVAL_UP,
    KEYVAL_DOWN
  }; // KeyValue

  // --------------------------------------------------------------------------
  // Name: MouseMessage (struct)
  // Desc: The mouse message
  // --------------------------------------------------------------------------
  struct MouseMessage
  {
    MouseParam    param;
    int           value;    
  }; // struct MouseMessage

  // --------------------------------------------------------------------------
  // Name: KeyboardMessage (struct)
  // Desc: The keyboard message
  // --------------------------------------------------------------------------
  struct KeyboardMessage
  {
    KeyParam      param;
    int           value;
  }; // struct KeyboardMessage

  // --------------------------------------------------------------------------
  // Get the current state of the mouse and keyboard
  // --------------------------------------------------------------------------
  int GetMouseState(MouseParam btn);
  int GetKeyboardState(DWORD key);

  // --------------------------------------------------------------------------
  // See if the message queue's are empty
  // --------------------------------------------------------------------------
  bool HasMouseMessage();
  bool HasKeyboardMessage();

  // --------------------------------------------------------------------------
  // Pop one message from the top of the message queue's.
  // --------------------------------------------------------------------------
  MouseMessage PopMouseMessage();
  KeyboardMessage PopKeyboardMessage();

private:
  // --------------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------------
  bool ReadMouseData();
  bool ReadKeyboardData();

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  LPDIRECTINPUT8              m_pDirectInput;         // Direct input device
  LPDIRECTINPUTDEVICE8        m_pMouse;               // Mouse device
  LPDIRECTINPUTDEVICE8        m_pKeyboard;            // Keyboard device
  DIMOUSESTATE2               m_MouseState;           // Stored mouse state
  BYTE                        m_KeyState[256];        // Stored key state
  std::queue<MouseMessage>    m_MouseMessageQueue;    // Queue of mouse messages
  std::queue<KeyboardMessage> m_KeyboardMessageQueue; // Queue of key messages

}; // class Input


#endif // _INPUT_H

// -- EOF

