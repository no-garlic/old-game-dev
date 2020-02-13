// ----------------------------------------------------------------------------
// File: EntityTypes.cs
// Desc: A generic entity used to supply a named PhysicsSphere
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: EntityPhysicsSphere 
  // Desc: A generic entity used to supply a named PhysicsSphere
  // --------------------------------------------------------------------------
  public class EntityPhysicsSphere : Entity
  {
    // ------------------------------------------------------------------------
    // Name: EntityPhysicsSphere
    // Desc: Constructor
    // Parm: Freeworld3D.EntityData a_data - the data to extract the entity
    //       properties from.
    // ------------------------------------------------------------------------
    public EntityPhysicsSphere(Freeworld3D.EntityData a_data) : base(a_data)
    {
    }
  }


  //
  // --------------------------------------------------------------------------
}


// -- EOF

