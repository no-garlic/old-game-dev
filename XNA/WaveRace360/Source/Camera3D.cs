using System;

using Microsoft.Xna.Framework;


namespace WaveRace360
{
  public class Camera3D
  {
    // ------------------------------------------------------------------------
    // Private Members
    //
    private Vector3         m_forward;        // The up vector
    private Vector3         m_right;          // The right vector
    private Vector3         m_up;             // The up vector
    private Vector3         m_pos;            // The camera position
    private float           m_fieldOfView;    // The field of view
    private float           m_aspectRatio;    // The aspect ration
    private float           m_nearPlane;      // The near plane
    private float           m_farPlane;       // The far plane
    private BoundingFrustum m_frustum;        // The bounding frustum
    private Matrix          m_viewMatrix;     // The view matrix
    private Matrix          m_projMatrix;     // The projection matrix
    private Matrix          m_viewProjMatrix; // The combined view proj matrix


    // ------------------------------------------------------------------------
    // Public Members
    //
    public Vector3          Forward         { get { return m_forward; } }
    public Vector3          Right           { get { return m_right; } }
    public Vector3          Up              { get { return m_up; } }
    public Vector3          Pos             { get { return m_pos; } }
    public float            FieldOfView     { get { return m_fieldOfView; } }
    public float            AspectRatio     { get { return m_aspectRatio; } }
    public float            NearPlane       { get { return m_nearPlane; } }
    public float            FarPlane        { get { return m_farPlane; } }
    public BoundingFrustum  Frustum         { get { return m_frustum; } }
    public Matrix           ViewMatrix      { get { return m_viewMatrix; } }
    public Matrix           ProjMatrix      { get { return m_projMatrix; } }
    public Matrix           ViewProjMatrix  { get { return m_viewProjMatrix; } }

    
    // ------------------------------------------------------------------------
    // Constructor
    //
    public Camera3D()
    {
      m_viewMatrix = Matrix.Identity;
      m_projMatrix = Matrix.Identity;
      m_frustum    = new BoundingFrustum(Matrix.Identity);      

      SetProjection(MathHelper.PiOver4, 0.75f, 1.0f, 10000.0f);
      SetView(Vector3.Forward, Vector3.Right, Vector3.Up);
    }


    // ------------------------------------------------------------------------
    // Set the projection of the camera
    //
    public void SetProjection(float a_fieldOfView, float a_aspectRatio, float a_nearPlane, float a_farPlane)
    {
      m_fieldOfView = a_fieldOfView;
      m_aspectRatio = a_aspectRatio;
      m_nearPlane   = a_nearPlane;
      m_farPlane    = a_farPlane;

      UpdateMatrix();
    }


    // ------------------------------------------------------------------------
    // Set the view
    //
    public void SetView(Vector3 a_forward, Vector3 a_right, Vector3 a_up)
    {
      m_forward = a_forward;
      m_right   = a_right;
      m_up      = a_up;

      UpdateMatrix();
    }


    // ------------------------------------------------------------------------
    // Set the view and position
    //
    public void SetView(Vector3 a_pos, Vector3 a_forward, Vector3 a_right, Vector3 a_up)
    {
      m_pos     = a_pos;
      m_forward = a_forward;
      m_right   = a_right;
      m_up      = a_up;

      UpdateMatrix();
    }

    
    // ------------------------------------------------------------------------
    // Set the position
    //
    public void SetPosition(Vector3 a_pos, Vector3 a_forward, Vector3 a_right, Vector3 a_up)
    {
      m_pos = a_pos;

      UpdateMatrix();
    }

    
    // ------------------------------------------------------------------------
    // Set the view using look-at vectors
    //
    public void SetLookAt(Vector3 a_eye, Vector3 a_at, Vector3 a_up)
    {
      m_pos = a_eye;
      m_up  = a_up;

      m_forward = a_at - a_eye;
      m_forward.Normalize();
      
      m_right = Vector3.Cross(m_forward, m_up);
      m_right.Normalize();

      UpdateMatrix();
    }


    // ------------------------------------------------------------------------
    // Update the projection and view matrices
    //
    private void UpdateMatrix()
    {
      // Calculate the projection matrix
      m_projMatrix = Matrix.CreatePerspectiveFieldOfView(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);

      // Calculate the view matrix
      m_viewMatrix = Matrix.CreateLookAt(m_pos, m_pos + m_forward, m_up);

      // Calculate the bounding frustum
      m_viewProjMatrix = Matrix.Multiply(m_viewMatrix, m_projMatrix);
      m_frustum.Matrix = m_viewProjMatrix;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

 