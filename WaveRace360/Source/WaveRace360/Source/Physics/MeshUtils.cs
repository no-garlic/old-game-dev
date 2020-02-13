
using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  public class MeshUtils
  {
    public static void CalculateBoundingBox(ModelMesh a_modelMesh, out BoundingBox a_boundingBox)
    {
      // TODO: Needs to iterate over the vertices and generate a tighter box.
      a_boundingBox = BoundingBox.CreateFromSphere(a_modelMesh.BoundingSphere);
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

