// ----------------------------------------------------------------------------
// File: SceneObject.cs
// Desc: Manages a scene object instance
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;


namespace WaveRace360
{
  public class DebugSettings
  {
    private Dictionary<String, bool> m_settings;


    public DebugSettings()
    {
      m_settings = new Dictionary<string,bool>();
    }


    public bool Get(String a_name)
    {
      if (m_settings.ContainsKey(a_name))
      {
        return m_settings[a_name];
      }
      else
      {
        return false;
      }
    }


    public void Set(String a_name, bool a_value)
    {
      m_settings[a_name] = a_value;
    }


    public void LoadFromFile()
    {
      // Load default settings from a file, later on...
    }

    
    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF


