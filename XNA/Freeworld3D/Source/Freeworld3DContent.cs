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
      cw.Write(value.Data);

      // Write the terrain data
      cw.Write(value.Terrain.Filename);
      cw.Write(value.Terrain.Type);
      cw.Write(value.Terrain.Size);
      cw.Write((double) value.Terrain.Step);
      cw.Write((double) value.Terrain.MaxHeight);
      
      // Write the terrain base layers
      cw.Write(value.TerrainBaseLayerList.Count);
      foreach (TerrainBaseLayerData data in value.TerrainBaseLayerList)
      {
        cw.Write(data.Name);
        cw.Write(data.TextureFilename);
        cw.Write((double) data.U);
        cw.Write((double) data.V);
      }

      // Write the terrain alpha layers
      cw.Write(value.TerrainAlphaLayerList.Count);
      foreach (TerrainAlphaLayerData data in value.TerrainAlphaLayerList)
      {
        cw.Write(data.Name);
        cw.Write(data.TextureFilename);
        cw.Write((double) data.U);
        cw.Write((double) data.V);
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
        cw.Write((double) data.U);
        cw.Write((double) data.V);
        cw.Write(data.SourceBlend);
        cw.Write(data.DestBlend);
      }

      // Write the terrain detail layers
      cw.Write(value.TerrainDetailLayerList.Count);
      foreach (TerrainDetailLayerData data in value.TerrainDetailLayerList)
      {
        cw.Write(data.Name);
        cw.Write(data.TextureFilename);
        cw.Write((double) data.U);
        cw.Write((double) data.V);
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
        foreach(KeyValuePair<String, String> property in data.Properties)
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
      return "Freeworld3D.FWReader, Freeworld3D, Version=1.0,Culture=neutral";
    }
  }


  // ------------------------------------------------------------------------
  // // The serialize reader
  //
  public class FWReader : ContentTypeReader<Content>
  {
    protected override Content Read(ContentReader cr, Content existingInstance)
    {
      Content content = new Content();
      int count = 0;

      // Read the source data for debugging
      content.Data = cr.ReadString();

      // Read the terrain data
      content.Terrain.Filename = cr.ReadString();
      content.Terrain.Type = cr.ReadString();
      content.Terrain.Size = cr.ReadInt32();
      content.Terrain.Step = (float) cr.ReadDouble();
      content.Terrain.MaxHeight = (float) cr.ReadDouble();

      // Read the terrain base layers
      count = cr.ReadInt32();
      for (int i = 0; i < count; i++)
      {
        TerrainBaseLayerData data = new TerrainBaseLayerData();
        data.Name = cr.ReadString();
        data.TextureFilename = cr.ReadString();
        data.U = (float) cr.ReadDouble();
        data.V = (float) cr.ReadDouble();
        content.TerrainBaseLayerList.Add(data);
      }

      // Read the terrain alpha layers
      count = cr.ReadInt32();
      for (int i = 0; i < count; i++)
      {
        TerrainAlphaLayerData data = new TerrainAlphaLayerData();
        data.Name = cr.ReadString();
        data.TextureFilename = cr.ReadString();
        data.U = (float) cr.ReadDouble();
        data.V = (float) cr.ReadDouble();
        data.DetailMode = cr.ReadBoolean();
        data.AlphaMapFilename = cr.ReadString();
        data.AlphaMapWidth = cr.ReadInt32();
        data.AlphaMapHieght = cr.ReadInt32();
        content.TerrainAlphaLayerList.Add(data);
      }

      // Read the terrain blend layers
      count = cr.ReadInt32();
      for (int i = 0; i < count; i++)
      {
        TerrainBlendLayerData data = new TerrainBlendLayerData();
        data.Name = cr.ReadString();
        data.TextureFilename = cr.ReadString();
        data.U = (float) cr.ReadDouble();
        data.V = (float) cr.ReadDouble();
        data.SourceBlend = cr.ReadString();
        data.DestBlend = cr.ReadString();
        content.TerrainBlendLayerList.Add(data);
      }

      // Read the terrain detail layers
      count = cr.ReadInt32();
      for (int i = 0; i < count; i++)
      {
        TerrainDetailLayerData data = new TerrainDetailLayerData();
        data.Name = cr.ReadString();
        data.TextureFilename = cr.ReadString();
        data.U = (float) cr.ReadDouble();
        data.V = (float) cr.ReadDouble();
        data.BlendMode = cr.ReadString();
        content.TerrainDetailLayerList.Add(data);
      }

      // Read the mesh list
      count = cr.ReadInt32();
      for (int i = 0; i < count; i++)
      {
        MeshData data = new MeshData();
        data.Filename = cr.ReadString();
        data.Transform = cr.ReadMatrix();
        content.MeshList.Add(data);
      }

      // Read the entity array
      count = cr.ReadInt32();
      for (int i = 0; i < count; i++)
      {
        EntityData data = new EntityData();
        data.Name = cr.ReadString();
        data.Type = cr.ReadString();
        data.Transform = cr.ReadMatrix();
        int propCount = cr.ReadInt32();
        for (int p = 0; p < propCount; p++)
        {
          data.Properties.Add(cr.ReadString(), cr.ReadString());
        }
        content.EntityList.Add(data);
      }

      return content;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

