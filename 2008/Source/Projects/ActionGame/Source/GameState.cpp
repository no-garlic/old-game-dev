
#include "GameState.h"
#include "GameWorld.h"
#include "ActionStartup.h"
#include "ActionFrontEnd.h"
#include "ActionLoadLevel.h"
#include "ActionPlayLevel.h"


GameStateManager *GameStateManager::s_pInstance = NULL;


GameStateManager &GameStateManager::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new GameStateManager();
    atexit(GameStateManager::DestroyInstance);
  }
  return *s_pInstance;
}


void GameStateManager::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
}


GameStateManager::GameStateManager()
{
  REF_COUNT_CTOR(GameStateManager);
}


GameStateManager::~GameStateManager()
{
  REF_COUNT_DTOR(GameStateManager);
}


bool GameStateManager::Init()
{
  ActionStartup *pAction = new ActionStartup();
  if (!GameWorld.PushAction(pAction))
  {
    delete pAction;
    return false;
  }

  return true;
}


bool GameStateManager::StartupComplete()
{
  ActionFrontEnd *pAction = new ActionFrontEnd();

  if (!GameWorld.PushAction(pAction))
  {
    delete pAction;
    return false;
  }

  return true;
}


bool GameStateManager::LoadLevel(const String &levelName)
{
  ActionLoadLevel *pAction = new ActionLoadLevel();
  pAction->SetLevelToLoad(levelName);

  if (!GameWorld.PushAction(pAction))
  {
    delete pAction;
    return false;
  }

  return true;
}


bool GameStateManager::LoadLevelComplete()
{
  ActionPlayLevel *pAction = new ActionPlayLevel();

  if (!GameWorld.PushAction(pAction))
  {
    delete pAction;
    return false;
  }

  return true;
}



// -- EOF


