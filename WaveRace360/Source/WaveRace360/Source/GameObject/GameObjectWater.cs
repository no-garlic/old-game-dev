
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectWater : GameObject
  {
    public WaterRender Water { get { return m_water; } }
    private WaterRender m_water;

    public GameObjectWater(String a_name, WaterRender.CreationParams a_params)
      : base (GameObjectTypeId.GOT_WATER, a_name)
    {
      m_water = new WaterRender();
      m_water.Create(a_params);
      
      AddInterface(new IWaterPhysics(this));
      AddInterface(new IWaterRender(this, m_water));
    }

  }
}


// -- EOF
