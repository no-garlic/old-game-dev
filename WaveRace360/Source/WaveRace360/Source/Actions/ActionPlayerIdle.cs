
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class ActionPlayerIdle : Action
  {
    
    public ActionPlayerIdle() : base ("ActionPlayerIdle")
    {
    }

    
    public override void Begin()
    {
    }


    public override void Complete()
    {
    }


    public override void Update(float a_frameTime)
    {
      IPlayerPhysics iPlayerPhysics = Object.GetInterface<IPlayerPhysics>(GameObjectInterfaceTypeId.GOI_PHYSICS);

      iPlayerPhysics.Throttle = 0.0f;
      iPlayerPhysics.Steering = 0.0f;

      Vector2 thumbstickL = Systems.GamePad.State.ThumbSticks.Left;

      if (thumbstickL.Length() > 0.05f)
      {
        Object.ChangeAction<ActionPlayerDrive>();
        return;
      }
    }

  
    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
