using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using Common;


namespace WaveRace360
{
  public class TerrainRender
  {
    // ------------------------------------------------------------------------
    // Private Members
    //
    TerrainHeightMap    m_heightMap;    // The terrain height map
    TerrainMesh         m_mesh;         // The terrain mesh

    Effect              m_basicEffect;
    EffectParameter     m_basicEffectWVP;


    // ------------------------------------------------------------------------
    // Public Properties
    //
    TerrainHeightMap    HeightMap     { get { return m_heightMap; } }
    TerrainMesh         Mesh          { get { return m_mesh; } }


    // ------------------------------------------------------------------------
    // Constructor
    //
    public TerrainRender()
    {
      m_heightMap = new TerrainHeightMap();
      m_mesh      = new TerrainMesh();
    }


    // ------------------------------------------------------------------------
    // Load the terrain for the level config provided
    //
    public bool Load(Freeworld3D.Content a_content)
    {
      m_basicEffect = Systems.Content.Load<Effect>(Asset.Resolve(AssetType.AT_SHADER, "BasicShader"));
      m_basicEffectWVP = m_basicEffect.Parameters["fx_WVP"];
      m_basicEffect.CommitChanges();

      if (!m_heightMap.Load(a_content))
      {
        return false;
      }

      if (!m_mesh.Load(a_content, m_heightMap))
      {
        return false;
      }

      return true;
    }


    public void Render()
    {
      Systems.Graphics.GraphicsDevice.RenderState.CullMode = CullMode.None;
      Systems.Graphics.GraphicsDevice.RenderState.FillMode = FillMode.WireFrame;

      m_basicEffectWVP.SetValue(Matrix.Identity * Systems.Camera.ViewMatrix * Systems.Camera.ProjMatrix);

      m_basicEffect.Begin();
      m_basicEffect.Techniques[0].Passes[0].Begin();

      m_mesh.Render();

      m_basicEffect.Techniques[0].Passes[0].End();
      m_basicEffect.End();

    }
    

    //
    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

