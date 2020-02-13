// ----------------------------------------------------------------------------
// File: GameLevelLoader.cs
// Desc: Loader class used to load game levels.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: GameLevelLoader
  // Desc: Loader class used to load game levels.
  //
  // Note: This class loads a given unloaded level, by calling it's load 
  //       functions as such:
  //
  //       - BeginLoading()    is called at the start.
  //       - LoadNextItem()    is called each frame until the level returns
  //                           true from calling IsLoaded().
  //       - LoadingComplete() is called once the last item is loaded.
  //
  //       This allows the level to load it's resources in the main thread
  //       while still rendering an animated laoding screen and processing
  //       input. The GameLevel classes need to be implemented in such a way
  //       that BeginLoading() and LoadNextItem() return each time they are
  //       called within a few milliseconds, therefore allowing the frame
  //       rate of the application to remain fast enough for the laoding
  //       screen animation.
  // --------------------------------------------------------------------------
  public class GameLevelLoader
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private GameLevel m_loadingLevel;   // The level that is currently loading
    private GameLevel m_requestedLevel; // The level requested to load


    // ------------------------------------------------------------------------
    // Name: GameLevelLoader
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public GameLevelLoader()
    {
      m_loadingLevel = null;
    }
    

    // ------------------------------------------------------------------------
    // Name: LoadLevel
    // Desc: Request that the given level is loaded. The level must not be 
    //       loaded before it is passed into this function, and will throw an 
    //       exception if it is.
    // Parm: GameLevel a_levelToLoad - the level to load
    // ------------------------------------------------------------------------
    public void LoadLevel(GameLevel a_levelToLoad)
    {
      m_requestedLevel = a_levelToLoad;
    }


    // ------------------------------------------------------------------------
    // Update the loading process
    //
    public void Update(float a_frameTime)
    {
      if (m_requestedLevel != null)
      {
        if (m_loadingLevel != null)
        {
          m_loadingLevel.CancelLoading();
          m_loadingLevel = null;
        }

        m_loadingLevel = m_requestedLevel;
        m_requestedLevel = null;

        m_loadingLevel.BeginLoading();
      }
    
      if (m_loadingLevel != null)
      {
        Exception loadingError = m_loadingLevel.GetLoadingError();
        if (loadingError != null)
        {
          m_loadingLevel = null;
          throw new Exception("Failed to load the level", loadingError);
        }
        else if (m_loadingLevel != null && m_loadingLevel.IsLoaded())
        {
          m_loadingLevel.LoadingComplete();
          Systems.Game.SetCurrentLevel(m_loadingLevel);
          m_loadingLevel = null;
        }
        else if (m_loadingLevel != null)
        {
          m_loadingLevel.LoadNextItem();
        }
      }
    }

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF


