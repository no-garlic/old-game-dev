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


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: class 
  // Desc: Entry point for the game
  // --------------------------------------------------------------------------
  static class Program
  {
    // ------------------------------------------------------------------------
    // Name: Main
    // Desc: Entry function for the game
    // Parm: String[] args - the arguments passed to the application
    // ------------------------------------------------------------------------
    static void Main(String[] args)
    {
      WaveRace game = new WaveRace();
      game.Run();
    }
  }


  // --------------------------------------------------------------------------
  // Name: Game 
  // Desc: The game class that run the main loop.
  // --------------------------------------------------------------------------
  public class WaveRace : WaveRace360.Game
  {
    // ------------------------------------------------------------------------
    // Name: Game
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public WaveRace() : base()
    {
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
    public override void CreateDefaultDebugSettings(DebugSettings a_settings)
    {
      a_settings.Set("Render.Physics", false);
      a_settings.Set("Render.Terrain", true);
      a_settings.Set("Render.Water", true);
      a_settings.Set("Render.Meshes", true);
      a_settings.Set("Render.Sky",  true);
    }


    // ------------------------------------------------------------------------
    // Name: LoadContent
    // Desc: Load the content at the start of the game
    // ------------------------------------------------------------------------
    protected override void LoadContent()
    {
      // Load the materials
      MaterialManager.Instance.AddMaterial("CelShader", new CelMaterial("CelLookup"));
      MaterialManager.Instance.AddMaterial("BasicShader", new BasicMaterial());
      MaterialManager.Instance.AddMaterial("SceneObjectShader", new SceneObjectMaterial());

      // Load the level
      Loader.LoadLevel(new GameLevelPlayable("Small"));
    }
    

    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the game loop
    // Parm: GameTime gameTime - the game time
    // ------------------------------------------------------------------------
    protected override void Update(GameTime a_gameTime)
    {
      // Update the game
      base.Update(a_gameTime);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
