// ----------------------------------------------------------------------------
// File: wxDirectX.cpp
// Desc: Global handles to the WX components
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "wxWindows/wxDirectX.h"
#include "wxWindows/wxDisplay.h"


// ----------------------------------------------------------------------------
// Teh application initialiser
// ----------------------------------------------------------------------------
wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);


// ----------------------------------------------------------------------------
// Create the application (called magically by wx windows)
// ----------------------------------------------------------------------------
wxAppConsole *wxCreateApp()
{
  wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "DirectX");
  return WxDisplay::GetApp();
}


// -- EOF

