
#include "GameState.h"
#include "GameWorld.h"
#include "ActionStartup.h"
#include "ActionFrontEnd.h"


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
}


GameStateManager::~GameStateManager()
{
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


bool GameStateManager::OnStartupComplete()
{
  ActionFrontEnd *pAction = new ActionFrontEnd();
  if (!GameWorld.PushAction(pAction))
  {
    delete pAction;
    return false;
  }

  return true;
}


// -- EOF


