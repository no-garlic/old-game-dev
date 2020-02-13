// ----------------------------------------------------------------------------
// File: TerrainMesh.cs
// Desc: Renders the terrain
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: TerrainMesh 
  // Desc: Renders the terrain
  // --------------------------------------------------------------------------
  public class TerrainMesh : IRender
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private VertexBuffer        m_vertexBuffer;       // The vertex buffer
    private IndexBuffer         m_indexBuffer;        // The index buffer
    private VertexDeclaration   m_vertexDeclaration;  // The vertex declaration
    private int                 m_size;               // The number of vertices in each axis
    private float               m_step;               // The world unit's size of each cell


    // ------------------------------------------------------------------------
    // Name: TerrainMesh
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public TerrainMesh()
    {
      m_vertexBuffer = null;
      m_indexBuffer  = null;
      m_vertexDeclaration = null;
    }


    // ------------------------------------------------------------------------
    // Name: Load
    // Desc: Load the terrain mesh
    // Parm: Freeworld3D.Content a_content - the level content definition
    // Parm: TerrainHeightMap a_heightMap - the heightmap
    // ------------------------------------------------------------------------
    public void Load(Freeworld3D.Content a_content, TerrainHeightMap a_heightMap)
    {
      m_size  = a_content.Terrain.Size;
      m_step  = a_content.Terrain.Step;

      // Create the buffers
      CreateIndexBuffer();
      CreateVertexBuffer(a_heightMap);

      // Create the vertex declaration
      m_vertexDeclaration = new VertexDeclaration(Systems.Graphics.GraphicsDevice, TerrainVertex.VertexElements);
    }


    // ------------------------------------------------------------------------
    // Name: CreateVertexBuffer
    // Desc: Create the vertex buffer for the entire terrain
    // Parm: TerrainHeightMap a_heightMap - the heightmap
    // ------------------------------------------------------------------------
    private void CreateVertexBuffer(TerrainHeightMap a_heightMap)
    {
      // Create the vertex array
      TerrainVertex[] vertexArray = new TerrainVertex[m_size * m_size];
      
      // Create the vertex buffer
      m_vertexBuffer = new VertexBuffer(Systems.Graphics.GraphicsDevice, typeof(TerrainVertex), m_size * m_size, BufferUsage.WriteOnly);

      // Set the vertex array data
      for (int row = 0; row < m_size; row++)
      {
        for (int col = 0; col < m_size; col++)
        {
          // Calculate the vertex position
          float x = (float) col * m_step;
          float y = a_heightMap.GetVertexHeight(row, col);
          float z = (float) row * m_step;

          // Set the vertex data
          vertexArray[col + (row * m_size)].Position = new Vector3(x, y, z);
        }
      }

      // Set the vertex buffer data
      m_vertexBuffer.SetData<TerrainVertex>(vertexArray, 0, vertexArray.Length);
    }


    // ------------------------------------------------------------------------
    // Name: CreateIndexBuffer
    // Desc: Create the index buffer for a single row of the terrain grid
    // ------------------------------------------------------------------------
    private void CreateIndexBuffer()
    {
      // Create the index array
      short[] indexArray = new short[m_size * 2];
      
      // Create the index buffer
      m_indexBuffer = new IndexBuffer(Systems.Graphics.GraphicsDevice, typeof(short), indexArray.Length, BufferUsage.WriteOnly);

      // Set the index array data
      int i = 0;
      for (int col = 0; col < m_size; col++)
      {
        indexArray[i++] = (short) (col + m_size);
        indexArray[i++] = (short) col;
      }

      // Set the index buffer data
      m_indexBuffer.SetData<short>(indexArray, 0, indexArray.Length);
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the entire terrain mesh
    // ------------------------------------------------------------------------
    public override void Render(Material a_material, Matrix a_worldMatrix)
    {
      // Get the graphics device
      GraphicsDevice gfx = Systems.Graphics.GraphicsDevice;
      
      a_material.SetTransforms(a_worldMatrix);

      // Bind the data to the device
      gfx.VertexDeclaration = m_vertexDeclaration;
      gfx.Vertices[0].SetSource(m_vertexBuffer, 0, TerrainVertex.SizeInBytes);
      gfx.Indices = m_indexBuffer;

      // Draw the grid one row at a time using a triangle strip
      for (int i = 0; i < m_size - 1; i++)
      {
        gfx.DrawIndexedPrimitives(PrimitiveType.TriangleStrip, i * m_size, 0, m_size * m_size, 0, 2 * (m_size - 1));
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

