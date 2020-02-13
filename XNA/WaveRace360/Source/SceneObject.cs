using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;


namespace WaveRace360
{
  public class SceneObject
  {
    // ------------------------------------------------------------------------
    // Private Members
    //
    private BoundingSphere  m_boundingSphere;   // The bounding sphere of the object
    private Matrix          m_transform;        // The model transform
    private String          m_modelName;        // The model name
    private bool            m_visible;          // Is the model visible


    // ------------------------------------------------------------------------
    // Read-Only Properties
    //
    public BoundingSphere  BoundingSphere   { get { return m_boundingSphere;  } }
    public String          ModelName        { get { return m_modelName;       } }


    // ------------------------------------------------------------------------
    // Read-Write Properties
    //
    public Matrix          Transform        { get { return m_transform;       } 
                                              set { m_transform = value;      } }
    public bool            Visible          { get { return m_visible;         } 
                                              set { m_visible = value;        } }

    
    // ------------------------------------------------------------------------
    // Constructor
    //
    public SceneObject()
    {
      m_visible         = true;
      m_transform       = Matrix.Identity;
      m_boundingSphere  = new BoundingSphere();
    }


    // ------------------------------------------------------------------------
    // Constructor
    //
    public SceneObject(String a_name)
    {
      // Set the members
      m_modelName       = a_name;
      m_visible         = true;
      m_transform       = Matrix.Identity;
      m_boundingSphere  = new BoundingSphere();

      // Load the model
      if (!Load(a_name))
      {
        throw new Exception("Failed to load the model");
      }
    }


    // ------------------------------------------------------------------------
    // Load the model
    //
    public bool Load(String a_name)
    {
      // Set the members
      m_modelName = a_name;
      m_visible   = true;
      m_boundingSphere.Center = Vector3.Zero;
      m_boundingSphere.Radius = 0.0f;

      // Check that the model has been pre loaded
      if (!Systems.Models.PreLoadModel(a_name))
      {
        return false;
      }

      // Get the model
      Model model = Systems.Models.GetModel(m_modelName);
      if (model == null)
      {
        return false;
      }

      // Calculate the bounding sphere of all sub meshes
      Vector3 center = new Vector3(0.0f, 0.0f, 0.0f);
      float radius = 0.0f;

      // Iterate all meshes
      foreach (ModelMesh mesh in model.Meshes)
      {
        // TODO: update 
      }

      // Assign the bounding sphere values
      m_boundingSphere.Center = center;
      m_boundingSphere.Radius = radius;
      return true;
    }


    // ------------------------------------------------------------------------
    // Render the model
    //
    public bool Render()
    {
      if (!m_visible)
      {
        return false;
      }

      Model model = Systems.Models.GetModel(m_modelName);
      if (model == null)
      {
        return false;
      }

      foreach (ModelMesh mesh in model.Meshes)
      {
        if (Systems.Camera.Frustum.Intersects(mesh.BoundingSphere))
        {
          foreach (BasicEffect be in mesh.Effects)
          {
            be.EnableDefaultLighting();

            be.World      = Transform * mesh.ParentBone.Transform;
            be.View       = Systems.Camera.ViewMatrix;
            be.Projection = Systems.Camera.ProjMatrix;
          }

          mesh.Draw();
        }
      }

      return true;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF


