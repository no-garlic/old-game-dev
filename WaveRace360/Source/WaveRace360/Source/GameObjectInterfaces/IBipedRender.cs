
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  public class IBipedRender : GameObjectInterface
  {
    public IBipedRender(GameObject a_object)
      : base (GameObjectInterfaceTypeId.GOI_RENDER, a_object)
    {
    }
    

    public override void Update(float a_frameTime)
    {
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
