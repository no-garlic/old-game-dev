// ----------------------------------------------------------------------------
// File: EntityTypes.cs
// Desc: A generic entity used to supply a named Waypoint
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: EntityWaypoint 
  // Desc: A generic entity used to supply a named Waypoint
  // --------------------------------------------------------------------------
  public class EntityWaypoint : Entity
  {
    // ------------------------------------------------------------------------
    // Name: EntityWaypoint
    // Desc: Constructor
    // Parm: Freeworld3D.EntityData a_data - the data to extract the entity
    //       properties from.
    // ------------------------------------------------------------------------
    public EntityWaypoint(Freeworld3D.EntityData a_data) : base(a_data)
    {
    }
  }


  //
  // --------------------------------------------------------------------------
}


// -- EOF

