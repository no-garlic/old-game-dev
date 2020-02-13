
#include "ActionFinishLevel.h"
#include "GameWorld.h"
#include "GameState.h"


ActionFinishLevel::ActionFinishLevel()
: GameAction()
{
  REF_COUNT_CTOR(ActionFinishLevel);
}


ActionFinishLevel::~ActionFinishLevel()
{
  REF_COUNT_DTOR(ActionFinishLevel);
}


void ActionFinishLevel::Start()
{
  // Dont render the scene
  GameWorld.GetScene().SetRenderingEnabled(true);

  // Render the user interface
  GameWorld.GetUI().SetRenderingEnabled(true);

  // Set the state
  m_State = AS_RUNNING;
}


void ActionFinishLevel::Update()
{
}


void ActionFinishLevel::End()
{
  // Set the state
  m_State = AS_ENDED;
}


// -- EOF

