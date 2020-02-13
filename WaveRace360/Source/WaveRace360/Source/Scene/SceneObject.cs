// ----------------------------------------------------------------------------
// File: SceneObject.cs
// Desc: Manages a scene object instance
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using JigLibX.Collision;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: SceneObject 
  // Desc: Manages an instance of a model, with an associated transform.
  // Note: The object must have been exported without frames, because the 
  //       transform stored in the bones is ignored in this class.
  // --------------------------------------------------------------------------
  public class SceneObject : IRender
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private BoundingSphere  m_boundingSphere;   // The bounding sphere of the object
    private BoundingBox     m_boundingBox;      // The bounding box
    private Matrix          m_transform;        // The model transform
    private String          m_modelName;        // The model name
    private bool            m_visible;          // Is the model visible
    private bool            m_loaded;           // Is the model loaded
    private PhysicsBody     m_physicsBody;      // The physics body for the object


    // ------------------------------------------------------------------------
    // Read-Only Properties
    // ------------------------------------------------------------------------
    public BoundingSphere  BoundingSphere   { get { return m_boundingSphere;  } }
    public BoundingBox     BoundingBox      { get { return m_boundingBox;     } }
    public String          ModelName        { get { return m_modelName;       } }


    // ------------------------------------------------------------------------
    // Read-Write Properties
    // ------------------------------------------------------------------------
    public Matrix          Transform        { get { return m_transform;       } 
                                              set { m_transform = value;      } }
    public bool            Visible          { get { return m_visible;         } 
                                              set { m_visible = value;        } }
    public PhysicsBody     PhysicsBody      { get { return m_physicsBody;     }
                                              set { m_physicsBody = value;    } }

    
    // ------------------------------------------------------------------------
    // Name: SceneObject
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public SceneObject()
    {
      m_loaded          = false;
      m_visible         = true;
      m_transform       = Matrix.Identity;
      m_boundingSphere  = new BoundingSphere();
      m_physicsBody     = null;
    }


    // ------------------------------------------------------------------------
    // Name: SceneObject
    // Desc: Constructor
    // Parm: String a_name - the name of the model
    // ------------------------------------------------------------------------
    public SceneObject(String a_name)
    {
      // Set the members
      m_loaded          = false;
      m_modelName       = a_name;
      m_visible         = true;
      m_transform       = Matrix.Identity;
      m_boundingSphere  = new BoundingSphere();
      m_boundingBox     = new BoundingBox();
      m_physicsBody     = null;

      // Load the model
      Load(a_name);
    }


    // ------------------------------------------------------------------------
    // Name: Load
    // Desc: Load the model for the given name
    // Parm: String a_name - the name of the model to load
    // ------------------------------------------------------------------------
    public void Load(String a_name)
    {
      // Set the members
      m_modelName = a_name;
      m_visible   = true;

      // Check that the model has been pre loaded
      Systems.Models.PreLoadModel(a_name);
      m_loaded = true;

      // Get the model
      Model model = Systems.Models.GetModel(m_modelName);

      // Cache the model info
      ModelInfo = Systems.Models.GetModelInfo(m_modelName);

      // Calculate the entire bounding sphere
      m_boundingSphere.Center = Vector3.Zero;
      m_boundingSphere.Radius = 0.0f;

      // Iterate all meshes
      foreach (ModelMesh mesh in model.Meshes)
      {
        if (m_boundingSphere.Radius == 0.0f)
        {
          m_boundingSphere = mesh.BoundingSphere;
          MeshUtils.CalculateBoundingBox(mesh, out m_boundingBox);
        }
        else
        {
          // TODO: This data should be cached with the model in the model cache so we dont
          // have to generate it for each instance of the same object.
          m_boundingSphere = BoundingSphere.CreateMerged(m_boundingSphere, mesh.BoundingSphere);
          BoundingBox tmpBox = new BoundingBox();
          MeshUtils.CalculateBoundingBox(mesh, out tmpBox);
          m_boundingBox = BoundingBox.CreateMerged(m_boundingBox, tmpBox);
        }
      }
    }


    // ------------------------------------------------------------------------
    // Name: CreatePhysicsBodyBox
    // Desc: Create a static physics body for the scene object
    // ------------------------------------------------------------------------
    public void CreatePhysicsBodyBox(MaterialProperties a_material)
    {
      if (!m_loaded)
      {
        throw new InvalidOperationException("Cannot create a physics body before the model is loaded.");
      }

      Vector3 scale = Vector3.Subtract(m_boundingBox.Max, m_boundingBox.Min);
      Vector3 center = m_boundingBox.Min + (scale * 0.5f);

      scale.X *= Transform.Right.Length();
      scale.Y *= Transform.Up.Length();
      scale.Z *= Transform.Forward.Length();

      center.X *= Transform.Right.Length();
      center.Y *= Transform.Up.Length();
      center.Z *= Transform.Forward.Length();

      // TODO: Needs some verification

      Matrix rotation = Transform;
      rotation.Translation = Vector3.Zero;
      rotation.Forward = Vector3.Normalize(rotation.Forward);
      rotation.Right = Vector3.Normalize(rotation.Right);
      rotation.Up = Vector3.Normalize(rotation.Up);

      m_physicsBody = new PhysicsBodyBox(scale, rotation, Transform.Translation + center, a_material);
      m_physicsBody.Body.Immovable = true;
    }


    // ------------------------------------------------------------------------
    // Name: CreatePhysicsBodySphere
    // Desc: Create a static physics body for the scene object
    // ------------------------------------------------------------------------
    public void CreatePhysicsBodySphere(MaterialProperties a_material)
    {
      if (!m_loaded)
      {
        throw new InvalidOperationException("Cannot create a physics body before the model is loaded.");
      }

      m_physicsBody = new PhysicsBodySphere(m_boundingSphere.Radius, m_boundingSphere.Center * Transform.Translation, a_material);
      m_physicsBody.Body.Immovable = true;
    }


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the model
    // ------------------------------------------------------------------------
    public override void Render(Material a_material, Matrix a_worldMatrix)
    {
      if (Systems.DebugSettings.Get("Render.Meshes"))
      {
        if (!m_loaded)
        {
          throw new InvalidOperationException("Cannot render a scene object before the model is loaded.");
        }

        if (!m_visible)
        {
          return;
        }

        Model model = Systems.Models.GetModel(m_modelName);
        if (model == null)
        {
          return;
        }

        Matrix[] transforms = new Matrix[model.Bones.Count];
        model.CopyAbsoluteBoneTransformsTo(transforms);

        foreach (ModelMesh mesh in model.Meshes)
        {
          float matrixScale = GetMatrixMaxScale(Transform);
          // Scale and translate the bounding sphere
          BoundingSphere bounds = new BoundingSphere(mesh.BoundingSphere.Center, mesh.BoundingSphere.Radius);
          bounds.Radius *= matrixScale;
          bounds.Center *= matrixScale;
          bounds.Center += Transform.Translation;

          a_material.SetTransforms(a_worldMatrix * transforms[mesh.ParentBone.Index]);

          if (Systems.CameraSettings.Frustum.Intersects(bounds))
          {
            Systems.Graphics.GraphicsDevice.Indices = mesh.IndexBuffer;

            foreach (ModelMeshPart part in mesh.MeshParts)
            {
              Systems.Graphics.GraphicsDevice.VertexDeclaration = part.VertexDeclaration;
              Systems.Graphics.GraphicsDevice.Vertices[0].SetSource(mesh.VertexBuffer, part.StreamOffset, part.VertexStride);
              Systems.Graphics.GraphicsDevice.Textures[0] = ((BasicEffect)part.Effect).Texture;
              Systems.Graphics.GraphicsDevice.DrawIndexedPrimitives(PrimitiveType.TriangleList, part.BaseVertex, 0, part.NumVertices, part.StartIndex, part.PrimitiveCount);
            }
          }
        }
      }
    }


    // ------------------------------------------------------------------------
    // Name: GetMatrixMaxScale
    // Desc: Get the largest scale from the matrix x, y, z vectors
    // Parm: Matrix a_matrix - the matrix
    // Retn: float       - the scale
    // ------------------------------------------------------------------------
    private float GetMatrixMaxScale(Matrix a_matrix)
    {
      float x = a_matrix.Right.Length();
      float y = a_matrix.Up.Length();
      float z = a_matrix.Forward.Length();

      return Math.Max(Math.Max(x, y), z);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF


