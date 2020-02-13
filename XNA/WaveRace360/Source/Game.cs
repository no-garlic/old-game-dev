using System;
using System.Collections.Generic;

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
  static class Program
  {
    // ------------------------------------------------------------------------
    // Main
    //
    static void Main(String[] args)
    {
      Game game = new Game();
      game.Run();
    }
  }


  public class Game : Microsoft.Xna.Framework.Game
  {
    // ------------------------------------------------------------------------
    // Members
    //
    private GameLevel     m_gameLevel;      // The game level


    // ------------------------------------------------------------------------
    // Constructor
    //
    public Game()
    {
      // Create the systems for this game
      Systems.Create(this);

      m_gameLevel = new GameLevel();
    }


    // ------------------------------------------------------------------------
    // Initialise
    //
    protected override void Initialize()
    {
      base.Initialize();

      Vector3 cameraPos = new Vector3(65.0f, 50.0f, -65.0f);
      Vector3 cameraAt  = new Vector3(65.0f, 0.0f, 65.0f);

      Systems.Camera.SetProjection(MathHelper.PiOver4, 4.0f / 3.0f, 1.0f, 10000.0f);
      Systems.Camera.SetLookAt(cameraPos, cameraAt, Vector3.Up);
    }


    // ------------------------------------------------------------------------
    // Load the content
    //
    protected override void LoadContent()
    {
      if (!m_gameLevel.Load("world"))
      {
        throw new Exception("Failed to load the level");
      }
    }


    // ------------------------------------------------------------------------
    // Unload the content
    //
    protected override void UnloadContent()
    {
      Systems.Content.Unload();
    }


    // ------------------------------------------------------------------------
    // Update the game loop
    // 
    protected override void Update(GameTime gameTime)
    {
      if (Keyboard.GetState().IsKeyDown(Keys.Escape) || GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
      {
        Exit();
      }
      
      base.Update(gameTime);
    }


    // ------------------------------------------------------------------------
    // Draw the scene
    //
    protected override void Draw(GameTime gameTime)
    {
      Systems.Graphics.GraphicsDevice.Clear(Color.CornflowerBlue);

      m_gameLevel.Render();

      base.Draw(gameTime);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
