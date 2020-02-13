// ----------------------------------------------------------------------------
// File: SkyMesh.cs
// Desc: The mesh for a sky box.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: SkyMesh 
  // Desc: Renders a skybox
  // --------------------------------------------------------------------------
  public class SkyMesh : IRender
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private Model m_skyboxModel;


    // ------------------------------------------------------------------------
    // Name: SkyMesh
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public SkyMesh() : base()
    {
      m_skyboxModel = Systems.Models.GetModel("Skybox");
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the selected surface (See SetSurface())
    // ------------------------------------------------------------------------
    public override void Render(Material a_material, Matrix a_worldMatrix)
    {
      a_material.SetTransforms(a_worldMatrix);

      foreach (ModelMesh mesh in m_skyboxModel.Meshes)
      {
        Systems.Graphics.GraphicsDevice.Indices = mesh.IndexBuffer;

        foreach (ModelMeshPart part in mesh.MeshParts)
        {
          Systems.Graphics.GraphicsDevice.VertexDeclaration = part.VertexDeclaration;
          Systems.Graphics.GraphicsDevice.Vertices[0].SetSource(mesh.VertexBuffer, part.StreamOffset, part.VertexStride);
          Systems.Graphics.GraphicsDevice.DrawIndexedPrimitives(PrimitiveType.TriangleList, part.BaseVertex, 0, part.NumVertices, part.StartIndex, part.PrimitiveCount);
        }
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

