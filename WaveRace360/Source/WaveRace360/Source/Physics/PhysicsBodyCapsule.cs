// ----------------------------------------------------------------------------
// File: PhysicsBodyCapsule.cs
// Desc: A Capsule rigid body
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
  // Name: PhysicsBodyCapsule
  // Desc: A Capsule rigid body
  // --------------------------------------------------------------------------
  public class PhysicsBodyCapsule : PhysicsBody
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public Capsule              Capsule         { get { return m_capsule; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    protected Vector3       m_position;
    protected Matrix        m_orientation;
    protected float         m_radius;
    protected float         m_length;
    protected Capsule       m_capsule;


    // ------------------------------------------------------------------------
    // Name: PhysicsBodyCapsule
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public PhysicsBodyCapsule(float a_radius, float a_length, Matrix a_orientation, Vector3 a_position, MaterialProperties a_material)
      : base(a_material)
    {
      m_body = new Body();
      m_collision = new CollisionSkin(m_body);

      m_position = a_position;
      m_orientation = a_orientation;
      m_radius = a_radius;
      m_length = a_length;

      m_capsule = new Capsule(Vector3.Transform(new Vector3(-0.5f,0,0), a_orientation), a_orientation, a_radius, a_length);

      m_collision.AddPrimitive(m_capsule, (int) MaterialTable.MaterialID.UserDefined, m_materialProperties);
      m_body.CollisionSkin = m_collision;

      Vector3 centerOfMass = SetMass(10.0f);

      m_body.MoveTo(m_position + centerOfMass, Matrix.Identity);
      m_collision.ApplyLocalTransform(new Transform(-centerOfMass, Matrix.Identity));
      m_body.EnableBody();

      m_scale = new Vector3(a_radius, a_radius, a_length * 0.5f);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
