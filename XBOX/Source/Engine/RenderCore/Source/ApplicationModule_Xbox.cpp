// ----------------------------------------------------------------------------
// File: ApplicationModule_Xbox.cpp
// Desc: The Xbox direct3d driver
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "ApplicationModule_Xbox.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Xbox::ApplicationModule_Xbox
// Desc: Constructor
// ----------------------------------------------------------------------------
ApplicationModule_Xbox::ApplicationModule_Xbox(const String &name)
: ApplicationModule(name)
{
  REF_COUNT_CTOR(ApplicationModule_Xbox);
} // ApplicationModule_Xbox


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Xbox::~ApplicationModule_Xbox
// Desc: destructor
// ----------------------------------------------------------------------------
ApplicationModule_Xbox::~ApplicationModule_Xbox()
{
  REF_COUNT_DTOR(ApplicationModule_Xbox);
} // ~ApplicationModule_Xbox


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Xbox::SetWindowTitle
// Desc: Sets the window title
// Parm: const String &str - the title
// ----------------------------------------------------------------------------
void ApplicationModule_Xbox::SetWindowTitle(const String &str)
{
  // Not implemented on Xbox
} // SetWindowTitle


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Xbox::Main
// Desc: The startup function for the module
// Parm: HINSTANCE hInstance      - the app instance
// Parm: HINSTANCE hPrevInstance  - the prev instance
// Parm: LPTSTR lpCmdLine         - the command line
// Parm: int iCmdShow             - the show mode
// Retn: int                      - the app return value
// ----------------------------------------------------------------------------
int ApplicationModule_Xbox::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
  // Initialise the engine
  if (!Create())
    return -1;

  // Run the engine
  return Run();
} // Main


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Xbox::Create
// Desc: Set the module's display
// Retn: bool                   - true if the application was initialised
// ----------------------------------------------------------------------------
bool ApplicationModule_Xbox::Create()
{
  // Create the application
  if (Application.Init(NULL, this))
    return true;

  return false;
} // Create


// ----------------------------------------------------------------------------
// Name: ApplicationModule_Xbox::Run
// Desc: Run the module
// Retn: int - the application return code
// ----------------------------------------------------------------------------
int ApplicationModule_Xbox::Run()
{
  bool run = true;
  while (run)
  {
    run = Application.RunFrame();
  } // while

  return Application.GetExitCode();
} // Run


// --------------------------------------------------------------------------
// Reset the device
// --------------------------------------------------------------------------
bool ApplicationModule_Xbox::ResetDisplay(bool toggleFullScreen, bool isFullScreen)
{
  Resize();
  return true;
} // ResetDisplay


// -- EOF



