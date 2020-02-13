// ----------------------------------------------------------------------------
// File: WaterMesh.cs
// Desc: Provides the custom LOD mesh for rendering the water.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: WaterMesh
  // Desc: Renders the ocean
  // --------------------------------------------------------------------------
  public class WaterMesh : IRender
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private WaterRender       m_parent;
    private VertexBuffer      m_vertexBuffer;
    private IndexBuffer       m_indexBuffer;
    private VertexDeclaration m_vertexDecl;


    // ------------------------------------------------------------------------
    // Name: WaterMesh
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public WaterMesh(WaterRender a_parent)
    {
      m_parent = a_parent;

      m_vertexBuffer = null;
      m_indexBuffer = null;
      m_vertexDecl = null;
    }


    // ------------------------------------------------------------------------
    // Name: Create
    // Desc: Create the mesh
    // ------------------------------------------------------------------------
    public void Create(WaterRender.CreationParams a_creationParams)
    {
      VertexPositionTexture[] waterVertices = CreateWaterVertices();
      int[] waterIndices = CreateWaterIndices();
      CreateBuffers(waterVertices, waterIndices);
    }


    // ------------------------------------------------------------------------
    // Name: GetHeightAt
    // Desc: Get the height at the world position specified
    // Parm: float a_xPos - the x position
    // Parm: float a_zPos - the z position
    // Retn: float     - the height
    // ------------------------------------------------------------------------
    public float GetHeightAt(float a_xPos, float a_zPos)
    {
      Vector2 position = new Vector2(a_xPos, a_zPos);
      float time = Systems.Game.RunTime;

      float totalHeight = m_parent.Params.Height;

      for (int i = 0; i < 4; i++)
      {
        float dotProduct = Vector2.Dot(m_parent.Simulation.WaveDirections[i], position);
        float argument = dotProduct / m_parent.Simulation.WaveLengths[i] + time * m_parent.Simulation.WaveSpeeds[i];
        float height = m_parent.Simulation.WaveHeights[i] * (float) Math.Sin(argument);

        totalHeight += height;
      }

      return totalHeight;
    }


    // ------------------------------------------------------------------------
    // Name: GetNormalAt
    // Desc: Get the normal at the world position specified
    // Parm: float a_xPos - the x position
    // Parm: float a_zPos - the z position
    // Retn: Vector3   - the normal (y up)
    // ------------------------------------------------------------------------
    public Vector3 GetNormalAt(float a_xPos, float a_zPos)
    {
      float extrudeDistance = 0.5f * m_parent.Params.Scale;

      Vector3 pointA = new Vector3(a_xPos - extrudeDistance, 0.0f, a_zPos);
      Vector3 pointB = new Vector3(a_xPos + extrudeDistance, 0.0f, a_zPos);
      Vector3 pointC = new Vector3(a_xPos, 0.0f, a_zPos - extrudeDistance);
      Vector3 pointD = new Vector3(a_xPos, 0.0f, a_zPos + extrudeDistance);

      pointA.Y = GetHeightAt(pointA.X, pointA.Z);
      pointB.Y = GetHeightAt(pointB.X, pointB.Z);
      pointC.Y = GetHeightAt(pointC.X, pointC.Z);
      pointD.Y = GetHeightAt(pointD.X, pointD.Z);

      Vector3 BA = (pointB - pointA);
      Vector3 DC = (pointD - pointC);

      BA.Normalize();
      DC.Normalize();

      Vector3 normal = Vector3.Cross(DC, BA);
      return normal;
    }
    

    // ------------------------------------------------------------------------
    // Name: CreateWaterVertices
    // Desc: Create the water vertex array
    // Retn: private VertexPositionTexture[] - the vertex data
    // ------------------------------------------------------------------------
    private VertexPositionTexture[] CreateWaterVertices()
    {
      VertexPositionTexture[] waterVertices = new VertexPositionTexture[m_parent.Params.MeshSize * m_parent.Params.MeshSize];

      int i = 0;
      for (int z = 0; z < m_parent.Params.MeshSize; z++)
      {
        for (int x = 0; x < m_parent.Params.MeshSize; x++)
        {
          Vector3 position = new Vector3(x * m_parent.Params.Scale, m_parent.Params.Height, -z * m_parent.Params.Scale);
          Vector2 texCoord = new Vector2(((float)x) / 30.0f, ((float)z) / 30.0f);

          waterVertices[i++] = new VertexPositionTexture(position, texCoord);
        }
      }

      m_vertexDecl = new VertexDeclaration(Systems.Game.GraphicsDevice, VertexPositionTexture.VertexElements);

      return waterVertices;
    }

    
    // ------------------------------------------------------------------------
    // Name: CreateWaterIndices
    // Desc: Create the index array for the water mesh
    // Retn: private int[] - the index array
    // ------------------------------------------------------------------------
    private int[] CreateWaterIndices()
    {
      int[] waterIndices = new int[(m_parent.Params.MeshSize) * 2 * (m_parent.Params.MeshSize - 1)];

      int i = 0;
      int z = 0;
      while (z < m_parent.Params.MeshSize - 1)
      {
        for (int x = 0; x < m_parent.Params.MeshSize; x++)
        {
          waterIndices[i++] = x + z * m_parent.Params.MeshSize;
          waterIndices[i++] = x + (z + 1) * m_parent.Params.MeshSize;
        }
        z++;

        if (z < m_parent.Params.MeshSize - 1)
        {
          for (int x = m_parent.Params.MeshSize - 1; x >= 0; x--)
          {
            waterIndices[i++] = x + (z + 1) * m_parent.Params.MeshSize;
            waterIndices[i++] = x + z * m_parent.Params.MeshSize;
          }
        }
        z++;
      }

      return waterIndices;
    }


    // ------------------------------------------------------------------------
    // Name: CreateBuffers
    // Desc: Create the vertex and index buffers
    // Parm: VertexPositionTexture[] vertices - the vertex data
    // Parm: int[] indices                    - the index data
    // ------------------------------------------------------------------------
    private void CreateBuffers(VertexPositionTexture[] vertices, int[] indices)
    {
      m_vertexBuffer = new VertexBuffer(Systems.Graphics.GraphicsDevice, VertexPositionTexture.SizeInBytes * vertices.Length, BufferUsage.WriteOnly);
      m_vertexBuffer.SetData(vertices);

      m_indexBuffer = new IndexBuffer(Systems.Graphics.GraphicsDevice, typeof(int), indices.Length, BufferUsage.WriteOnly);
      m_indexBuffer.SetData(indices);
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the selected surface (See SetSurface())
    // ------------------------------------------------------------------------
    public override void Render(Material a_material, Matrix a_worldMatrix)
    {
      // Get the graphics device
      GraphicsDevice gfx = Systems.Graphics.GraphicsDevice;

      a_material.SetTransforms(a_worldMatrix);
      
      // Bind the data to the device
      gfx.Vertices[0].SetSource(m_vertexBuffer, 0, VertexPositionTexture.SizeInBytes);
      gfx.Indices = m_indexBuffer;
      gfx.VertexDeclaration = m_vertexDecl;

      // Draw the mesh
      gfx.DrawIndexedPrimitives(
        PrimitiveType.TriangleStrip, 
        0, 
        0, 
        m_parent.Params.MeshSize * m_parent.Params.MeshSize, 
        0, 
        m_parent.Params.MeshSize * 2 * (m_parent.Params.MeshSize - 1) - 2);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

