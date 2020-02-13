// ----------------------------------------------------------------------------
// File: EntityManager.cs
// Desc: The Manager that holds all entites that are defined in hte current level
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: EntityManager
  // Desc: The Manager that holds all entites that are defined in hte current 
  //       level
  // --------------------------------------------------------------------------
  public class EntityManager
  {
    // ------------------------------------------------------------------------
    // Public Members
    // ------------------------------------------------------------------------
    public static EntityManager       Instance      { get { return s_instance; } }
    public List<EntityPosition>       Position      { get { return m_position; } }
    public List<EntityPlayer>         Player        { get { return m_player; } }
    public List<EntityPhysicsBox>     PhysicsBox    { get { return m_physicsBox; } }
    public List<EntityPhysicsSphere>  PhysicsSphere { get { return m_physicsSphere; } }


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    private static EntityManager        s_instance = new EntityManager();
    private List<EntityPosition>        m_position;         // All position entities
    private List<EntityPlayer>          m_player;           // All player entities
    private List<EntityPhysicsBox>      m_physicsBox;       // All physics box entities
    private List<EntityPhysicsSphere>   m_physicsSphere;    // All physics sphere entities

    
    // ------------------------------------------------------------------------
    // Name: EntityManager
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public EntityManager()
    {
      m_position = new List<EntityPosition>();
      m_player = new List<EntityPlayer>();
      m_physicsBox = new List<EntityPhysicsBox>();
      m_physicsSphere = new List<EntityPhysicsSphere>();
    }


    // ------------------------------------------------------------------------
    // Name: Load
    // Desc: Load all entities for the given content
    // Parm: Freeworld3D.Content a_content - the content to load the entities 
    //       from
    // ------------------------------------------------------------------------
    public void Load(Freeworld3D.Content a_content)
    {
      foreach (Freeworld3D.EntityData data in a_content.EntityList)
      {
        // Position 
        if (data.Type == "Position")
        {
          m_position.Add(new EntityPosition(data));
        }

        // Player
        else if (data.Type == "Player")
        {
          m_player.Add(new EntityPlayer(data));
        }

        // Physics Box
        else if (data.Type == "PhysicsBox")
        {
          m_physicsBox.Add(new EntityPhysicsBox(data));
        }

        // Physics Sphere
        else if (data.Type == "PhysicsSphere")
        {
          m_physicsSphere.Add(new EntityPhysicsSphere(data));
        }

        // Unknown
        else
        {
          throw new Exception("Unknown entity type: " + data.Type);
        }
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

