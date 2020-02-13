// ----------------------------------------------------------------------------
// File: Camera3D.cs
// Desc: The base class for all cameras
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: Camera3D
  // Desc: The base class for all cameras. This class provides an interface to 
  //       modify the global camera settings, and also provides functions (for
  //       example rotate) that extend the basic concept of a 3 vector camera.
  // --------------------------------------------------------------------------
  public abstract class Camera3D
  {
    // ------------------------------------------------------------------------
    // Name: Camera3D
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public Camera3D()
    {
      SetProjection(MathHelper.PiOver4, 1280.0f / 720.0f, 1.0f, 10000.0f);
      SetView(new Vector3(), Vector3.Forward, Vector3.Right, Vector3.Up);
    }
    
    
    // ------------------------------------------------------------------------
    // Name: SetProjection
    // Desc: Set the projection of the camera
    // Parm: float a_fieldOfView - the field of view
    // Parm: float a_aspectRatio - the aspect ratio
    // Parm: float a_nearPlane - the near plane
    // Parm: float a_farPlane - the far plane
    // ------------------------------------------------------------------------
    public static void SetProjection(float a_fieldOfView, float a_aspectRatio, float a_nearPlane, float a_farPlane)
    {
      Systems.CameraSettings.FieldOfView  = a_fieldOfView;
      Systems.CameraSettings.AspectRatio  = a_aspectRatio;
      Systems.CameraSettings.NearPlane    = a_nearPlane;
      Systems.CameraSettings.FarPlane     = a_farPlane;

      UpdateMatrix();
    }


    // ------------------------------------------------------------------------
    // Name: SetView
    // Desc: Sets the camera's view
    // Parm: Vector3 a_forward - the look vector
    // Parm: Vector3 a_right - the right vector
    // Parm: Vector3 a_up  - the up vector
    // ------------------------------------------------------------------------
    public static void SetView(Vector3 a_forward, Vector3 a_right, Vector3 a_up)
    {
      Systems.CameraSettings.ForwardVector  = a_forward;
      Systems.CameraSettings.RightVector    = a_right;
      Systems.CameraSettings.UpVector       = a_up;

      UpdateMatrix();
    }


    // ------------------------------------------------------------------------
    // Name: SetView
    // Desc: Sets the camera's view and position
    // Parm: Vector3 a_pos - the camera position
    // Parm: Vector3 a_forward - the look vector
    // Parm: Vector3 a_right - the right vector
    // Parm: Vector3 a_up  - the up vector
    // ------------------------------------------------------------------------
    public static void SetView(Vector3 a_pos, Vector3 a_forward, Vector3 a_right, Vector3 a_up)
    {
      Systems.CameraSettings.CameraPosition = a_pos;
      Systems.CameraSettings.ForwardVector  = a_forward;
      Systems.CameraSettings.RightVector    = a_right;
      Systems.CameraSettings.UpVector       = a_up;

      UpdateMatrix();
    }

    
    // ------------------------------------------------------------------------
    // Name: SetPosition
    // Desc: Set the camera's position
    // Parm: Vector3 a_pos - the camera position
    // ------------------------------------------------------------------------
    public static void SetPosition(Vector3 a_pos)
    {
      Systems.CameraSettings.CameraPosition = a_pos;

      UpdateMatrix();
    }

    
    // ------------------------------------------------------------------------
    // Name: SetLookAt
    // Desc: Set the camera's view and position using look-at values
    // Parm: Vector3 a_eye - the camera position (or eye point)
    // Parm: Vector3 a_at - the point that the camera is looking at
    // Parm: Vector3 a_up - the up vector
    // ------------------------------------------------------------------------
    public static void SetLookAt(Vector3 a_eye, Vector3 a_at, Vector3 a_up)
    {
      Systems.CameraSettings.CameraPosition = a_eye;
      Systems.CameraSettings.UpVector  = a_up;

      Systems.CameraSettings.ForwardVector = a_at - a_eye;
      Systems.CameraSettings.ForwardVector.Normalize();
      
      Systems.CameraSettings.RightVector = Vector3.Cross(Systems.CameraSettings.ForwardVector, Systems.CameraSettings.UpVector);
      Systems.CameraSettings.RightVector.Normalize();

      UpdateMatrix();
    }


    // ------------------------------------------------------------------------
    // Name: Rotate
    // Desc: Rotate the camera in 3D (rotate about it's current view)
    // Parm: float x - the amount to rotate around the x axis
    // Parm: float y - the amount to rotate around the y axis
    // Parm: float z - the amount to rotate around the z axis
    // ------------------------------------------------------------------------
    public static void Rotate(float x, float y, float z)
    {
      Vector3 forward = Systems.CameraSettings.ForwardVector;
      Vector3 right   = Systems.CameraSettings.RightVector;
      Vector3 up      = Systems.CameraSettings.UpVector;

      if (x != 0.0f)
      {
        Matrix rotationMatrix = Matrix.CreateFromAxisAngle(right, x);
        forward = Vector3.TransformNormal(forward, rotationMatrix);
        up = Vector3.TransformNormal(up, rotationMatrix);
      }
      if (y != 0.0f)
      {
        Matrix rotationMatrix = Matrix.CreateFromAxisAngle(up, y);
        forward = Vector3.TransformNormal(forward, rotationMatrix);
        right = Vector3.TransformNormal(right, rotationMatrix);
      }
      if (z != 0.0f)
      {
        Matrix rotationMatrix = Matrix.CreateFromAxisAngle(forward, z);
        up = Vector3.TransformNormal(up, rotationMatrix);
        right = Vector3.TransformNormal(right, rotationMatrix);
      }

      forward.Normalize();
      right = Vector3.Cross(up, forward);
      right.Normalize();
      up = Vector3.Cross(forward, right);
      up.Normalize();

      SetView(forward, right, up);
    }


    // ------------------------------------------------------------------------
    // Name: UpdateMatrix
    // Desc: Update the camera settings's view, projection, and combined 
    //       matrices. Also generates a bounding frustum
    // ------------------------------------------------------------------------
    public static void UpdateMatrix()
    {
      // Calculate the projection matrix
      Systems.CameraSettings.ProjMatrix = Matrix.CreatePerspectiveFieldOfView(
        Systems.CameraSettings.FieldOfView, 
        Systems.CameraSettings.AspectRatio, 
        Systems.CameraSettings.NearPlane, 
        Systems.CameraSettings.FarPlane);

      // Calculate the view matrix
      Systems.CameraSettings.ViewMatrix = Matrix.CreateLookAt(
        Systems.CameraSettings.CameraPosition, 
        Systems.CameraSettings.CameraPosition+ Systems.CameraSettings.ForwardVector, 
        Systems.CameraSettings.UpVector);

      // Calculate the bounding frustum
      Systems.CameraSettings.ViewProjMatrix = Matrix.Multiply(Systems.CameraSettings.ViewMatrix, Systems.CameraSettings.ProjMatrix);
      Systems.CameraSettings.Frustum.Matrix = Systems.CameraSettings.ViewProjMatrix;
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Abstract function to update the camera each frame.
    // Parm: float a_frameTime - the delta frame time
    // ------------------------------------------------------------------------
    public abstract void Update(float a_frameTime);


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

 