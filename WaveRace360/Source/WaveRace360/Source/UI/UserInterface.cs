// ----------------------------------------------------------------------------
// File: UserInterface.cs
// Desc: The user interface hook for the application.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: UserInterface
  // Desc: The user interface hook for the application. See Canvas.cs for more
  //       information.
  // --------------------------------------------------------------------------
  public class UserInterface
  {
    // ------------------------------------------------------------------------
    // Private Properties
    // ------------------------------------------------------------------------
    private SortedList<int, Canvas> m_canvas; // The canvas dictionary


    // ------------------------------------------------------------------------
    // Name: UserInterface
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public UserInterface()
    {
      m_canvas = new SortedList<int, Canvas>(new CanvasPriorityComparer());
    }


    // ------------------------------------------------------------------------
    // Name: AddCanvas
    // Desc: Add the canvas to the list
    // Parm: Canvas a_canvas - the canvas
    // ------------------------------------------------------------------------
    public void AddCanvas(Canvas a_canvas)
    {
      if (m_canvas.ContainsKey(a_canvas.Priority))
      {
        throw new Exception("The canvas priority must be unique");
      }

      m_canvas.Add(a_canvas.Priority, a_canvas);
    }

    
    // ------------------------------------------------------------------------
    // Name: RemoveCanvas
    // Desc: Remove the canvas
    // Parm: Canvas a_canvas the canvas to remove
    // ------------------------------------------------------------------------
    public void RemoveCanvas(Canvas a_canvas)
    {
      m_canvas.Remove(a_canvas.Priority);
    }

    
    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the current canvas
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public void Update(float a_frameTime)
    {
      foreach (KeyValuePair<int, Canvas> canvasPair in m_canvas)
      {
        if (canvasPair.Value.Enabled)
        {
          canvasPair.Value.Update(a_frameTime);
        }
      }
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the current canvas.
    // ------------------------------------------------------------------------
    public void Render()
    {
      foreach (KeyValuePair<int, Canvas> canvasPair in m_canvas)
      {
        if (canvasPair.Value.Enabled)
        {
          canvasPair.Value.Render();
        }
      }
    }
  }


  // --------------------------------------------------------------------------
  // Name: CanvasPriorityComparer 
  // Desc: Compares 2 priorities - used as a sorting functor.
  // --------------------------------------------------------------------------
  public class CanvasPriorityComparer : IComparer<int>
  {
    public int Compare(int a_first, int a_second)
    {
      // higher priorities are rendered last (ontop).
      return a_first - a_second;
    }
  }


  //
  // ------------------------------------------------------------------------
}


// -- EOF

