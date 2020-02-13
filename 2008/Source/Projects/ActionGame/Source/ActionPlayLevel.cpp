
#include "ActionPlayLevel.h"
#include "GameWorld.h"
#include "GameState.h"


ActionPlayLevel::ActionPlayLevel()
: GameAction()
{
  REF_COUNT_CTOR(ActionPlayLevel);
}


ActionPlayLevel::~ActionPlayLevel()
{
  REF_COUNT_DTOR(ActionPlayLevel);
}


void ActionPlayLevel::Start()
{
  // Dont render the scene
  GameWorld.GetScene().SetRenderingEnabled(true);

  // Render the user interface
  GameWorld.GetUI().SetRenderingEnabled(true);

  // Set the state
  m_State = AS_RUNNING;
}


void ActionPlayLevel::Update()
{
}


void ActionPlayLevel::End()
{
  // Set the state
  m_State = AS_ENDED;
}


// -- EOF

