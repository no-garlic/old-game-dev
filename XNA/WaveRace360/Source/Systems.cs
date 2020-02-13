using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;


namespace WaveRace360
{
  class Systems
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public static Camera3D              Camera    { get { return s_systems.m_camera; } }
    public static GraphicsDeviceManager Graphics  { get { return s_systems.m_graphics; } }
    public static ContentManager        Content   { get { return s_systems.m_content; } }
    public static ModelCache            Models    { get { return s_systems.m_modelCache; } }


    // ------------------------------------------------------------------------
    // Private Members
    //
    private static  Systems                 s_systems;      // The singleton instance
    private         Camera3D                m_camera;       // The camera
    private         GraphicsDeviceManager   m_graphics;     // The graphics device
    private         ContentManager          m_content;      // The content manager
    private         ModelCache              m_modelCache;   // The model cache


    // ------------------------------------------------------------------------
    // Creation
    //
    public static void Create(Game a_game)
    {
      s_systems = new Systems(a_game);
    }


    // ------------------------------------------------------------------------
    // Constructor
    //
    private Systems(Game a_game)
    {
      m_graphics    = new GraphicsDeviceManager(a_game);
      m_content     = new ContentManager(a_game.Services);
      m_modelCache  = new ModelCache();
      m_camera      = new Camera3D();
    }


    //
    // ------------------------------------------------------------------------
  }
}

// -- EOF