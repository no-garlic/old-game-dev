// ----------------------------------------------------------------------------
// File: Canvas.cs
// Desc: A base class for a canvas.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------
using System;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: Canvas
  // Desc: The base class for canvas classes.
  //
  // Note: Each canvas is a complete 2D scene and can manage what it draws 
  //       internally however it wishes. 
  //
  // More: To manage the complexity in the UI, the canvas should only be used 
  //       as the hook to get the Update() and Render() function, and provide
  //       a way for a level to set the canvas they require as the current 
  //       canvas. In other words, it is like a 2D module. So for the complex
  //       classes, it is better to manage a sub-system which is designed for
  //       the task and hook it into a canvases Update() and Render() functions.
  // --------------------------------------------------------------------------
  public abstract class Canvas
  {
    // ------------------------------------------------------------------------
    // Public members
    // ------------------------------------------------------------------------
    public bool Enabled { get { return m_enabled; } set { m_enabled = value; } }
    public int Priority { get { return m_priority; } }
    

    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private bool  m_enabled;    // Is the canvas enabled
    private int   m_priority;   // The render priority

    
    // ------------------------------------------------------------------------
    // Name: Canvas
    // Desc: Constructor
    // Parm: int a_priority - the canvas priority
    // ------------------------------------------------------------------------
    public Canvas(int a_priority)
    {
      m_priority = a_priority;
      m_enabled = true;
    }

    
    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the canvas each frame
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public abstract void Update(float a_frameTime);


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the canvas each frame
    // ------------------------------------------------------------------------
    public abstract void Render();


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

