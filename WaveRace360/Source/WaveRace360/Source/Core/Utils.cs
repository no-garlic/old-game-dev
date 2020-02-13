// ----------------------------------------------------------------------------
// File: Utils.cs
// Desc: 
// Auth: Michael Petrou
// (C) Copyright: 2009
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public abstract class Utils
  {
    public static String RandomName()
    {
      Guid g = Guid.NewGuid();
      return g.ToString();
    }


    class ByteSwap
    {
      public static UInt16 swap(UInt16 input)
      {
        return ((UInt16)(
        ((0xFF00 & input) >> 8) |
        ((0x00FF & input) << 8)));
      }

      public static UInt32 swap(UInt32 input)
      {
        return ((UInt32)(
        ((0xFF000000 & input) >> 24) |
        ((0x00FF0000 & input) >> 8) |
        ((0x0000FF00 & input) << 8) |
        ((0x000000FF & input) << 24)));
      }

      public static float swap(float input)
      {
        byte[] tmpIn = BitConverter.GetBytes(input);
        byte[] tmpOut = new byte[4];
        tmpOut[0] = tmpIn[3];
        tmpOut[1] = tmpIn[2];
        tmpOut[2] = tmpIn[1];
        tmpOut[3] = tmpIn[0];
        return BitConverter.ToSingle(tmpOut, 0);
      }

      public static double swap(double input)
      {
        byte[] tmpIn = BitConverter.GetBytes(input);
        byte[] tmpOut = new byte[8];
        tmpOut[0] = tmpIn[7];
        tmpOut[1] = tmpIn[6];
        tmpOut[2] = tmpIn[5];
        tmpOut[3] = tmpIn[4];
        tmpOut[4] = tmpIn[3];
        tmpOut[5] = tmpIn[2];
        tmpOut[6] = tmpIn[1];
        tmpOut[7] = tmpIn[0];
        return BitConverter.ToSingle(tmpOut, 0);
      }
    }

  }

}


// -- EOF

