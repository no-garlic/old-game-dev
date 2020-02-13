using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using Common;


namespace WaveRace360
{
  public class GameLevel
  {
    // ------------------------------------------------------------------------
    // Private Members
    //
    private List<SceneObject>   m_staticObjects;    // All static objects
    private TerrainRender       m_terrainRender;    // The terrain object


    // ------------------------------------------------------------------------
    // Public Properties
    //
    public List<SceneObject>    StaticObjects   { get { return m_staticObjects; } }
    public TerrainRender        Terrain         { get { return m_terrainRender; } }


    // ------------------------------------------------------------------------
    // Constructor
    //
    public GameLevel()
    {
      m_staticObjects = new List<SceneObject>();
      m_terrainRender = new TerrainRender();
    }


    // ------------------------------------------------------------------------
    // Load a file
    //
    public bool Load(String a_filename)
    {
      // Load the scene file definition
      Freeworld3D.Content content;
      content = Systems.Content.Load<Freeworld3D.Content>(Asset.Resolve(AssetType.AT_LEVEL, a_filename));

      // Check that the file was loaded
      if (content == null)
      {
        return false;
      }

      // Load the terrain
      if (!m_terrainRender.Load(content))
      {
        return false;
      }

      // Load all static meshes
      foreach (Freeworld3D.MeshData mesh in content.MeshList)
      {
        SceneObject obj = new SceneObject(mesh.Filename);
        obj.Transform = mesh.Transform;
        m_staticObjects.Add(obj);
      }
      
      return true;
    }
    

    // ------------------------------------------------------------------------
    // Render the level
    //
    public void Render()
    {
      // Render the terrain
      m_terrainRender.Render();

      // Render all of the static objects
      foreach (SceneObject obj in m_staticObjects)
      {
        if (obj.Visible)
        {
          obj.Render();
        }
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

