// ----------------------------------------------------------------------------
// File: AnimationFrame.cs
// Desc: Manages an animation frame - which is a single frame for all bones 
//       within an animation clip
// Auth: Michael Petrou
// Note: Credit to the Microsoft XNA Skinning Sample which this code is based on.
// (C) Copyright: 2008
// ----------------------------------------------------------------------------
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;


namespace SkinnedModel
{
  // --------------------------------------------------------------------------
  // Name: SkinnedModel
  // Desc: Manages an animation frame - which is a single frame for all bones 
  //       within an animation clip
  // --------------------------------------------------------------------------
  public class AnimationFrame
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public TimeSpan         Time      { get { return m_time; } }
    public IList<Keyframe>  Keyframes { get { return m_keyframes; } }
   
    
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private TimeSpan        m_time;
    private IList<Keyframe> m_keyframes;


    // ------------------------------------------------------------------------
    // Name: AnimationFrame
    // Desc: Constructor
    // Parm: TimeSpan a_time - the time of the animation frame
    // Parm: IList<Keyframe> a_keyframes - the list of keyframes for the 
    //       animation frame
    // ------------------------------------------------------------------------
    public AnimationFrame(TimeSpan a_time, IList<Keyframe> a_keyframes)
    {
      m_time = a_time;
      m_keyframes = a_keyframes;
    }
  }


  // --------------------------------------------------------------------------
  // Name: AnimationFrameReader 
  // Desc: Reads the data from an XNB
  // --------------------------------------------------------------------------
  public class AnimationFrameReader : ContentTypeReader<AnimationFrame>
  {
    protected override AnimationFrame Read(ContentReader input, AnimationFrame existingInstance)
    {
      TimeSpan time = input.ReadObject<TimeSpan>();
      IList<Keyframe> keyframes = input.ReadObject<IList<Keyframe>>();
      
      return new AnimationFrame(time, keyframes);
    }
  }


}


// -- EOF


