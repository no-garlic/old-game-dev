
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameLoaderTerrain : GameLoader
  {
    public GameLoaderTerrain(GameLevel a_level, String a_levelName, Freeworld3D.Content a_content)
    : base(a_level, a_levelName, a_content)
    {
    }


    public override void LoadNextItem()
    {
      GameObjectTerrain terrainRender = new GameObjectTerrain("Terrain", m_loadContent, m_levelName);
      SetLoaded();
    }
    

  }
}


// -- EOF
