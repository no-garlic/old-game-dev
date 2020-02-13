
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectTrigger : GameObject
  {
    public GameObjectTrigger(String a_name)
      : base (GameObjectTypeId.GOT_TRIGGER, a_name)
    {
      AddInterface(new ITriggerLogic(this));
      AddInterface(new ITriggerPhysics(this));
    }

  }
}


// -- EOF
