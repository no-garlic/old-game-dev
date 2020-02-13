// ----------------------------------------------------------------------------
// File: GameLevelFrontEnd.cs
// Desc: The level that runs the front end of the game
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: GameLevelFrontEnd 
  // Desc: The entire front end of the game is managed in this level.
  // --------------------------------------------------------------------------
  public class GameLevelFrontEnd : GameLevel
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private Exception     m_loadError;  // If a loading error occured
    private Canvas        m_canvas;     // The frontend canvas

    
    // ------------------------------------------------------------------------
    // Name: GameLevelFrontEnd
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public GameLevelFrontEnd()
    {
    }


    // ------------------------------------------------------------------------
    // Name: BeginLoading
    // Desc: Called from the loader requesting this level to begin loading.
    // ------------------------------------------------------------------------
    public override void BeginLoading()
    {
      try
      {
        // Show the canvas
        m_canvas = new CanvasFrontEnd();
        Systems.UI.AddCanvas(m_canvas);
      }
      catch (Exception e)
      {
        m_loadError = e;
      }
    }


    // ------------------------------------------------------------------------
    // Name: LoadNextItem
    // Desc: Called by the loader to load the next item.
    // ------------------------------------------------------------------------
    public override void LoadNextItem()
    {
    }


    // ------------------------------------------------------------------------
    // Name: CancelLoading
    // Desc: Called from the loader if another level is requested before this 
    //       level has completed loading. This level should stop loading and 
    //       prepare to be deleted. 
    //
    // Note: This level *SHOULD NOT* allow the IsLoadInError() function to
    //       return true if the load was cancelled in this way, as that will 
    //       generate a fatal exception.
    // ------------------------------------------------------------------------
    public override void CancelLoading() 
    {
      // TODO
    }
        

    // ------------------------------------------------------------------------
    // Name: IsLoaded
    // Desc: Test if this level is loaded or not
    // Retn: bool - true if loaded, otherwise false.
    // ------------------------------------------------------------------------
    public override bool IsLoaded()
    {
      return true;
    }


    // ------------------------------------------------------------------------
    // Name: GetLoadingError
    // Desc: Test if this level encountered an error loading.
    // Retn: Exception - the exception that occurred during loading, or
    //       null if no error occurred.
    // ------------------------------------------------------------------------
    public override Exception GetLoadingError()
    {
      return m_loadError;
    }


    // ------------------------------------------------------------------------
    // Name: LoadingComplete
    // Desc: Called from the loader when this level has completed loading.
    // ------------------------------------------------------------------------
    public override void LoadingComplete()
    {
    }


    // ------------------------------------------------------------------------
    // Name: Unload
    // Desc: Unload anything that is not pooled
    // ------------------------------------------------------------------------
    public override void Unload()
    {
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the level each frame (once it has finished loading).
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public override void Update(float a_frameTime)
    {
      // If the player presses start or waits 5 seconds then load the game level
      if (Systems.GamePad.IsButtonPressed(Buttons.Start))
      {
        // Load a playable game level
        Systems.Game.Loader.LoadLevel(new GameLevelPlayable("Level1"));

        // Remove the canvas
        Systems.UI.RemoveCanvas(m_canvas);
      }
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the level each frame (once it has fineished loading).
    // ------------------------------------------------------------------------
    public override void Render()
    {
      // Clear the device
      Systems.Graphics.GraphicsDevice.Clear(Color.White);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

