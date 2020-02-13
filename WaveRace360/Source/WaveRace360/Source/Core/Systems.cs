// ----------------------------------------------------------------------------
// File: Systems.cs
// Desc: Global systems for the game
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;

using JigLibX.Physics;
using JigLibX.Geometry;
using JigLibX.Collision;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: Systems
  // Desc: Global systems container
  // --------------------------------------------------------------------------
  public class Systems
  {
    // ------------------------------------------------------------------------
    // Public Members
    // ------------------------------------------------------------------------
    public static Game                  Game            { get { return s_systems.m_game; } } 
    public static DebugSettings         DebugSettings   { get { return s_systems.m_game.DebugSettings; } }
    public static CameraSettings        CameraSettings  { get { return s_systems.m_cameraSettings; } }
    public static GraphicsDeviceManager Graphics        { get { return s_systems.m_graphics; } }
    public static ContentManager        Content         { get { return s_systems.m_content; } }
    public static ModelCache            Models          { get { return s_systems.m_modelCache; } }
    public static Environment           Env             { get { return s_systems.m_env; } }
    public static UserInterface         UI              { get { return s_systems.m_ui; } }
    public static GamePad               GamePad         { get { return s_systems.m_gamepad; } }
    public static PhysicsSystem         PhysicsSystem   { get { return s_systems.m_physicsSystem; } set { s_systems.m_physicsSystem = value; } }
    public static CollisionSystem       CollisionSystem { get { return s_systems.m_physicsSystem.CollisionSystem; } }
    public static MaterialTable         MaterialTable   { get { return s_systems.m_physicsSystem.CollisionSystem.MaterialTable; } }


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private static  Systems                 s_systems;        // The singleton instance
    private         Game                    m_game;           // The game
    private         CameraSettings          m_cameraSettings; // The camera settings
    private         GraphicsDeviceManager   m_graphics;       // The graphics device
    private         ContentManager          m_content;        // The content manager
    private         ModelCache              m_modelCache;     // The model cache
    private         Environment             m_env;            // The environment
    private         UserInterface           m_ui;             // The user interface
    private         GamePad                 m_gamepad;        // The gamepad
    private         PhysicsSystem           m_physicsSystem;  // The physics system


    // ------------------------------------------------------------------------
    // Name: Create
    // Desc: Create the systems singleton
    // Parm: Game a_game - the game to create the systems for
    // ------------------------------------------------------------------------
    public static void Create(Game a_game)
    {
      s_systems = new Systems(a_game);
    }


    // ------------------------------------------------------------------------
    // Name: Systems
    // Desc: Constructor
    // Parm: Game a_game - the game to create the systems for
    // ------------------------------------------------------------------------
    private Systems(Game a_game)
    {
      m_game            = a_game;
      m_graphics        = new GraphicsDeviceManager(a_game);
      m_content         = new ContentManager(a_game.Services);
      m_modelCache      = new ModelCache();
      m_cameraSettings  = new CameraSettings();
      m_env             = new Environment();
      m_ui              = new UserInterface();
      m_gamepad         = new GamePad(PlayerIndex.One);
    }


    // ------------------------------------------------------------------------
    // Name: CurrentLevel
    // Desc: Get the current level as the type specified
    // ------------------------------------------------------------------------
    public T CurrentLevel<T>() where T : GameLevel
    {
      T tLevel = default(T);
      if (m_game.CurrentLevel != null)
      {
        tLevel = m_game.CurrentLevel as T;
      }
      return tLevel;
    }


    //
    // ------------------------------------------------------------------------
  }
}

// -- EOF