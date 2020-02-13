
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameLoaderEntities : GameLoader
  {
    public GameLoaderEntities(GameLevel a_level, String a_levelName, Freeworld3D.Content a_content)
    : base(a_level, a_levelName, a_content)
    {
    }


    public override void LoadNextItem()
    {
      EntityManager.Instance.Load(m_loadContent);
      SetLoaded();
    }


  }
}


// -- EOF
