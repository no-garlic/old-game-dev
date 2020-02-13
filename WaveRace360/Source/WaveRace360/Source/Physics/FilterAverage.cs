
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  public class FilterAverage
  {
    // ------------------------------------------------------------------------
    // Public Properties
    // ------------------------------------------------------------------------


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private float[] m_history;
    private int     m_historyCount;
    private int     m_historyIndex;


    // ------------------------------------------------------------------------
    // Name: FilterAverage
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public FilterAverage(int a_historyCount)
    {
      m_history = new float[a_historyCount];
      m_historyCount = a_historyCount;
      m_historyIndex = -1;
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Updates the spring
    // Parm: a_frameTime - the frame time
    // Parm: a_value - the input value to filter
    // Parm: a_target - the target value being pulled to
    // Retn: the filtered value
    // ------------------------------------------------------------------------
    public float Update(float a_frameTime, float a_value, float a_target)
    {
      if (m_historyIndex != -1)
      {
        m_history[m_historyIndex++] = a_target;
        
        if (m_historyIndex == m_historyCount)
        {
          m_historyIndex = 0;
        }

        a_value = 0;

        for (int i = 0; i < m_historyCount; ++i)
        {
          a_value += m_history[i];
        }

        a_value = a_value / m_historyCount;
      }
      else
      {
        for (int i = 0; i < m_historyCount; ++i)
        {
          m_history[i] = a_target;
        }

        m_historyIndex = 0;
        a_value = a_target;
      }

      return a_value;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

