// ----------------------------------------------------------------------------
// File: wxDirectXContext.h
// Desc: The WX module base class for directX
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __WX_DIRECTX_MODULE_H_
#define __WX_DIRECTX_MODULE_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "wxWindows/wxDirectX.h"


// ----------------------------------------------------------------------------
// The base module class to implement directx into wx windows
// ----------------------------------------------------------------------------
class wxDirectXModule : public wxModule
{
public:
  // --------------------------------------------------------------------------
  // Init and Exit events for the module
  // --------------------------------------------------------------------------
  bool OnInit() { return true; }
  void OnExit() { UnregisterClasses(); }

  // --------------------------------------------------------------------------
  // Register and unregister the module classes
  // --------------------------------------------------------------------------
  static bool RegisterClasses();
  static void UnregisterClasses();

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  static bool ms_registeredDirectXClasses;

  // --------------------------------------------------------------------------
  // Declare then class for dynamic construction
  // --------------------------------------------------------------------------
  DECLARE_DYNAMIC_CLASS(wxDirectXModule)

};


#endif // __WX_DIRECTX_MODULE_H_

// -- EOF

