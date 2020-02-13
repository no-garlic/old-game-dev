// ----------------------------------------------------------------------------
// File: PhysicsBodyBox.cs
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
  // Name: PhysicsBodyBox
  // Desc: A box rigid body
  // --------------------------------------------------------------------------
  public class PhysicsBodyBox : PhysicsBody
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public Box              Box         { get { return m_box; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    protected Vector3       m_position;
    protected Matrix        m_orientation;
    protected Box           m_box;


    // ------------------------------------------------------------------------
    // Name: PhysicsBodyBox
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public PhysicsBodyBox(Vector3 a_scale, Matrix a_orientation, Vector3 a_position, MaterialProperties a_material)
      : base(a_material)
    {
      m_body = new Body();
      m_collision = new CollisionSkin(m_body);

      m_position = a_position;
      m_orientation = a_orientation;
      m_scale = a_scale;

      m_box = new Box(-0.5f * m_scale, m_orientation, m_scale);

      m_collision.AddPrimitive(m_box, (int) MaterialTable.MaterialID.UserDefined, m_materialProperties);
      m_body.CollisionSkin = m_collision;

      Vector3 centerOfMass = SetMass(1.0f);

      m_body.MoveTo(m_position, Matrix.Identity);
      m_collision.ApplyLocalTransform(new Transform(-centerOfMass, Matrix.Identity));
      m_body.EnableBody();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
