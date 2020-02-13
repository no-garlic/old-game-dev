
#include "GameWorld.h"


GameWorldManager *GameWorldManager::s_pInstance = NULL;


GameWorldManager &GameWorldManager::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new GameWorldManager();
    atexit(GameWorldManager::DestroyInstance);
  }
  return *s_pInstance;
}


void GameWorldManager::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
}


GameWorldManager::GameWorldManager()
: m_pCurrentAction (NULL),
  m_pPendingAction (NULL)
{
}


GameWorldManager::~GameWorldManager()
{
}


bool GameWorldManager::Init()
{
  if (!m_Input.Init())
    return false;

  if (!m_Camera.Init())
    return false;

  if (!m_UI.Init())
    return false;

  if (!m_Scene.Init())
    return false;

  return true;
}


void GameWorldManager::Shutdown()
{
  m_Scene.Shutdown();
  m_UI.Shutdown();
  m_Camera.Shutdown();
  m_Input.Shutdown();
}


void GameWorldManager::SetRenderState()
{
  m_Scene.SetRenderState();
  m_Camera.SetRenderState();
}


void GameWorldManager::App()
{
  if (!m_pCurrentAction)
  {
    m_pCurrentAction = m_pPendingAction;
    m_pPendingAction = NULL;
  }

  if (m_pCurrentAction)
  {
    ActionState actionState = m_pCurrentAction->GetState();

    if (actionState == AS_NEW)
    {
      m_pCurrentAction->Start();
    }
    else if (actionState == AS_RUNNING)
    {
      if (m_pPendingAction)
      {
        m_pCurrentAction->End();
      }
      else
      {
        m_pCurrentAction->Update();
      }
    }
    else if (actionState == AS_ENDED)
    {
      delete m_pCurrentAction;
      m_pCurrentAction = m_pPendingAction;
      m_pPendingAction = NULL;

      if (m_pCurrentAction)
      {
        m_pCurrentAction->Start();
      }
    }
    else if (actionState == AS_ERROR)
    {
      DEBUG_BREAK;
      Application.RequestExit(-1);
    }
    else
    {
      m_pCurrentAction->Update();
    }
  }

  m_Input.Update();
  m_Scene.Update();
  m_Camera.Update();
  m_UI.Update();
}


void GameWorldManager::Cull()
{
  m_Scene.Cull();
}


void GameWorldManager::Draw()
{
  m_Scene.Draw();
  m_UI.Draw();
}

  
bool GameWorldManager::PushAction(GameAction *pAction)
{
  if (m_pPendingAction)
  {
    DEBUG_BREAK;
    return false;
  }

  if (pAction->GetState() != AS_NEW)
  {
    DEBUG_BREAK;
    return false;
  }

  m_pPendingAction = pAction;
  return true;
}


// -- EOF

