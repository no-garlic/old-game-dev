
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  public class ICameraLogic : GameObjectInterface
  {
    private CameraFly m_debugCamera;
    private bool m_debugCameraMode;

    public bool DebugCameraMode { get { return m_debugCameraMode; } }

    public ICameraLogic(GameObject a_object)
      : base (GameObjectInterfaceTypeId.GOI_LOGIC, a_object)
    {
      m_debugCamera = new CameraFly();
      m_debugCameraMode = false;
    }
    

    public override void Update(float a_frameTime)
    {
      Camera3D.SetProjection(MathHelper.PiOver4, 1280.0f / 720.0f, 1.0f, 4000.0f);

      if (Systems.GamePad.IsButtonPressed(Microsoft.Xna.Framework.Input.Buttons.RightShoulder))
      {
        m_debugCameraMode = !m_debugCameraMode;
      }

      if (m_debugCameraMode)
      {
        m_debugCamera.Update(a_frameTime);
      }
      else
      {
        GameObjectPlayer targetObject = GameObjectManager.Instance.FindObject<GameObjectPlayer>("Player");

        Vector3 cameraAt  = targetObject.Transform.Translation + (Vector3.Up * 3.0f);
        Vector3 cameraPos = cameraAt + ((targetObject.Transform.Forward) * 14.0f) + (Vector3.Up * 1.5f);
        cameraPos.Y = 9.0f;
        Camera3D.SetLookAt(cameraPos, cameraAt, Vector3.Up);
      }

      Object.Transform = Systems.CameraSettings.ViewMatrix;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
