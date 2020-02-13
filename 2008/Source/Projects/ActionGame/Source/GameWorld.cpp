
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
  REF_COUNT_CTOR(GameWorldManager);

  m_pCamera = new GameCamera();
  m_pScene  = new GameScene();
  m_pUI     = new GameUI();
  m_pInput  = new GameInput();
}


GameWorldManager::~GameWorldManager()
{
  REF_COUNT_DTOR(GameWorldManager);
}


bool GameWorldManager::Init()
{
  if (!m_pInput->Init())
    return false;

  if (!m_pCamera->Init())
    return false;

  if (!m_pUI->Init())
    return false;

  if (!m_pScene->Init())
    return false;

  return true;
}


void GameWorldManager::Shutdown()
{
  if (m_pPendingAction)
  {
    delete m_pPendingAction;
  }

  if (m_pCurrentAction)
  {
    // TODO: Handle this better - maybe the action is loading, doing something in the 
    // background as End() is only a signal to end, it does not actually guarnetee 
    // the action has ended.
    m_pCurrentAction->End();
    delete m_pCurrentAction;
  }

  m_pScene->Shutdown();
  m_pUI->Shutdown();
  m_pCamera->Shutdown();
  m_pInput->Shutdown();

  delete m_pCamera;
  delete m_pScene;
  delete m_pUI;
  delete m_pInput;

  m_pCamera = NULL;
  m_pScene  = NULL;
  m_pUI     = NULL;
  m_pInput  = NULL;
}


void GameWorldManager::SetRenderState()
{
  NULL_ASSERT(m_pScene);
  NULL_ASSERT(m_pCamera);

  m_pScene->SetRenderState();
  m_pCamera->SetRenderState();
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
      if (m_pCurrentAction->GetState() == AS_ERROR)
      {
        DEBUG_BREAK;
        Application.RequestExit(-1);
      }
    }
    else if (actionState == AS_RUNNING)
    {
      if (m_pPendingAction)
      {
        m_pCurrentAction->End();

        if (m_pCurrentAction->GetState() == AS_ENDED)
        {
          delete m_pCurrentAction;
          m_pCurrentAction = m_pPendingAction;
          m_pPendingAction = NULL;

          if (m_pCurrentAction)
          {
            m_pCurrentAction->Start();
            if (m_pCurrentAction->GetState() == AS_ERROR)
            {
              DEBUG_BREAK;
              Application.RequestExit(-1);
            }
          }
        }
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

  NULL_ASSERT(m_pInput);
  NULL_ASSERT(m_pScene);
  NULL_ASSERT(m_pCamera);
  NULL_ASSERT(m_pUI);

  m_pInput->Update();
  m_pScene->App();
  m_pCamera->Update();
  m_pUI->Update();
}


void GameWorldManager::Cull()
{
  NULL_ASSERT(m_pScene);

  m_pScene->Cull();
}


void GameWorldManager::Draw()
{
  NULL_ASSERT(m_pScene);
  NULL_ASSERT(m_pUI);

  // Begin rendering and clear the buffer
  Device->BeginScene();
  Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Color::Gray, 1.0f, 0);

  // Render all game objects
  m_pScene->Draw();

  // Render the user interface
  m_pUI->Render();

  // Done rendering
  Device->EndScene();
  Device->Present(0, 0, 0, 0);
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

