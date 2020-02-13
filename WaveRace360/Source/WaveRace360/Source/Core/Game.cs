// ----------------------------------------------------------------------------
// File: Game.cs
// Desc: Game class for the XNA project.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

using JigLibX.Physics;
using JigLibX.Geometry;
using JigLibX.Collision;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: Game 
  // Desc: The game class that run the main loop.
  // --------------------------------------------------------------------------
  public class Game : Microsoft.Xna.Framework.Game
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private GameLevel         m_gameLevel;      // The current game level
    private GameLevelLoader   m_loader;         // The game level loader
    private float             m_frameTime;      // The frame time
    private TimeSpan          m_frameTimeSpan;  // The frame time span
    private float             m_runTime;        // The time running
    private DebugSettings     m_debugSettings;  // The debug settings
    private int               m_updateCount;    // The number of calls to Update
    private int               m_renderCount;    // The number of calls to Draw
    

    // ------------------------------------------------------------------------
    // Public Members
    // ------------------------------------------------------------------------
    public GameLevel        CurrentLevel  { get { return m_gameLevel; } }
    public GameLevelLoader  Loader        { get { return m_loader; } }
    public float            FrameTime     { get { return m_frameTime; } }
    public TimeSpan         FrameTimeSpan { get { return m_frameTimeSpan; } }
    public float            RunTime       { get { return m_runTime; } }
    public DebugSettings    DebugSettings { get { return m_debugSettings; } }

    
    // ------------------------------------------------------------------------
    // Name: Game
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public Game() : base()
    {
      // Create the systems for this game
      Systems.Create(this);

      // Load the debug settings
      m_debugSettings = new DebugSettings();
      CreateDefaultDebugSettings(m_debugSettings);
      m_debugSettings.LoadFromFile();

      // Set the render target usage based on the platform
      Systems.Graphics.PreparingDeviceSettings +=
        new EventHandler<PreparingDeviceSettingsEventArgs>(SetPresentationParameters);

      // Enable multisampling (anitaliasing)
      Systems.Graphics.PreferMultiSampling = true;

      // Require shader 2 for skinning
      Systems.Graphics.MinimumVertexShaderProfile = ShaderProfile.VS_2_0;
      Systems.Graphics.MinimumPixelShaderProfile = ShaderProfile.PS_2_0;
      
#if XBOX
      // Set the size of the window
      Systems.Graphics.PreferredBackBufferWidth = 1280;
      Systems.Graphics.PreferredBackBufferHeight = 720;
#else
      // Set the size of the window
      Systems.Graphics.PreferredBackBufferWidth = 1024;
      Systems.Graphics.PreferredBackBufferHeight = 576;
      //Systems.Graphics.PreferredBackBufferWidth = 1280;
      //Systems.Graphics.PreferredBackBufferHeight = 720;
      //Systems.Graphics.PreferredBackBufferWidth = 1152;
      //Systems.Graphics.PreferredBackBufferHeight = 640;
#endif

      // Set v-sync off
      //Systems.Graphics.SynchronizeWithVerticalRetrace = false;
      //this.IsFixedTimeStep = false;

      // Physics Setup
      Systems.PhysicsSystem = new PhysicsSystem();
      Systems.PhysicsSystem.CollisionSystem = new CollisionSystemSAP();
      Systems.PhysicsSystem.Gravity = 25.0f * Vector3.Down;
      //Systems.PhysicsSystem.EnableFreezing = true;
      Systems.PhysicsSystem.SolverType = PhysicsSystem.Solver.Normal;
      //Systems.PhysicsSystem.CollisionSystem.UseSweepTests = true;
      //Systems.PhysicsSystem.NumCollisionIterations = 5;
      //Systems.PhysicsSystem.NumContactIterations = 15;
      //Systems.PhysicsSystem.NumPenetrationRelaxtionTimesteps = 20;

      // Set the time to 0
      m_frameTime = 0.0f;
      m_runTime = 0.0f;

      // No level is currently loaded
      m_gameLevel = null;

      // Create the game level loader
      m_loader = new GameLevelLoader();
    }


    // ------------------------------------------------------------------------
    // Name: SetPresentationParameters
    // Desc: Called to prepare the presentation parameters
    // ------------------------------------------------------------------------
    void SetPresentationParameters(object a_sender, PreparingDeviceSettingsEventArgs a_eventArgs)
    {
      a_eventArgs.GraphicsDeviceInformation.PresentationParameters.RenderTargetUsage = RenderTargetUsage.PlatformContents;
    }


    // ------------------------------------------------------------------------
    // Name: Initialize
    // Desc: Initialise the game
    // ------------------------------------------------------------------------
    protected override void Initialize()
    {
      base.Initialize();
    }


    // ------------------------------------------------------------------------
    // Name: CreateDefaultDebugSettings
    // Desc: Create the default debug settings
    // ------------------------------------------------------------------------
    public virtual void CreateDefaultDebugSettings(DebugSettings a_settings)
    {
      a_settings.Set("Render.Physics", true);
      a_settings.Set("Render.Terrain", true);
      a_settings.Set("Render.Water", true);
      a_settings.Set("Render.Meshes", true);
      a_settings.Set("Render.Sky", true);
    }


    // ------------------------------------------------------------------------
    // Name: SetCurrentLevel
    // Desc: Set the current level.
    // ------------------------------------------------------------------------
    public void SetCurrentLevel(GameLevel a_level)
    {
      if (a_level != null && !a_level.IsLoaded())
      {
        throw new Exception("Cannot set a current level that is not loaded.");
      }

      if (m_gameLevel != null)
      {
        m_gameLevel.Unload();
      }

      m_gameLevel = a_level;
    }


    // ------------------------------------------------------------------------
    // Name: LoadContent
    // Desc: Load the content at the start of the game
    // ------------------------------------------------------------------------
    protected override void LoadContent()
    {
      base.LoadContent();
    }


    // ------------------------------------------------------------------------
    // Name: UnloadContent
    // Desc: Unload the content at the end of the game
    // ------------------------------------------------------------------------
    protected override void UnloadContent()
    {
      Systems.Content.Unload();
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the game loop
    // Parm: GameTime gameTime - the game time
    // ------------------------------------------------------------------------
    protected override void Update(GameTime gameTime)
    {
      // Get the time since the last frame
      m_frameTime     = (float) (gameTime.ElapsedGameTime.TotalSeconds);
      m_frameTimeSpan = gameTime.ElapsedGameTime;
      m_runTime       = (float) (gameTime.TotalGameTime.TotalSeconds);
      m_updateCount++;

      // Clear the render manager
      RenderManager.Instance.Clear();

      // Update the input
      Systems.GamePad.Update(m_frameTime);

      bool exitKey = false;

#if !XBOX
      exitKey = Keyboard.GetState().IsKeyDown(Keys.Escape);
#endif

      // Exit the game
      if (exitKey || Systems.GamePad.IsButtonPressed(Buttons.Back))
      {
        Exit();
      }

      // Update the level loader
      m_loader.Update(m_frameTime);

      // Update the current game level
      if (m_gameLevel != null)
      {
        m_gameLevel.Update(m_frameTime);
      }
      
      // Update the user interface
      Systems.UI.Update(m_frameTime);

      // Integrate the physics timestep
      float timeStep = (float) gameTime.ElapsedGameTime.Ticks / TimeSpan.TicksPerSecond;
      if (timeStep < 1.0f / 30.0f)
      {
        Systems.PhysicsSystem.Integrate(timeStep);
      }
      else
      {
        Systems.PhysicsSystem.Integrate(1.0f / 30.0f);
      }

      // Call the base update function
      base.Update(gameTime);
    }


    // ------------------------------------------------------------------------
    // Name: Draw
    // Desc: Render the game
    // Parm: GameTime gameTime - the game time
    // ------------------------------------------------------------------------
    protected override void Draw(GameTime gameTime)
    {
      m_renderCount++;

      // Render the game level
      if (m_gameLevel != null)
      {
        m_gameLevel.Render();
      }

      // Render the UI
      Systems.UI.Render();

      // Call the base draw function
      base.Draw(gameTime);

      // Clear the render manager
      RenderManager.Instance.Clear();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
