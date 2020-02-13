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


namespace Freeworld3D
{
  // ------------------------------------------------------------------------
  // Define the content processor metadata
  //
  [ContentProcessor(DisplayName = "Freeworld 3D Processor")]


  // ------------------------------------------------------------------------
  // The content processor
  //
  public class FWProcessor : ContentProcessor<String, Content>
  {
    public override Content Process(String input, ContentProcessorContext context)
    {
      Content content = new Content();
      if (!content.Load(input))
      {
        throw new InvalidContentException();
      }
      return content;
    }
  }


  // ------------------------------------------------------------------------
  // Define the content importer metadata
  //
  [ContentImporter(".cfg", DisplayName = "Freeworld 3D Importer", DefaultProcessor = "Freeworld3D")]


  // ------------------------------------------------------------------------
  // The content importer
  //
  public class FWImporter : ContentImporter<String>
  {
    public override String Import(String filename, ContentImporterContext context)
    {
      return File.ReadAllText(filename);
    }
  }
  

  // ------------------------------------------------------------------------
  // Define the content serializer metadata
  //
  [ContentTypeWriter]


  // ------------------------------------------------------------------------
  // The serialize writer
  //
  public class FWWriter : ContentTypeWriter<Content>
  {
    protected override void Write(ContentWriter cw, Content value)
    {
      // Write the source text for debugging
      cw.Write(value.SourceData);

      // Write the light data
      cw.Write(value.Light.LightDirection);
      cw.Write(value.Light.AmbientColor.R);
      cw.Write(value.Light.AmbientColor.G);
      cw.Write(value.Light.AmbientColor.B);
      cw.Write(value.Light.AmbientColor.A);
      cw.Write(value.Light.DiffuseColor.R);
      cw.Write(value.Light.DiffuseColor.G);
      cw.Write(value.Light.DiffuseColor.B);
      cw.Write(value.Light.DiffuseColor.A);

      // Write the sky data
      cw.Write(value.Sky.Top);
      cw.Write(value.Sky.Bottom);
      cw.Write(value.Sky.Front);
      cw.Write(value.Sky.Back);
      cw.Write(value.Sky.Left);
      cw.Write(value.Sky.Right);

      // Write the fog data
      cw.Write(value.Fog.FogMode);
      cw.Write(value.Fog.FogColor.R);
      cw.Write(value.Fog.FogColor.G);
      cw.Write(value.Fog.FogColor.B);
      cw.Write(value.Fog.FogColor.A);
      cw.Write((double)value.Fog.Start);
      cw.Write((double)value.Fog.End);
      cw.Write((double)value.Fog.Density);

      // Write the terrain data
      cw.Write(value.Terrain.Filename);
      cw.Write(value.Terrain.Type);
      cw.Write(value.Terrain.Size);
      cw.Write((double)value.Terrain.Step);
      cw.Write((double)value.Terrain.MaxHeight);

      // Write the terrain base layers
      cw.Write(value.TerrainBaseLayerList.Count);
      foreach (TerrainBaseLayerData data in value.TerrainBaseLayerList)
      {
        cw.Write(data.Name);
        cw.Write(data.TextureFilename);
        cw.Write((double)data.U);
        cw.Write((double)data.V);
      }

      // Write the terrain alpha layers
      cw.Write(value.TerrainAlphaLayerList.Count);
      foreach (TerrainAlphaLayerData data in value.TerrainAlphaLayerList)
      {
        cw.Write(data.Name);
        cw.Write(data.TextureFilename);
        cw.Write((double)data.U);
        cw.Write((double)data.V);
        cw.Write(data.DetailMode);
        cw.Write(data.AlphaMapFilename);
        cw.Write(data.AlphaMapWidth);
        cw.Write(data.AlphaMapHieght);
      }

      // Write the terrain blend layers
      cw.Write(value.TerrainBlendLayerList.Count);
      foreach (TerrainBlendLayerData data in value.TerrainBlendLayerList)
      {
        cw.Write(data.Name);
        cw.Write(data.TextureFilename);
        cw.Write((double)data.U);
        cw.Write((double)data.V);
        cw.Write(data.SourceBlend);
        cw.Write(data.DestBlend);
      }

      // Write the terrain detail layers
      cw.Write(value.TerrainDetailLayerList.Count);
      foreach (TerrainDetailLayerData data in value.TerrainDetailLayerList)
      {
        cw.Write(data.Name);
        cw.Write(data.TextureFilename);
        cw.Write((double)data.U);
        cw.Write((double)data.V);
        cw.Write(data.BlendMode);
      }

      // Write the mesh array
      cw.Write(value.MeshList.Count);
      foreach (MeshData mesh in value.MeshList)
      {
        cw.Write(mesh.Filename);
        cw.Write(mesh.Transform);
      }

      // Write the entity array
      cw.Write(value.EntityList.Count);
      foreach (EntityData data in value.EntityList)
      {
        cw.Write(data.Name);
        cw.Write(data.Type);
        cw.Write(data.Transform);

        // Write the properties
        cw.Write(data.Properties.Count);
        foreach (KeyValuePair<String, String> property in data.Properties)
        {
          cw.Write(property.Key);
          cw.Write(property.Value);
        }
      }
    }

    public override String GetRuntimeType(TargetPlatform targetPlatform)
    {
      return typeof(Content).AssemblyQualifiedName;
    }

    public override String GetRuntimeReader(TargetPlatform targetPlatform)
    {
      return typeof(FWReader).AssemblyQualifiedName;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

