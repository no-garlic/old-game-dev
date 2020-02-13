
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  public abstract class IActorLogic : GameObjectInterface
  {
    public IActorLogic(GameObject a_object)
      : base (GameObjectInterfaceTypeId.GOI_LOGIC, a_object)
    {
    }
    

    public virtual void OnTrigger(GameObjectTrigger a_triggerObject)
    {
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
