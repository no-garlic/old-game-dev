// ----------------------------------------------------------------------------
// File: CameraSettings.cs
// Desc: The global camera settings for the application.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: CameraSettings
  // Desc: The camera settings define the state of the current camera, and 
  //       provide the view and projection matricies for shaders. Multiple 
  //       cameras (that inherit from Camera3D) can use the same settings, and 
  //       each time a camera is activated it uses the same global settings.
  // --------------------------------------------------------------------------
  public class CameraSettings
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    public Matrix           ViewMatrix;       // The view matrix
    public Matrix           ProjMatrix;       // The projection matrix
    public Matrix           ViewProjMatrix;   // The view * projection matrix
    public BoundingFrustum  Frustum;          // The bounding frustum
    public Vector3          CameraPosition;   // The camera position
    public Vector3          ForwardVector;    // The forward vector
    public Vector3          UpVector;         // The up vector
    public Vector3          RightVector;      // The right vector
    public float            FieldOfView;      // The field of view
    public float            AspectRatio;      // The aspect ration
    public float            NearPlane;        // The near plane
    public float            FarPlane;         // The far plane


    // ------------------------------------------------------------------------
    // Name: CameraSettings
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public CameraSettings()
    {
      ViewMatrix      = Matrix.Identity;
      ProjMatrix      = Matrix.Identity;
      ViewProjMatrix  = Matrix.Identity;
      CameraPosition  = Vector3.Zero;
      ForwardVector   = Vector3.Zero;
      UpVector        = Vector3.Zero;
      RightVector     = Vector3.Zero;
      Frustum         = new BoundingFrustum(Matrix.Identity);   
      FieldOfView     = 0.0f;
      AspectRatio     = 0.0f;
      NearPlane       = 0.0f;
      FarPlane        = 0.0f;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
