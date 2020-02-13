
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  public class IPlayerRender : GameObjectInterface
  {
    private SceneObject m_model;
    private Material m_material;


    public IPlayerRender(GameObject a_object)
      : base (GameObjectInterfaceTypeId.GOI_RENDER, a_object)
    {
      m_model = new SceneObject("sea-doo");
      m_material = MaterialManager.Instance.GetMaterial<SceneObjectMaterial>("SceneObjectShader");
    }
    

    public override void Update(float a_frameTime)
    {
      m_model.Transform = Object.Transform;

      Matrix transform = Matrix.CreateScale(1.0f, 1.0f, -1.0f) * m_model.Transform;
      m_material.AddForRender(m_model, RenderPriority.StaticMesh, transform, CullMode.CullClockwiseFace);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
