// ----------------------------------------------------------------------------
// File: GameObjectEnumerator.cs
// Desc: Enumerates either all or specific types of game objects
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectEnumerator
  {
    private Dictionary<String, GameObject>.Enumerator m_enumerator;
    private GameObjectTypeId m_typeId;
    private bool m_useTypeId;
    private GameObject m_current;


    public GameObjectEnumerator(Dictionary<String, GameObject>.Enumerator a_enumerator)
    {
      m_enumerator = a_enumerator;
      m_useTypeId = false;
      m_current = null;

      AdvanceEnumerator();
    }


    public GameObjectEnumerator(Dictionary<String, GameObject>.Enumerator a_enumerator, GameObjectTypeId a_typeId)
    {
      m_enumerator = a_enumerator;
      m_typeId = a_typeId;
      m_useTypeId = true;
      m_current = null;

      AdvanceEnumerator();
    }


    public GameObject Current()
    {
      return m_current;
    }


    public bool MoveNext()
    {
      return AdvanceEnumerator();
    }


    private bool AdvanceEnumerator()
    {
      bool hasNext = m_enumerator.MoveNext();

      if (!hasNext)
      {
        m_current = null;
        return false;
      }
      else if (m_useTypeId == false || m_enumerator.Current.Value.TypeId == m_typeId)
      {
        m_current = m_enumerator.Current.Value;
        return true;
      }

      while (hasNext)
      {
        hasNext = m_enumerator.MoveNext();

        if (!hasNext)
        {
          m_current = null;
          return false;
        }

        if (m_enumerator.Current.Value.TypeId == m_typeId)
        {
          m_current = m_enumerator.Current.Value;
          return true;
        }
      }

      return false;
    }

    
  };
}


// -- EOF
