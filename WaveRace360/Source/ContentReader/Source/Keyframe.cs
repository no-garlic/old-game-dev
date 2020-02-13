// ----------------------------------------------------------------------------
// File: Keyframe.cs
// Desc: Manages a single transform for a single bone within an animation clip.
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
  // Name: Keyframe
  // Desc: Manages a single transform for a single bone within an animation clip.
  // --------------------------------------------------------------------------
  public class Keyframe
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public int          Bone          { get { return m_bone; } }
    public TimeSpan     Time          { get { return m_time; } }
    public Vector3      Translation   { get { return m_translation; } }
    public Quaternion   Rotation      { get { return m_rotation; } }

    
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private int         m_bone;
    private TimeSpan    m_time;         //<- Note - this is not required in this structure as the parent AnimationFrame has this value.
    private Vector3     m_translation;
    private Quaternion  m_rotation;


    // ------------------------------------------------------------------------
    // Name: Keyframe
    // Desc: Constructor
    // Parm: int a_bone         - the bone index for the keyframe
    // Parm: TimeSpan a_time    - the time of the keyframe
    // Parm: Vector3 a_translation - the translation for the keyframe
    // Parm: Quaternion a_rotation - the rotation for the keyframe
    // ------------------------------------------------------------------------
    public Keyframe(int a_bone, TimeSpan a_time, Vector3 a_translation, Quaternion a_rotation)
    {
      m_bone = a_bone;
      m_time = a_time;
      m_translation = a_translation;
      m_rotation = a_rotation;
    }
  }


  // --------------------------------------------------------------------------
  // Name: KeyframeReader 
  // Desc: Reads the data from an XNB
  // --------------------------------------------------------------------------
  public class KeyframeReader : ContentTypeReader<Keyframe>
  {
    protected override Keyframe Read(ContentReader input, Keyframe existingInstance)
    {
      int bone = input.ReadObject<int>();
      TimeSpan time = input.ReadObject<TimeSpan>();
      Vector3 translation = input.ReadObject<Vector3>();
      Quaternion rotation = input.ReadObject<Quaternion>();

      return new Keyframe(bone, time, translation, rotation);
    }
  }


}


// -- EOF

