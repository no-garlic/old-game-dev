
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectSky : GameObject
  {
    public SkyRender Sky { get { return m_sky; } }
    private SkyRender m_sky;
    
    public GameObjectSky(String a_name, String a_textureName)
      : base (GameObjectTypeId.GOT_SKY, a_name)
    {
      m_sky = new SkyRender(a_textureName);

      AddInterface(new ISkyRender(this, m_sky));
    }

  }
}


// -- EOF
