
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public abstract class GameLoader
  {
    protected GameLevel m_level;
    protected bool m_isLoaded;
    protected String m_levelName;
    protected Freeworld3D.Content m_loadContent;

    public GameLoader(GameLevel a_level, String a_levelName, Freeworld3D.Content a_content)
    {
      m_level = a_level;
      m_levelName = a_levelName;
      m_loadContent = a_content;
    }

    
    public void SetLoaded()
    {
      m_isLoaded = true;
    }


    public bool IsLoaded()
    {
      return m_isLoaded;
    }


    public abstract void LoadNextItem();


  }
}


// -- EOF
