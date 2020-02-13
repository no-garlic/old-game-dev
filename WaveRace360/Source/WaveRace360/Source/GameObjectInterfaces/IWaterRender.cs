
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class IWaterRender : GameObjectInterface
  {
    private WaterRender m_water;


    public IWaterRender(GameObject a_object, WaterRender a_water)
      : base (GameObjectInterfaceTypeId.GOI_RENDER, a_object)
    {
      m_water = a_water;
    }
    

    public override void Update(float a_frameTime)
    {
      m_water.AddForRender();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
