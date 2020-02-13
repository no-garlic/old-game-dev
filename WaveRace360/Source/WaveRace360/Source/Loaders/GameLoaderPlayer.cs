
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameLoaderPlayer : GameLoader
  {
    private int m_step = 0;

    public GameLoaderPlayer(GameLevel a_level, String a_levelName, Freeworld3D.Content a_content)
    : base(a_level, a_levelName, a_content)
    {
    }


    public override void LoadNextItem()
    {
      if (m_step == 0)
      {
        GameObjectPlayer player = new GameObjectPlayer("Player", m_loadContent);
        m_step++;
      }
      else
      {
        GameObjectCamera camera = new GameObjectCamera("Camera", m_loadContent);
        SetLoaded();
      }
    }


  }
}


// -- EOF
