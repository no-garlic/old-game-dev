
#include "ActionLoadLevel.h"
#include "GameWorld.h"
#include "GameState.h"
#include "GameLevel.h"


ActionLoadLevel::ActionLoadLevel()
: GameAction()
{
  REF_COUNT_CTOR(ActionLoadLevel);
  
  m_pLoadingLevel = NULL;
}


ActionLoadLevel::~ActionLoadLevel()
{
  REF_COUNT_DTOR(ActionLoadLevel);

  if (m_pLoadingLevel)
  {
    m_pLoadingLevel->CancelLoad(true);
    delete m_pLoadingLevel;
  }
}


void ActionLoadLevel::SetLevelToLoad(const String &levelName)
{
  m_LevelName = levelName;
}


void ActionLoadLevel::Start()
{
  // Show the level loading screen
  GameWorld.GetUI().ShowLevelLoadingScreen();

  // Dont render the scene
  GameWorld.GetScene().SetRenderingEnabled(false);

  // Render the user interface
  GameWorld.GetUI().SetRenderingEnabled(true);

  // Get the level file handle
  FileHandle handle = Application.GetLevelDatabase()->FindFileHandle(m_LevelName);
  if (!handle.IsValid())
  {
    m_State = AS_ERROR;
    return;
  }

  // Create the level and load it in the background
  m_pLoadingLevel = new GameLevel();
  if (!m_pLoadingLevel->BeginLoad(handle))
  {
    delete m_pLoadingLevel;
    m_pLoadingLevel = NULL;

    m_State = AS_ERROR;
    return;
  }

  // Set the state
  m_State = AS_RUNNING;
}


void ActionLoadLevel::Update()
{
  if (m_pLoadingLevel)
  {
    switch (m_pLoadingLevel->GetLoadState())
    {
      case GameLevel::LS_LOADING:
      case GameLevel::LS_CANCEL:
      {
        // Update the loading progress bar
        uint progress = m_pLoadingLevel->GetLoadProgress();
        GameWorld.GetUI().SetLevelLoadingProgress(progress);
        break;
      }

      case GameLevel::LS_LOADED:
      {

        // TODO - detect that the load time is no less than a few seconds
        //        if so, add a sleep and slow down the progress bar.


        // Change the level
        GameWorld.GetScene().ChangeLevel(m_pLoadingLevel);
        m_pLoadingLevel = NULL;

        // Hide the loading sequence
        GameWorld.GetUI().HideLoadingSequence();

        // Notify that the level has completed loading
        if (!GameState.LoadLevelComplete())
        {
          m_State = AS_ERROR;
          break;
        }

        // Exit the action
        m_State = AS_ENDED;
        break;
      }

      case GameLevel::LS_FAILED:
      {
        m_State = AS_ERROR;
        break;
      }
      
      case GameLevel::LS_CANCELLED:
      {
        // Hide the loading sequence
        GameWorld.GetUI().HideLoadingSequence();

        // Exit the action
        m_State = AS_ENDED;
        break;
      }
    };
  }
}


void ActionLoadLevel::End()
{
  if (m_pLoadingLevel && m_pLoadingLevel->GetLoadState() == GameLevel::LS_LOADING)
  {
    m_pLoadingLevel->CancelLoad(false);
  }
}



// -- EOF


