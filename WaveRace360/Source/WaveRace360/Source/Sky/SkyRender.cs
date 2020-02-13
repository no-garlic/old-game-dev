// ----------------------------------------------------------------------------
// File: SkyRender.cs
// Desc: Renders a sykbox
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: SkyRender
  // Desc: Renders a skybox
  // --------------------------------------------------------------------------
  public class SkyRender
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private SkyMesh       m_mesh;
    private SkyMaterial   m_material;


    // ------------------------------------------------------------------------
    // Name: SkyRender
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public SkyRender(String a_name)
    {
      m_mesh = new SkyMesh();
      m_material = new SkyMaterial(a_name);
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the sky box
    // ------------------------------------------------------------------------
    public void AddForRender()
    {
      if (Systems.DebugSettings.Get("Render.Sky"))
      {
        m_material.AddForRender(m_mesh, RenderPriority.Sky, Matrix.Identity, CullMode.None);
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

