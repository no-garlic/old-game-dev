// ----------------------------------------------------------------------------
// File: ApplicationModule.h
// Desc: A module interface that derived classes use to install themselves into 
//       the Application
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __APPLICATION_MODLE_H_
#define __APPLICATION_MODLE_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "DisplaySettings.h"


// ----------------------------------------------------------------------------
// Name: ApplicationModule (class)
// Desc: The application module class
// ----------------------------------------------------------------------------
class ApplicationModule
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ApplicationModule(const String &name);
  virtual ~ApplicationModule();

  // --------------------------------------------------------------------------
  // The module's startup function
  // --------------------------------------------------------------------------
  virtual int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow) = 0;

  // --------------------------------------------------------------------------
  // Get the module name
  // --------------------------------------------------------------------------
  const String &GetName() { return m_Name; }

  // --------------------------------------------------------------------------
  // Initialsiation
  // --------------------------------------------------------------------------
  virtual bool Create()         = 0;
  virtual bool Init()           = 0;
  virtual void Shutdown()       = 0;

  // --------------------------------------------------------------------------
  // Process the given processId
  // --------------------------------------------------------------------------
  virtual void App()            = 0;
  virtual void Cull()           = 0;
  virtual void Draw()           = 0;

  // --------------------------------------------------------------------------
  // Request the module to exit
  // --------------------------------------------------------------------------
  virtual void RequestExit(int exitCode);
  virtual bool RegisterTypes();
  virtual bool SetDisplaySettings(DisplaySettings &settings) = 0;

  // --------------------------------------------------------------------------
  // Other callback functions
  // --------------------------------------------------------------------------
  virtual void SetWindowTitle(const String &str) = 0;
  virtual bool ResetDisplay(bool toggleFullScreen, bool isFullScreen) = 0;
  virtual void Resize() = 0;
  virtual void SetRenderState() = 0;

protected:
  // --------------------------------------------------------------------------
  // Allow the ApplicationCentral to access this class
  // --------------------------------------------------------------------------
  friend class ApplicationCentral;

  // --------------------------------------------------------------------------
  // Is this a null render module type?
  // --------------------------------------------------------------------------
  virtual bool IsNullRender() { return false; }

  // --------------------------------------------------------------------------
  // The display and window settings
  // --------------------------------------------------------------------------
  DEVICE            m_pDevice;
  String            m_Name;

}; // class ApplicationModule


// ----------------------------------------------------------------------------
// Macro for registering modules
// ----------------------------------------------------------------------------
#define REGISTER_MODULE(x) namespace A##x { ApplicationModuleManager::CreationFunctor<x> g_ModuleReg(#x); };


// ----------------------------------------------------------------------------
// Name: ApplicationModuleManager (class)
// Desc: Holds a cache of application modules
// ----------------------------------------------------------------------------
class ApplicationModuleManager
{
public:
  // --------------------------------------------------------------------------
  // Abstract struct to create a module instance
  // --------------------------------------------------------------------------
  struct BaseCreationFunctor
  {
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    BaseCreationFunctor(const char *name) : Name(name) {}

    // ------------------------------------------------------------------------
    // Create the module instance
    // ------------------------------------------------------------------------
    virtual ApplicationModule *Create(const String &name) = 0;

    // ------------------------------------------------------------------------
    // The name
    // ------------------------------------------------------------------------
    std::string Name;
  }; // struct BaseCreationFunctor

  // --------------------------------------------------------------------------
  // Templated struct to create a module instance
  // --------------------------------------------------------------------------
  template <class T>
  struct CreationFunctor : public BaseCreationFunctor
  {
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    CreationFunctor(const char *name) : BaseCreationFunctor(name)
    {
      ApplicationModuleManager::GetInstance().Register(this);
    } // CreationFunctors

    // ------------------------------------------------------------------------
    // Create the module instance
    // ------------------------------------------------------------------------
    virtual ApplicationModule *Create(const String &name)
    {
      return new T(name);
    }; // Create
  }; // struct CreationFunctor

  // --------------------------------------------------------------------------
  // Get the singleton instance
  // --------------------------------------------------------------------------
  static ApplicationModuleManager &GetInstance();

  // --------------------------------------------------------------------------
  // Destroy the singleton instance
  // --------------------------------------------------------------------------
  static void DestroyInstance();

  // --------------------------------------------------------------------------
  // Register a module
  // --------------------------------------------------------------------------
  void Register(BaseCreationFunctor *pCreationFunctor);
  
  // --------------------------------------------------------------------------
  // Get a module
  // --------------------------------------------------------------------------
  ApplicationModule *Create(const char *name);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  static ApplicationModuleManager              *s_pInstance;
  std::map<std::string, BaseCreationFunctor *>  m_Modules;

}; // class ApplicationModuleManager


#endif // __APPLICATION_MODLE_H_


// -- EOF

