// ----------------------------------------------------------------------------
// File: GameLevelStartup.cs
// Desc: The startup level is created as the first level of the game.
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
  // Name: GameLevelStartup 
  // Desc: The startup level is the first level that is ever created, and it 
  //       will display the startup sequence and then promptly load the front 
  //       end.
  // --------------------------------------------------------------------------
  public class GameLevelStartup : GameLevel
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private CanvasStartupSequence m_canvas;
    private bool                  m_loaded;
    Exception                     m_loadError;

    
    // ------------------------------------------------------------------------
    // Name: GameLevelStartup
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public GameLevelStartup()
    {
      m_loaded = false;

      try
      {
        m_canvas = new CanvasStartupSequence();
      }
      catch (Exception e)
      {
        m_loadError = e;
      }
    }


    // ------------------------------------------------------------------------
    // Name: BeginLoading
    // Desc: Called from the loader requesting this level to begin loading.
    // ------------------------------------------------------------------------
    public override void BeginLoading()
    {
      Systems.UI.AddCanvas(m_canvas);
      m_canvas.Progress = 0.0f;
    }


    // ------------------------------------------------------------------------
    // Name: LoadNextItem
    // Desc: Called by the loader to load the next item.
    // ------------------------------------------------------------------------
    public override void LoadNextItem()
    {
      // Skip to the next image if any button is pressed
      if (m_canvas != null)
      {
        // If a key is pressed, skip to the next image
        if (Systems.GamePad.IsAnyButtonPressed())
        {
          m_canvas.SkipNext();
        }

        // Check if the sequence is complete, if so set loaded to true.
        if (m_canvas.Progress == 1.0f)
        {
          m_loaded = true;
        }
      }
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
      return m_loaded;
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
      // Load the front end now
      Systems.Game.Loader.LoadLevel(new GameLevelFrontEnd());

      // Remove the canvas
      Systems.UI.RemoveCanvas(m_canvas);
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

