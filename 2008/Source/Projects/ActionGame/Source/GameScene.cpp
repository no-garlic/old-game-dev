
#include "GameScene.h"
#include "GameLevel.h"


GameScene::GameScene()
{
  REF_COUNT_CTOR(GameScene);

  m_pLevel = NULL;
  m_RenderingEnabled = true;
}


GameScene::~GameScene()
{
  REF_COUNT_DTOR(GameScene);

  ChangeLevel(NULL);
}


bool GameScene::Init()
{
  return true;
}


void GameScene::Shutdown()
{
}


void GameScene::App()
{
  if (m_pLevel)
  {
    m_pLevel->GetRenderLevel().App();
  }
}


void GameScene::Cull()
{
  if (m_pLevel)
  {
    m_pLevel->GetRenderLevel().Cull();
  }
}


void GameScene::Draw()
{
  if (m_RenderingEnabled && m_pLevel)
  {
    m_pLevel->GetRenderLevel().Draw();
  }
}


void GameScene::SetRenderingEnabled(bool enabled)
{
  m_RenderingEnabled = enabled;
}


void GameScene::SetRenderState()
{
  if (m_pLevel)
  {
    m_pLevel->GetRenderLevel().SetRenderState();
  }
}


void GameScene::ChangeLevel(GameLevel *pLevel)
{
  if (m_pLevel)
  {
    if (!m_pLevel->Unload())
    {
      LOG_ERROR << "Failed to unload the level" << ENDLOG;
      DEBUG_BREAK;
    }

    delete m_pLevel;
    m_pLevel = NULL;
  }

  m_pLevel = pLevel;
}


// -- EOF

