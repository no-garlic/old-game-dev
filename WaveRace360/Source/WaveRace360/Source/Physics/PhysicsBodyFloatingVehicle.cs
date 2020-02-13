// ----------------------------------------------------------------------------
// File: PhysicsBodyFloatingVehicle.cs
// Desc: The physics for a floating vehicle
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
  // Name: PhysicsBodyFloatingVehicle
  // Desc: The physics for a floating vehicle
  // --------------------------------------------------------------------------
  public class PhysicsBodyFloatingVehicle : PhysicsBodyBox
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public float Throttle { get { return m_throttle; } set { m_throttle = value; } }
    public float Steering { get { return m_steering; } set { m_steering = value; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private WaterMesh   m_water;
    private Vector3[]   m_corners;
    private const int   m_numCorners = 4;
    private float       m_volume;

    // Cached data each update
    private Vector3     m_bodyCenter;
    private Matrix      m_bodyRotation;
    private Vector3     m_bodyVelocity;
    private float       m_linearVelocity;
    private float       m_speedFactor;

    // Impulse parameters for stability
    private float       m_yOffsetUpper;
    private float       m_yOffsetLower;
    private float       m_yImpulsePerMeterUpperAtIdle;
    private float       m_yImpulsePerMeterLowerAtIdle;
    private float       m_yImpulsePerMeterUpperAtMaxSpeed;
    private float       m_yImpulsePerMeterLowerAtMaxSpeed;
    private float       m_yImpulseScaleUpper;
    private float       m_yImpulseScaleLower;

    // Pitch / roll parameters for stability
    private float       m_maxAngularVelocityAtIdle;
    private float       m_maxAngularVelocityAtMaxSpeed;
    private float       m_maxRollAtIdle;
    private float       m_maxRollAtMaxSpeed;
    private float       m_maxPitchAtIdle;
    private float       m_maxPitchAtMaxSpeed;

    // Motion parameters for driving
    private float       m_throttle;
    private float       m_maxSpeed;
    private float       m_accelerationScale;
    private float       m_decelerationScale;

    // Turning parameters
    private float       m_steering;
    private float       m_turnScale;

    
    // ------------------------------------------------------------------------
    // Name: PhysicsBodyFloatingVehicle
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public PhysicsBodyFloatingVehicle(WaterMesh a_water, Vector3 a_scale, Matrix a_orientation, Vector3 a_position, MaterialProperties a_material)
    : base(a_scale, a_orientation, a_position, a_material)
    {
      // Store the water
      m_water = a_water;

      // Calculate the volume of the box
      m_volume = a_scale.X * a_scale.Y * a_scale.Z;

      // Calculate the corner points, and set the Y to be the center point along the axis of the box
      m_corners = new Vector3[m_numCorners];
      m_corners[0] = new Vector3(a_scale.X *  0.5f, a_scale.Y * -0.5f, a_scale.Z *  0.5f);
      m_corners[1] = new Vector3(a_scale.X *  0.5f, a_scale.Y * -0.5f, a_scale.Z * -0.5f);
      m_corners[2] = new Vector3(a_scale.X * -0.5f, a_scale.Y * -0.5f, a_scale.Z * -0.5f);
      m_corners[3] = new Vector3(a_scale.X * -0.5f, a_scale.Y * -0.5f, a_scale.Z *  0.5f);

      // Impulse parameters for stability
      m_yOffsetUpper                    = a_scale.Y * 0.125f;
      m_yOffsetLower                    = a_scale.Y * 0.125f;
      m_yImpulsePerMeterUpperAtIdle     = -Systems.PhysicsSystem.Gravity.Y * (m_body.Mass / m_volume) * 0.85f;
      m_yImpulsePerMeterLowerAtIdle     = -Systems.PhysicsSystem.Gravity.Y * (m_body.Mass / m_volume) * 0.5f;
      m_yImpulsePerMeterUpperAtMaxSpeed = -Systems.PhysicsSystem.Gravity.Y * (m_body.Mass / m_volume) * 0.65f;
      m_yImpulsePerMeterLowerAtMaxSpeed = -Systems.PhysicsSystem.Gravity.Y * (m_body.Mass / m_volume) * 0.45f;
      m_yImpulseScaleUpper              = 0.45f;
      m_yImpulseScaleLower              = 0.65f;

      // Pitch parameters for stability
      m_maxAngularVelocityAtIdle        = MathHelper.ToRadians(10.0f);
      m_maxAngularVelocityAtMaxSpeed    = MathHelper.ToRadians(4.0f);
      m_maxRollAtIdle                   = MathHelper.ToRadians(25.0f);
      m_maxRollAtMaxSpeed               = MathHelper.ToRadians(10.0f);
      m_maxPitchAtIdle                  = MathHelper.ToRadians(30.0f);
      m_maxPitchAtMaxSpeed              = MathHelper.ToRadians(20.0f);

      // Motion parameters for driving
      m_maxSpeed                        = 60.0f;
      m_accelerationScale               = 1.0f;
      m_decelerationScale               = 1.0f;

      // Turning parameters
      m_turnScale                       = 0.6f;
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
      
      // Update the impulses to maintain buoyancy
      UpdateBuoyancy(a_frameTime);

      // Update the motion / power
      UpdateThrottleAndDrag(a_frameTime);

      // Clamp the linear and angular velocity
      ClampVelocity(a_frameTime);

      // Clamp the roll and pitch
      ClampOrientation(a_frameTime);
    }


    private void UpdateBuoyancy(float a_frameTime)
    {
      // Storage for all corner impulses
      float[] cornerImpulse = new float[m_numCorners];

      // Calculate the impulse for all corners
      for (int i = 0; i < m_numCorners; i++)
      {
        // Get the corner in world space
        Vector3 cornerWorldSpace = Vector3.Transform(m_corners[i], m_bodyRotation);
        cornerWorldSpace += m_bodyCenter;
        float yCorner = cornerWorldSpace.Y;

        // Get the height of the water surface
        float yWater = m_water.GetHeightAt(cornerWorldSpace.X, cornerWorldSpace.Z);

        // Get the current velocity of the corner point in the Y axis
        float cornerVelocity = m_body.GetVelocity(m_corners[i]).Y;

        // Determine the distance between the water surface and the corner center point
        float yDelta = yCorner - yWater;

        // Determine wether an upwards, downwards, or neither impulse is required
        if (yDelta > m_yOffsetLower)
        {
          cornerImpulse[i] = GetLowerImpulseToCorner(i, yDelta - m_yOffsetLower, cornerVelocity);
        }
        else if (-yDelta > m_yOffsetUpper)
        {
          cornerImpulse[i] = GetUpperImpulseToCorner(i, -yDelta - m_yOffsetUpper, cornerVelocity);
        }
        else
        {
          cornerImpulse[i] = 0.0f;
        }
      }

      // Apply the impulse for all corners
      for (int i = 0; i < m_numCorners; i++)
      {
        Vector3 impulseVector = new Vector3(0.0f, cornerImpulse[i], 0.0f);
        m_body.ApplyBodyImpulse(impulseVector, m_corners[i]);
      }
    }


    private float GetUpperImpulseToCorner(int a_cornerIndex, float a_yDelta, float a_currentVelocityY)
    {
      // Get the impulse value at idle and at max speed
      float impulseAtIdle = m_yImpulsePerMeterUpperAtIdle * a_yDelta;
      float impulseAtMaxSpeed = m_yImpulsePerMeterUpperAtMaxSpeed * a_yDelta;

      // Interpolate between the two impulses based on the speed factor
      float impulse = MathHelper.Lerp(impulseAtIdle, impulseAtMaxSpeed, m_speedFactor);

      // Scale the impulse if the corner already has a +Y velocity
      if (a_currentVelocityY > 0.0f)
      {
        impulse *= m_yImpulseScaleUpper;
      }

      return impulse;
    }


    private float GetLowerImpulseToCorner(int a_cornerIndex, float a_yDelta, float a_currentVelocityY)
    {
      // Get the impulse value at idle and at max speed
      float impulseAtIdle = m_yImpulsePerMeterLowerAtIdle * a_yDelta;
      float impulseAtMaxSpeed = m_yImpulsePerMeterLowerAtMaxSpeed * a_yDelta;

      // Interpolate between the two impulses based on the speed factor
      float impulse = MathHelper.Lerp(impulseAtIdle, impulseAtMaxSpeed, m_speedFactor);

      // Scale the impulse if the corner already has a -Y velocity
      if (a_currentVelocityY < 0.0f)
      {
        impulse *= m_yImpulseScaleLower;
      }

      return -impulse;
    }


    private void UpdateThrottleAndDrag(float a_frameTime)
    {
      Vector3 impulse = new Vector3(0.0f, 0.0f, m_throttle * m_accelerationScale * m_volume);
      m_body.ApplyBodyImpulse(impulse);

      float decelerationFactor = (1.0f - m_throttle) * m_decelerationScale * a_frameTime;
      m_body.Velocity += new Vector3(m_body.Velocity.X * -decelerationFactor, 0.0f, m_body.Velocity.Z * -decelerationFactor);

      if (m_steering != 0.0f)
      {
        float angle = -m_steering * a_frameTime * m_speedFactor * m_turnScale;
        Matrix orientation = m_body.Orientation;
        Matrix rotation = Matrix.CreateFromYawPitchRoll(angle, 0.0f, 0.0f);
        m_body.Orientation = orientation * rotation;     
      }
    }


    private void ClampVelocity(float a_frameTime)
    {
      float velocitySquared = m_body.Velocity.LengthSquared();
      if (velocitySquared > m_maxSpeed * m_maxSpeed)
      {
        m_body.Velocity = Vector3.Normalize(m_body.Velocity);
        m_body.Velocity *= m_maxSpeed;
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
        yaw = m_steering * a_frameTime;
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


    /*
    // ------------------------------------------------------------------------
    // Name: UpdateBuoyancy
    // Desc: Apply impulses to maintain buoyancy
    // Parm: a_water - the water surface
    // ------------------------------------------------------------------------
    public void UpdateBuoyancy(WaterMesh a_water)
    {
      Vector3 center = m_body.Transform.Position;
      Matrix rotation = m_body.Transform.Orientation;

      for (int i = 0; i < m_numCorners; i++)
      {
        // Get the corner in world space
        Vector3 cornerWorldSpace = Vector3.Transform(m_corners[i], rotation);
        cornerWorldSpace += center;
        float yCorner = cornerWorldSpace.Y;

        // Get the height of the water surface
        float yWater = a_water.GetHeightAt(cornerWorldSpace.X, cornerWorldSpace.Z);

        // Constant tuning values
        float minDepth = m_scale.Y * 0.25f;
        float impulsePerMeter = -PhysicsManager.PhysicsSystem.Gravity.Y * (m_body.Mass / m_volume);

        // Apply the minimum depth offset to the corner
        yCorner -= minDepth;

        // If the corner is below the water surface, apply an impulse
        if (yCorner < yWater)
        {
          float depth = yWater - yCorner;
          float impulse = depth * impulsePerMeter;

          // Scale the magnitude of the impulse if the velocity of the corner is in the +Y axis
          float cornerVelocity = m_body.GetVelocity(m_corners[i]).Y;          
          if (cornerVelocity > 0.0f)
          {
            impulse *= 0.75f;
          }

          float worldVelocity = MathHelper.Clamp(100.0f - m_body.Velocity.Length(), 0.0f, 100.0f);
          float velocityScaling = (worldVelocity + 25.0f) / 200.0f;

          // Apply an impulse to the corner
          Vector3 impulseVector = new Vector3(0.0f, impulse * velocityScaling, 0.0f);
          m_body.ApplyBodyImpulse(impulseVector, m_corners[i]);
        }
        else
        {
          yCorner += (minDepth * 2.0f);
          minDepth = m_scale.Y;

          float depth = yCorner - yWater;
          float impulse = depth * impulsePerMeter;

          float cornerVelocity = m_body.GetVelocity(m_corners[i]).Y;          
          if (cornerVelocity > 0.0f)
          {
            // Apply an impulse to the corner
            Vector3 impulseVector = new Vector3(0.0f, -impulse, 0.0f);
            m_body.ApplyBodyImpulse(impulseVector, m_corners[i]);
          }
        }
      }

      float len = m_body.AngularVelocity.Length();
      if (len > 0.25f)
      {
        m_body.AngularVelocity *= (0.25f / len);
      }
    }


    public void SetThrottle(float a_value)
    {
      m_body.ApplyBodyImpulse(new Vector3(0.0f, 0.0f, a_value));
    }
    */


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

