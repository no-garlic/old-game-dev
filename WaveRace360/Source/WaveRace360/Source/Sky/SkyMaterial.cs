// ----------------------------------------------------------------------------
// File: SkyMaterial.cs
// Desc: The material for rendering a skybox.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: SkyMaterial 
  // Desc: Skybox material that renders the skybox mesh one surface at a time.
  // --------------------------------------------------------------------------
  public class SkyMaterial : Material
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private TextureCube     m_textureCube;
    private EffectParameter m_texture;
    private EffectParameter m_matrixView;
    private EffectParameter m_matrixProjection;
    


    // ------------------------------------------------------------------------
    // Name: SkyMaterial
    // Desc: Constructor
    // Parm: Freeworld3D.Content a_content - the level content definition
    // ------------------------------------------------------------------------
    public SkyMaterial(String a_name) : base("SkyShader")
    {
      m_textureCube = Systems.Content.Load<TextureCube>(Asset.Resolve(AssetType.AT_TEXTURE, a_name));
    }


    // ------------------------------------------------------------------------
    // Name: CreateParameters
    // Desc: Create any effect file parameters - called after the effect is 
    //       loaded.
    // ------------------------------------------------------------------------
    protected override void CreateParameters()
    {
      m_matrixProjection = m_effect.Parameters["m_projectionMatrix"];
      m_matrixView = m_effect.Parameters["m_viewMatrix"];
      m_texture = m_effect.Parameters["m_texture"];
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
      m_matrixView.SetValue(Systems.CameraSettings.ViewMatrix);
      m_matrixProjection.SetValue(Systems.CameraSettings.ProjMatrix);
      m_texture.SetValue(m_textureCube);
    }


    public override void SetTransforms(Matrix a_worldMatrix)
    {
    }
    

    // ------------------------------------------------------------------------
    // Name: SetState
    // Desc: Called before the effect is started, allowing any changes in render
    //       state to be pushed.
    // ------------------------------------------------------------------------
    protected override void SetState()
    {
      Systems.Graphics.GraphicsDevice.RenderState.DepthBufferWriteEnable = false;
    }


    // ------------------------------------------------------------------------
    // Name: ResetState
    // Desc: Called after the effect has finished to return the render state to 
    //       it's default.
    // ------------------------------------------------------------------------
    protected override void ResetState()
    {
      Systems.Graphics.GraphicsDevice.RenderState.DepthBufferWriteEnable = true;
      Systems.Graphics.GraphicsDevice.RenderState.DepthBufferEnable = true;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

