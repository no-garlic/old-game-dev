
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class ActionPlayerDrive : Action
  {
    
    public ActionPlayerDrive() : base ("ActionPlayerDrive")
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

      Vector2 thumbstickL = Systems.GamePad.State.ThumbSticks.Left;
      Vector2 thumbstickR = Systems.GamePad.State.ThumbSticks.Right;
      
      if (thumbstickL.Length() > 0.0f)
      {
        iPlayerPhysics.Steering = thumbstickL.X;
        iPlayerPhysics.Throttle = thumbstickL.Length();
      }
      else
      {
        Object.ChangeAction<ActionPlayerIdle>();
        return;
      }
    }

  
    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
