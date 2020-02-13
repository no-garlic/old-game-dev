
using System;

using Microsoft.Xna.Framework;




namespace WaveRace360
{
  public class BitFlags
  {
    public static ulong Zero = 0x00000000;
    public static ulong Fill = 0xffffffff;


    public ulong Bits = Zero;


    public void Set(ulong a_value)
    {
      Bits = a_value;
    }


    public void Clear()
    {
      Bits = 0x00000000;
    }


    public void Add(ulong a_value)
    {
      Bits |= a_value;
    }


    public void Remove(ulong a_value)
    {
      Bits &= ~a_value;
    }


    public bool Equals(ulong a_value)
    {
      return (a_value == Bits);
    }


    public bool Test(ulong a_value)
    {
      return (a_value == (Bits & a_value));
    }
    

  }
}


// -- EOF

