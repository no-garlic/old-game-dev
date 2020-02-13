
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  public class FilterSpring
  {
    // ------------------------------------------------------------------------
    // Public Properties
    // ------------------------------------------------------------------------
    public float Velocity     { get { return m_velocity; } }
    public float Acceleration { get { return m_acceleration; } }
    public float Spring       { get { return m_spring; } set { m_spring = value; } }
    public float Drag         { get { return m_drag; } set { m_drag = value; } }


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private float m_velocity;
    private float m_acceleration;
    private float m_spring;
    private float m_drag;


    // ------------------------------------------------------------------------
    // Name: FilterSpring
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public FilterSpring(float a_spring, float a_drag)
    {
      m_spring = a_spring;
      m_drag = a_drag;
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Updates the spring
    // Parm: a_frameTime - the frame time
    // Parm: a_value - the input value to filter
    // Parm: a_target - the target value being pulled to
    // Parm: a_useAcceleration - should acceleration be used
    // Retn: the filtered value
    // ------------------------------------------------------------------------
    public float Update(float a_frameTime, float a_value, float a_target, bool a_useAcceleration)
    {
      float fltTarget = a_target;
      float fltValue  = a_value;

      if (a_useAcceleration)
      {
        // Calculate acceleration based on spring force (applied to 1kg mass)
        // a = k * x
        m_acceleration = m_spring * (fltTarget - fltValue);
      }
      else
      {
        m_acceleration = 0;
      }

      // Add drag
      m_acceleration -= m_velocity * m_drag;

      // Adjust velocity v' = v + at
      m_velocity += m_acceleration * a_frameTime;

      // Calculate new value x' = x + vt + 0.5at^2
      fltValue = fltValue + m_velocity * a_frameTime + 0.5f * m_acceleration * a_frameTime * a_frameTime;

      return fltValue;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

