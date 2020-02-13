// ----------------------------------------------------------------------------
// File: AnimationModule.h
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __GAME_MODULE_H_
#define __GAME_MODULE_H_


// ----------------------------------------------------------------------------
// Use the basic viewer code
// ----------------------------------------------------------------------------
#define USE_VIEWER 0


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libEngine.h"

#if !USE_VIEWER
#include "GameScene.h"
#endif


// ----------------------------------------------------------------------------
// We use a different base class for our module on XBOX and PC.
// ----------------------------------------------------------------------------
#if XBOX
#define BaseModuleType ApplicationModule_Xbox
#else
#define BaseModuleType ApplicationModule_Win32
#endif


// ----------------------------------------------------------------------------
// Name: AnimationModule  (class)
// Desc: Test Module
// ----------------------------------------------------------------------------
class AnimationModule : public BaseModuleType
{
public:
  // --------------------------------------------------------------------------
  // Constructor and Destructor
  // --------------------------------------------------------------------------
  AnimationModule(const String &name);
  virtual ~AnimationModule();

  // --------------------------------------------------------------------------
  // This function is called after Direct3D has been created, but before the
  // Device and window are created and is an opportunity for the module to 
  // do caps testing and set the display settings used for device and window
  // creation.
  // --------------------------------------------------------------------------
  virtual bool SetDisplaySettings(DisplaySettings &settings);

  // --------------------------------------------------------------------------
  // This function is called after the main application objects are created,
  // and is where the module should create any resources it needs prior to
  // the main loop.
  // --------------------------------------------------------------------------
  virtual bool Init();

  // --------------------------------------------------------------------------
  // This function is called prior to the application exiting and prior to the
  // main application objects being destroyed. The module should clean up all
  // resources here.
  // --------------------------------------------------------------------------
  virtual void Shutdown();

  // --------------------------------------------------------------------------
  // The following functions are called sequentially each frame. The intention
  // is that the App function handle all application input and processing, the
  // Cull function handle the visibility culling, and the draw function handle
  // the rendering.
  // --------------------------------------------------------------------------
  virtual void App();
  virtual void Cull();
  virtual void Draw();

  // --------------------------------------------------------------------------
  // This function is called only on the PC build when the application window 
  // is toggled between fullscreen and windowed mode, or when the application
  // is in windowed mode and the window is resized.
  // --------------------------------------------------------------------------
  virtual void Resize();

  // --------------------------------------------------------------------------
  // Set the global render state for the module.
  // --------------------------------------------------------------------------
  virtual void SetRenderState();

  // --------------------------------------------------------------------------
  // Register the custom types
  // --------------------------------------------------------------------------
  virtual bool RegisterTypes();

private:
#if !USE_VIEWER
  GameScene *m_pScene;
#endif

}; // class AnimationModule


#endif // __GAME_MODULE_H_

// -- EOF



