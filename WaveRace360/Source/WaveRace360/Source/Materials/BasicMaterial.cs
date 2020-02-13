// ----------------------------------------------------------------------------
// File: BasicMaterial.cs
// Desc: A basic material to render any object with a texture.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: BasicMaterial 
  // Desc: A basic vertex-lit material to render any object with a texture.
  // --------------------------------------------------------------------------
  class BasicMaterial : Material
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private EffectParameter   m_worldViewProjection;  // The world*view*projection matrix
    private EffectParameter   m_world;                // The world matrix
    private EffectParameter   m_lightDirection;       // The light direction



    // ------------------------------------------------------------------------
    // Name: BasicMaterial
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public BasicMaterial() : base("BasicShader")
    {
    }


    // ------------------------------------------------------------------------
    // Name: CreateParameters
    // Desc: Create any effect file parameters - called after the effect is 
    //       loaded.
    // ------------------------------------------------------------------------
    protected override void CreateParameters()
    {
      m_worldViewProjection = m_effect.Parameters["m_worldViewProjection"];
      m_lightDirection      = m_effect.Parameters["m_lightDirection"];
      m_world               = m_effect.Parameters["m_world"];
    }


    // ------------------------------------------------------------------------
    // Name: SetParameters
    // Desc: Set the effect parameters - called each time that the material is 
    //       about to render an IRender object.
    // ------------------------------------------------------------------------
    protected override void SetParameters()
    {
      // Set the light direction
      m_lightDirection.SetValue(Systems.Env.LightDirection);
    }


    public override void SetTransforms(Matrix a_worldMatrix)
    {
      // Set the (world * view * projection) matrix.
      Matrix wvp = a_worldMatrix * Systems.CameraSettings.ViewProjMatrix;
      m_worldViewProjection.SetValue(wvp);

      // Set the world matrix
      m_world.SetValue(a_worldMatrix);
      m_effect.CommitChanges();
    }


    //
    //
    // ------------------------------------------------------------------------
  }
}
