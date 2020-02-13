// ----------------------------------------------------------------------------
// File: AnimationClip.cs
// Desc: Manages an animation clip - which is a sequence of keyframes
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
  // Name: AnimationClip
  // Desc: Manages an animation clip - which is a sequence of keyframes
  // --------------------------------------------------------------------------
  public class AnimationClip
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public TimeSpan               Duration          { get { return m_duration; } }
    public IList<AnimationFrame>  AnimationFrames   { get { return m_animationFrames; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private IList<AnimationFrame> m_animationFrames;
    private TimeSpan              m_duration;


    // ------------------------------------------------------------------------
    // Name: AnimationClip
    // Desc: Constructor
    // Parm: TimeSpan a_duration - the duration of the clip
    // Parm: IList<AnimationFrame> a_animationFrames - the frames for the clip
    // ------------------------------------------------------------------------
    public AnimationClip(TimeSpan a_duration, IList<AnimationFrame> a_animationFrames)
    {
      m_duration = a_duration;
      m_animationFrames = a_animationFrames;
    }
  }


  // --------------------------------------------------------------------------
  // Name: AnimationClipReader 
  // Desc: Reads the data from an XNB
  // --------------------------------------------------------------------------
  public class AnimationClipReader : ContentTypeReader<AnimationClip>
  {
    protected override AnimationClip Read(ContentReader input, AnimationClip existingInstance)
    {
      TimeSpan duration = input.ReadObject<TimeSpan>();
      IList<AnimationFrame> animationFrames = input.ReadObject<IList<AnimationFrame>>();

      return new AnimationClip(duration, animationFrames);
    }
  }



}


// -- EOF

