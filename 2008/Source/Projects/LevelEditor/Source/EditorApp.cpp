
// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "EditorApp.h"
#include "EditorMainFrame.h"


// ----------------------------------------------------------------------------
// Create the main frame for the application
// ----------------------------------------------------------------------------
WxDisplayFrame *EditorApp::CreateFrame()
{
  // Get the display settings
  const DisplaySettings &settings = WxDisplay::GetDisplaySettings();

  // Get the wondow position and size
  wxPoint pos(settings.InitialWindowPosition.x, settings.InitialWindowPosition.y);
  wxSize size(settings.InitialWindowSize.cx, settings.InitialWindowSize.cy);

  // Create the main frame
  EditorMainFrame *pFrame = new EditorMainFrame(NULL, wxT(settings.InitialWindowCaption.c_str()), pos, size);
  WxDisplay::SetFrame(pFrame);

  // Set the min application frame size
  pFrame->SetMinSize(wxSize(800, 600));

  // Initialise the controls
  pFrame->InitControls();
  return pFrame;
}



// -- EOF


