
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using JigLibX.Collision;




namespace WaveRace360
{
  public class ITriggerPhysics : GameObjectInterface
  {
    PhysicsBody m_body;
    
    public ITriggerPhysics(GameObject a_object)
      : base (GameObjectInterfaceTypeId.GOI_PHYSICS, a_object)
    {
      m_body = new PhysicsBodyBox(Vector3.One, Matrix.Identity, Vector3.Zero, Systems.MaterialTable.GetMaterialProperties(0));
      m_body.Skin.LinkedObjectName = Object.Name;
      m_body.Skin.callbackFn += this.TriggerCallback;
    }
    

    public override void Update(float a_frameTime)
    {
    }


    public bool TriggerCallback(CollisionSkin a_skin0, CollisionSkin a_skin1)
    {

      if (a_skin0.LinkedObjectName == Object.Name)
      {
        ITriggerLogic iTriggerLogic = Object.GetInterface<ITriggerLogic>(GameObjectInterfaceTypeId.GOI_LOGIC);
        iTriggerLogic.OnTrigger(a_skin1);
      }
      else if (a_skin1.LinkedObjectName == Object.Name)
      {
        ITriggerLogic iTriggerLogic = Object.GetInterface<ITriggerLogic>(GameObjectInterfaceTypeId.GOI_LOGIC);
        iTriggerLogic.OnTrigger(a_skin0);
      }

      return false;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
