// ----------------------------------------------------------------------------
// File: TerrainHeightMap.cs
// Desc: A basic terrain heightmap class
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: TerrainHeightMap
  // Desc: A heightmap class for terrain.
  // --------------------------------------------------------------------------
  public class TerrainHeightMap
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private int               m_size;
    private ushort[]          m_rawData;
    private float             m_step;
    private float             m_maxHeight;


    // ------------------------------------------------------------------------
    // Name: TerrainHeightMap
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public TerrainHeightMap()
    {
      m_rawData = null;
    }


    // ------------------------------------------------------------------------
    // Name: Load
    // Desc: Load the heightmap
    // Parm: Freeworld3D.Content a_content - the level content definition
    // Parm: String a_levelName        - the name of the level
    // ------------------------------------------------------------------------
    public void Load(Freeworld3D.Content a_content, String a_levelName)
    {
      m_size       = a_content.Terrain.Size;
      m_step       = a_content.Terrain.Step;
      m_maxHeight  = 65536.0f * a_content.Terrain.MaxHeight;

      Terrain.RawData data = Systems.Content.Load<Terrain.RawData>(Asset.ResolveLevel(AssetType.AT_TERRAIN, a_levelName, a_content.Terrain.Filename));
      m_rawData = data.AsUInt16();
    }


    // ------------------------------------------------------------------------
    // Name: GetHeightAt
    // Desc: Get the height at the specified world position
    // Parm: float a_xPos - the x position
    // Parm: float a_zPos - the z position
    // Retn: float     - the height
    // ------------------------------------------------------------------------
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
    // Name: GetVertexHeight
    // Desc: Get the height at the specified vertex
    // Parm: int x - the x index
    // Parm: int y - the y index
    // Retn: float - the height
    // ------------------------------------------------------------------------
    public float GetVertexHeight(int x, int y)
    {
      return m_maxHeight * (((float) GetVertexHeightRaw(x, y)) / 65536.0f);
    }


    // ------------------------------------------------------------------------
    // Name: GetVertexNormal
    // Desc: Get the normal at the specified vertex
    // Parm: int x - the x vertex
    // Parm: int y - the y vertex
    // Retn: Vector3 - the normal
    // ------------------------------------------------------------------------
    public Vector3 GetVertexNormal(int x, int y)
    {
      float x1 = GetVertexHeight(x-1, y);
      float x2 = GetVertexHeight(x+1, y);
      float y1 = GetVertexHeight(x, y-1);
      float y2 = GetVertexHeight(x, y+1);

      Vector3 A = new Vector3(0.0f, y1 - y2, 1.0f);
      Vector3 B = new Vector3(1.0f, x1 - x2, 0.0f);

      return Vector3.Cross(A, B);      
    }


    // ------------------------------------------------------------------------
    // Name: GetVertexHeightRaw
    // Desc: Get the raw height (as a 16bit unsigned short) at the specified 
    //       vertex
    // Parm: int x - the x index
    // Parm: int y - the y index
    // Retn: ushort - the height
    // ------------------------------------------------------------------------
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
    // ------------------------------------------------------------------------
  }
}


// -- EOF

