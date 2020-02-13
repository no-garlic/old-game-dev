// ----------------------------------------------------------------------------
// File: AnimationBlender.cs
// Desc: Plays and blends multiple animations
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
  // Name: AnimationBlender
  // Desc: Plays and blends multiple animations
  // --------------------------------------------------------------------------
  public class AnimationBlender
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public Matrix           RootTransform   { get { return m_rootTransform; }
                                              set { m_rootTransform = value; } }
    public Matrix[]         BoneTransforms  { get { return m_skinTransforms; } }
    public Matrix[]         WorldTransforms { get { return m_skinTransforms; } }
    public Matrix[]         SkinTransforms  { get { return m_skinTransforms; } }
    public IList<Matrix>    BindPose        { get { return m_skinningData.BindPose; } }
    public List<Animation>  Animations      { get { return m_animations; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private SkinningData    m_skinningData;
    private List<Animation> m_animations;
    private Matrix[]        m_boneTransforms;
    private Matrix[]        m_worldTransforms;
    private Matrix[]        m_skinTransforms;
    private Matrix          m_rootTransform;


    // ------------------------------------------------------------------------
    // Name: AnimationBlender
    // Desc: Constructor
    // Parm: Model a_model - the model to animate
    // ------------------------------------------------------------------------
    public AnimationBlender(Model a_model)
    {
      m_skinningData = a_model.Tag as SkinningData;
      if (m_skinningData == null)
      {
        throw new InvalidOperationException("This model does not contain a SkinningData tag.");
      }
      
      m_animations = new List<Animation>();
      m_boneTransforms = new Matrix[m_skinningData.BindPose.Count];
      m_worldTransforms = new Matrix[m_skinningData.BindPose.Count];
      m_skinTransforms = new Matrix[m_skinningData.BindPose.Count];

      m_skinningData.BindPose.CopyTo(m_boneTransforms, 0);
    }


    // ------------------------------------------------------------------------
    // Name: PlayAnimation
    // Desc: Play an animation by name
    // Parm: String a_name - the animation name
    // Retn: Animation - the animation class to control the playback
    // ------------------------------------------------------------------------
    public Animation PlayAnimation(String a_name)
    {
      Animation anim = new Animation(a_name, m_skinningData);
      m_animations.Add(anim);
      return anim;
    }


    // ------------------------------------------------------------------------
    // Name: RemoveAnimation
    // Desc: Remove an animation from the blender
    // Parm: Animation a_animation - the animation to remove
    // ------------------------------------------------------------------------
    public void RemoveAnimation(Animation a_animation)
    {
      m_animations.Remove(a_animation);
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update all playing animations
    // Parm: float a_frameTime - the frame time
    // ------------------------------------------------------------------------
    public void Update(float a_frameTime)
    {
      // Sort the animations in priority order (1 is the highest, 0 is the lowest)
      m_animations.Sort(CompareAnimation);

      // Create the blend buffer
      AnimationUtils.AnimationBlendBuffer blendBuffer = new AnimationUtils.AnimationBlendBuffer(m_skinningData.BindPose.Count);

      // Apply the animation transforms scaled by the claculated influence
      float influence = 0.0f;
      for (int animIndex = 0; animIndex < m_animations.Count; animIndex++)
      {
        // Get the animation
        Animation anim = m_animations[animIndex];

        // Update the animation
        anim.Update(a_frameTime);

        // Once the influence is used up, the animations have no effect
        if (influence == 1.0f)
        {
          continue;
        }

        // Calculate the influence for this animation
        float targetInfluence = MathHelper.Min(anim.Influence, 1.0f - influence);

        // If this is the last animation in the list, it must use all of the remaining influence
        if (animIndex == m_animations.Count - 1)
        {
          targetInfluence = 1.0f - influence;
        }

        // Update the accumulate influence used
        influence = MathHelper.Clamp(influence + targetInfluence, 0.0f, 1.0f);

        // This is where we blend the matrices by the targetInfluence
        for (int i = 0; i < m_skinningData.BindPose.Count; i++)
        {
          blendBuffer.Add(i, anim.BoneTranslation[i], anim.BoneRotation[i], targetInfluence);
        }

        // Should the animation be removed automatically
        if ((anim.Finished && anim.RemoveOnFinish) || (anim.Influence == 0.0f && anim.RemoveOnZeroInfluence))
        {
          RemoveAnimation(anim);
        }
      }

      // Blend the buffer
      blendBuffer.Blend();
      Vector3 blendTranslation = new Vector3();
      Quaternion blendRotation = new Quaternion();

      // Update the bone transforms
      for (int i = 0; i < m_skinningData.BindPose.Count; i++)
      {
        blendBuffer.GetKey(i, out blendTranslation, out blendRotation);
        Matrix m = Matrix.CreateFromQuaternion(blendRotation);
        m.Translation = blendTranslation;
        m_boneTransforms[i] = m;
      }

      // Update the world transforms
      m_worldTransforms[0] = m_boneTransforms[0] * m_rootTransform;
      for (int bone = 1; bone < m_worldTransforms.Length; bone++)
      {
        int parentBone = m_skinningData.SkeletonHierarchy[bone];
        m_worldTransforms[bone] = m_boneTransforms[bone] * m_worldTransforms[parentBone];
      }

      // Update the skin transforms
      for (int bone = 0; bone < m_skinTransforms.Length; bone++)
      {
        m_skinTransforms[bone] = m_skinningData.InverseBindPose[bone] * m_worldTransforms[bone];
      }
    }
    

    // ------------------------------------------------------------------------
    // Name: CompareKeyframeTimes
    // Desc: Comparison function for sorting keyframes into ascending time order.
    // ------------------------------------------------------------------------
    static int CompareAnimation(Animation a_a, Animation a_b)
    {
      int result = a_a.Priority.CompareTo(a_b.Priority);

      // Compare with the hash also otherwise the sort algorithm will 
      // produce different animations each frame.
      if (result == 0)
      {
        result = a_a.Id.CompareTo(a_b.Id);
      }

      return result;
    }


  }
}


// -- EOF



