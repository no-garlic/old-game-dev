using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using System.IO;


namespace Freeworld3D
{
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
      content.SourceData = cr.ReadString();
      
      // Read the light data
      content.Light.LightDirection = cr.ReadVector3();
      content.Light.AmbientColor = new Color(cr.ReadByte(), cr.ReadByte(), cr.ReadByte(), cr.ReadByte());
      content.Light.DiffuseColor = new Color(cr.ReadByte(), cr.ReadByte(), cr.ReadByte(), cr.ReadByte());
      
      // Read the sky data
      content.Sky.Top = cr.ReadString();
      content.Sky.Bottom = cr.ReadString();
      content.Sky.Front = cr.ReadString();
      content.Sky.Back = cr.ReadString();
      content.Sky.Left = cr.ReadString();
      content.Sky.Right = cr.ReadString();

      // Read the fog data
      content.Fog.FogMode = cr.ReadString();
      content.Fog.FogColor = new Color(cr.ReadByte(), cr.ReadByte(), cr.ReadByte(), cr.ReadByte());
      content.Fog.Start = (float) cr.ReadDouble();
      content.Fog.End = (float) cr.ReadDouble();
      content.Fog.Density = (float) cr.ReadDouble();
      
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

