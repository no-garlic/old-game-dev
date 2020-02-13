using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using Common;


namespace WaveRace360
{
  public class TerrainMesh
  {
    // ------------------------------------------------------------------------
    // Private Members
    //
    VertexBuffer        m_vertexBuffer;       // The vertex buffer
    IndexBuffer         m_indexBuffer;        // The index buffer
    VertexDeclaration   m_vertexDeclaration;  // The vertex declaration
    int                 m_size;               // The number of vertices in each axis
    float               m_step;               // The world unit's size of each cell


    // ------------------------------------------------------------------------
    // Public Properties
    //


    // ------------------------------------------------------------------------
    // Constructor
    //
    public TerrainMesh()
    {
      m_vertexBuffer = null;
      m_indexBuffer  = null;
      m_vertexDeclaration = null;
    }


    // ------------------------------------------------------------------------
    // Load the terrain for the level config provided
    //
    public bool Load(Freeworld3D.Content a_content, TerrainHeightMap a_heightMap)
    {
      m_size  = a_content.Terrain.Size;
      m_step  = a_content.Terrain.Step;

      // Create the buffers
      CreateIndexBuffer();
      CreateVertexBuffer(a_heightMap);

      // Create the vertex declaration
      m_vertexDeclaration = new VertexDeclaration(Systems.Graphics.GraphicsDevice, VertexPositionColorTexture.VertexElements);

      return true;
    }


    // ------------------------------------------------------------------------
    // Create the vertex buffer
    //
    private void CreateVertexBuffer(TerrainHeightMap a_heightMap)
    {
      // Create the vertex array
      VertexPositionColorTexture[] vertexArray = new VertexPositionColorTexture[m_size * m_size];
      
      // Create the vertex buffer
      m_vertexBuffer = new VertexBuffer(Systems.Graphics.GraphicsDevice, typeof(VertexPositionColorTexture), m_size * m_size, BufferUsage.WriteOnly);

      // Set the vertex array data
      for (int row = 0; row < m_size; row++)
      {
        for (int col = 0; col < m_size; col++)
        {
          // Calculate the vertex position
          float x = (float) col * m_step;
          float y = a_heightMap.GetVertexHeight(row, col);
          float z = (float) row * m_step;

          // Calculate the texture coordinates
          float u = 1.0f - ((float) col / (float) m_size);
          float v = 1.0f - ((float) row / (float) m_size);

          // Set the vertex data
          vertexArray[col + (row * m_size)].Position = new Vector3(x, y, z);
          vertexArray[col + (row * m_size)].Color = Color.White;
          vertexArray[col + (row * m_size)].TextureCoordinate = new Vector2(u, v);
        }
      }

      // Set the vertex buffer data
      m_vertexBuffer.SetData<VertexPositionColorTexture>(vertexArray, 0, vertexArray.Length);
    }


    // ------------------------------------------------------------------------
    // Create the index buffer
    //
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
        indexArray[i++] = (short) col;
        indexArray[i++] = (short) (col + m_size);
      }

      // Set the index buffer data
      m_indexBuffer.SetData<short>(indexArray, 0, indexArray.Length);
    }


    // ------------------------------------------------------------------------
    // Render the terrain mesh
    //
    public void Render()
    {
      // Get the graphics device
      GraphicsDevice gfx = Systems.Graphics.GraphicsDevice;
      
      // Bind the data to the device
      gfx.VertexDeclaration = m_vertexDeclaration;
      gfx.Vertices[0].SetSource(m_vertexBuffer, 0, VertexPositionColorTexture.SizeInBytes);
      gfx.Indices = m_indexBuffer;

      // Draw the grid one row at a time using a triangle strip
      for (int i = 0; i < m_size - 1; i++)
      {
        gfx.DrawIndexedPrimitives(PrimitiveType.TriangleStrip, i * m_size, 0, m_size * m_size, 0, 2 * (m_size - 1));
      }
    }

    
    //
    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

