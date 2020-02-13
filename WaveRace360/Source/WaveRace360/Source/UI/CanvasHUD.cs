// ----------------------------------------------------------------------------
// File: CanvasHUD.cs
// Desc: The canvas class for the game HUD.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: CanvasHUD
  // Desc: The canvas class for the game HUD.
  // --------------------------------------------------------------------------
  public class CanvasHUD : Canvas
  {
    // ------------------------------------------------------------------------
    // Public Properties
    // ------------------------------------------------------------------------
    public float    Speed     { get { return m_speed; } set { m_speed = value; } }
    public int      Gear      { get { return m_gear; } set { m_gear = value; } }
    public Vector2  Heading   { get { return m_heading; } set { m_heading = value; } }
    public Vector2  Position  { get { return m_position; } set { m_position = value; } }
        
    
    // ------------------------------------------------------------------------
    // Private Properties
    // ------------------------------------------------------------------------
    private SpriteBatch     m_spriteBatch;  // The sprite batch to render with
    private SpriteFont      m_font;         // The font
    private float           m_speed;        // The movement speed
    private int             m_gear;         // The gear (1..4)
    private Vector2         m_heading;      // The heading vector (flat on the x,z ground plane)
    private Vector2         m_position;     // The unit position within the world bounds (0,0 .. 1,1)


    // ------------------------------------------------------------------------
    // Name: CanvasHUD
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public CanvasHUD() : base(CanvasPriority.PlayerHUD)
    {
      m_position = new Vector2();
      m_heading = new Vector2();
      m_spriteBatch = new SpriteBatch(Systems.Graphics.GraphicsDevice);
      m_font = Systems.Content.Load<SpriteFont>(Asset.Resolve(AssetType.AT_FONT, "Arial"));
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the canvas each frame
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public override void Update(float a_frameTime)
    {
      // TODO
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

      // Convert the speed to a multiple of 5
      int speed = (int) m_speed;
      speed = speed / 5;
      speed = speed * 5;

      // Draw the text
      m_spriteBatch.Begin();
      m_spriteBatch.DrawString(m_font, "Speed: " + Convert.ToString(speed), new Vector2(10, 10), Color.Orange);
      m_spriteBatch.End();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

