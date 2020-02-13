
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class ITerrainRender : GameObjectInterface
  {
    private TerrainRender m_terrain;


    public ITerrainRender(GameObject a_object, TerrainRender a_terrain)
      : base (GameObjectInterfaceTypeId.GOI_RENDER, a_object)
    {
      m_terrain = a_terrain;
    }
    

    public override void Update(float a_frameTime)
    {
      m_terrain.AddForRender();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
