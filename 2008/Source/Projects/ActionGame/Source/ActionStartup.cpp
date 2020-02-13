
#include "ActionStartup.h"
#include "GameWorld.h"
#include "GameState.h"


ActionStartup::ActionStartup()
: GameAction()
{
  REF_COUNT_CTOR(ActionStartup);
}


ActionStartup::~ActionStartup()
{
  REF_COUNT_DTOR(ActionStartup);
}


void ActionStartup::Start()
{
  // Show the loading sequence
  GameWorld.GetUI().ShowLoadingSequence();

  // Dont render the scene
  GameWorld.GetScene().SetRenderingEnabled(false);

  // Render the user interface
  GameWorld.GetUI().SetRenderingEnabled(true);

  // Set the state
  m_State = AS_RUNNING;
}


void ActionStartup::Update()
{
  uint progress = GameWorld.GetUI().GetLoadingSequenceProgress();

  if (progress == 100)
  {
    if (!GameState.StartupComplete())
    {
      m_State = AS_ERROR;
    }
  }
}


void ActionStartup::End()
{
  // Hide the loading sequence
  GameWorld.GetUI().HideLoadingSequence();

  // Set the state
  m_State = AS_ENDED;
}


// -- EOF

