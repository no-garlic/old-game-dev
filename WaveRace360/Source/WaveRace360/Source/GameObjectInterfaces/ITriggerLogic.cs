
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using JigLibX.Collision;




namespace WaveRace360
{
  public class ITriggerLogic : GameObjectInterface
  {
    public ITriggerLogic(GameObject a_object)
      : base (GameObjectInterfaceTypeId.GOI_LOGIC, a_object)
    {
    }
    

    public override void Update(float a_frameTime)
    {
    }


    public void OnTrigger(CollisionSkin a_otherSkin)
    {
      GameObject triggerObject = Object;
      GameObject sourceObject = GameObjectManager.Instance.FindObject<GameObject>(a_otherSkin.LinkedObjectName);

      if (sourceObject.GetType().IsSubclassOf(typeof(GameObjectActor)))
      {
        IActorLogic iLogic = sourceObject.GetInterface<IActorLogic>(GameObjectInterfaceTypeId.GOI_LOGIC);
        if (iLogic != null)
        {
          iLogic.OnTrigger(Object as GameObjectTrigger);
        }
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
