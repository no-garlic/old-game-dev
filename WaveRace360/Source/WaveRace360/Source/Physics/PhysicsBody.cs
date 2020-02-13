// ----------------------------------------------------------------------------
// File: PhysicsBody.cs
// Desc: The rigid body base class
// Auth: Michael Petrou
// (C) Copyright: 2009
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using JigLibX.Math;
using JigLibX.Physics;
using JigLibX.Collision;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: PhysicsBody
  // Desc: The rigid body base class
  // --------------------------------------------------------------------------
  public abstract class PhysicsBody : IRender
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public Vector3            Scale     { get { return m_scale; } }
    public CollisionSkin      Skin      { get { return m_collision; } }
    public Body               Body      { get { return m_body; } }
    public MaterialProperties Material  { get { return m_materialProperties; } }


    // ------------------------------------------------------------------------
    // Protected members
    // ------------------------------------------------------------------------
    protected Body                  m_body;
    protected CollisionSkin         m_collision;
    protected Vector3               m_scale;
    protected VertexPositionColor[] m_renderData;
    protected MaterialProperties    m_materialProperties;

    
    // ------------------------------------------------------------------------
    // Protected members
    // ------------------------------------------------------------------------
    private static List<PhysicsBody> s_debugRenderList;


    // ------------------------------------------------------------------------
    // Name: PhysicsBody
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public PhysicsBody(MaterialProperties a_material)
    {
      if (s_debugRenderList == null)
      {
        s_debugRenderList = new List<PhysicsBody>();
      }
      s_debugRenderList.Add(this);

      m_materialProperties = new MaterialProperties(a_material.Elasticity, a_material.StaticRoughness, a_material.DynamicRoughness);
      m_scale = Vector3.One;
    }


    // ------------------------------------------------------------------------
    // Name: PhysicsBody
    // Desc: Destructor
    // ------------------------------------------------------------------------
    ~PhysicsBody()
    {
      s_debugRenderList.Remove(this);
    }


    // ------------------------------------------------------------------------
    // Name: SetMass
    // Desc: Set the mass of the body
    // Parm: a_mass - The mass of the body
    // Retn: The center of mass
    // ------------------------------------------------------------------------
    protected Vector3 SetMass(float a_mass)
    {
      JigLibX.Geometry.PrimitiveProperties primitiveProperties = new JigLibX.Geometry.PrimitiveProperties(
        JigLibX.Geometry.PrimitiveProperties.MassDistributionEnum.Solid, 
        JigLibX.Geometry.PrimitiveProperties.MassTypeEnum.Density, 
        a_mass);

      float outMass; 
      Vector3 outCenterOfMass;
      Matrix outInertiaTensor;
      Matrix outInertiaTensorCenterOfMass;

      m_collision.GetMassProperties(
        primitiveProperties, 
        out outMass, 
        out outCenterOfMass, 
        out outInertiaTensor, 
        out outInertiaTensorCenterOfMass);

      m_body.BodyInertia = outInertiaTensorCenterOfMass;
      m_body.Mass = outMass;

      return outCenterOfMass;
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the object.
    // ------------------------------------------------------------------------
    public override void Render(Material a_material, Matrix a_worldMatrix)
    {
      if (m_body.CollisionSkin != null)
      {
        a_material.SetTransforms(a_worldMatrix);

        VertexPositionColor[] wireframeData = m_body.GetBodyWireframe();

        if (m_renderData == null)
        {
          m_renderData = new VertexPositionColor[wireframeData.Length];
        }

        wireframeData.CopyTo(m_renderData, 0);
        m_body.TransformWireframe(m_renderData);

        Systems.Graphics.GraphicsDevice.VertexDeclaration = new VertexDeclaration(Systems.Graphics.GraphicsDevice, 
          VertexPositionColor.VertexElements);

        Systems.Graphics.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>(
          PrimitiveType.LineStrip, m_renderData, 0, m_renderData.Length - 1);
      }
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render all physics bodies
    // ------------------------------------------------------------------------
    public static void DebugRender(Material a_material)
    {
      foreach (PhysicsBody body in s_debugRenderList)
      {
        a_material.AddForRender(body, RenderPriority.Debug, Matrix.Identity, CullMode.None);
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

