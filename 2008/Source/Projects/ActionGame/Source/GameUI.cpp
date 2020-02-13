
#include "GameUI.h"


GameUI::GameUI()
{
  REF_COUNT_CTOR(GameUI);

  m_RenderingDisabled = false;
  m_ShowLoadingScreen = false;
  m_ShowFrontEnd      = false;
}


GameUI::~GameUI()
{
  REF_COUNT_DTOR(GameUI);
}


bool GameUI::Init()
{
  FileHandle loadingScreenHandle = Application.GetUIDatabase()->FindFileHandle("LoadingScreen.cfg");
  if (!m_LoadingScreenSequence.Init(loadingScreenHandle))
    return false;

  // Loading Screen

  // Font End

  return true;
}


void GameUI::Shutdown()
{
}


void GameUI::Update()
{
  if (m_ShowLoadingScreen)
  {
    m_LoadingScreenSequence.Update();
  }

  // Loading screen

  else if (m_ShowFrontEnd)
  {
    m_GameFrontEnd.Update();
  }
}


void GameUI::Render()
{
  if (m_RenderingDisabled)
  {
    return;
  }

  if (m_ShowLoadingScreen)
  {
    m_LoadingScreenSequence.Render();
  }

  // Loading Screen

  else if (m_ShowFrontEnd)
  {
    m_GameFrontEnd.Render();
  }
}


void GameUI::SetRenderingEnabled(bool enabled)
{
  m_RenderingDisabled = !enabled;
}


void GameUI::ShowLoadingSequence()
{
  m_ShowLoadingScreen = true;
  //m_LoadingScreenSequence.Start(3.0f, 0.4f);
  m_LoadingScreenSequence.Start(0.2f, 0.1f);
}


void GameUI::HideLoadingSequence()
{
  m_ShowLoadingScreen = false;
}


uint GameUI::GetLoadingSequenceProgress()
{
  return m_LoadingScreenSequence.GetProgress();
}


void GameUI::ShowLevelLoadingScreen()
{
  // TODO
}


void GameUI::HideLevelLoadingScreen()
{
  // TODO
}


void GameUI::SetLevelLoadingProgress(uint progress)
{
  // TODO
}


void GameUI::ShowFrontEnd()
{
  m_ShowFrontEnd = true;
}


void GameUI::HideFrontEnd()
{
  m_ShowFrontEnd = false;
}


// -- EOF

