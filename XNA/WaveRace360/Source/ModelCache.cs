using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;


namespace WaveRace360
{
  public class ModelCache
  {
    // ------------------------------------------------------------------------
    // Members
    //
    Dictionary<String, Model>   m_models;   // All loaded models


    // ------------------------------------------------------------------------
    // Constructor
    //
    public ModelCache()
    {
      m_models = new Dictionary<String, Model>();
    }


    // ------------------------------------------------------------------------
    // Get a model
    //
    public Model GetModel(String a_name)
    {
      Model model;
      if (m_models.TryGetValue(a_name, out model))
      {
        return model;
      }

      return LoadModel(a_name);
    }


    // ------------------------------------------------------------------------
    // Preload a model
    //
    public bool PreLoadModel(String a_name)
    {
      if (GetModel(a_name) == null)
      {
        return false;
      }

      return true;
    }


    // ------------------------------------------------------------------------
    // Load a model
    //
    private Model LoadModel(String a_name)
    {
      Model model = Systems.Content.Load<Model>(Asset.Resolve(AssetType.AT_MODEL, a_name));

      if (model != null)
      {
        m_models.Add(a_name, model);
      }
      
      return model;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

