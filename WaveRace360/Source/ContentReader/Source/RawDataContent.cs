using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using System.IO;


namespace Terrain
{
  // ------------------------------------------------------------------------
  // // The serialize reader
  //
  public class RawDataReader : ContentTypeReader<RawData>
  {
    protected override RawData Read(ContentReader cr, RawData existingInstance)
    {
      int count = cr.ReadInt32();
      byte[] bytes = cr.ReadBytes(count);
      return new RawData(bytes);
    }

    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

