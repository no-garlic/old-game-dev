// ----------------------------------------------------------------------------
// File: Environment.cs
// Desc: Holds the environment values that are used globally by all materials.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: Environment
  // Desc: Holds the environment values that are used globally by all materials.
  // --------------------------------------------------------------------------
  public class Environment
  {
    // ------------------------------------------------------------------------
    // Public members
    // ------------------------------------------------------------------------
    public Vector3  LightDirection;   // The light direction


    // ------------------------------------------------------------------------
    // Name: (
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public Environment()
    {
      LightDirection = Vector3.Down;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

