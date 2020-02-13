using System;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;


namespace WaveRace360
{
  // ------------------------------------------------------------------------
  // Asset types
  //
  public enum AssetType
  {
    AT_MODEL,
    AT_LEVEL,
    AT_TEXTURE,
    AT_TERRAIN,
    AT_SHADER
  }


  public class Asset
  {
    // ------------------------------------------------------------------------
    // Resolve the fully qualified asset name
    //
    public static String Resolve(AssetType a_type, String a_assetName)
    {
      String pathName = "Content\\";

      switch (a_type)
      {
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
      }

      return pathName + a_assetName;
    }


    //
    // ------------------------------------------------------------------------
  }
}

// -- EOF