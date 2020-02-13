
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;

using JigLibX.Collision;




namespace WaveRace360
{
  public class GameLoaderStaticMeshes : GameLoader
  {
    private List<Freeworld3D.MeshData>.Enumerator m_iterator;

    public GameLoaderStaticMeshes(GameLevel a_level, String a_levelName, Freeworld3D.Content a_content)
    : base(a_level, a_levelName, a_content)
    {
      m_iterator = m_loadContent.MeshList.GetEnumerator();
    }


    public override void LoadNextItem()
    {
      if (m_iterator.MoveNext())
      {
        Freeworld3D.MeshData mesh = m_iterator.Current;

        GameObjectModel gObj = new GameObjectModel(Utils.RandomName(), mesh.Filename, "SceneObjectShader");
        gObj.Transform = mesh.Transform;
//        gObj.Model.CreatePhysicsBodyBox(Systems.MaterialTable.GetMaterialProperties((int) MaterialTable.MaterialID.NormalNormal));
      }
      else
      {
        SetLoaded();
      }
    }
    

  }
}


// -- EOF
  