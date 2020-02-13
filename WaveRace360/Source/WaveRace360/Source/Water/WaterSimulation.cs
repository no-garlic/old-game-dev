// ----------------------------------------------------------------------------
// File: WaterSimulation.cs
// Desc: Runs the water simulation to calculate the displation.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: WaterSimulation
  // Desc: Renders the ocean
  // --------------------------------------------------------------------------
  public class WaterSimulation
  {
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private WaterRender m_parent;
    private float[]     m_waveSpeeds;
    private float[]     m_waveHeights;
    private float[]     m_waveLengths;
    private Vector2[]   m_waveDirs;


    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public float[]    WaveSpeeds      { get { return m_waveSpeeds; } }
    public float[]    WaveHeights     { get { return m_waveHeights; } }
    public float[]    WaveLengths     { get { return m_waveLengths; } }
    public Vector2[]  WaveDirections  { get { return m_waveDirs; } }


    // ------------------------------------------------------------------------
    // Name: WaterSimulation
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public WaterSimulation(WaterRender a_parent)
    {
      m_parent = a_parent;

      m_waveSpeeds = new float[4];
      m_waveHeights = new float[4];
      m_waveLengths = new float[4];
      m_waveDirs = new Vector2[4];
    }

    // ------------------------------------------------------------------------
    // Name: Create
    // Desc: Create the simulation resources
    // ------------------------------------------------------------------------
    public void Create(WaterRender.CreationParams a_creationParams)
    {
      for (int i = 0; i < 4; i++)
      {
        m_waveSpeeds[i] = a_creationParams.Waves[i].Speed;
        m_waveHeights[i] = a_creationParams.Waves[i].Height;
        m_waveLengths[i] = a_creationParams.Waves[i].Length;
        m_waveDirs[i] = a_creationParams.Waves[i].Direction;
        m_waveDirs[i].Normalize();
      }
    }
    

    //
    // ------------------------------------------------------------------------
  };
}


// -- EOF

