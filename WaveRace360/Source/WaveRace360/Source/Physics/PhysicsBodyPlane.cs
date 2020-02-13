// ----------------------------------------------------------------------------
// File: PhysicsBodyPlane.cs
// Desc: A Plane rigid body
// Auth: Michael Petrou
// (C) Copyright: 2009
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;

using JigLibX.Math;
using JigLibX.Physics;
using JigLibX.Geometry;
using JigLibX.Collision;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: PhysicsBodyPlane
  // Desc: A Plane rigid body
  // --------------------------------------------------------------------------
  public class PhysicsBodyPlane : PhysicsBody
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public float Height { get { return m_height; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private float m_height;
    private JigLibX.Geometry.Plane m_plane;


    // ------------------------------------------------------------------------
    // Name: PhysicsBodyPlane
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public PhysicsBodyPlane(float a_height, MaterialProperties a_material)
      : base(a_material)
    {
      m_height = a_height;

      m_body = new Body();
      m_collision = new CollisionSkin(null);

      m_plane = new JigLibX.Geometry.Plane(Vector3.Up, -a_height);
      m_collision.AddPrimitive(m_plane, (int) MaterialTable.MaterialID.UserDefined, m_materialProperties);

      PhysicsSystem.CurrentPhysicsSystem.CollisionSystem.AddCollisionSkin(m_collision);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
