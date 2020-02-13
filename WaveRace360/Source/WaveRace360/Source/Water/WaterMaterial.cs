// ----------------------------------------------------------------------------
// File: WaterMaterial.cs
// Desc: The material for shading the water.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: WaterMaterial 
  // Desc: Water material that renders the ocean surface.
  // --------------------------------------------------------------------------
  public class WaterMaterial : Material
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private WaterRender     m_parent;
    private Texture         m_waterBumpTexture;
    private TextureCube     m_waterEnvTexture;
    private EffectParameter m_worldParam;     
    private EffectParameter m_viewParam;    
    private EffectParameter m_projectionParam;    
    private EffectParameter m_bumpMapParam;     
    private EffectParameter m_bumpStrengthParam;     
    private EffectParameter m_cubeMapParam;    
    private EffectParameter m_texStretchParam;     
    private EffectParameter m_texSpeedParam;     
    private EffectParameter m_cameraPosParam;    
    private EffectParameter m_tileSizeXParam;     
    private EffectParameter m_tileSizeZParam;    
    private EffectParameter m_timeParam;
    private EffectParameter m_waterColorParam;
    private EffectParameter m_specularColorParam;
    private EffectParameter m_reflectiveColorParam;
    private EffectParameter m_waveSpeedsParam;
    private EffectParameter m_waveHeightsParam;
    private EffectParameter m_waveLengthsParam;
    private EffectParameter m_waveDir0Param;
    private EffectParameter m_waveDir1Param;
    private EffectParameter m_waveDir2Param;
    private EffectParameter m_waveDir3Param;


    // ------------------------------------------------------------------------
    // Name: WaterMaterial
    // Desc: Constructor
    // Parm: Freeworld3D.Content a_content - the level content definition
    // ------------------------------------------------------------------------
    public WaterMaterial(WaterRender a_parent) : base("WaterShader")
    {
      m_parent = a_parent;
    }


    // ------------------------------------------------------------------------
    // Name: Create
    // Desc: Create the material
    // ------------------------------------------------------------------------
    public void Create(WaterRender.CreationParams a_creationParams)
    {
      m_waterEnvTexture = Systems.Content.Load<TextureCube>(Asset.Resolve(AssetType.AT_TEXTURE, a_creationParams.EnvMap));
      m_waterBumpTexture = Systems.Content.Load<Texture2D>(Asset.Resolve(AssetType.AT_TEXTURE, a_creationParams.BumpMap));
    }


    // ------------------------------------------------------------------------
    // Name: CreateParameters
    // Desc: Create any effect file parameters - called after the effect is 
    //       loaded.
    // ------------------------------------------------------------------------
    protected override void CreateParameters()
    {
      m_worldParam            = m_effect.Parameters["m_world"];
      m_viewParam             = m_effect.Parameters["m_view"];
      m_projectionParam       = m_effect.Parameters["m_projection"];
      m_bumpMapParam          = m_effect.Parameters["m_bumpMap"];
      m_bumpStrengthParam     = m_effect.Parameters["m_bumpStrength"];
      m_cubeMapParam          = m_effect.Parameters["m_cubeMap"];
      m_texStretchParam       = m_effect.Parameters["m_texStretch"];
      m_texSpeedParam         = m_effect.Parameters["m_texSpeed"];
      m_cameraPosParam        = m_effect.Parameters["m_cameraPos"];
      m_tileSizeXParam        = m_effect.Parameters["m_tileSizeX"];
      m_tileSizeZParam        = m_effect.Parameters["m_tileSizeZ"];
      m_timeParam             = m_effect.Parameters["m_time"];
      m_waterColorParam       = m_effect.Parameters["m_waterColor"];
      m_specularColorParam    = m_effect.Parameters["m_specularColor"];
      m_reflectiveColorParam  = m_effect.Parameters["m_reflectiveColor"];
      m_waveSpeedsParam       = m_effect.Parameters["m_waveSpeeds"];
      m_waveHeightsParam      = m_effect.Parameters["m_waveHeights"];
      m_waveLengthsParam      = m_effect.Parameters["m_waveLengths"];
      m_waveDir0Param         = m_effect.Parameters["m_waveDir0"];
      m_waveDir1Param         = m_effect.Parameters["m_waveDir1"];
      m_waveDir2Param         = m_effect.Parameters["m_waveDir2"];
      m_waveDir3Param         = m_effect.Parameters["m_waveDir3"];
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
      m_worldParam.SetValue(Matrix.Identity);
      m_viewParam.SetValue(Systems.CameraSettings.ViewMatrix);
      m_projectionParam.SetValue(Systems.CameraSettings.ProjMatrix);
      m_bumpMapParam.SetValue(m_waterBumpTexture);
      m_bumpStrengthParam.SetValue(m_parent.Params.BumpStrength);
      m_cubeMapParam.SetValue(m_waterEnvTexture);
      m_texStretchParam.SetValue(m_parent.Params.TextureStretch);
      m_texSpeedParam.SetValue(m_parent.Params.TextureSpeed);
      m_cameraPosParam.SetValue(Systems.CameraSettings.CameraPosition);
      m_tileSizeXParam.SetValue(m_parent.Params.MeshSize * m_parent.Params.Scale);
      m_tileSizeZParam.SetValue(m_parent.Params.MeshSize * m_parent.Params.Scale);
      m_timeParam.SetValue(Systems.Game.RunTime);
      m_waterColorParam.SetValue(m_parent.Params.WaterColor);
      m_specularColorParam.SetValue(m_parent.Params.SpecularColor);
      m_reflectiveColorParam.SetValue(m_parent.Params.ReflectiveColor);
      m_waveSpeedsParam.SetValue(m_parent.Simulation.WaveSpeeds);
      m_waveHeightsParam.SetValue(m_parent.Simulation.WaveHeights);
      m_waveLengthsParam.SetValue(m_parent.Simulation.WaveLengths);
      m_waveDir0Param.SetValue(m_parent.Simulation.WaveDirections[0]);
      m_waveDir1Param.SetValue(m_parent.Simulation.WaveDirections[1]);
      m_waveDir2Param.SetValue(m_parent.Simulation.WaveDirections[2]);
      m_waveDir3Param.SetValue(m_parent.Simulation.WaveDirections[3]);
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
      Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = true;
    }


    // ------------------------------------------------------------------------
    // Name: ResetState
    // Desc: Called after the effect has finished to return the render state to 
    //       it's default.
    // ------------------------------------------------------------------------
    protected override void ResetState()
    {
      Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = false;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

