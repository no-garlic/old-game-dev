
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  public class IModelRender : GameObjectInterface
  {
    private SceneObject m_model;
    private Material m_material;


    public IModelRender(GameObject a_object, SceneObject a_model, Material a_material)
      : base (GameObjectInterfaceTypeId.GOI_RENDER, a_object)
    {
      m_model = a_model;
      m_material = a_material;
    }
    

    public override void Update(float a_frameTime)
    {
      if (m_model.Visible)
      {
        Matrix transform = Matrix.CreateScale(1.0f, 1.0f, -1.0f) * Object.Transform;
        m_material.AddForRender(m_model, RenderPriority.StaticMesh, transform, CullMode.CullClockwiseFace);
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF
