// ----------------------------------------------------------------------------
// File: TerrainVertex.cs
// Desc: Vertex type for the terrain
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: TerrainVertex
  // Desc: Vertex type for the terrain
  // --------------------------------------------------------------------------
  public struct TerrainVertex
  {
    public Vector3 Position;
    
    public static int SizeInBytes { get { return sizeof(float) * 3; } }
    
    public static readonly VertexElement[] VertexElements = { new VertexElement(0, 0, VertexElementFormat.Vector3, VertexElementMethod.Default, VertexElementUsage.Position, 0) };
    
    public TerrainVertex(Vector3 a_position)
    {
      Position = a_position;
    }

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

