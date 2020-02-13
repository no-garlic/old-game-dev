using System;
using System.Collections.Generic;
using System.IO;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Content.Pipeline;
using Microsoft.Xna.Framework.Content.Pipeline.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline.Processors;
using Microsoft.Xna.Framework.Content.Pipeline.Serialization.Compiler;

using Common;


namespace Freeworld3D
{
  public class MeshData
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public String Filename;
    public Matrix Transform;
  }


  public class TerrainData
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public String Filename;
    public int    Size;
    public float  Step;
    public float  MaxHeight;
    public String Type;
  }

  public class TerrainBaseLayerData
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public String Name;
    public String TextureFilename;
    public float  U;
    public float  V;
  }

  public class TerrainAlphaLayerData
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public String Name;
    public String TextureFilename;
    public float  U;
    public float  V;
    public bool   DetailMode;
    public String AlphaMapFilename;
    public int    AlphaMapWidth;
    public int    AlphaMapHieght;
  }

  public class TerrainBlendLayerData
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public String Name;
    public String TextureFilename;
    public float  U;
    public float  V;
    public String SourceBlend;
    public String DestBlend;
  }

  public class TerrainDetailLayerData
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public String Name;
    public String TextureFilename;
    public float  U;
    public float  V;
    public String BlendMode;
  }


  public class EntityData
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public String Name;
    public String Type;
    public Matrix Transform;
    public Dictionary<String, String> Properties;

    public EntityData() { Properties = new Dictionary<String, String>(); }
  }


  public class Content
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public List<MeshData>                 MeshList;
    public TerrainData                    Terrain;
    public String                         Data;
    public List<TerrainBaseLayerData>     TerrainBaseLayerList;
    public List<TerrainAlphaLayerData>    TerrainAlphaLayerList;
    public List<TerrainBlendLayerData>    TerrainBlendLayerList;
    public List<TerrainDetailLayerData>   TerrainDetailLayerList;
    public List<EntityData>               EntityList;


    // ------------------------------------------------------------------------
    // Constructor
    //
    public Content()
    {
      MeshList                = new List<MeshData>();
      Terrain                 = new TerrainData();
      TerrainBaseLayerList    = new List<TerrainBaseLayerData>();
      TerrainAlphaLayerList   = new List<TerrainAlphaLayerData>();
      TerrainBlendLayerList   = new List<TerrainBlendLayerData>();
      TerrainDetailLayerList  = new List<TerrainDetailLayerData>();
      EntityList              = new List<EntityData>();
    }


    // ------------------------------------------------------------------------
    // Enumeration of the types of data to read from the file
    //
    enum ReadType
    {
      READ_NONE,                // Nothing
      READ_MESH,                // Meshes
      READ_TERRAIN,             // Terrain geometry
      READ_TERRAIN_LAYER,       // Terrain texture / layer
      READ_ENTITY               // Entity instances
    };


    // ------------------------------------------------------------------------
    // Load the content from the String provided
    //
    public bool Load(String a_data)
    {
      Data = a_data;

      Parser parser = new Parser();
      parser.Create(a_data);

      ReadType readType = ReadType.READ_NONE;      
      
      // Iterate through all items
      foreach (Parser.TokenItem item in parser.TokenItems)
      {
        // Find the type of data we are reading
        if (item.Indent == 1)
        {
          if (item.Tokens.Count > 0)
          {
            String typeName = item.Tokens[0];

            if (typeName == "SCENELAYERS")
              readType = ReadType.READ_MESH;
            else if (typeName == "TERRAIN")
              readType = ReadType.READ_TERRAIN;
            else if (typeName == "TERRAINLAYERS")
              readType = ReadType.READ_TERRAIN_LAYER;
            else if (typeName == "ENTITIES")
              readType = ReadType.READ_ENTITY;
            else 
              readType = ReadType.READ_NONE;
          }
        }
                
        // Add a mesh
        if (readType == ReadType.READ_MESH && item.Indent == 3)
        {
          AddMesh(item.Tokens);
          continue;
        }

        // Add the terrain
        if (readType == ReadType.READ_TERRAIN && item.Indent == 1)
        {
          AddTerrain(item.Tokens);
          continue;
        }
        
        // Add a terrain layer
        if (readType == ReadType.READ_TERRAIN_LAYER && item.Indent == 2)
        {
          AddTerrainLayer(item.Tokens);
          continue;
        }

        // Add an entity
        if (readType == ReadType.READ_ENTITY && item.Indent == 3)
        {
          AddEntity(item.Tokens);
          continue;
        }

        // Add an entity property
        if (readType == ReadType.READ_ENTITY && item.Indent == 4)
        {
          AddEntityProperty(item.Tokens);
          continue;
        }
      }
      return true;
    }

       
    // ------------------------------------------------------------------------
    // Add a mesh
    //
    private void AddMesh(List<String> a_tokens)
    {
      // pot1.X,7,Euler,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,40.521508,9.592181,15.444002,1.000000

      if (a_tokens.Count != 19)
      {
        throw new Exception("Invalid format for mesh section");
      }

      if (a_tokens[2] != "Euler")
      {
        throw new Exception("Only euler transforms are supported, please re-export with euler transforms selected rather than vector + quaternion");
      }

      Freeworld3D.MeshData mesh = new Freeworld3D.MeshData();
      
      mesh.Filename = StringUtil.RemoveFileExtension(a_tokens[0]);

      mesh.Transform.M11 = (float) Convert.ToDouble(a_tokens[3]);
      mesh.Transform.M12 = (float) Convert.ToDouble(a_tokens[4]);
      mesh.Transform.M13 = (float) Convert.ToDouble(a_tokens[5]);
      mesh.Transform.M14 = (float) Convert.ToDouble(a_tokens[6]);

      mesh.Transform.M21 = (float) Convert.ToDouble(a_tokens[7]);
      mesh.Transform.M22 = (float) Convert.ToDouble(a_tokens[8]);
      mesh.Transform.M23 = (float) Convert.ToDouble(a_tokens[9]);
      mesh.Transform.M24 = (float) Convert.ToDouble(a_tokens[10]);

      mesh.Transform.M31 = (float) Convert.ToDouble(a_tokens[11]);
      mesh.Transform.M32 = (float) Convert.ToDouble(a_tokens[12]);
      mesh.Transform.M33 = (float) Convert.ToDouble(a_tokens[13]);
      mesh.Transform.M34 = (float) Convert.ToDouble(a_tokens[14]);

      mesh.Transform.M41 = (float) Convert.ToDouble(a_tokens[15]);
      mesh.Transform.M42 = (float) Convert.ToDouble(a_tokens[16]);
      mesh.Transform.M43 = (float) Convert.ToDouble(a_tokens[17]);
      mesh.Transform.M44 = (float) Convert.ToDouble(a_tokens[18]);

      MeshList.Add(mesh);
    }


    // ------------------------------------------------------------------------
    // Add the terrain
    //
    private void AddTerrain(List<String> a_tokens)
    {
      // terrain size, step, heightmap, type, max height
      // TERRAIN,65,4.000000,/terrain/heightmap.bmp,24bitBMP,1.000000

      if (a_tokens.Count != 6)
      {
        throw new Exception("Invalid format for terrain section");
      }

      Terrain.Size        = Convert.ToInt32(a_tokens[1]);
      Terrain.Step        = (float) Convert.ToDouble(a_tokens[2]);
      Terrain.Filename    = StringUtil.RemoveFilePathAndExtension(a_tokens[3]);
      Terrain.Type        = a_tokens[4];
      Terrain.MaxHeight   = (float) Convert.ToDouble(a_tokens[5]);
    }


    // ------------------------------------------------------------------------
    // Add a terrain layer
    //
    private void AddTerrainLayer(List<String> a_tokens)
    {
      if (a_tokens.Count == 0)
      {
        throw new Exception("Invalid format for terrain layer section");
      }

      String layerType = a_tokens[0];
      if (layerType == "BASELAYER")
      {
        AddTerrainBaseLayer(a_tokens);
        return;
      }
      else if (layerType == "ALPHALAYER")
      {
        AddTerrainAlphaLayer(a_tokens);
        return;
      }
      else if (layerType == "DETAILLAYER")
      {
        AddTerrainDetailLayer(a_tokens);
        return;
      }
      else if (layerType == "BLENDLAYER")
      {
        AddTerrainBlendLayer(a_tokens);
        return;
      }
      else 
      {
        throw new Exception("Invalid format for terrain layer section");
      }
    }  


    // ------------------------------------------------------------------------
    // Add a terrain base layer
    //
    private void AddTerrainBaseLayer(List<String> a_tokens)
    {
	    // layer type, name, texture, scale u, scale v
      // BASELAYER,    New Layer,  /terrain/New Layer.jpg,   1.000000, 1.000000

      if (a_tokens.Count != 5)
      {
        throw new Exception("Invalid format for terrain base layer section");
      }

      TerrainBaseLayerData layer = new TerrainBaseLayerData();

      layer.Name              = a_tokens[1];
      layer.TextureFilename   = StringUtil.RemoveFilePathAndExtension(a_tokens[2]);
      layer.U                 = (float) Convert.ToDouble(a_tokens[3]);
      layer.V                 = (float) Convert.ToDouble(a_tokens[4]);

      TerrainBaseLayerList.Add(layer);
    }    


    // ------------------------------------------------------------------------
    // Add a terrain alpha layer
    //
    private void AddTerrainAlphaLayer(List<String> a_tokens)
    {
      // layer type, name, texture, scale u, scale v, detail mode, alpha map, alpha width, alpha height
	    // ALPHALAYER,   New Layer1, /terrain/New Layer1.jpg,  1.000000, 1.000000, False,  New Layer1_alpha.raw, 32, 32

      if (a_tokens.Count != 9)
      {
        throw new Exception("Invalid format for terrain alpha layer section");
      }

      TerrainAlphaLayerData layer = new TerrainAlphaLayerData();

      layer.Name              = a_tokens[1];
      layer.TextureFilename   = StringUtil.RemoveFilePathAndExtension(a_tokens[2]);
      layer.U                 = (float) Convert.ToDouble(a_tokens[3]);
      layer.V                 = (float) Convert.ToDouble(a_tokens[4]);
      layer.AlphaMapFilename  = StringUtil.RemoveFilePathAndExtension(a_tokens[6]);
      layer.AlphaMapWidth     = Convert.ToInt32(a_tokens[7]);
      layer.AlphaMapHieght    = Convert.ToInt32(a_tokens[8]);

      if (a_tokens[5] == "False")
      {
        layer.DetailMode = false;
      }
      else
      {
        layer.DetailMode = true;
      }

      TerrainAlphaLayerList.Add(layer);
    }    


    // ------------------------------------------------------------------------
    // Add a terrain detail layer
    //
    private void AddTerrainDetailLayer(List<String> a_tokens)
    {
      // layer type, name, texture, scale u, scale v, blend mode
	    // DETAILLAYER,  New Layer2, /terrain/New Layer2.jpg,  1.000000, 1.000000, Modulate

      if (a_tokens.Count != 6)
      {
        throw new Exception("Invalid format for terrain detail layer section");
      }

      TerrainDetailLayerData layer = new TerrainDetailLayerData();

      layer.Name              = a_tokens[1];
      layer.TextureFilename   = StringUtil.RemoveFilePathAndExtension(a_tokens[2]);
      layer.U                 = (float) Convert.ToDouble(a_tokens[3]);
      layer.V                 = (float) Convert.ToDouble(a_tokens[4]);
      layer.BlendMode         = a_tokens[5];

      TerrainDetailLayerList.Add(layer);
    }


    // ------------------------------------------------------------------------
    // Add a terrain blend layer
    //
    private void AddTerrainBlendLayer(List<String> a_tokens)
    {
      // layer type, name, texture, scale u, scale v, source blend, destination blend
      // BLENDLAYER,   Lightmap0,  /terrain/Lightmap0.jpg,   1.000000, 1.000000, ZERO, SRC_COLOR

      if (a_tokens.Count != 7)
      {
        throw new Exception("Invalid format for terrain blend layer section");
      }

      TerrainBlendLayerData layer = new TerrainBlendLayerData();

      layer.Name              = a_tokens[1];
      layer.TextureFilename   = StringUtil.RemoveFilePathAndExtension(a_tokens[2]);
      layer.U                 = (float) Convert.ToDouble(a_tokens[3]);
      layer.V                 = (float) Convert.ToDouble(a_tokens[4]);
      layer.SourceBlend       = a_tokens[5];
      layer.DestBlend         = a_tokens[6];

      TerrainBlendLayerList.Add(layer);
    }    


    // ------------------------------------------------------------------------
    // Add an entity
    //
    private void AddEntity(List<String> a_tokens)
    {
      // Waypoint1,Waypoint,Euler,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,121.017664,2.365581,145.258608,1.000000,2

      if (a_tokens.Count != 20)
      {
        throw new Exception("Invalid format for entity section");
      }

      if (a_tokens[2] != "Euler")
      {
        throw new Exception("Only euler transforms are supported, please re-export with euler transforms selected rather than vector + quaternion");
      }

      EntityData data = new EntityData();

      data.Name = a_tokens[0];
      data.Type = a_tokens[1];

      data.Transform.M11 = (float) Convert.ToDouble(a_tokens[3]);
      data.Transform.M12 = (float) Convert.ToDouble(a_tokens[4]);
      data.Transform.M13 = (float) Convert.ToDouble(a_tokens[5]);
      data.Transform.M14 = (float) Convert.ToDouble(a_tokens[6]);

      data.Transform.M21 = (float) Convert.ToDouble(a_tokens[7]);
      data.Transform.M22 = (float) Convert.ToDouble(a_tokens[8]);
      data.Transform.M23 = (float) Convert.ToDouble(a_tokens[9]);
      data.Transform.M24 = (float) Convert.ToDouble(a_tokens[10]);

      data.Transform.M31 = (float) Convert.ToDouble(a_tokens[11]);
      data.Transform.M32 = (float) Convert.ToDouble(a_tokens[12]);
      data.Transform.M33 = (float) Convert.ToDouble(a_tokens[13]);
      data.Transform.M34 = (float) Convert.ToDouble(a_tokens[14]);

      data.Transform.M41 = (float) Convert.ToDouble(a_tokens[15]);
      data.Transform.M42 = (float) Convert.ToDouble(a_tokens[16]);
      data.Transform.M43 = (float) Convert.ToDouble(a_tokens[17]);
      data.Transform.M44 = (float) Convert.ToDouble(a_tokens[18]);

      EntityList.Add(data);    
    }    
    

    // ------------------------------------------------------------------------
    // Add an entity property
    //
    private void AddEntityProperty(List<String> a_tokens)
    {
      // Id,2

      if (a_tokens.Count != 2)
      {
        throw new Exception("Invalid format for entity property section");
      }

      if (EntityList.Count == 0)
      {
        throw new Exception("Invalid format for entity property section (no entities in EntityList)");
      }

      // Add the property to the most recent entity
      EntityData data = EntityList[EntityList.Count - 1];
      data.Properties.Add(a_tokens[0], a_tokens[1]);
    }    

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

