// ----------------------------------------------------------------------------
// File: EntityTypes.cs
// Desc: A generic entity used to supply a named CourseMarker
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: EntityCourseMarker 
  // Desc: A generic entity used to supply a named CourseMarker
  // --------------------------------------------------------------------------
  public class EntityCourseMarker : Entity
  {
    // ------------------------------------------------------------------------
    // Name: EntityCourseMarker
    // Desc: Constructor
    // Parm: Freeworld3D.EntityData a_data - the data to extract the entity
    //       properties from.
    // ------------------------------------------------------------------------
    public EntityCourseMarker(Freeworld3D.EntityData a_data) : base(a_data)
    {
    }
  }


  //
  // --------------------------------------------------------------------------
}


// -- EOF

