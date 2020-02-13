
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using JigLibX.Collision;




namespace WaveRace360
{
  public class IPlayerPhysics : GameObjectInterface
  {
    public float Throttle { get { return m_throttle; } set { m_throttle = value; } }
    public float Steering { get { return m_steering; } set { m_steering = value; } }


    private float m_throttle;   // The throttle (0..1)
    private float m_steering;   // The steering (-1..0..1)
    private PhysicsBodySeaDoo m_playerPhysics;

    private Vector3 m_initialPosition;
    private Matrix m_initialOrientation;
    

    public IPlayerPhysics(GameObject a_object, Freeworld3D.Content a_content)
      : base (GameObjectInterfaceTypeId.GOI_PHYSICS, a_object)
    {
      // Ensure that there is 1 player entity defined
      if (EntityManager.Instance.Player.Count != 1)
      {
        throw new Exception("Exactly 1 player entity must be defined, found: " + Convert.ToString(EntityManager.Instance.Player.Count));
      }

      // Get the transform from the player entity
      EntityPlayer ePlayer = EntityManager.Instance.Player[0];
      Object.Transform = ePlayer.Transform;

      // Get the water game object
      GameObjectWater goWater = GameObjectManager.Instance.FindObject<GameObjectWater>("Water");
      if (goWater == null)
      {
        throw new Exception("The Water game object was not found");
      }

      // Copy the parent game object's transform
      Matrix transform = Object.Transform;

      // Move the transform to the position and orientation of the entity - this is where the render
      // model is placed.
      Vector3 startPos = transform.Translation;
      startPos.Y = goWater.Water.Mesh.GetHeightAt(startPos.X, startPos.Z);
      transform.Translation = startPos;
      Object.Transform = transform;

      // Now we start work on the physics body - create an orientation transform from the entity
      // transform.
      m_initialOrientation = transform;
      m_initialOrientation.Translation = Vector3.Zero;

      // Move the position up a little from the entity position, so it will drop and settle upon
      // being spawned.
      m_initialPosition = transform.Translation + new Vector3(0.0f, 0.5f, 0.0f);

      // Create the physics body for the player
      MaterialProperties playerMaterial = new MaterialProperties(0.3f, 0.5f, 0.3f);
      m_playerPhysics = new PhysicsBodySeaDoo(goWater.Water.Mesh, new Vector3(3.5f, 1.0f, 8.5f), Matrix.Identity, Vector3.Zero, playerMaterial);
      m_playerPhysics.Skin.LinkedObjectName = Object.Name;
      m_playerPhysics.Body.MoveTo(m_initialPosition, m_initialOrientation);
    }
    

    public override void Update(float a_frameTime)
    {
      // Set the inputs to the player physics
      m_playerPhysics.Throttle = m_throttle;
      m_playerPhysics.Steering = m_steering;

      // Ignore the throttle and steering when the debug camera mode is active
      GameObjectCamera camera = GameObjectManager.Instance.FindObject<GameObjectCamera>("Camera");
      if (camera != null)
      {
        ICameraLogic cameraLogic = camera.GetInterface<ICameraLogic>(GameObjectInterfaceTypeId.GOI_LOGIC);
        if (cameraLogic != null)
        {
          if (cameraLogic.DebugCameraMode)
          {
            m_playerPhysics.Throttle = 0.0f;
            m_playerPhysics.Steering = 0.0f;
            m_playerPhysics.Body.Velocity = Vector3.Zero;
          }
        }
      }

      // Reset the position of the player
      if (Systems.GamePad.IsButtonPressed(Microsoft.Xna.Framework.Input.Buttons.LeftShoulder))
      {
        m_playerPhysics.Body.Velocity = Vector3.Zero;
        m_playerPhysics.Body.MoveTo(m_initialPosition, m_initialOrientation);
      }

      // Update the player physics
      m_playerPhysics.Update(a_frameTime);

      // Set the parent game object transform to be the render matrix from the player physics
      Object.Transform = m_playerPhysics.RenderMatrix;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
