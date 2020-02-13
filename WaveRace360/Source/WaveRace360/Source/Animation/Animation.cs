// ----------------------------------------------------------------------------
// File: Animation.cs
// Desc: Manages an animation clip
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------
using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using SkinnedModel;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: Animation
  // Desc: Manages an animation clip
  // --------------------------------------------------------------------------
  public class Animation
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public int    Id                    { get { return m_id; } }
    public String Name                  { get { return m_name; } } 
    public float  Duration              { get { return m_duration; } }
    public float  Time                  { get { return m_time; } 
                                          set { m_time = value; } }
    public float  Progress              { get { return m_time * m_durationInv; }
                                          set { m_time = m_duration * value; } }
    public float  Speed                 { get { return m_speed; }
                                          set { m_speed = value; } } 
    public bool   Finished              { get { return !m_looping && m_time == m_duration; } }
    public bool   Looping               { get { return m_looping; } 
                                          set { m_looping = value; } }
    public bool   Manual                { get { return m_manual; } 
                                          set { m_manual = value; } }
    public bool   RemoveOnFinish        { get { return m_removeOnFinish; }
                                          set { m_removeOnFinish = value; } }
    public bool   RemoveOnZeroInfluence { get { return m_removeOnZeroInfluence; }
                                          set { m_removeOnZeroInfluence = value; } }
    public bool   Paused                { get { return m_paused; } 
                                          set { m_paused = value; } }
    public float  Influence             { get { return m_influence; }
                                          set { m_influence = MathHelper.Clamp(value, 0.0f, 1.0f); } }
    public float  Priority              { get { return m_priority; }
                                          set { m_priority = MathHelper.Clamp(value, 0.0f, 1.0f); } }
    public Vector3[]    BoneTranslation { get { return m_boneTranslation; } }
    public Quaternion[] BoneRotation    { get { return m_boneRotation; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private static int      s_idCounter = 0;
    private int             m_id;
    private String          m_name;
    private AnimationClip   m_clip;
    private SkinningData    m_skinningData;
    private float           m_duration;
    private float           m_durationInv;
    private float           m_time;
    private float           m_speed;
    private bool            m_looping;
    private bool            m_manual;
    private bool            m_paused;
    private bool            m_removeOnFinish;
    private bool            m_removeOnZeroInfluence;
    private float           m_influence;
    private float           m_priority;
    private float           m_easeInDuration;
    private float           m_easeInInfluence;
    private Vector3[]       m_boneTranslation;
    private Quaternion[]    m_boneRotation;


    // ------------------------------------------------------------------------
    // Name: Animation
    // Desc: Constructor
    // Parm: String a_name - the animation clip name
    // Parm: SkinningData a_skinningData - the skinning data
    // ------------------------------------------------------------------------
    public Animation(String a_name, SkinningData a_skinningData)
    {
      // Assign the Id and increment the counter
      m_id = s_idCounter;
      s_idCounter++;

      // Ensure that the duration is non-zero
      m_clip = a_skinningData.AnimationClips[a_name];
      if ((float) m_clip.Duration.TotalSeconds == 0.0f)
      {
        throw new ArgumentOutOfRangeException("duration");
      }

      // Store the values
      m_name = a_name;
      m_skinningData = a_skinningData;
      m_boneTranslation = new Vector3[a_skinningData.BindPose.Count];
      m_boneRotation = new Quaternion[a_skinningData.BindPose.Count];
      m_duration = (float) m_clip.Duration.TotalSeconds;
      m_durationInv = 1.0f / m_duration;
      m_removeOnFinish = false;
      m_influence = 1.0f;
      m_easeInDuration = 0.0f;
      m_easeInInfluence = 1.0f;
      m_time = 0.0f;
      m_speed = 1.0f;
      m_looping = false;
      m_manual = false;
      m_paused = false;
    }
    

    // ------------------------------------------------------------------------
    // Name: EaseIn
    // Desc: Ease the animation in over the given time
    // Parm: float a_duration - the time to ease in
    // ------------------------------------------------------------------------
    public void EaseIn(float a_duration)
    {
      EaseIn(a_duration, 1.0f);
    }


    // ------------------------------------------------------------------------
    // Name: EaseIn
    // Desc: Ease the animation in over the given time
    // Parm: float a_duration - the time to ease in
    // Parm: float a_influence - the destination influence value once eased in.
    // ------------------------------------------------------------------------
    public void EaseIn(float a_duration, float a_influence)
    {
      if (a_duration == 0.0f)
      {
        throw new ArgumentOutOfRangeException("a_duration");
      }

      if (a_influence == 0.0f)
      {
        throw new ArgumentOutOfRangeException("a_influence");
      }

      m_influence = 0.0f;
      m_easeInDuration = a_duration;
      m_easeInInfluence = a_influence / a_duration;
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update the animation
    // Parm: float a_frameTime - the frame time
    // ------------------------------------------------------------------------
    public void Update(float a_frameTime)
    {
      // If paused or in manual update mode, dont update the m_time
      if (!m_paused && !m_manual)
      {
        // Scale the update time by the animation speed
        float deltaTime = a_frameTime * m_speed;

        // Apply the ease in influence
        if (m_easeInDuration > 0.0f)
        {
          float t = MathHelper.Min(m_easeInDuration, deltaTime);
          m_easeInDuration -= deltaTime;
          if (m_easeInDuration < 0.0f)
          {
            m_easeInDuration = 0.0f;
          }

          m_influence += (m_easeInInfluence * t);
        }

        // Add the delta to m_time
        m_time += deltaTime;

        // If we have past the end of the animation
        if (m_time > m_duration)
        {
          if (m_looping)
          {
            // If looping then loop the animation
            while (m_time > m_duration)
            {
              m_time -= m_duration;
            }
          }
          else
          {
            // If not looping, set to the last animation frame
            m_time = m_duration;
          }
        }
      }

      // Initialise the bones to the bind pose
      m_skinningData.BindPoseTranslation.CopyTo(m_boneTranslation, 0);
      m_skinningData.BindPoseRotation.CopyTo(m_boneRotation, 0);

      // Apply the bone transforms from the keyframes
      AnimationUtils.Blend(m_clip.AnimationFrames, m_time, m_boneTranslation, m_boneRotation);
    }


  }
}


// -- EOF



