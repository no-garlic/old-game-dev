
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameLoaderWater : GameLoader
  {
    public GameLoaderWater(GameLevel a_level, String a_levelName, Freeworld3D.Content a_content)
    : base(a_level, a_levelName, a_content)
    {
    }


    public override void LoadNextItem()
    {
      WaterRender.CreationParams waterParams = new WaterRender.CreationParams();
      WaterRender.SetDefaultCreationParams(ref waterParams);

      waterParams.WaterColor = new Vector4(0.1f, 0.55f, 0.8f, 0.875f);

      waterParams.Waves[0] = new WaterRender.Wave(1.0f, 0.15f, 23.0f, new Vector2(-1.0f, 0.19f));
      waterParams.Waves[1] = new WaterRender.Wave(1.3f, 0.25f, 8.0f, new Vector2(-1.0f, 0.13f));
      waterParams.Waves[2] = new WaterRender.Wave(0.5f, 0.15f, 13.0f, new Vector2(-1.0f, 0.79f));
      waterParams.Waves[3] = new WaterRender.Wave(1.5f, 0.35f, 11.0f, new Vector2(0.13f, -1.0f));

      waterParams.BumpStrength = 0.5f;
      waterParams.Height = 4.75f;
      waterParams.TextureSpeed = 0.45f;
      waterParams.TextureStretch = 12.0f;

      GameObjectWater waterRender = new GameObjectWater("Water", waterParams);

      SetLoaded();
    }
    

  }
}


// -- EOF
