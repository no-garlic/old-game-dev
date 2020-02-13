// ----------------------------------------------------------------------------
// File: RenderPriority.cs
// Desc: 
// Auth: Michael Petrou
// (C) Copyright: 2009
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public enum RenderPriority
  {
    Sky         = 100,
    Terrain     = 200,
    Water       = 300,
    StaticMesh  = 400,

    Debug       = 1000
  }
}


// -- EOF

