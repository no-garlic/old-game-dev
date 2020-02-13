// ----------------------------------------------------------------------------
// File: SceneObjectMaterial.cs
// Desc: A material to render a textured object.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: SceneObjectMaterial
  // Desc: A material to render a textured object.
  // --------------------------------------------------------------------------
  class SceneObjectMaterial : Material
  {
    // ------------------------------------------------------------------------
    // Private members
    //
    // ------------------------------------------------------------------------
    private EffectParameter m_worldViewProjection;    // The world*view*projection matrix
    private EffectParameter m_world;                  // The world matrix
    private EffectParameter m_lightDirection;         // The light direction


    // ------------------------------------------------------------------------
    // Name: SceneObjectMaterial
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public SceneObjectMaterial()
      : base("SceneObjectShader")
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
      m_lightDirection = m_effect.Parameters["m_lightDirection"];
      m_world = m_effect.Parameters["m_world"];
    }


    // ------------------------------------------------------------------------
    // Name: SetParameters
    // Desc: Set the effect parameters - called each time that the material is 
    //       about to render an IRender object.
    // Parm: Matrix a_worldMatrix - the world matrix that the IRender object is 
    //       to be rendered with.
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


    // ------------------------------------------------------------------------
    // Name: SetState
    // Desc: Called before the effect is started, allowing any changes in render
    //       state to be pushed.
    // ------------------------------------------------------------------------
    protected override void SetState()
    {
      //Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = true;
      //Systems.Graphics.GraphicsDevice.RenderState.AlphaSourceBlend = Blend.SourceAlpha;
      //Systems.Graphics.GraphicsDevice.RenderState.AlphaDestinationBlend = Blend.InverseSourceAlpha;

      //Systems.Graphics.GraphicsDevice.RenderState.AlphaTestEnable = true;
      //Systems.Graphics.GraphicsDevice.RenderState.ReferenceAlpha = 102;
    }


    // ------------------------------------------------------------------------
    // Name: ResetState
    // Desc: Called after the effect has finished to return the render state to 
    //       it's default.
    // ------------------------------------------------------------------------
    protected override void ResetState()
    {
      //Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = false;
      //Systems.Graphics.GraphicsDevice.RenderState.AlphaTestEnable = false;
    }


    //
    // ------------------------------------------------------------------------
  }
}
