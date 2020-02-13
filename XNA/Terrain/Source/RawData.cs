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


namespace Terrain
{
  public class RawData
  {
    // ------------------------------------------------------------------------
    // Public Members
    //
    public byte[] Data;
    public int    Count;


    // ------------------------------------------------------------------------
    // Constructor
    //
    public RawData(byte[] bytes)
    {
      Count = bytes.Length;
      Data  = new byte[Count];

      for (int i = 0; i < Count; i++)
      {
        Data[i] = bytes[i];
      }
    }


    // ------------------------------------------------------------------------
    // Get the data as unsigned short
    //
    public ushort[] AsUInt16()
    {
      ushort[] data = new ushort[Count / 2];

      for (int i = 0; i < Count / 2; i++)
      {
        data[i] = BitConverter.ToUInt16(Data, i * 2);
      }

      return data;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

