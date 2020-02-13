// ----------------------------------------------------------------------------
// File: Main.cpp
// Desc: Main class that creates the application modules
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"


// ----------------------------------------------------------------------------
// Name: WinMain
// Desc: Main function
// Parm: HINSTANCE hInstance      - the app instance
// Parm: HINSTANCE hPrevInstance  - the prev instance
// Parm: LPTSTR lpCmdLine         - the command line
// Parm: int iCmdShow             - the show mode
// Retn: int WINAPI               - the app return value
// ----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
  try
  {
    // The default module to load if there is not a module specified
    String moduleName = "Game";

    // Get the command line
    String commandLine = String(lpCmdLine);
    if (commandLine.length() > 0)
    {
      // Find the first white space in the command line
      int pos = static_cast<int>(commandLine.find_first_of(' '));
      if (pos >= 0)
      {
        // Remove the module name from the command line
        moduleName  = commandLine.substr(0, pos);
        commandLine = commandLine.substr(pos + 1);

        // Uppercase the module name
        ToUpper(moduleName);
      } // if
      else
      {
        // Remove the module name from the command line
        moduleName  = commandLine;
        commandLine = "";

        // Uppercase the module name
        ToUpper(moduleName);
      } // else
    } // if

    // Add the application args
    AppArgs.Append(commandLine);

    // Append Module to the name
    moduleName.append("Module");
    LOG_INFO << "Loading: " << moduleName << ENDLOG;

    // Get the process mode
    uint processMode = PMODE_ONE;
    if (AppArgs.HasOption("-multi"))
    {
      const StringArray processModeArgs = AppArgs.GetOptionArgs("-multi");
      if (processModeArgs.empty())
      {
        processMode = PMODE_TWO;
      } // if
      else
      {
        const String &processModeStr = processModeArgs[0];
        if (processModeStr == "1")
          processMode = PMODE_ONE;
        if (processModeStr == "2")
          processMode = PMODE_TWO;
        else if (processModeStr == "3")
          processMode = PMODE_THREE;
      } // else
    } // if

    // Initialise the memory manager to allocate memory in 1024 byte chunks 
    // and use seperate threads in the renderer.
    MemoryManager.Init(processMode, 1024);

    // Create the module that we want to run
    ApplicationModule *pModule = ApplicationModuleManager::GetInstance().Create(moduleName.c_str());
    if (!pModule)
      return -1;

    // Run the application module
    pModule->Main(hInstance, hPrevInstance, lpCmdLine, iCmdShow);

    // Return the application return code
    return ApplicationCentral.GetExitCode();
  } // try
  catch (GeneralException &e)
  {
    String str = e.GetDescription();
    str += "\n";
    str += e.GetTrace();

    LOG_EXCEPTION(e);
    ::MessageBox(NULL, str.c_str(), "Exception", MB_OK | MB_ICONERROR);
    return -1;
  } // catch

#ifdef _HANDLE_EXCEPTIONS
  catch (std::exception &e)
  {
    LOG_INFO << "Exception: " << e.what() << ENDLOG;
    ::MessageBox(NULL, e.what(), "Exception", MB_OK | MB_ICONERROR);
    return -1;
  } // catch
  catch (...)
  {
    LOG_INFO << "Unknown Exception" << ENDLOG;
    ::MessageBox(NULL, "Unknown Exception", "Exception", MB_OK | MB_ICONERROR);
    return -1;
  } // catch
#endif 

}; // WinMain


// -- EOF
