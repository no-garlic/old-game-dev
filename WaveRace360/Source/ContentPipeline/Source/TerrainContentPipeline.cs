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


namespace Terrain
{
  // ------------------------------------------------------------------------
  // Define the content processor metadata
  //
  [ContentProcessor(DisplayName = "RawData Processor")]


  // ------------------------------------------------------------------------
  // The content processor
  //
  public class RawDataProcessor : ContentProcessor<RawData, RawData>
  {
    public override RawData Process(RawData input, ContentProcessorContext context)
    {
      return new RawData(input.Data);
    }
  }


  // ------------------------------------------------------------------------
  // Define the content importer metadata
  //
  [ContentImporter(".raw", DisplayName = "RawData Importer", DefaultProcessor = "RawDataProcessor")]


  // ------------------------------------------------------------------------
  // The content importer
  //
  public class RawDataImporter : ContentImporter<RawData>
  {
    public override RawData Import(String filename, ContentImporterContext context)
    {
      byte[] bytes = File.ReadAllBytes(filename);
      return new RawData(bytes);
    }
  }

  // ------------------------------------------------------------------------
  // Define the content serializer metadata
  //
  [ContentTypeWriter]


  // ------------------------------------------------------------------------
  // The serialize writer
  //
  public class RawDataWriter : ContentTypeWriter<RawData>
  {
    protected override void Write(ContentWriter cw, RawData value)
    {
      cw.Write(value.Count);
      cw.Write(value.Data);
    }

    public override String GetRuntimeType(TargetPlatform targetPlatform)
    {
      return typeof(RawData).AssemblyQualifiedName;
    }

    public override String GetRuntimeReader(TargetPlatform targetPlatform)
    {
      return typeof(RawDataReader).AssemblyQualifiedName;
    }
  }
}


// -- EOF

