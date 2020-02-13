
#include "Engine/ApplicationModule.h"
#include "Engine/MemoryManager.h"


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
ApplicationModule::ApplicationModule()
: m_pDevice               (NULL),
  m_DeviceObjectsCreated  (false)
{
  REF_COUNT_CTOR(ApplicationModule);
} // ApplicationModule


// ----------------------------------------------------------------------------
// Name: ApplicationModule::~ApplicationModule
// Desc: destructor
// ----------------------------------------------------------------------------
ApplicationModule::~ApplicationModule()
{
  REF_COUNT_DTOR(ApplicationModule);
} // ~ApplicationModule


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
  String uppercaseName = ToUpper(name);

  // Find the module
  std::map<std::string, ApplicationModuleManager::BaseCreationFunctor *>::iterator findIter = m_Modules.find(uppercaseName);
  if (findIter == m_Modules.end())
    return NULL;

  // Return the module
  return findIter->second->Create();
} // Create


// -- EOF




