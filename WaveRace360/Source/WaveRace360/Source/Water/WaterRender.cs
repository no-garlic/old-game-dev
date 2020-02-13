// ----------------------------------------------------------------------------
// File: WaterRender.cs
// Desc: Renders the water surface.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: WaterRender
  // Desc: Renders the ocean
  // --------------------------------------------------------------------------
  public class WaterRender
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private CreationParams    m_creationParams;
    private WaterSimulation   m_simulation;
    private WaterMaterial     m_material;
    private WaterMesh         m_mesh;


    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public CreationParams   Params      { get { return m_creationParams; } }
    public WaterSimulation  Simulation  { get { return m_simulation; } } 
    public WaterMaterial    Material    { get { return m_material; } }
    public WaterMesh        Mesh        { get { return m_mesh; } }


    // ------------------------------------------------------------------------
    // Definition of a wave
    // ------------------------------------------------------------------------
    public class Wave
    {
      public Wave(float a_speed, float a_height, float a_length, Vector2 a_direction)
      {
        Speed     = a_speed;
        Height    = a_height;
        Length    = a_length;
        Direction = a_direction;
      }

      public float     Speed;
      public float     Height;
      public float     Length;
      public Vector2   Direction;
    };


    // ------------------------------------------------------------------------
    // Parameters to create the water system with
    // ------------------------------------------------------------------------
    public class CreationParams
    {
      public CreationParams()
      {
        Waves = new Wave[4];
      }

      public int       MeshSize;
      public float     Scale;
      public float     Height;
      public String    EnvMap;
      public String    BumpMap;
      public float     TextureStretch;
      public float     TextureSpeed;
      public float     BumpStrength;
      public Vector4   WaterColor;
      public Vector4   SpecularColor;
      public Vector4   ReflectiveColor;
      public Wave[]    Waves;
    };


    // ------------------------------------------------------------------------
    // Name: WaterRender
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public static void SetDefaultCreationParams(ref CreationParams a_params)
    {
      a_params.MeshSize         = 128;
      a_params.Scale            = 10.0f;
      a_params.Height           = 5.0f;
      a_params.EnvMap           = "Land";
      a_params.BumpMap          = "WaterBump";
      a_params.TextureStretch   = 16.0f;
      a_params.TextureSpeed     = 0.25f;
      a_params.BumpStrength     = 0.25f;
      a_params.WaterColor       = new Vector4(0.0f, 0.35f, 0.8f, 1.0f);
      a_params.SpecularColor    = new Vector4(0.8f, 0.6f, 1.0f, 1.0f);
      a_params.ReflectiveColor  = new Vector4(0.9f, 0.9f, 1.0f, 1.0f);
      a_params.Waves[0]         = new Wave(1.0f, 0.3f, 15.0f, new Vector2(-1, 0));
      a_params.Waves[1]         = new Wave(2.0f, 0.4f, 6.0f,  new Vector2(-1, 0.5f));
      a_params.Waves[2]         = new Wave(0.5f, 0.2f, 20.0f, new Vector2(-1, 0.7f));
      a_params.Waves[3]         = new Wave(1.5f, 1.5f, 10.0f, new Vector2(-1, -0.5f));
    }


    // ------------------------------------------------------------------------
    // Name: WaterRender
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public WaterRender()
    {
      m_simulation = new WaterSimulation(this);
      m_material = new WaterMaterial(this);
      m_mesh = new WaterMesh(this);
    }


    // ------------------------------------------------------------------------
    // Name: Create
    // Desc: Create the child classes
    // ------------------------------------------------------------------------
    public void Create(CreationParams a_creationParams)
    {
      m_creationParams = a_creationParams;

      m_simulation.Create(a_creationParams);
      m_material.Create(a_creationParams);
      m_mesh.Create(a_creationParams);
    }

    
    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the water surface
    // ------------------------------------------------------------------------
    public void AddForRender()
    {
      if (Systems.DebugSettings.Get("Render.Water"))
      {
        m_material.AddForRender(m_mesh, RenderPriority.Water, Matrix.Identity, CullMode.None);
      }
    }
    

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

