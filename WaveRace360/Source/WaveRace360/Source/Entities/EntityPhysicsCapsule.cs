// ----------------------------------------------------------------------------
// File: EntityTypes.cs
// Desc: A generic entity used to supply a named PhysicsCapsule
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: EntityPhysicsBox 
  // Desc: A generic entity used to supply a named PhysicsCapsule
  // --------------------------------------------------------------------------
  public class EntityPhysicsCapsule : Entity
  {
    // ------------------------------------------------------------------------
    // Name: EntityPhysicsCapsule
    // Desc: Constructor
    // Parm: Freeworld3D.EntityData a_data - the data to extract the entity
    //       properties from.
    // ------------------------------------------------------------------------
    public EntityPhysicsCapsule(Freeworld3D.EntityData a_data) : base(a_data)
    {
    }
  }


  //
  // --------------------------------------------------------------------------
}


// -- EOF

