using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using Common;


namespace WaveRace360
{
  public class TerrainHeightMap
  {
    // ------------------------------------------------------------------------
    // Private Members
    //
    private int               m_size;
    private ushort[]          m_rawData;
    private float             m_step;
    private float             m_maxHeight;


    // ------------------------------------------------------------------------
    // Public Properties
    //
    public ushort[]           Data { get { return m_rawData; } } 
    

    // ------------------------------------------------------------------------
    // Constructor
    //
    public TerrainHeightMap()
    {
      m_rawData = null;
    }


    // ------------------------------------------------------------------------
    // Load the terrain for the level config provided
    //
    public bool Load(Freeworld3D.Content a_content)
    {
      m_size       = a_content.Terrain.Size;
      m_step       = a_content.Terrain.Step;
      m_maxHeight  = 16.0f;

      String pathName = "Content\\terrain\\" + a_content.Terrain.Filename;
      Terrain.RawData data = Systems.Content.Load<Terrain.RawData>(pathName);

      m_rawData = data.AsUInt16();

      return true;
    }


    // ------------------------------------------------------------------------
    // Get the height at the specified world position
    //
    public float GetHeightAt(float a_xPos, float a_zPos)
    {
      int xIndex = (int) (a_xPos / m_step);
      int yIndex = (int) (a_zPos / m_step);

      // TODO: Need to determine which triangle of the quad this point is and interpolate correctly.

      float heightA = GetVertexHeight(xIndex, yIndex);
      float heightB = GetVertexHeight(xIndex + 1, yIndex);
      float heightC = GetVertexHeight(xIndex, yIndex + 1);
      float heightD = GetVertexHeight(xIndex + 1, yIndex + 1);

      return (heightA + heightB + heightC + heightD) * 0.25f;
    }


    // ------------------------------------------------------------------------
    // Get the height at the specified vertex
    //
    public float GetVertexHeight(int x, int y)
    {
      return m_maxHeight * (((float) GetVertexHeightRaw(x, y)) / 65536.0f);
    }


    // ------------------------------------------------------------------------
    // Get the height at the specified vertex
    //
    public ushort GetVertexHeightRaw(int x, int y)
    {
      if (x < 0) x = 0;
      if (y < 0) y = 0;
      if (x >= m_size) x = m_size - 1;
      if (y >= m_size) y = m_size - 1;
      
      int index = (x * m_size) + y;
      return m_rawData[index];
    }


    //
    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

