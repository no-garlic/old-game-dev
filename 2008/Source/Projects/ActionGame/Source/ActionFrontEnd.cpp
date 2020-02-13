
#include "ActionFrontEnd.h"
#include "GameWorld.h"
#include "GameState.h"


ActionFrontEnd::ActionFrontEnd()
: GameAction()
{
  REF_COUNT_CTOR(ActionFrontEnd);
}


ActionFrontEnd::~ActionFrontEnd()
{
  REF_COUNT_DTOR(ActionFrontEnd);
}


void ActionFrontEnd::Start()
{
  // Show the front end
  GameWorld.GetUI().ShowFrontEnd();

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
  // Hide the front end
  GameWorld.GetUI().HideFrontEnd();

  // Set the state
  m_State = AS_ENDED;
}


// -- EOF

