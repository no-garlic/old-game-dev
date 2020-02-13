// ----------------------------------------------------------------------------
// File: PhysicsBodySphere.cs
// Desc: A box rigid body
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
  // Name: PhysicsBodySphere
  // Desc: A box rigid body
  // --------------------------------------------------------------------------
  public class PhysicsBodySphere : PhysicsBody
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public Sphere            Sphere         { get { return m_sphere; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    protected Vector3       m_position;
    protected Sphere        m_sphere;


    // ------------------------------------------------------------------------
    // Name: PhysicsBodySphere
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public PhysicsBodySphere(float a_radius, Vector3 a_position, MaterialProperties a_material)
      : base(a_material)
    {
      m_body = new Body();
      m_collision = new CollisionSkin(m_body);

      m_position = a_position;
      m_scale = Vector3.One * a_radius;

      m_sphere = new Sphere(Vector3.Zero, a_radius);

      m_collision.AddPrimitive(m_sphere, (int) MaterialTable.MaterialID.UserDefined, m_materialProperties);
      m_body.CollisionSkin = m_collision;

      Vector3 centerOfMass = SetMass(10.0f);
      m_body.MoveTo(m_position + centerOfMass, Matrix.Identity);
      m_body.EnableBody();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
