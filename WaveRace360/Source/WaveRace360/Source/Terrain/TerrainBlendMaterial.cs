// ----------------------------------------------------------------------------
// File: TerrainBlendMaterial.cs
// Desc: Material for rendering the terrain
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: TerrainBlendMaterial 
  // Desc: This material is for rending the terrain with multiple blend textures
  //       and a lightmap in a singe pass.
  //
  // Note: The material uses 4 texture stages as such:
  //       - 1: The base texture
  //       - 2: The first blended texture
  //       - 3: The second blended texture
  //       - 4: R = base texture blend interpolant
  //            G = first blended texture interpolant
  //            B = second blended texture interpolant
  //            A = combined lightmap & shadowmap
  // --------------------------------------------------------------------------
  public class TerrainBlendMaterial : Material
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private Texture2D         m_textureColor1;
    private Texture2D         m_textureColor2;
    private Texture2D         m_textureColor3;
    private Texture2D         m_textureBlend;
    private float             m_size;
    private float             m_U1;
    private float             m_V1;
    private float             m_U2;
    private float             m_V2;
    private float             m_U3;
    private float             m_V3;


    // ------------------------------------------------------------------------
    // Name: TerrainBlendMaterial
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public TerrainBlendMaterial() : base("TerrainBlendShader")
    {
      m_textureColor1 = null;
      m_textureColor2 = null;
      m_textureColor3 = null;
      m_textureBlend  = null;
    }


    // ------------------------------------------------------------------------
    // Name: Load
    // Desc: Load the material resources
    // Parm: Freeworld3D.Content a_data - the level content definition
    // Parm: String a_levelName     - the name of the level
    // ------------------------------------------------------------------------
    public void Load(Freeworld3D.Content a_data, String a_levelName)
    {
      // Check that the required content exists
      if (a_data.TerrainBaseLayerList.Count != 1)
      {
        throw new Exception("There must be 1 base layer in the terrain");
      }
      if (a_data.TerrainAlphaLayerList.Count != 2)
      {
        throw new Exception("There must be 2 alpha layers in the terrain");
      }
      if (a_data.TerrainBlendLayerList.Count < 1)
      {
        throw new Exception("There must be 1 blend layer in the terrain");
      }

      // Get the layers
      Freeworld3D.TerrainBaseLayerData  baseLayer   = a_data.TerrainBaseLayerList[0];
      Freeworld3D.TerrainAlphaLayerData alphaLayer1 = a_data.TerrainAlphaLayerList[0];
      Freeworld3D.TerrainAlphaLayerData alphaLayer2 = a_data.TerrainAlphaLayerList[1];
      Freeworld3D.TerrainBlendLayerData blendLayer  = a_data.TerrainBlendLayerList[0];

      // Load the 3 color textures
      m_textureColor1 = Systems.Content.Load<Texture2D>(Asset.ResolveLevel(AssetType.AT_TERRAIN, a_levelName, baseLayer.TextureFilename));
      m_textureColor2 = Systems.Content.Load<Texture2D>(Asset.ResolveLevel(AssetType.AT_TERRAIN, a_levelName, alphaLayer1.TextureFilename));
      m_textureColor3 = Systems.Content.Load<Texture2D>(Asset.ResolveLevel(AssetType.AT_TERRAIN, a_levelName, alphaLayer2.TextureFilename));
      
      // Load the 2 alpha textures
      Terrain.RawData alphaData1 = Systems.Content.Load<Terrain.RawData>(Asset.ResolveLevel(AssetType.AT_TERRAIN, a_levelName, alphaLayer1.AlphaMapFilename));
      Terrain.RawData alphaData2 = Systems.Content.Load<Terrain.RawData>(Asset.ResolveLevel(AssetType.AT_TERRAIN, a_levelName, alphaLayer2.AlphaMapFilename));

      // Load the lightmap texture
      Texture2D lightMap = Systems.Content.Load<Texture2D>(Asset.ResolveLevel(AssetType.AT_TERRAIN, a_levelName, blendLayer.TextureFilename));

      // Ensure all textures are the same size
      if (alphaData1.Count != alphaData2.Count || alphaData1.Count != (lightMap.Width * lightMap.Height) || lightMap.Width != lightMap.Height)
      {
        throw new Exception("The terrain alpha layers and blend layer must be the same dimensions");
      }

      // Create the blend texture
      CreateBlendTexture(alphaData1, alphaData2, lightMap);

      // Get the world size of the terrain
      m_size = a_data.Terrain.Step * (float) (a_data.Terrain.Size - 1);

      // Calculate the texture wrapping factors
      m_U1 = baseLayer.U;
      m_V1 = baseLayer.V;
      m_U2 = alphaLayer1.U;
      m_V2 = alphaLayer1.V;
      m_U3 = alphaLayer2.U;
      m_V3 = alphaLayer2.V;
    }


    // ------------------------------------------------------------------------
    // Name: CreateBlendTexture
    // Desc: Create the fourth texture using a lightmap
    // Parm: Terrain.RawData a_blend1 - the first blend interpolant
    // Parm: Terrain.RawData a_blend2 - the second blend interpolant
    // Parm: Texture2D a_lightMap - the lightmap texture
    // ------------------------------------------------------------------------
    private void CreateBlendTexture(Terrain.RawData a_blend1, Terrain.RawData a_blend2, Texture2D a_lightMap)
    {
#if XBOX
      const int A1 = 3;
      const int A2 = 2;
      const int A3 = 1;
      const int LM = 0;
      const int LS = 3; // Lightmap source index
#else
      const int A1 = 0;
      const int A2 = 1;
      const int A3 = 2;
      const int LM = 3;
      const int LS = 0; // Lightmap source index
#endif

      // Get the lightmap data
      byte[] lightMapData = new byte[a_lightMap.Width * a_lightMap.Height * 4];
      a_lightMap.GetData<byte>(lightMapData);

      // Create an array to write the data into
      int count = a_blend1.Count;
      byte[] bytes = new byte[count * 4];

      // Create the blend texture data
      for (int i = 0; i < count; i++)
      {
        // Get the base index
        int index = i * 4;

        // Assign the second blend amount first
        bytes[index + A1] = a_blend2.Data[i];

        // Calculate the remaining available blend
        byte remainder = (byte) (255 - a_blend2.Data[i]);

        // Assign the second and third blends
        if (a_blend1.Data[i] <= remainder)
        {
          bytes[index + A2] = a_blend1.Data[i];
          bytes[index + A3] = (byte) (remainder - a_blend1.Data[i]);
        }
        else
        {
          bytes[index + A2] = remainder;
          bytes[index + A3] = 0;
        }

        // Copy the light map data
        bytes[index + LM] = lightMapData[index + LS];
      }
      // Create the blend texture
      m_textureBlend = new Texture2D(Systems.Graphics.GraphicsDevice, a_lightMap.Width, a_lightMap.Height, 1, TextureUsage.None, SurfaceFormat.Color);
      m_textureBlend.SetData<byte>(bytes);
    }


    // ------------------------------------------------------------------------
    // Name: CreateParameters
    // Desc: Create any effect file parameters - called after the effect is 
    //       loaded.
    // ------------------------------------------------------------------------
    protected override void CreateParameters()
    {
      // TODO: This implementation does not cache the parameters yet, it 
      // fetches them every time (performance warning).
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
      m_effect.Parameters["texture_Color1"].SetValue(m_textureColor1);
      m_effect.Parameters["texture_Color2"].SetValue(m_textureColor2);
      m_effect.Parameters["texture_Color3"].SetValue(m_textureColor3);
      m_effect.Parameters["texture_Blend"].SetValue(m_textureBlend);
      m_effect.Parameters["texture_Color1_U"].SetValue(m_U1 / m_size);
      m_effect.Parameters["texture_Color1_V"].SetValue(m_V1 / m_size);
      m_effect.Parameters["texture_Color2_U"].SetValue(m_U2 / m_size);
      m_effect.Parameters["texture_Color2_V"].SetValue(m_V2 / m_size);
      m_effect.Parameters["texture_Color3_U"].SetValue(m_U3 / m_size);
      m_effect.Parameters["texture_Color3_V"].SetValue(m_V3 / m_size);
      m_effect.Parameters["texture_Blend_U"].SetValue( 1.0f / m_size);
      m_effect.Parameters["texture_Blend_V"].SetValue( 1.0f / m_size);
    }


    public override void SetTransforms(Matrix a_worldMatrix)
    {
      m_effect.Parameters["matrix_WorldViewProj"].SetValue(a_worldMatrix * Systems.CameraSettings.ViewProjMatrix);
      m_effect.CommitChanges();
    }
    
    // ------------------------------------------------------------------------
    // Name: SetState
    // Desc: Called before the effect is started, allowing any changes in render
    //       state to be pushed.
    // ------------------------------------------------------------------------
    protected override void SetState()
    {
#if XBOX
      Systems.Graphics.GraphicsDevice.RenderState.CullMode = CullMode.CullClockwiseFace;
#else
      Systems.Graphics.GraphicsDevice.RenderState.CullMode = CullMode.CullCounterClockwiseFace;
#endif

      //Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = false;
      Systems.Graphics.GraphicsDevice.RenderState.DepthBufferEnable = true;
      Systems.Graphics.GraphicsDevice.RenderState.DepthBufferWriteEnable = true;
    }


    // ------------------------------------------------------------------------
    // Name: ResetState
    // Desc: Called after the effect has finished to return the render state to 
    //       it's default.
    // ------------------------------------------------------------------------
    protected override void ResetState()
    {
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

