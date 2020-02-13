// ----------------------------------------------------------------------------
// File: CameraFly.cs
// Desc: A simple fly camera tha is controlled with the gamepad
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: CameraFly 
  // Desc: A simple fly camera tha is controlled with the gamepad
  // --------------------------------------------------------------------------
  public class CameraFly : Camera3D
  {
    // ------------------------------------------------------------------------
    // Name: CameraFly
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public CameraFly()
    {
      SetView(new Vector3(), Vector3.Forward, Vector3.Right, Vector3.Up);
      SetProjection(MathHelper.PiOver4, 1280.0f / 720.0f, 1.0f, 10000.0f);
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the camera based on the gamepad input
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public override void Update(float a_frameTime)
    {
      const float thumbstickThreashold  = 0.05f;
      const float forwardScale          = 100.0f;
      const float straffeScale          = 100.0f;
      const float yawScale              = 4.0f;
      const float pitchScale            = 4.0f;

      // Update camera position
      Vector2 left = Systems.GamePad.State.ThumbSticks.Left;
      if (left.Length() > thumbstickThreashold)
      {
        Systems.CameraSettings.CameraPosition += Systems.CameraSettings.ForwardVector * left.Y * forwardScale * a_frameTime;
        Systems.CameraSettings.CameraPosition -= Systems.CameraSettings.RightVector * left.X * straffeScale * a_frameTime;
        UpdateMatrix();
      }

      // Update camera rotation
      Vector2 right = Systems.GamePad.State.ThumbSticks.Right;
      if (right.Length() > thumbstickThreashold)
      {
        float x = MathHelper.ToRadians(right.X) * yawScale;
        float y = MathHelper.ToRadians(right.Y) * pitchScale;

        Rotate(-y, -x, 0.0f);
      }

      // Keep the camera level to the ground (ie, no tilt)
      Vector3 forwardVec = Systems.CameraSettings.ForwardVector;
      Vector3 rightVec   = Systems.CameraSettings.RightVector;
      Vector3 upVec      = Systems.CameraSettings.UpVector;

      rightVec.Y = 0.0f;
      rightVec.Normalize();
      upVec = Vector3.Up;

      SetView(forwardVec, rightVec, upVec);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
