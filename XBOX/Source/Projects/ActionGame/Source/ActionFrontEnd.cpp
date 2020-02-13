
#include "ActionFrontEnd.h"
#include "GameWorld.h"
#include "GameState.h"


ActionFrontEnd::ActionFrontEnd()
: GameAction()
{
}


ActionFrontEnd::~ActionFrontEnd()
{
}


void ActionFrontEnd::Start()
{
  // Dont render the scene
  GameWorld.GetScene().SetRenderingEnabled(false);

  // Render the user interface
  GameWorld.GetUI().SetRenderingEnabled(true);

  // Set the state
  m_State = AS_RUNNING;
}


void ActionFrontEnd::Update()
{
}


void ActionFrontEnd::End()
{
  // Set the state
  m_State = AS_ENDED;
}


// -- EOF

