
#include "GameLevel.h"
#include "GameLevelLoader.h"


GameLevel::GameLevel()
{
  REF_COUNT_CTOR(GameLevel);

  m_pLoadThread = NULL;
  m_LoadState   = LS_NONE;
  m_LoadCount   = 0;
  m_LoadCurrent = 0;
}


GameLevel::~GameLevel()
{
  REF_COUNT_DTOR(GameLevel);

  Unload();
}


void GameLevel::SetLoadState(GameLevel::LoadState state)
{
  OS::MutexLock l(m_StateMutex);
  m_LoadState = state;
}


GameLevel::LoadState GameLevel::GetLoadState() const
{
  OS::MutexLock l(m_StateMutex);
  return m_LoadState;
}


uint GameLevel::GetLoadProgress() const
{
  OS::MutexLock l(m_LoadCountMutex);

  if (m_LoadCount == 0)
    return 0;

  return (uint) ((100 * m_LoadCurrent) / m_LoadCount);
}


bool GameLevel::BeginLoad(FileHandle handle)
{
  OS::MutexLock l(m_StateMutex);

  if (m_LoadState != GameLevel::LS_NONE)
  {
    LOG_ERROR << "Cannot load a level when the load state is not LS_NONE" << ENDLOG;
    m_LoadState = LS_FAILED;
    return false;
  }
  
  m_Handle = handle;
  if (!m_Config.Load(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to load the level config file: " << handle << ENDLOG;
    m_LoadState = LS_FAILED;
    return false;
  }

  // Generate the queue of items to load
  GenerateLoadQueue();

  // Create the load thread
  m_pLoadThread = new OS::Thread(&GameLevel::BackgroundLoadThread, this);
  m_LoadState = LS_LOADING;

  return true;
}


void GameLevel::CancelLoad(bool wait)
{
  if (GetLoadState() != GameLevel::LS_LOADING)
    return;

  SetLoadState(GameLevel::LS_CANCEL);

  if (m_pLoadThread && wait)
  {
    bool done = false;
    while (!done)
    {
      if (m_CancelEvent.Wait(1000))
      {
        done = true;
      }
      else
      {
        if (GetLoadState() == GameLevel::LS_CANCELLED)
        {
          done = true;
        }
      }
    }
  }
}


OS::ThreadReturnType GameLevel::BackgroundLoadThread(void *pArg)
{
  GameLevel *pGameLevel = (GameLevel *) pArg;
  pGameLevel->BackgroundLoad();
  return 0;
}


#define CHECK_LOAD_CANCEL { if (GetLoadState() == GameLevel::LS_CANCEL) {\
                            SetLoadState(GameLevel::LS_CANCELLED);\
                            ClearQueue(m_LoadQueue); m_CancelEvent.Set();\
                            return; } }


void GameLevel::BackgroundLoad()
{
  CHECK_LOAD_CANCEL;

  m_LoadCountMutex.Acquire();
  m_LoadCurrent = 0;
  m_LoadCountMutex.Release();

  while (!m_LoadQueue.empty())
  {
    CHECK_LOAD_CANCEL;

    GameLevel::LoadItem *pLoadItem = m_LoadQueue.front();
    m_LoadQueue.pop();

    bool result = pLoadItem->Load();
    delete pLoadItem;

    if (!result)
    {
      SetLoadState(GameLevel::LS_FAILED);
      return;
    }

    m_LoadCountMutex.Acquire();
    m_LoadCurrent++;
    m_LoadCountMutex.Release();
  }

  SetLoadState(GameLevel::LS_LOADED);
}


bool GameLevel::GenerateLoadQueue()
{
  OS::MutexLock l(m_LoadCountMutex);

  m_LoadCount = 0;

  const ConfigSectionMap &sections = m_Config.GetSections();

  ConfigSectionMap::const_iterator iter(sections.begin()), end(sections.end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &section = iter->second;

    if (!GenerateLoadQueueFromConfig(section))
      return false;
  }

  return true;
}


bool GameLevel::GenerateLoadQueueFromConfig(const ConfigSection &cfg)
{
  if (!StrICmp(cfg.Type, "Scene") && !StrICmp(cfg.Type, "Group"))
  {
    return false;
  }

  ConfigSectionMap::const_iterator iter(cfg.ChildSections.begin()), end(cfg.ChildSections.end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &section = iter->second;

    if (StrICmp(section.Type, "Group"))
    {
      if (!GenerateLoadQueueFromConfig(section))
        return false;
    }
    else
    {
      LOG_INFO << "Found level object: " << section.Name << " (" << section.Type << ")" << ENDLOG;

      GameLevel::LoadItem *pItem = new GameLevel::LoadItem(this);

      if (!pItem->Init(section))
      {
        delete pItem;
        LOG_ERROR << "Failed to initialise the load item: " << section.Name << " from the config file: " << m_Handle << ENDLOG;
        return false;
      }

      m_LoadQueue.push(pItem);
      m_LoadCount++;
    }
  }
  return true;
}


bool GameLevel::Unload()
{
  if (m_pLoadThread)
  {
    CancelLoad(true);
  }

  delete m_pLoadThread;
  m_pLoadThread = NULL;

  m_LoadState   = LS_NONE;
  m_LoadCount   = 0;
  m_LoadCurrent = 0;

  return true;
}


GameLevel::LoadItem::LoadItem(GameLevel *pLevel)
{
  pLoader = new GameLevelLoader(pLevel, this);
}


GameLevel::LoadItem::~LoadItem()
{
  delete pLoader;
}


bool GameLevel::LoadItem::Init(const ConfigSection &data)
{
  return pLoader->Init(data);
}


bool GameLevel::LoadItem::Load()
{
  return pLoader->Load();
}



// -- EOF


