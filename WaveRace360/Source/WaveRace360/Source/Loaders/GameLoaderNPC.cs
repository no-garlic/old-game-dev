
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameLoaderNPC : GameLoader
  {
    public GameLoaderNPC(GameLevel a_level, String a_levelName, Freeworld3D.Content a_content)
    : base(a_level, a_levelName, a_content)
    {
    }


    public override void LoadNextItem()
    {
      SetLoaded();
    }
    

  }
}


// -- EOF
