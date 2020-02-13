// ----------------------------------------------------------------------------
// File: CanvasStartupSequence.cs
// Desc: A canvas for teh initial loading sequence.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: CanvasStartupSequence 
  // Desc: A canvas for the initial loading sequence
  // --------------------------------------------------------------------------
  public class CanvasStartupSequence : Canvas
  {
    // ------------------------------------------------------------------------
    // Public Properties
    // ------------------------------------------------------------------------
    public float Progress { get { return GetProgress(); } set { SetProgress(value); } }
    public float Duration { get { return m_duration; } }


    // ------------------------------------------------------------------------
    // Private Properties
    // ------------------------------------------------------------------------
    private SpriteBatch     m_spriteBatch;  // The sprite batch to render with
    private float           m_progress;     // The current progress
    private float           m_duration;     // The total duration for the entire sequence
    private float           m_interval;     // The duration of each image
    private int             m_numImages;    // The number of images to display
    private int             m_currImage;    // The current image
    private Texture2D[]     m_imageArray;   // The array of images


    // ------------------------------------------------------------------------
    // Name: CanvasStartupSequence
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public CanvasStartupSequence() : base(CanvasPriority.StartupSequence)
    {
      m_spriteBatch = new SpriteBatch(Systems.Graphics.GraphicsDevice);
      m_progress    = 0.0f;
      m_currImage   = 0;

      // Show 3 images over 10 seconds
      m_numImages   = 3;
      m_duration    = 6.0f;
      m_interval    = m_duration / (float) m_numImages;

      // Load the images
      m_imageArray = new Texture2D[m_numImages];
      m_imageArray[0] = Systems.Content.Load<Texture2D>(Asset.Resolve(AssetType.AT_UI, "StartupSequence1"));
      m_imageArray[1] = Systems.Content.Load<Texture2D>(Asset.Resolve(AssetType.AT_UI, "StartupSequence2"));
      m_imageArray[2] = Systems.Content.Load<Texture2D>(Asset.Resolve(AssetType.AT_UI, "StartupSequence3"));
    }


    // ------------------------------------------------------------------------
    // Name: SetProgress
    // Desc: Set the sequence progress
    // Parm: float a_progress - the progress (0..1)
    // ------------------------------------------------------------------------
    public void SetProgress(float a_progress)
    {
      m_progress = MathHelper.Clamp(a_progress, 0.0f, 1.0f);
    }


    // ------------------------------------------------------------------------
    // Name: GetProgress
    // Desc: Get the sequence progress
    // Retn: float - the sequence progress (0..1)
    // ------------------------------------------------------------------------
    public float GetProgress()
    {
      return m_progress;
    }


    // ------------------------------------------------------------------------
    // Name: SkipNext
    // Desc: Skip to the next image (by setting the progress) - used if the 
    //       player presses a button while the loading sequence is showing.
    // ------------------------------------------------------------------------
    public void SkipNext()
    {
      m_currImage++;

      if (m_currImage >= m_numImages)
      {
        m_currImage = m_numImages - 1;
        m_progress = 1.0f;
      }
      else
      {
        m_progress = (1.0f / (float) m_numImages) * (float) m_currImage;
      }
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the canvas each frame
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public override void Update(float a_frameTime)
    {
      // Update the progress
      m_progress += a_frameTime * (1.0f / m_duration);

      // Have we finished?
      if (m_progress >= 1.0f)
      {
        m_progress = 1.0f;
        return;
      }

      // Get the elapsed time
      float elapsed = m_duration * m_progress;

      // Calculate the image we should be displaying now
      m_currImage = (int) (elapsed / m_interval);
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the canvas
    // ------------------------------------------------------------------------
    public override void Render()
    {
      // Get the viewport
      Viewport viewport = Systems.Graphics.GraphicsDevice.Viewport;
      Rectangle rect = new Rectangle(viewport.X, viewport.Y, viewport.Width, viewport.Height);
      
      // TODO: handle fading. Detect when the progress is almost about to 
      // change, and fade in / fade out (pass in gray -> black to this 
      // function to fade).
      m_spriteBatch.Begin();
      m_spriteBatch.Draw(m_imageArray[m_currImage], rect, Color.White);
      m_spriteBatch.End();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

