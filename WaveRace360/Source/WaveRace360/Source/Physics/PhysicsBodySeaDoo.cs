// ----------------------------------------------------------------------------
// File: PhysicsBodySeaDoo.cs
// Desc: 
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
  // Name: PhysicsBodySeaDoo
  // Desc: 
  // --------------------------------------------------------------------------
  public class PhysicsBodySeaDoo : PhysicsBodyBox
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public float Throttle { get { return m_throttle; } set { m_throttle = value; } }
    public float Steering { get { return m_steering; } set { m_steering = value; } }
    public Matrix RenderMatrix { get { return m_renderMatrix; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private WaterMesh     m_water;
    private bool          m_firstUpdate;
    private Matrix        m_renderMatrix;
    private float         m_renderHeightOffset;
    private Vector3[]     m_corners;
    private const int     m_numCorners = 4;
    private float         m_volume;

    // Cached data each update
    private Vector3       m_bodyCenter;
    private Matrix        m_bodyRotation;
    private Vector3       m_bodyVelocity;
    private float         m_linearVelocity;
    private float         m_speedFactor;

    // Motion parameters for driving
    private float         m_throttle;
    private float         m_maxSpeed;
    private float         m_accelerationScale;
    private float         m_decelerationScale;

    // Pitch / roll parameters for stability
    private float         m_maxAngularVelocityAtIdle;
    private float         m_maxAngularVelocityAtMaxSpeed;
    private float         m_maxRollAtIdle;
    private float         m_maxRollAtMaxSpeed;
    private float         m_maxPitchAtIdle;
    private float         m_maxPitchAtMaxSpeed;

    // Turning parameters
    private float         m_steering;
    private float         m_steeringAngle;
    private float         m_lean;
    private float         m_leanScale;
    private float         m_turnScale;

    // Spring Filters
    private FilterSpring  m_positionFilter;
    private float         m_positionFilterSpring;
    private float         m_positionFilterDrag;
    private FilterSpring  m_rollFilter;
    private float         m_rollFilterSpring;
    private float         m_rollFilterDrag;
    private FilterSpring  m_pitchFilter;
    private float         m_pitchFilterSpring;
    private float         m_pitchFilterDrag;

    // Average filters
    private FilterAverage m_steeringFilter;
    private FilterAverage m_leanFilter;

    
    // ------------------------------------------------------------------------
    // Name: PhysicsBodySeaDoo
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public PhysicsBodySeaDoo(WaterMesh a_water, Vector3 a_scale, Matrix a_orientation, Vector3 a_position, MaterialProperties a_material) : 
      base(a_scale, a_orientation, a_position, a_material)
    {
      m_water = a_water;
      m_firstUpdate = true;

      // The height offset when geenrating the render matrix
      m_renderHeightOffset = 0.4f;

      // Calculate the volume of the box
      m_volume = a_scale.X * a_scale.Y * a_scale.Z;
      
      // Calculate the corner points, and set the Y to be the center point along the axis of the box
      m_corners = new Vector3[m_numCorners];
      m_corners[0] = new Vector3(a_scale.X *  0.5f, a_scale.Y * -0.5f, a_scale.Z *  0.5f);
      m_corners[1] = new Vector3(a_scale.X *  0.5f, a_scale.Y * -0.5f, a_scale.Z * -0.5f);
      m_corners[2] = new Vector3(a_scale.X * -0.5f, a_scale.Y * -0.5f, a_scale.Z * -0.5f);
      m_corners[3] = new Vector3(a_scale.X * -0.5f, a_scale.Y * -0.5f, a_scale.Z *  0.5f);

      // Motion parameters for driving
      m_maxSpeed                        = 60.0f;
      m_accelerationScale               = 3.0f;
      m_decelerationScale               = 1.15f;

      // Pitch parameters for stability
      m_maxAngularVelocityAtIdle        = MathHelper.ToRadians(10.0f);
      m_maxAngularVelocityAtMaxSpeed    = MathHelper.ToRadians(4.0f);
      m_maxRollAtIdle                   = MathHelper.ToRadians(25.0f);
      m_maxRollAtMaxSpeed               = MathHelper.ToRadians(10.0f);
      m_maxPitchAtIdle                  = MathHelper.ToRadians(30.0f);
      m_maxPitchAtMaxSpeed              = MathHelper.ToRadians(20.0f);

      // Turning parameters
      m_turnScale                       = 1.8f;
      m_leanScale                       = 0.1f;

      // Springs
      m_positionFilterSpring            = 75.0f;
      m_positionFilterDrag              = 4.0f;
      m_positionFilter                  = new FilterSpring(m_positionFilterSpring, m_positionFilterDrag);

      m_rollFilterSpring                = 5.0f;
      m_rollFilterDrag                  = 0.5f;
      m_rollFilter                      = new FilterSpring(m_rollFilterSpring, m_rollFilterDrag);

      m_pitchFilterSpring               = 5.0f;
      m_pitchFilterDrag                 = 0.5f;
      m_pitchFilter                     = new FilterSpring(m_pitchFilterSpring, m_pitchFilterDrag);

      m_steeringFilter                  = new FilterAverage(35);
      m_leanFilter                      = new FilterAverage(35);
    }


    public void Update(float a_frameTime)
    {
      // Pre-cache values needed by multiple functions during the update
      m_bodyCenter = m_body.Position;
      m_bodyRotation = m_body.Orientation;
      m_bodyVelocity = m_body.Velocity;
      Vector2 linearVelocity = new Vector2(m_bodyVelocity.X, m_bodyVelocity.Z);
      m_linearVelocity = linearVelocity.Length();
      m_speedFactor = MathHelper.Clamp(m_linearVelocity / m_maxSpeed, 0.0f, m_maxSpeed);
      
      // Update the motion / power
      UpdateThrottleAndDrag(a_frameTime);

      // Clamp the linear and angular velocity
      ClampVelocity(a_frameTime);

      // Clamp the roll and pitch
      ClampOrientation(a_frameTime);

      // Update the render matrix
      UpdateRenderMatrix(a_frameTime);
      m_firstUpdate = false;
    }


    private void UpdateThrottleAndDrag(float a_frameTime)
    {
      Vector3 impulse = new Vector3(0.0f, 0.0f, m_throttle * m_accelerationScale * m_volume);
      m_body.ApplyBodyImpulse(impulse);

      float decelerationFactor = (1.0f - m_throttle) * m_decelerationScale * a_frameTime;
      m_body.Velocity += new Vector3(m_body.Velocity.X * -decelerationFactor, 0.0f, m_body.Velocity.Z * -decelerationFactor);

      float angle = -m_steering * a_frameTime * m_speedFactor * m_turnScale;

      m_steeringAngle = m_steeringFilter.Update(a_frameTime, m_steeringAngle, angle);

      Matrix orientation = m_body.Orientation;
      Matrix rotation = Matrix.CreateFromYawPitchRoll(m_steeringAngle, 0.0f, 0.0f);
      m_body.Orientation = orientation * rotation;     
    }
    

    private void ClampVelocity(float a_frameTime)
    {
      float velocitySquared = m_body.Velocity.LengthSquared();
      if (velocitySquared > m_maxSpeed * m_maxSpeed)
      {
        m_body.Velocity = Vector3.Normalize(m_body.Velocity);
        m_body.Velocity *= m_maxSpeed;
      }

      if (velocitySquared > 0.1f)
      {
        float speed = m_body.Velocity.Length();
        Vector3 forward = m_body.Orientation.Forward;
        forward *= speed;
        forward.Y = m_body.Velocity.Y;
        forward.X = -forward.X;
        forward.Z = -forward.Z;
        m_body.Velocity = forward;
      }

      Matrix matrix = m_body.Orientation;
      Matrix invMatrix = Matrix.Invert(m_body.Orientation);

      Vector3 angularVelocityWorld = m_body.AngularVelocity;
      Vector3 angularVelocityLocal = Vector3.Transform(angularVelocityWorld, invMatrix);

      float maxAngularVelocity = MathHelper.Lerp(m_maxAngularVelocityAtIdle, m_maxAngularVelocityAtMaxSpeed, m_speedFactor);

      float yaw = angularVelocityLocal.Y;
      float pitch = MathHelper.Clamp(angularVelocityLocal.X, -maxAngularVelocity, maxAngularVelocity);
      float roll = MathHelper.Clamp(angularVelocityLocal.Z, -maxAngularVelocity, maxAngularVelocity);

      if (m_speedFactor == 0.0f)
      {
        yaw = 0.0f;
      }
      else
      {
        yaw = m_steeringAngle * a_frameTime;
      }

      angularVelocityLocal = new Vector3(pitch, yaw, roll);
      angularVelocityWorld = Vector3.Transform(angularVelocityLocal, matrix);

      m_body.AngularVelocity = angularVelocityWorld;
    }


    private void ClampOrientation(float a_frameTime)
    {
      Matrix orientation = m_body.Orientation;

      float maxRoll = MathHelper.Lerp(m_maxRollAtIdle, m_maxRollAtMaxSpeed, m_speedFactor);
      float maxPitch = MathHelper.Lerp(m_maxPitchAtIdle, m_maxPitchAtMaxSpeed, m_speedFactor);

      float roll = (float) Math.Asin((float) orientation.Right.Y);
      roll = MathHelper.Clamp(roll, -maxRoll, maxRoll);
      roll = (float) Math.Sin((float) roll);

      orientation.Right = new Vector3(orientation.Right.X, roll, orientation.Right.Z);
      orientation.Right.Normalize();
      
      float pitch = (float) Math.Asin((float) orientation.Forward.Y);
      pitch = MathHelper.Clamp(pitch, -maxPitch, maxPitch);
      pitch = (float) Math.Sin((float) pitch);

      orientation.Forward = Vector3.Cross(orientation.Up, orientation.Right);
      orientation.Forward = new Vector3(orientation.Forward.X, pitch, orientation.Forward.Z);
      orientation.Forward.Normalize();

      orientation.Up = Vector3.Cross(orientation.Right, orientation.Forward);
      orientation.Up.Normalize();

      m_body.Orientation = orientation;
    }


    private void UpdateRenderMatrix(float a_frameTime)
    {
      Vector3 position = Body.Position;

      float averageHeight = 0.0f;
      Vector3 averageNormal = new Vector3();

      for (int i = 0; i < m_numCorners; i++)
      {
        // Get the corner in world space
        Vector3 cornerWorldSpace = Vector3.Transform(m_corners[i], m_bodyRotation);
        cornerWorldSpace += m_bodyCenter;

        // Get the height of the water surface
        float yWater = m_water.GetHeightAt(cornerWorldSpace.X, cornerWorldSpace.Z);
        averageHeight += yWater;

        Vector3 cornerNormal = m_water.GetNormalAt(cornerWorldSpace.X, cornerWorldSpace.Z);
        averageNormal += cornerNormal;
      }

      float currentYPos = m_renderMatrix.Translation.Y;

      averageNormal.Normalize();
      averageNormal.X *= (0.2f + ((1.0f - m_speedFactor) * 0.8f));
      averageNormal.Z *= (0.2f + ((1.0f - m_speedFactor) * 0.8f));
      averageNormal.Normalize();

      if (!m_firstUpdate)
      {
        averageNormal.X = m_rollFilter.Update(a_frameTime, m_renderMatrix.Up.X, averageNormal.X, true);
        averageNormal.Z = m_pitchFilter.Update(a_frameTime, m_renderMatrix.Up.Z, averageNormal.Z, true);
      }

      m_renderMatrix = Body.Orientation;
      m_renderMatrix.Up = averageNormal;      

      m_renderMatrix.Forward = Vector3.Cross(m_renderMatrix.Up, m_renderMatrix.Right);
      m_renderMatrix.Forward = Vector3.Normalize(m_renderMatrix.Forward);
      m_renderMatrix.Right = Vector3.Cross(m_renderMatrix.Forward, m_renderMatrix.Up);

      m_lean = m_steering * m_leanScale;
      m_renderMatrix.Right = m_renderMatrix.Right + new Vector3(0.0f, m_lean, 0.0f);

      m_renderMatrix.Right = Vector3.Normalize(m_renderMatrix.Right);
      m_renderMatrix.Forward = Vector3.Cross(m_renderMatrix.Up, m_renderMatrix.Right);
      m_renderMatrix.Forward = Vector3.Normalize(m_renderMatrix.Forward);

      if (m_firstUpdate)
      {
        position.Y = averageHeight / 4.0f;
      }
      else
      {
        position.Y = m_positionFilter.Update(a_frameTime, currentYPos - m_renderHeightOffset, averageHeight / 4.0f, true);
      }
      position.Y += m_renderHeightOffset;
      m_renderMatrix.Translation = position;
    }
    

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

