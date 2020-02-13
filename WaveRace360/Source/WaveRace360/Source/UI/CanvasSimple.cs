// ----------------------------------------------------------------------------
// File: CanvasSimple.cs
// Desc: A simple canvas class that provides the ability to render a fullscreen 
//       texture
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: CanvasSimple
  // Desc: A simple canvas class that provides the ability to render a 
  //       fullscreen texture
  // --------------------------------------------------------------------------
  public class CanvasSimple : Canvas
  {
    // ------------------------------------------------------------------------
    // Private Properties
    // ------------------------------------------------------------------------
    private SpriteBatch     m_spriteBatch;  // The sprite batch to render with
    private Texture2D       m_image;        // The image


    // ------------------------------------------------------------------------
    // Name: CanvasSimple
    // Desc: Constructor
    // Parm: String a_imageName - the name of the texture image to display
    // Parm: int a_priority - the canvas priority
    // ------------------------------------------------------------------------
    public CanvasSimple(String a_imageName, int a_priority)
      : base(a_priority)
    {
      m_spriteBatch = new SpriteBatch(Systems.Graphics.GraphicsDevice);
      m_image = Systems.Content.Load<Texture2D>(Asset.Resolve(AssetType.AT_UI, a_imageName));
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the canvas each frame
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public override void Update(float a_frameTime)
    {
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the canvas each frame
    // ------------------------------------------------------------------------
    public override void Render()
    {
      // Get the viewport
      Viewport viewport = Systems.Graphics.GraphicsDevice.Viewport;
      Rectangle rect = new Rectangle(viewport.X, viewport.Y, viewport.Width, viewport.Height);

      // Draw the image
      m_spriteBatch.Begin();
      m_spriteBatch.Draw(m_image, rect, Color.White);
      m_spriteBatch.End();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

