
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class ISkyRender : GameObjectInterface
  {
    private SkyRender m_sky;


    public ISkyRender(GameObject a_object, SkyRender a_sky)
      : base (GameObjectInterfaceTypeId.GOI_RENDER, a_object)
    {
      m_sky = a_sky;
    }
    

    public override void Update(float a_frameTime)
    {
      m_sky.AddForRender();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
