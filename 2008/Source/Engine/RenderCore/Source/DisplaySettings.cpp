// ----------------------------------------------------------------------------
// File: DisplaySettings.cpp
// Desc: Settings used to configure the display
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "DisplaySettings.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
DisplaySettings::DisplaySettings()
{
#if XBOX
  ZeroMemory(&FullScreenParams, sizeof(D3DPRESENT_PARAMETERS));

  FullScreenParams.BackBufferWidth                  = 640;
  FullScreenParams.BackBufferHeight                 = 480;
  FullScreenParams.BackBufferFormat                 = D3DFMT_X8R8G8B8;
  FullScreenParams.BackBufferCount                  = 1;
  FullScreenParams.MultiSampleType                  = D3DMULTISAMPLE_NONE;
  FullScreenParams.SwapEffect                       = D3DSWAPEFFECT_DISCARD;
  FullScreenParams.hDeviceWindow                    = NULL;
  FullScreenParams.Windowed                         = FALSE;
  FullScreenParams.EnableAutoDepthStencil           = TRUE;
  FullScreenParams.AutoDepthStencilFormat           = D3DFMT_D24S8;
  FullScreenParams.Flags                            = 0;
  FullScreenParams.FullScreen_RefreshRateInHz       = 0;
  FullScreenParams.FullScreen_PresentationInterval  = D3DPRESENT_INTERVAL_DEFAULT;

#else
  ZeroMemory(&WindowParams, sizeof(D3DPRESENT_PARAMETERS));
  ZeroMemory(&FullScreenParams, sizeof(D3DPRESENT_PARAMETERS));
  ZeroMemory(&NullParams, sizeof(D3DPRESENT_PARAMETERS));

  WindowParams.BackBufferCount                = 1;
  WindowParams.BackBufferFormat               = D3DFMT_X8R8G8B8;
  WindowParams.Windowed                       = TRUE;
  WindowParams.MultiSampleType                = D3DMULTISAMPLE_NONE;
  WindowParams.MultiSampleQuality             = 0;
  WindowParams.EnableAutoDepthStencil         = TRUE;
  WindowParams.AutoDepthStencilFormat         = D3DFMT_D24X8;
  WindowParams.PresentationInterval           = D3DPRESENT_INTERVAL_IMMEDIATE;
  WindowParams.Flags                          = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
  WindowParams.SwapEffect                     = D3DSWAPEFFECT_DISCARD;
  WindowParams.FullScreen_RefreshRateInHz     = 0;
  WindowParams.BackBufferWidth                = 0;
  WindowParams.BackBufferHeight               = 0;

  FullScreenParams.BackBufferCount            = 1;
  FullScreenParams.BackBufferFormat           = D3DFMT_X8R8G8B8;
  FullScreenParams.Windowed                   = FALSE;
  FullScreenParams.MultiSampleType            = D3DMULTISAMPLE_NONE;
  FullScreenParams.MultiSampleQuality         = 0;
  FullScreenParams.EnableAutoDepthStencil     = TRUE;
  FullScreenParams.AutoDepthStencilFormat     = D3DFMT_D24X8;
  FullScreenParams.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
  FullScreenParams.Flags                      = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
  FullScreenParams.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
  FullScreenParams.FullScreen_RefreshRateInHz = 60;
  FullScreenParams.BackBufferWidth            = 800;
  FullScreenParams.BackBufferHeight           = 600;

  NullParams.BackBufferCount                  = 1;
  NullParams.BackBufferFormat                 = D3DFMT_A8R8G8B8;
  NullParams.Windowed                         = TRUE;
  NullParams.MultiSampleType                  = D3DMULTISAMPLE_NONE;
  NullParams.MultiSampleQuality               = 0;
  NullParams.EnableAutoDepthStencil           = FALSE;
  NullParams.AutoDepthStencilFormat           = D3DFMT_D32;
  NullParams.PresentationInterval             = D3DPRESENT_INTERVAL_DEFAULT;
  NullParams.Flags                            = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
  NullParams.SwapEffect                       = D3DSWAPEFFECT_DISCARD;
  NullParams.FullScreen_RefreshRateInHz       = 0;
  NullParams.BackBufferWidth                  = 800;
  NullParams.BackBufferHeight                 = 600;

  InitialWindowSize.cx      = 800;
  InitialWindowSize.cy      = 600;

  PreviousWindowSize.cx     = 800;
  PreviousWindowSize.cy     = 600;

  PreviousClientSize.cx     = 0;
  PreviousClientSize.cy     = 0;

  InitialWindowPosition.x   = CW_USEDEFAULT;
  InitialWindowPosition.y   = CW_USEDEFAULT;

  PreviousWindowPosition.x  = 0;
  PreviousWindowPosition.y  = 0;

  PreviousClientPosition.x  = 0;
  PreviousClientPosition.y  = 0;

  WindowClassName           = "Application";
  InitialWindowCaption      = "Application";

  StartFullScreen           = false;
  IsNull                    = false;

  WindowStyle               = WS_OVERLAPPEDWINDOW;
  FullScreenStyle           = WS_POPUP;
#endif
} // DisplaySettings


// -- EOF

