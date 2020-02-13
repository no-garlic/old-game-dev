
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class GameObjectModel : GameObject
  {
    public SceneObject Model { get { return m_model; } }
    private SceneObject m_model;
    private Material m_material;
    
    public GameObjectModel(String a_name, String a_modelName, String a_materialName)
      : base (GameObjectTypeId.GOT_MODEL, a_name)
    {
      m_model = new SceneObject(a_modelName);
      m_model.Transform = m_transform;

      m_material = MaterialManager.Instance.GetMaterial<Material>(a_materialName);

      AddInterface(new IModelRender(this, m_model, m_material));
      AddInterface(new IModelPhysics(this));
    }


    public override void SetTransform(Matrix a_transform)
    {
      m_transform = a_transform;
      m_model.Transform = a_transform;
    }

  }
}


// -- EOF
