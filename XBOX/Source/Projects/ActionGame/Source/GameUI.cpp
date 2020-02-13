
#include "GameUI.h"


GameUI::GameUI()
{
}


GameUI::~GameUI()
{
}


bool GameUI::Init()
{
  return true;
}


void GameUI::Shutdown()
{
}


void GameUI::Update()
{
}


void GameUI::Draw()
{
}


void GameUI::SetRenderingEnabled(bool enabled)
{
}


void GameUI::ShowLoadingSequence()
{
}


void GameUI::HideLoadingSequence()
{
}


uint GameUI::GetLoadingSequenceProgress()
{
  // 1 to 100

  return (uint) Application.GetRunningTime() * 10.0f;
}



// -- EOF

