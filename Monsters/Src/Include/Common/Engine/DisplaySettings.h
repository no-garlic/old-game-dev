// ----------------------------------------------------------------------------
// File: DisplaySettings.h
// Desc: Settings used to configure the display
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __DISPLAY_SETTINGS_H_
#define __DISPLAY_SETTINGS_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"


// ----------------------------------------------------------------------------
// Name: DisplaySettings (struct)
// Desc: Structure to hold the settings
// ----------------------------------------------------------------------------
struct DisplaySettings
{
  DisplaySettings();
  ~DisplaySettings();

  // Display type
  bool                    StartFullScreen;        // Do we start in fullscreen mode
  bool                    IsNull;                 // Is this a null renderer

  // Windowed
  D3DPRESENT_PARAMETERS   WindowParams;           // Params for window mode
  DWORD                   WindowStyle;            // The window style
  String                  WindowClassName;        // Window class name
  String                  InitialWindowCaption;   // Initial window caption
  SIZE                    InitialWindowSize;      // Initial window size
  SIZE                    PreviousWindowSize;     // Previous window size
  SIZE                    PreviousClientSize;     // Previous client size
  POINT                   InitialWindowPosition;  // Initial window position
  POINT                   PreviousWindowPosition; // Previous window position
  POINT                   PreviousClientPosition; // Previous client position

  // Fullscreen
  D3DPRESENT_PARAMETERS   FullScreenParams;       // Params for fullscreen mode
  DWORD                   FullScreenStyle;        // The fullscreen window style

  // Null
  D3DPRESENT_PARAMETERS   NullParams;             // Params for null renderer mode

}; // struct DisplaySettings


#endif // __DISPLAY_SETTINGS_H_

// -- EOF

