// ----------------------------------------------------------------------------
// File: AssetType.cs
// Desc: Defines the types of assets that exist in the content, and a way to 
//       resolve a path to them.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: AssetType
  // Desc: The types of assets that are supported - each type exists in a 
  //       seperate folder in the content.
  // --------------------------------------------------------------------------
  public enum AssetType
  {
    AT_ACTOR,
    AT_MODEL,
    AT_LEVEL,
    AT_TEXTURE,
    AT_UI,
    AT_TERRAIN,
    AT_SHADER,
    AT_FONT
  }


  // --------------------------------------------------------------------------
  // Name: Asset
  // Desc: Static class acting as a namespace to access the Resolve() functions.
  // --------------------------------------------------------------------------
  public class Asset
  {
    // ------------------------------------------------------------------------
    // Name: ResolveLevel
    // Desc: Resolve the fully qualified asset name that exists within a level.
    // Parm: AssetType a_type - the asset type
    // Parm: String a_levelName - the level name
    // Parm: String a_assetName - the asset name to resolve
    // Retn: String - the full path to the asset
    // ------------------------------------------------------------------------
    public static String ResolveLevel(AssetType a_type, String a_levelName, String a_assetName)
    {
      String pathName = "Content\\levels\\" + a_levelName + "\\";

      switch (a_type)
      {
        case AssetType.AT_TEXTURE:
        {
          pathName += "textures\\";
          break;
        }
        case AssetType.AT_TERRAIN:
        {
          pathName += "terrain\\";
          break;
        }
      }

      return pathName + a_assetName;
    }


    // ------------------------------------------------------------------------
    // Name: ResolveLevel
    // Desc: Resolve the fully qualified asset name.
    // Parm: AssetType a_type - the asset type
    // Parm: String a_assetName - the asset name to resolve
    // Retn: String - the full path to the asset
    // ------------------------------------------------------------------------
    public static String Resolve(AssetType a_type, String a_assetName)
    {
      String pathName = "Content\\";

      switch (a_type)
      {
        case AssetType.AT_ACTOR:
        {
          pathName += "actors\\";
          break;
        }
        case AssetType.AT_MODEL:
        {
          pathName += "models\\";
          break;
        }
        case AssetType.AT_LEVEL:
        {
          pathName += "levels\\";
          break;
        }
        case AssetType.AT_TEXTURE:
        {
          pathName += "textures\\";
          break;
        }
        case AssetType.AT_UI:
        {
          pathName += "ui\\";
          break;
        }
        case AssetType.AT_TERRAIN:
        {
          pathName += "terrain\\";
          break;
        }
        case AssetType.AT_SHADER:
        {
          pathName += "shaders\\";
          break;
        }
        case AssetType.AT_FONT:
        {
          pathName += "fonts\\";
          break;
        }
      }

      return pathName + a_assetName;
    }


    //
    // ------------------------------------------------------------------------
  }
}

// -- EOF