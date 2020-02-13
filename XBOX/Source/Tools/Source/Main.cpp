// ----------------------------------------------------------------------------
// File: Main.cpp
// Desc: Main class that creates the application modules
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libEngine.h"

#if PC
#include "MeshConvertModule.h"
#endif


// ----------------------------------------------------------------------------
// Register the modules
// ----------------------------------------------------------------------------
#if PC
REGISTER_MODULE(MeshConvertModule);
#endif



// ----------------------------------------------------------------------------
// Logging callback for console builds
// ----------------------------------------------------------------------------
#ifdef TOOLS
#include <iostream>
void LogToConsoleCallbackFunction(const char *pMsg)
{
  std::cout << pMsg << std::endl;
}
#endif


// ----------------------------------------------------------------------------
// Name: WinMain
// Desc: Main function
// Parm: HINSTANCE hInstance      - the app instance
// Parm: HINSTANCE hPrevInstance  - the prev instance
// Parm: LPTSTR lpCmdLine         - the command line
// Parm: int iCmdShow             - the show mode
// Retn: int WINAPI               - the app return value
// ----------------------------------------------------------------------------
int WINAPI WinStart(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
  REF_COUNT_TURN_OFF;

#ifdef _HANDLE_EXCEPTIONS
  try {
#endif // _HANDLE_EXCEPTIONS

#ifdef TOOLS
    // For tools builds, we log to the console
    LOG_CALLBACK(LogToConsoleCallbackFunction);
#endif
    // The default module to load if there is not a module specified
    String moduleName = "";
    String normalCaseModuleName = moduleName;

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
        normalCaseModuleName = moduleName;

        // Uppercase the module name
        ToUpper(moduleName);
      } // if
      else
      {
        // Remove the module name from the command line
        moduleName  = commandLine;
        commandLine = "";
        normalCaseModuleName = moduleName;

        // Uppercase the module name
        ToUpper(moduleName);
      } // else
    } // if

    // Add the application args
    AppArgs.Append(commandLine);

    // Create the module that we want to run
    LOG_INFO << "Loading: " << normalCaseModuleName << ENDLOG;
    ApplicationModule *pModule = ApplicationModuleManager::GetInstance().Create(moduleName.c_str());
    if (!pModule)
    {
      LOG_ERROR << "Failed to find the module: " << normalCaseModuleName << ENDLOG;
      return -1;
    }

    // Run the application module
    int retCode = pModule->Main(hInstance, hPrevInstance, lpCmdLine, iCmdShow);

    // Return the application return code
    return Application.GetExitCode() ? Application.GetExitCode() : retCode;

#ifdef _HANDLE_EXCEPTIONS
  } // try
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


#if XBOX
void __cdecl main()
{
  WinStart(NULL, NULL, (LPTSTR) "", 0);
  ASSERT(NULL, "XBOX Application Terminated");
  OS::Sleep(INFINITE);
}

#else // !XBOX
#ifdef TOOLS

int main(int argc, char *argv[])
{
  String cmdLine;
  for (int i = 1; i < argc; i++)
  {
    cmdLine += argv[i];
    if (i != argc - 1)
      cmdLine += " ";
  }

  return WinStart(GetModuleHandle(0), NULL, (LPTSTR) cmdLine.c_str(), SW_SHOW);
}

#else // !TOOLS

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
  return WinStart(hInstance, hPrevInstance, lpCmdLine, iCmdShow);
}

#endif // !TOOLS
#endif // !XBOX


// -- EOF
