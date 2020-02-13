
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectPlayer : GameObject
  {
    public GameObjectPlayer(String a_name, Freeworld3D.Content a_content)
      : base (GameObjectTypeId.GOT_PLAYER, a_name)
    {
      AddInterface(new IPlayerLogic(this));
      AddInterface(new IPlayerPhysics(this, a_content));
      AddInterface(new IPlayerRender(this));

      ChangeAction<ActionPlayerDrive>();
    }

  }
}


// -- EOF
