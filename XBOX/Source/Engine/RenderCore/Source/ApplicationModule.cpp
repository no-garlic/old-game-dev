
#include "ApplicationModule.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Static initialisers
// ----------------------------------------------------------------------------
ApplicationModuleManager* ApplicationModuleManager::s_pInstance = NULL;


// ----------------------------------------------------------------------------
// Name: ApplicationModule::ApplicationModule
// Desc: Constructor
// Parm: unsigned int processMode   - the process mode
// Parm: unsigned int bytesPerHeap  - the size of the mem heaps
// ----------------------------------------------------------------------------
ApplicationModule::ApplicationModule(const String &name)
: m_pDevice               (NULL),
  m_Name                  (name)
{
  REF_COUNT_CTOR(ApplicationModule);

  // Ensure the ApplicationCentral instance has been created
  ApplicationCentral::GetInstance();
} // ApplicationModule


// ----------------------------------------------------------------------------
// Name: ApplicationModule::~ApplicationModule
// Desc: destructor
// ----------------------------------------------------------------------------
ApplicationModule::~ApplicationModule()
{
  REF_COUNT_DTOR(ApplicationModule);
} // ~ApplicationModule


// --------------------------------------------------------------------------
// Name: ApplicationModule::RequestExit
// Desc: Request the module to exit
// --------------------------------------------------------------------------
void ApplicationModule::RequestExit(int exitCode)
{
  Application.RequestExit(exitCode);
} // RequestExit


// ----------------------------------------------------------------------------
// Name: ApplicationModuleManager::GetInstance
// Desc: Get the singleton instance
// Retn: ApplicationModuleManager * - the instance
// ----------------------------------------------------------------------------
ApplicationModuleManager &ApplicationModuleManager::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new ApplicationModuleManager();
    atexit(ApplicationModuleManager::DestroyInstance);
  } // if

  return *s_pInstance;
} // GetInstance


// ----------------------------------------------------------------------------
// Name: ApplicationModuleManager::DestroyInstance
// Desc: Destroy the singleton instance
// ----------------------------------------------------------------------------
void ApplicationModuleManager::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
} // DestroyInstance


// ----------------------------------------------------------------------------
// Name: ApplicationModuleManager::Register
// Desc: register a module
// Parm: ApplicationModule *pModule - the module
// Parm: const char *name           - the module name
// ----------------------------------------------------------------------------
void ApplicationModuleManager::Register(BaseCreationFunctor *pCreationFunctor)
{
  // Get the uppercase name
  String uppercaseName = pCreationFunctor->Name;
  ToUpper(uppercaseName);

  // Insert the module
  m_Modules.insert(std::make_pair(uppercaseName, pCreationFunctor));
} // Register


// ----------------------------------------------------------------------------
// Name: ApplicationModuleManager::Create
// Desc: Create a module by name
// Parm: const char *name    - the module name
// Retn: ApplicationModule * - the module, or NULL if not found
// ----------------------------------------------------------------------------
ApplicationModule *ApplicationModuleManager::Create(const char *name)
{
  // Get the uppercase name
  String uppercaseName = ToUpper(name) + ToUpper("Module");

  // Find the module
  std::map<std::string, ApplicationModuleManager::BaseCreationFunctor *>::iterator findIter = m_Modules.find(uppercaseName);
  if (findIter == m_Modules.end())
    return NULL;

  // Return the module
  return findIter->second->Create(name);
} // Create


// ----------------------------------------------------------------------------
// Register any types that the applciation needs to create once the device
// has been created.  Override this function and add any custom types.
// ----------------------------------------------------------------------------
bool ApplicationModule::RegisterTypes()
{
  extern bool RegisterEngineContent();
  return (RegisterEngineContent());
}


// -- EOF




