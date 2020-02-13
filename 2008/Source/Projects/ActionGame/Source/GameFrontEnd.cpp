
#include "GameFrontEnd.h"
#include "GameState.h"


GameFrontEnd::GameFrontEnd()
{
}


GameFrontEnd::~GameFrontEnd()
{
}


void GameFrontEnd::Update()
{
  if (!LoadLevel("Demo.lev"))
  {
    LOG_ERROR << "Failed to load the level: Test.lev" << ENDLOG;
  }
}


void GameFrontEnd::Render()
{
}


bool GameFrontEnd::LoadLevel(const String &levelName)
{
  LOG_INFO << "Loading the level: " << levelName << ENDLOG;
  return GameState.LoadLevel(levelName);
}


// -- EOF

