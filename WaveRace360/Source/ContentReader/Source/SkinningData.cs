// ----------------------------------------------------------------------------
// File: SkinningData.cs
// Desc: Manages the skinning data and animation clips associated with a skinned
//       mesh.
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
  // Name: SkinningData
  // Desc: Manages the skinning data and animation clips associated with a 
  //       skinned mesh.
  // --------------------------------------------------------------------------
  public class SkinningData
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public IDictionary<string, AnimationClip>   AnimationClips      { get { return m_animationClips; } }
    public IList<Matrix>                        BindPose            { get { return m_bindPose; } }
    public IList<Vector3>                       BindPoseTranslation { get { return m_bindPoseTranslation; } }
    public IList<Quaternion>                    BindPoseRotation    { get { return m_bindPoseRotation; } }
    public IList<Matrix>                        InverseBindPose     { get { return m_inverseBindPose; } }
    public IList<int>                           SkeletonHierarchy   { get { return m_skeletonHierarchy; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private IDictionary<string, AnimationClip>  m_animationClips;
    private IList<Matrix>                       m_bindPose;
    private IList<Vector3>                      m_bindPoseTranslation;
    private IList<Quaternion>                   m_bindPoseRotation;
    private IList<Matrix>                       m_inverseBindPose;
    private IList<int>                          m_skeletonHierarchy;


    // ------------------------------------------------------------------------
    // Name: SkinningData
    // Desc: Constructor
    // Parm: IDictionary<string, AnimationClip> a_animationClips - the list of 
    //       animation clips
    // Parm: IList<Matrix> a_bindPose     - the list of bind pose matrices
    // Parm: IList<Matrix> a_inverseBindPose - the list of inverse bind pose amtrices
    // Parm: IList<int> a_skeletonHierarchy - the skeleton hierarchy (bone indexes)
    // ------------------------------------------------------------------------
    public SkinningData(IDictionary<string, AnimationClip> a_animationClips, IList<Matrix> a_bindPose, IList<Matrix> a_inverseBindPose, IList<int> a_skeletonHierarchy)
    {
      m_animationClips = a_animationClips;
      m_bindPose = a_bindPose;
      m_inverseBindPose = a_inverseBindPose;
      m_skeletonHierarchy = a_skeletonHierarchy;

      m_bindPoseTranslation = new List<Vector3>();
      m_bindPoseRotation = new List<Quaternion>();

      for (int i = 0; i < m_bindPose.Count; i++)
      {
        Vector3 scale = new Vector3();
        Vector3 translation = new Vector3();
        Quaternion rotation = new Quaternion();

        m_bindPose[i].Decompose(out scale, out rotation, out translation);

        m_bindPoseTranslation.Add(translation);
        m_bindPoseRotation.Add(rotation);
      }
    }
  }


  // --------------------------------------------------------------------------
  // Name: SkinningDataReader 
  // Desc: Reads the data from an XNB
  // --------------------------------------------------------------------------
  public class SkinningDataReader : ContentTypeReader<SkinningData>
  {
    protected override SkinningData Read(ContentReader input, SkinningData existingInstance)
    {
      IDictionary<string, AnimationClip> animationClips;
      IList<Matrix> bindPose, inverseBindPose;
      IList<int> skeletonHierarchy;

      animationClips = input.ReadObject<IDictionary<string, AnimationClip>>();
      bindPose = input.ReadObject<IList<Matrix>>();
      inverseBindPose = input.ReadObject<IList<Matrix>>();
      skeletonHierarchy = input.ReadObject<IList<int>>();

      return new SkinningData(animationClips, bindPose, inverseBindPose, skeletonHierarchy);
    }
  }


  
}


// -- EOF


