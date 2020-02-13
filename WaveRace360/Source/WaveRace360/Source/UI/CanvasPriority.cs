// ----------------------------------------------------------------------------
// File: CanvasPriority.cs
// Desc: The canvas priority list
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;




namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: CanvasPriority
  // Desc: The canvas priority list. Each canvas should have a unique priority 
  //       and when multiple are added to the UserInterface, they are rendered 
  //       in priority order (higher priorities are rendered last (ontop)).
  // --------------------------------------------------------------------------
  public class CanvasPriority
  {
    public static int StartupSequence     = 1200;
    public static int FrontEnd            = 1100;
    public static int LoadingScreen       = 1000;
    public static int PlayerHUD           = 500;
  }


  //
  // --------------------------------------------------------------------------
}

// -- EOF

