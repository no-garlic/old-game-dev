
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  public class IModelPhysics : GameObjectInterface
  {
    public IModelPhysics(GameObject a_object)
      : base (GameObjectInterfaceTypeId.GOI_PHYSICS, a_object)
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
