// ----------------------------------------------------------------------------
// File: MaterialManager.cs
// Desc: Manager class for all materials.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: MaterialManager
  // Desc: MaterialManager class for all materials.
  // --------------------------------------------------------------------------
  public class MaterialManager
  {
    // ------------------------------------------------------------------------
    // Public Members
    // ------------------------------------------------------------------------
    public static MaterialManager Instance { get { return s_instance; } }


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private static MaterialManager s_instance = new MaterialManager();
    private Dictionary<String, Material> m_materials;


    // ------------------------------------------------------------------------
    // Name: Material
    // Desc: Constructor
    // Parm: String a_effectName - the name of the effect file to load
    // ------------------------------------------------------------------------
    public MaterialManager()
    {
      m_materials = new Dictionary<string,Material>();
    }


    // ------------------------------------------------------------------------
    // Name: AddMaterial
    // Desc: Add the material
    // ------------------------------------------------------------------------
    public void AddMaterial(String a_name, Material a_material)
    {
      Material material;
      if (m_materials.TryGetValue(a_name, out material))
      {
        throw new InvalidOperationException("Cannot manage duplicate material names");
      }

      m_materials[a_name] = a_material;
    }


    // ------------------------------------------------------------------------
    // Name: GetMaterial
    // Desc: Get the material for the given name
    // ------------------------------------------------------------------------
    public T GetMaterial<T>(String a_name) where T : Material
    {
      Material material;
      if (m_materials.TryGetValue(a_name, out material))
      {
        return material as T;
      }

      return null;
    }
    

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

