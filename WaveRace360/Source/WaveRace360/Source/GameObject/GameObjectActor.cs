
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public abstract class GameObjectActor : GameObject
  {
    public GameObjectActor(GameObjectTypeId a_typeId, String a_name)
      : base (a_typeId, a_name)
    {
    }


  }
}


// -- EOF
