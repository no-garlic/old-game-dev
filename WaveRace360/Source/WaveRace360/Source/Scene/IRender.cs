// ----------------------------------------------------------------------------
// File: IRender.cs
// Desc: The render interface
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: IRender
  // Desc: The render interface. Any object that uses this interface can be 
  //       rendered my a Material.
  // --------------------------------------------------------------------------
  public abstract class IRender
  {
    public AssetData.ModelInfo ModelInfo = new AssetData.ModelInfo();


    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the object.
    // ------------------------------------------------------------------------
    public abstract void Render(Material a_material, Matrix a_worldMatrix);


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF


