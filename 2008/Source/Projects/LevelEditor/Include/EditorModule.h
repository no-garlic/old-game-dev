// ----------------------------------------------------------------------------
// File: EditorModule.h
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __EDITOR_MODULE_H_
#define __EDITOR_MODULE_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libEngine.h"
#include "libEditor.h"


// ----------------------------------------------------------------------------
// Name: EditorModule  (class)
// Desc: Test Module
// ----------------------------------------------------------------------------
class EditorModule : public ApplicationModule_Wx
{
public:
  // --------------------------------------------------------------------------
  // Constructor and Destructor
  // --------------------------------------------------------------------------
  EditorModule(const String &name);
  virtual ~EditorModule();

  // --------------------------------------------------------------------------
  // Create the wx application
  // --------------------------------------------------------------------------
  virtual WxDisplayApp *CreateApp(DisplaySettings ds);

  // --------------------------------------------------------------------------
  // Set the display settings
  // --------------------------------------------------------------------------
  virtual bool SetDisplaySettings(DisplaySettings &settings);

  // --------------------------------------------------------------------------
  // Init and shutdown the module
  // --------------------------------------------------------------------------
  virtual bool Init();
  virtual void Shutdown();

  // --------------------------------------------------------------------------
  // Process functions
  // --------------------------------------------------------------------------
  virtual void App();
  virtual void Cull();
  virtual void Draw();

  // --------------------------------------------------------------------------
  // Called when the appliation has been resized or moved
  // --------------------------------------------------------------------------
  virtual void Resize();
  virtual void Move();

  // --------------------------------------------------------------------------
  // Set the render state
  // --------------------------------------------------------------------------
  virtual void SetRenderState();

}; // class EditorModule


#endif // __EDITOR_MODULE_H_

// -- EOF



