// ----------------------------------------------------------------------------
// File: ModelCache.cs
// Desc: Manages a cache of all loaded objects.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: ModelCache
  // Desc: Manages a cache of all loaded objects (for object instancing).
  // --------------------------------------------------------------------------
  public class ModelCache
  {
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private SortedList<String, Model>               m_models;     // All loaded models
    private SortedList<String, AssetData.ModelInfo> m_modelInfo;  // All model info


    // ------------------------------------------------------------------------
    // Name: ModelCache
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public ModelCache()
    {
      m_models = new SortedList<String, Model>();
      m_modelInfo = new SortedList<string,AssetData.ModelInfo>();
    }


    // ------------------------------------------------------------------------
    // Name: GetModel
    // Desc: Get the model for the given name. If the model has already been 
    //       loaded it is returned, othersie it is loaded and then returned.
    // Parm: String a_name - the name of the model to get
    // Retn: Model - the model
    // ------------------------------------------------------------------------
    public Model GetModel(String a_name)
    {
      Model model;
      if (m_models.TryGetValue(a_name, out model))
      {
        return model;
      }

      return LoadModel(a_name);
    }

    
    public AssetData.ModelInfo GetModelInfo(String a_name)
    {
      AssetData.ModelInfo modelInfo;
      if (m_modelInfo.TryGetValue(a_name, out modelInfo))
      {
        return modelInfo;
      }

      throw new KeyNotFoundException("The model info was not found: " + a_name);
    }


    // ------------------------------------------------------------------------
    // Name: PreLoadModel
    // Desc: Pre-load the model for a given name
    // Parm: String a_name - the name of the model to pre-load.
    // ------------------------------------------------------------------------
    public void PreLoadModel(String a_name)
    {
      GetModel(a_name);
    }


    // ------------------------------------------------------------------------
    // Name: LoadModel
    // Desc: Load a model from the content pipeline for the given name
    // Parm: String a_name - the name of the model
    // Retn: private Model - the model
    // ------------------------------------------------------------------------
    private Model LoadModel(String a_name)
    {
      Model model = Systems.Content.Load<Model>(Asset.Resolve(AssetType.AT_MODEL, a_name));
      m_models.Add(a_name, model);

      if (!m_modelInfo.ContainsKey(a_name))
      {
        AssetData.ModelInfo modelInfo = null;

        try
        {
          String modelInfoName = a_name + "_info";
          modelInfo = Systems.Content.Load<AssetData.ModelInfo>(Asset.Resolve(AssetType.AT_MODEL, modelInfoName));
        }
        catch (Exception)
        {
          modelInfo = new AssetData.ModelInfo();
        }

        m_modelInfo.Add(a_name, modelInfo);
      }


      return model;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

