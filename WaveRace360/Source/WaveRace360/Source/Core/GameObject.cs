// ----------------------------------------------------------------------------
// File: GameObject.cs
// Desc: Base game object class for any updatable object in the game
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: GameObject
  // Desc: Base game object class for any updatable object in the game
  // --------------------------------------------------------------------------
  public abstract class GameObject
  {
    // ------------------------------------------------------------------------
    // Public Members
    // ------------------------------------------------------------------------
    public String Name { get { return m_name; } }
    public GameObjectTypeId TypeId { get { return m_typeId; } }
    public Matrix Transform { get { return m_transform; } set { SetTransform(value); } }
    public Action CurrentAction { get { return m_action; } }


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    protected String m_name;
    protected GameObjectTypeId m_typeId;
    protected Matrix m_transform;
    protected Action m_action;
    protected Dictionary<GameObjectInterfaceTypeId, GameObjectInterface> m_interfaces;


    // ------------------------------------------------------------------------
    // Name: GameObject
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public GameObject(GameObjectTypeId a_typeId, String a_name)
    {
      m_name = a_name;
      m_typeId = a_typeId;
      m_transform = new Matrix();
      m_interfaces = new Dictionary<GameObjectInterfaceTypeId,GameObjectInterface>();
      GameObjectManager.Instance.AddObject(this);
    }
    

    // ------------------------------------------------------------------------
    // Name: ~GameObject
    // Desc: Desstructor
    // ------------------------------------------------------------------------
    ~GameObject()
    {
      GameObjectManager.Instance.RemoveObject(this);
    }


    // ------------------------------------------------------------------------
    // Name: SetTransform
    // Desc: Sets the transform
    // ------------------------------------------------------------------------
    public virtual void SetTransform(Matrix a_transform)
    {
      m_transform = a_transform;
    }


    // ------------------------------------------------------------------------
    // Name: AddInterface
    // Desc: Adds an interface to the array
    // ------------------------------------------------------------------------
    protected void AddInterface(GameObjectInterface a_interface)
    {
      if (m_interfaces.ContainsKey(a_interface.TypeId))
      {
        throw new ArgumentException("Duplicate named game object");
      }

      m_interfaces[a_interface.TypeId] = a_interface;
    }


    // ------------------------------------------------------------------------
    // Name: GetInterface
    // Desc: Gets an interface from the array
    // ------------------------------------------------------------------------
    public T GetInterface<T>(GameObjectInterfaceTypeId a_typeId) where T : GameObjectInterface
    {
      GameObjectInterface value;
      if (m_interfaces.TryGetValue(a_typeId, out value))
      {
        return value as T;
      }

      return null;
    }


    // ------------------------------------------------------------------------
    // Name: ChangeAction
    // Desc: Create an instance of the given action and set it as the current
    // ------------------------------------------------------------------------
    public void ChangeAction<T>() where T : Action
    {
      if (m_action != null)
      {
        m_action.Complete();
        m_action = null;
      }
      
      m_action = Activator.CreateInstance<T>();
      m_action.SetGameObject(this);
      m_action.Begin();
    }


    // ------------------------------------------------------------------------
    // Name: GetAction
    // Desc: Get the current action as the specified type if it is, otherwise 
    //       returns null.
    // ------------------------------------------------------------------------
    public T GetAction<T>() where T : Action
    {
      return m_action as T;
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Updates the game object's interfaces
    // ------------------------------------------------------------------------
    public virtual void Update(float a_frameTime)
    {
      if (m_action != null)
      {
        m_action.Update(a_frameTime);
      }

      foreach (GameObjectInterface iface in m_interfaces.Values)
      {
        iface.Update(a_frameTime);
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
