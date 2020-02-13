// ----------------------------------------------------------------------------
// File: GameLevelPlayable.cs
// Desc: The game level that exists when the game is actuallg being played - 
//       that is the player is racing.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

using JigLibX.Collision;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: GameLevelPlayable 
  // Desc: The game level that exists when the game is actuallg being played - 
  //       that is the player is racing.
  // --------------------------------------------------------------------------
  public class GameLevelPlayable : GameLevel
  {
    // ------------------------------------------------------------------------
    // Public Properties
    // ------------------------------------------------------------------------
    public String Name { get { return m_levelName; } }


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private String                      m_levelName;        // The name of the level to load
    private CanvasLoadingScreen         m_loadingCanvas;    // The loading screen canvas
    private bool                        m_loaded;           // Is the level loaded
    private int                         m_loadStep;         // The load step
    private Freeworld3D.Content         m_loadContent;      // The content to load from
    private float                       m_loadTimer;        // Minimum time we should load until
    private Exception                   m_loadException;    // The exception that occured while loading
    private List<GameLoader>            m_loaders;
    private List<GameLoader>.Enumerator m_iterator;
    

    // ------------------------------------------------------------------------
    // Name: GameLevelPlayable
    // Desc: Constructor
    // Parm: String a_levelName - the name of the level to load.
    // ------------------------------------------------------------------------
    public GameLevelPlayable(String a_levelName)
    {
      m_levelName = a_levelName;
      m_loaded    = false;
      m_loadStep  = 0;
      m_loaders   = new List<GameLoader>();
    }


    // ------------------------------------------------------------------------
    // Name: BeginLoading
    // Desc: Called from the loader requesting this level to begin loading.
    // ------------------------------------------------------------------------
    public override void BeginLoading()
    {
      // Make sure we load for atelast 3 seconds, so the splash screen does not look stupid.
      m_loadTimer = Systems.Game.RunTime + 3.0f; 
      m_loadStep  = 0;

      // Show the loading screen
      m_loadingCanvas = new CanvasLoadingScreen();
      Systems.UI.AddCanvas(m_loadingCanvas);
    }


    // ------------------------------------------------------------------------
    // Name: LoadNextItem
    // Desc: Called by the loader to load the next item.
    // ------------------------------------------------------------------------
    public override void LoadNextItem()
    {
      try
      {
        switch (m_loadStep)
        {
          case 0:
          {
            m_loadContent = Systems.Content.Load<Freeworld3D.Content>(Asset.ResolveLevel(AssetType.AT_LEVEL, m_levelName, "world"));
            m_loadStep++;
            break;
          }
            
          case 1:
          {
            m_loaders.Add(new GameLoaderEntities(this, m_levelName, m_loadContent));
            m_loaders.Add(new GameLoaderEnvironment(this, m_levelName, m_loadContent));
            m_loaders.Add(new GameLoaderNPC(this, m_levelName, m_loadContent));
            m_loaders.Add(new GameLoaderPhysics(this, m_levelName, m_loadContent));
            m_loaders.Add(new GameLoaderWater(this, m_levelName, m_loadContent));
            m_loaders.Add(new GameLoaderPlayer(this, m_levelName, m_loadContent));
            m_loaders.Add(new GameLoaderSky(this, m_levelName, m_loadContent));
            m_loaders.Add(new GameLoaderStaticMeshes(this, m_levelName, m_loadContent));
            m_loaders.Add(new GameLoaderTerrain(this, m_levelName, m_loadContent));

            m_iterator = m_loaders.GetEnumerator();
            m_iterator.MoveNext();
            m_loadStep++;
            break;
          }

          case 2:
          {
            if (m_iterator.Current.IsLoaded())
            {
              if (!m_iterator.MoveNext())
              {
                m_loadStep++;
                break;
              }
            }

            m_iterator.Current.LoadNextItem();
            break;
          }

          case 3:
          {
            // Wait until the loading timer has expired and set loading to complete.
            if (Systems.Game.RunTime >= m_loadTimer)
            {
              m_loadContent = null;
              m_loaded = true;
              m_loadStep++;
            }
            break;
          }
        }
      }
      catch (Exception e)
      {
        // Flag the loading as failed
        m_loadException = e;
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
      m_loaded = false;
      m_loadContent = null;
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
      return m_loadException;
    }


    // ------------------------------------------------------------------------
    // Name: LoadingComplete
    // Desc: Called from the loader when this level has completed loading.
    // ------------------------------------------------------------------------
    public override void LoadingComplete()
    {
      // Hide the loading screen
      Systems.UI.RemoveCanvas(m_loadingCanvas);
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
      // Update all game objects
      GameObjectManager.Instance.Update(a_frameTime);
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the level each frame (once it has fineished loading).
    // ------------------------------------------------------------------------
    public override void Render()
    {
      // Clear the device
      Systems.Graphics.GraphicsDevice.Clear(Color.White);

      // Render the physics objects
      if (Systems.DebugSettings.Get("Render.Physics"))
      {
        BasicMaterial physicsMaterial = MaterialManager.Instance.GetMaterial<BasicMaterial>("BasicShader");
        PhysicsBody.DebugRender(physicsMaterial);
      }

      // Render all objects
      RenderManager.Instance.Render();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

