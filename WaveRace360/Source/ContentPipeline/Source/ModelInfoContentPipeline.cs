using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Content.Pipeline;
using Microsoft.Xna.Framework.Content.Pipeline.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline.Processors;
using Microsoft.Xna.Framework.Content.Pipeline.Serialization.Compiler;
using System.IO;


namespace AssetData
{
  // ------------------------------------------------------------------------
  // Define the content serializer metadata
  //
  [ContentTypeWriter]


  // ------------------------------------------------------------------------
  // The serialize writer
  //
  public class ModelInfoWriter : ContentTypeWriter<ModelInfo>
  {
    protected override void Write(ContentWriter cw, ModelInfo value)
    {
      /*
      <?xml version="1.0" encoding="utf-8" ?>
      <XnaContent>
        <Asset Type="AssetData.ModelInfo">
          <TwoSided>false</TwoSided>
          <AlphaBlend>false</AlphaBlend>
          <AlphaMask>false</AlphaMask>
          <ReferenceAlpha>0</ReferenceAlpha>
        </Asset>
      </XnaContent>
      */

      cw.Write(value.TwoSided);
      cw.Write(value.AlphaBlend);
      cw.Write(value.AlphaMask);
      cw.Write(value.ReferenceAlpha);
    }

    public override String GetRuntimeType(TargetPlatform targetPlatform)
    {
      return typeof(ModelInfo).AssemblyQualifiedName;
    }

    public override String GetRuntimeReader(TargetPlatform targetPlatform)
    {
      return typeof(ModelInfoReader).AssemblyQualifiedName;
    }
  }
}


// -- EOF

