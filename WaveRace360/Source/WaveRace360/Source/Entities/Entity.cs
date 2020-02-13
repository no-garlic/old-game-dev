// ----------------------------------------------------------------------------
// File: Entity.cs
// Desc: Base class for all entities
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: Entity
  // Desc: Base class for all entities
  // --------------------------------------------------------------------------
  public class Entity
  {
    // ------------------------------------------------------------------------
    // Members
    // ------------------------------------------------------------------------
    public String   Name;       // The entity name
    public Matrix   Transform;  // The entity transform


    // ------------------------------------------------------------------------
    // Name: Entity
    // Desc: Constructor
    // Parm: Freeworld3D.EntityData a_data - the data to extract teh entities 
    //       properties from
    // ------------------------------------------------------------------------
    public Entity(Freeworld3D.EntityData a_data)
    {
      Name      = a_data.Name;
      Transform = a_data.Transform;
    }
  }


  //
  // --------------------------------------------------------------------------
}


// -- EOF

