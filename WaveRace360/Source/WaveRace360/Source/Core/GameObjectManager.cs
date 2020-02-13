// ----------------------------------------------------------------------------
// File: GameObjectManager.cs
// Desc: Manages all game objects
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: GameObjectManager
  // Desc: Manages all game objects
  // --------------------------------------------------------------------------
  public class GameObjectManager
  {
    // ------------------------------------------------------------------------
    // Public Members
    // ------------------------------------------------------------------------
    public static GameObjectManager Instance { get { return s_instance; } }

    
    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private static GameObjectManager s_instance = new GameObjectManager();
    private Dictionary<String, GameObject> m_objects;


    // ------------------------------------------------------------------------
    // Name: GameObject
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public GameObjectManager()
    {
      m_objects = new Dictionary<string, GameObject>();
    }


    // ------------------------------------------------------------------------
    // Name: AddObject
    // Desc: Add a game object to the manager
    // ------------------------------------------------------------------------
    public void AddObject(GameObject a_object)
    {
      if (m_objects.ContainsKey(a_object.Name))
      {
        throw new ArgumentException("Duplicate named game object");
      }

      m_objects[a_object.Name] = a_object;
    }


    // ------------------------------------------------------------------------
    // Name: RemoveObject
    // Desc: Remove a game object from the manager
    // ------------------------------------------------------------------------
    public void RemoveObject(GameObject a_object)
    {
      if (!m_objects.ContainsKey(a_object.Name))
      {
        throw new ArgumentException("Game object not found");
      }

      m_objects.Remove(a_object.Name);
    }


    // ------------------------------------------------------------------------
    // Name: FindObject
    // Desc: Find a game object by name
    // ------------------------------------------------------------------------
    public T FindObject<T>(String a_name) where T : GameObject
    {
      GameObject value;
      if (m_objects.TryGetValue(a_name, out value))
      {
        return value as T;
      }

      return null;
    }

    
    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Updates the all game objects
    // ------------------------------------------------------------------------
    public void Update(float a_frameTime)
    {
      foreach (GameObject obj in m_objects.Values)
      {
        obj.Update(a_frameTime);
      }
    }


    // ------------------------------------------------------------------------
    // Name: GetEnumerator
    // Desc: Get an enumerator over all game objects
    // ------------------------------------------------------------------------
    public GameObjectEnumerator GetEnumerator()
    {
      return new GameObjectEnumerator(m_objects.GetEnumerator());
    }


    // ------------------------------------------------------------------------
    // Name: GetEnumerator
    // Desc: Get an enumerator over all game objects of the given type
    // ------------------------------------------------------------------------
    public GameObjectEnumerator GetEnumerator(GameObjectTypeId a_typeId)
    {
      return new GameObjectEnumerator(m_objects.GetEnumerator(), a_typeId);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
