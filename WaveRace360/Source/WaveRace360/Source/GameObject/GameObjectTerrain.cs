
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectTerrain : GameObject
  {
    public TerrainRender Terrain { get { return m_terrain; } }
    private TerrainRender m_terrain;
    
    public GameObjectTerrain(String a_name, Freeworld3D.Content a_terrainConfig, String a_levelName)
      : base (GameObjectTypeId.GOT_TERRAIN, a_name)
    {
      m_terrain = new TerrainRender();
      m_terrain.Load(a_terrainConfig, a_levelName);

      AddInterface(new ITerrainRender(this, m_terrain));
    }

  }
}


// -- EOF
