
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectCamera : GameObject
  {
    public bool EnableDebugCamera { get { return m_enableDebugCamera; } set { m_enableDebugCamera = value; } }
    private bool m_enableDebugCamera;

    public GameObjectCamera(String a_name, Freeworld3D.Content a_content)
      : base (GameObjectTypeId.GOT_CAMERA, a_name)
    {
      m_enableDebugCamera = false;

      AddInterface(new ICameraLogic(this));
    }

  }
}


// -- EOF
