// ----------------------------------------------------------------------------
// File: CelMaterial.cs
// Desc: A material to render a textured object with cartoon lighting (cel 
//       shading).
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: CelMaterial
  // Desc: A material to render a textured object with cartoon lighting (cel 
  //       shading).
  // --------------------------------------------------------------------------
  class CelMaterial : Material
  {
    // ------------------------------------------------------------------------
    // Private members
    //
    // ------------------------------------------------------------------------
    private EffectParameter   m_worldViewProjection;    // The world*view*projection matrix
    private EffectParameter   m_world;                  // The world matrix
    private EffectParameter   m_lightDirection;         // The light direction
    private EffectParameter   m_celTexture;             // The cel texture
    private EffectParameter   m_edgeOffset;             // The edge offset
    private Texture2D         m_celTextureResource;     // The cel texture resource


    // ------------------------------------------------------------------------
    // Name: CelMaterial
    // Desc: Constructor
    // Parm: String a_cellTextureName - the name of the cell texture to use
    // ------------------------------------------------------------------------
    public CelMaterial(String a_cellTextureName) : base("ObjectCelShader")
    {
      m_celTextureResource = Systems.Content.Load<Texture2D>(Asset.Resolve(AssetType.AT_TEXTURE, a_cellTextureName));
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
      m_celTexture          = m_effect.Parameters["m_celTexture"];
      m_edgeOffset          = m_effect.Parameters["m_edgeOffset"];
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

      // Set the cel texture
      m_celTexture.SetValue(m_celTextureResource);

      // Set the edge offset
      m_edgeOffset.SetValue(0.03f);
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
      //Systems.Graphics.GraphicsDevice.RenderState.AlphaTestEnable = true;
    }


    // ------------------------------------------------------------------------
    // Name: ResetState
    // Desc: Called after the effect has finished to return the render state to 
    //       it's default.
    // ------------------------------------------------------------------------
    protected override void ResetState()
    {
      //Systems.Graphics.GraphicsDevice.RenderState.AlphaTestEnable = false;
    }


    //
    // ------------------------------------------------------------------------
  }
}
