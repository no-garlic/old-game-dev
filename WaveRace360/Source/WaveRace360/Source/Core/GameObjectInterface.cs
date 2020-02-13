// ----------------------------------------------------------------------------
// File: GameObjectInterface.cs
// Desc: An interface for the game object
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: GameObjectInterface
  // Desc: An interface for the game object
  // --------------------------------------------------------------------------
  public abstract class GameObjectInterface
  {
    // ------------------------------------------------------------------------
    // Public Members
    // ------------------------------------------------------------------------
    public GameObject Object { get { return m_object; } }
    public GameObjectInterfaceTypeId TypeId { get { return m_typeId; } }


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private GameObject m_object;
    private GameObjectInterfaceTypeId m_typeId;


    // ------------------------------------------------------------------------
    // Name: GameObjectInterface
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public GameObjectInterface(GameObjectInterfaceTypeId a_typeId, GameObject a_object)
    {
      m_typeId = a_typeId;
      m_object = a_object;
    }
    

    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Updates the game object
    // ------------------------------------------------------------------------
    public abstract void Update(float a_frameTime);


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
