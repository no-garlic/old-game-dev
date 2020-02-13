
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public abstract class Action
  {
    private String m_name;
    public String Name { get { return m_name; } }

    private GameObject m_object;
    public GameObject Object { get { return m_object; } }


    public Action(String a_name)
    {
      m_name = a_name;
    }

    
    public virtual void SetGameObject(GameObject a_object)
    {
      m_object = a_object;
    }


    public abstract void Begin();
    public abstract void Complete();
    public abstract void Update(float a_frameTime);

  

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
