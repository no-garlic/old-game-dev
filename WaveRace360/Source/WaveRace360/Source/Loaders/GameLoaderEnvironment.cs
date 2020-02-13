
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameLoaderEnvironment : GameLoader
  {
    public GameLoaderEnvironment(GameLevel a_level, String a_levelName, Freeworld3D.Content a_content)
    : base(a_level, a_levelName, a_content)
    {
    }


    public override void LoadNextItem()
    {
      // Systems.Env.LightDirection = m_loadContent.Light.LightDirection;
      Systems.Env.LightDirection = new Vector3(0.5f, -0.75f, 0.25f);
      Systems.Env.LightDirection.Normalize();
      SetLoaded();
    }


  }
}


// -- EOF
