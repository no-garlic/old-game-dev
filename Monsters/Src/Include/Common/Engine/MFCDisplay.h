// ----------------------------------------------------------------------------
// File: MFCDisplay.h
// Desc: Wrapper for a single view MFC application
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MFC_DISPLAY_H_
#define __MFC_DISPLAY_H_


// ----------------------------------------------------------------------------
// Inlcudes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Engine/ApplicationCentral.h"
#include "Engine/ApplicationModule_MFC.h"


// ----------------------------------------------------------------------------
// Only include this file if MFC is enabled
// ----------------------------------------------------------------------------
#ifdef __MFC_ENABLED


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class MFC_Application;
class MFC_MainFrame;


// ----------------------------------------------------------------------------
// Name: MFCDisplay (class)
// Desc: Wrapper for a single view MFC application
// ----------------------------------------------------------------------------
class MFCDisplay
{
public:
  // --------------------------------------------------------------------------
  // Get the MFC handles
  // --------------------------------------------------------------------------
  static CWinApp                *GetApp()     { return s_pApplication; }
  static CWnd                   *GetWnd()     { return s_pWnd;         }
  static ApplicationModule_MFC  *GetModule()  { return s_pModule;      }

  // --------------------------------------------------------------------------
  // Get and set the module
  // --------------------------------------------------------------------------
  static void SetModule(ApplicationModule_MFC *pModule) { s_pModule = pModule; }
  static void SetWnd(CWnd *pWnd)                        { s_pWnd = pWnd;       }
  static void SetApp(CWinApp *pApp);

  // --------------------------------------------------------------------------
  // Get the settings
  // --------------------------------------------------------------------------
  static DisplaySettings &GetDisplaySettings() { return s_DisplaySettings; }

  // --------------------------------------------------------------------------
  // Destroy the application
  // --------------------------------------------------------------------------
  static void DestroyApp();
  
private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  static CWinApp                *s_pApplication;
  static CWnd                   *s_pWnd;
  static ApplicationModule_MFC  *s_pModule;
  static DisplaySettings         s_DisplaySettings;

}; // class MFCDisplay


// ----------------------------------------------------------------------------
// Name: MFC_Application  (class)
// Desc: The MFC application
// ----------------------------------------------------------------------------
class MFC_Application : public CWinApp
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MFC_Application();
  virtual ~MFC_Application();

  // --------------------------------------------------------------------------
  // Function overrides
  // --------------------------------------------------------------------------
  virtual BOOL InitInstance();
  virtual BOOL OnIdle(LONG lCount);

  // --------------------------------------------------------------------------
  // Message map
  // --------------------------------------------------------------------------
  DECLARE_MESSAGE_MAP()

}; // class MFC_Application


// ----------------------------------------------------------------------------
// Name: MFC_MainFrame  (class)
// Desc: The MFC Main Frame
// ----------------------------------------------------------------------------
class MFC_MainFrame : public CFrameWnd
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MFC_MainFrame();
  virtual ~MFC_MainFrame();

  // --------------------------------------------------------------------------
  // Allow this class to be created through reflection
  // --------------------------------------------------------------------------
  DECLARE_DYNCREATE(MFC_MainFrame);

  // --------------------------------------------------------------------------
  // Function overrides
  // --------------------------------------------------------------------------
  virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
  virtual void OnSize(UINT nType, int cx, int cy);

  // --------------------------------------------------------------------------
  // Message map
  // --------------------------------------------------------------------------
  DECLARE_MESSAGE_MAP()

}; // class MFC_MainFrame


#endif // __MFC_ENABLED
#endif // __MFC_DISPLAY_H_

// -- EOF


