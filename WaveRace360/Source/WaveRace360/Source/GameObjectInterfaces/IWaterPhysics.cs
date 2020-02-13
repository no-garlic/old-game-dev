// ----------------------------------------------------------------------------
// File: IWaterPhysics.cs
// Desc: Creates and manages the physics for the water
// Auth: Michael Petrou
// (C) Copyright: 2009
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;

using JigLibX.Collision;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: IWaterPhysics
  // Desc: Creates and manages the physics for the water
  // --------------------------------------------------------------------------
  public class IWaterPhysics : GameObjectInterface
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private PhysicsBodyPlane m_water;


    // ------------------------------------------------------------------------
    // Name: IWaterPhysics
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public IWaterPhysics(GameObject a_object)
      : base (GameObjectInterfaceTypeId.GOI_PHYSICS, a_object)
    {
      MaterialProperties waterMaterial = new MaterialProperties(0.0f, 0.5f, 0.3f);
      m_water = new PhysicsBodyPlane(5.0f, waterMaterial);
      m_water.Skin.LinkedObjectName = Object.Name;
    }


    public override void Update(float a_frameTime)
    {
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

