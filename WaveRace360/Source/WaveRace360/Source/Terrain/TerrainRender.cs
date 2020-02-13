// ----------------------------------------------------------------------------
// File: TerrainRender.cs
// Desc: Manages the terrian classes and provides the main point of interface
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: TerrainRender
  // Desc: Manages the terrain
  // --------------------------------------------------------------------------
  public class TerrainRender
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private TerrainHeightMap      m_heightMap;      // The terrain height map
    private TerrainMesh           m_mesh;           // The terrain mesh
    private TerrainBlendMaterial  m_blendMaterial;  // The blend material
    private float                 m_worldUnits;     // The size of the terrain in world units


    // ------------------------------------------------------------------------
    // Public Properties
    // ------------------------------------------------------------------------
    public TerrainHeightMap     HeightMap     { get { return m_heightMap; } }
    public TerrainMesh          Mesh          { get { return m_mesh; } }
    public float                WorldUnits    { get { return m_worldUnits; } }


    // ------------------------------------------------------------------------
    // Name: TerrainRender
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public TerrainRender()
    {
      m_heightMap     = new TerrainHeightMap();
      m_mesh          = new TerrainMesh();
      m_blendMaterial = new TerrainBlendMaterial();
    }


    // ------------------------------------------------------------------------
    // Name: Load
    // Desc: Load the terrain for the level config provided
    // Parm: Freeworld3D.Content a_content - the level content configuration
    // Parm: String a_levelName        - the level name
    // ------------------------------------------------------------------------
    public void Load(Freeworld3D.Content a_content, String a_levelName)
    {
      // Load the height map
      m_heightMap.Load(a_content, a_levelName);

      // Load the mesh
      m_mesh.Load(a_content, m_heightMap);

      // Load the material
      m_blendMaterial.Load(a_content, a_levelName);

      // Set the size
      m_worldUnits = a_content.Terrain.Step * (float) a_content.Terrain.Size;
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the terrain
    // ------------------------------------------------------------------------
    public void AddForRender()
    {
      if (Systems.DebugSettings.Get("Render.Terrain"))
      {
        m_blendMaterial.AddForRender(m_mesh, RenderPriority.Terrain, Matrix.Identity, CullMode.CullCounterClockwiseFace);
      }
    }
    

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

