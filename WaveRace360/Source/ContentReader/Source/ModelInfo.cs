using System;
using System.Collections.Generic;
using System.IO;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;


namespace AssetData
{
  public class ModelInfo
  {
    public bool TwoSided = false;
    public bool AlphaBlend = false;
    public bool AlphaMask = false;
    public int  ReferenceAlpha = 0;
  }


  public class ModelInfoReader : ContentTypeReader<ModelInfo>
  {
    protected override ModelInfo Read(ContentReader cr, ModelInfo existingInstance)
    {
      ModelInfo info = new ModelInfo();

      info.TwoSided = cr.ReadBoolean();
      info.AlphaBlend = cr.ReadBoolean();
      info.AlphaMask = cr.ReadBoolean();
      info.ReferenceAlpha = cr.ReadInt32();

      return info;
    }
  }


}


// -- EOF

