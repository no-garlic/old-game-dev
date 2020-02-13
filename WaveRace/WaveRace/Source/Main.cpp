// ----------------------------------------------------------------------------
// File: Main.cpp
// Desc: Main application entry point
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Main application includes
// ----------------------------------------------------------------------------
#include "Main.h"
#include "Application.h"
#include "Engine/ASE.h"


// ----------------------------------------------------------------------------
// Build our app or ASE2ASB
// ----------------------------------------------------------------------------
// #define ASE2ASB


// ----------------------------------------------------------------------------
// Global variable definitions
// Core game application processing engine
// ----------------------------------------------------------------------------
Application g_App; 


// ----------------------------------------------------------------------------
// If we have compiled with _CONSOLE, we use main() as the entry point, 
// otherwise we use WinMain() as the entry point.  This allows us to build our 
// appication with or without a console.
// ----------------------------------------------------------------------------
#ifdef _CONSOLE


// ----------------------------------------------------------------------------
// Name: main
// Desc: Main entry point for a console app
// Parm: int argc     - the number of args
// Parm: char **argv  - the args as a string array
// Retn: int          - the exit code
// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    // Collate the command line parameters into a LPSTR
    std::string ___cmd_line;
    for (int ___i = 0; ___i < argc - 1; ___i++)
    {
        ___cmd_line += argv[___i + 1];
        ___cmd_line += " ";
    } // for

    // Set the same args as we expect to get from WinMain()
    HINSTANCE   hInstance     = 0;
    HINSTANCE   hPrevInstance = 0;
    LPTSTR      lpCmdLine     = (LPTSTR) _T(___cmd_line.c_str());
    int         iCmdShow      = SW_SHOWNORMAL;
#else


// ----------------------------------------------------------------------------
// Name: WinMain
// Desc: Main application entry point
// Parm: HINSTANCE hInstance      - the application instance
// Parm: HINSTANCE hPrevInstance  - the prevoius instance
// Parm: LPTSTR lpCmdLine         - the command line params
// Parm: int iCmdShow             - the show status
// Retn: int WINAPI               - the application return code
// ----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
#endif


// ----------------------------------------------------------------------------
// This application can be built in a configuration to convert ASE files to ASB,
// or in a configuration to play the game depinding on the define ASE2ASB
// ----------------------------------------------------------------------------
#ifdef ASE2ASB
    // Strip the path from the ASE filename
    std::string ase_name    = lpCmdLine;
    int pos                 = ase_name.find_last_of("\\");
    int pos2                = ase_name.find_last_of("/");

    if (pos2 > pos) 
        pos = pos2;

    if (pos > 0)
    {
        std::string path_name = ase_name.substr(0, pos);
        ase_name = ase_name.substr(pos + 1);
    } // if

    // Copy the filename and replace ASE with ASB
    pos                     = ase_name.find_last_of(".");
    std::string asb_name    = ase_name;
    asb_name.at(pos + 1)    = 'a';
    asb_name.at(pos + 2)    = 's';
    asb_name.at(pos + 3)    = 'b';

    // Convert the file
    char msg[256];
    if (!ASELoader::ConvertFile(ase_name.c_str(), asb_name.c_str()))
    {
        sprintf(msg, "Failed to convert %s to %s", ase_name.c_str(), asb_name.c_str());
        MessageBox(0, msg, "ASE2ASB", MB_OK);
    } // if

    return 0;


// ----------------------------------------------------------------------------
// This is the game entry point
// ----------------------------------------------------------------------------
#else
	// Initialise the application engine.
	if (!g_App.InitInstance(hInstance, lpCmdLine, iCmdShow)) 
        return EXIT_FAILURE;
    
    // Begin the application process. Will return when app due to exit.
    int retCode = g_App.Begin();

    // Shut down the engine, just to be polite, before exiting.
    g_App.ShutDown();

    // Return the correct exit code.
    return retCode;
#endif

} // WinMain


// ----------------------------------------------------------------------------
// Name: Application
// Desc: Allows the rest of the application to retrieve the game app pointer
// Retn: Application* - the application pointer
// ----------------------------------------------------------------------------
Application *Application()
{
    return &g_App;
} // Application


// -- EOF

