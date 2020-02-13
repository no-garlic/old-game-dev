
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectBiped : GameObjectActor
  {

    
    public GameObjectBiped(String a_name)
      : base (GameObjectTypeId.GOT_BIPED, a_name)
    {
      AddInterface(new IBipedLogic(this));
      AddInterface(new IBipedPhysics(this));
      AddInterface(new IBipedRender(this));
    }

  
  }
}


// -- EOF
