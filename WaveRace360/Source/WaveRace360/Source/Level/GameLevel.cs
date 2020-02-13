// ----------------------------------------------------------------------------
// File: GameLevel.cs
// Desc: Base class for a game level.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: GameLevel
  // Desc: Base class for a game level
  // --------------------------------------------------------------------------
  public abstract class GameLevel
  {
    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the level each frame (once it has finished loading).
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public abstract void Update(float a_frameTime);


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the level each frame (once it has fineished loading).
    // ------------------------------------------------------------------------
    public abstract void Render();


    // ------------------------------------------------------------------------
    // Name: BeginLoading
    // Desc: Called from the loader requesting this level to begin loading.
    // ------------------------------------------------------------------------
    public abstract void BeginLoading();

    
    // ------------------------------------------------------------------------
    // Name: LoadingComplete
    // Desc: Called from the loader when this level has completed loading.
    // ------------------------------------------------------------------------
    public abstract void LoadingComplete();

    
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
    public abstract void CancelLoading();

    
    // ------------------------------------------------------------------------
    // Name: LoadNextItem
    // Desc: Called by the loader to load the next item.
    // ------------------------------------------------------------------------
    public abstract void LoadNextItem();

    
    // ------------------------------------------------------------------------
    // Name: IsLoaded
    // Desc: Test if this level is loaded or not
    // Retn: bool - true if loaded, otherwise false.
    // ------------------------------------------------------------------------
    public abstract bool IsLoaded();

    
    // ------------------------------------------------------------------------
    // Name: GetLoadingError
    // Desc: Test if this level encountered an error loading.
    // Retn: Exception - the exception that occurred during loading, or
    //       null if no error occurred.
    // ------------------------------------------------------------------------
    public abstract Exception GetLoadingError();


    // ------------------------------------------------------------------------
    // Name: Unload
    // Desc: Unload anything that is not pooled
    // ------------------------------------------------------------------------
    public abstract void Unload();

  
    //
    // ------------------------------------------------------------------------
  };
}


// -- EOF

