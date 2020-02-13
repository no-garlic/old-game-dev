
#include "GameInput.h"


GameInput::GameInput()
{
  REF_COUNT_CTOR(GameInput);
}


GameInput::~GameInput()
{
  REF_COUNT_DTOR(GameInput);
}


bool GameInput::Init()
{
  return true;
}


void GameInput::Shutdown()
{
}


void GameInput::Update()
{
}


// -- EOF

