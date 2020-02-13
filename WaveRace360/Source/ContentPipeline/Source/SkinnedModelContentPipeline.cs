// ----------------------------------------------------------------------------
// File: SkinnedModelProcessor.cs
// Desc: A content processor for a skinned model and associated animations
// Auth: Michael Petrou
// Note: Credit to the Microsoft XNA Skinning Sample which this code is based on.
// (C) Copyright: 2008
// ----------------------------------------------------------------------------
using System;
using System.IO;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content.Pipeline;
using Microsoft.Xna.Framework.Content.Pipeline.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline.Processors;
using Microsoft.Xna.Framework.Content.Pipeline.Serialization.Compiler;
using SkinnedModel;


namespace SkinnedModel
{
  // --------------------------------------------------------------------------
  // Name: SkinnedModelProcessor 
  // Desc: Custom processor extends the builtin framework ModelProcessor class,
  //       adding animation support.
  // --------------------------------------------------------------------------
  [ContentProcessor]
  public class SkinnedModelProcessor : ModelProcessor
  {
    // Maximum number of bone matrices we can render using shader 2.0
    // in a single pass. If you change this, update SkinnedModelfx to match.
    const int MaxBones = 59;


    // ------------------------------------------------------------------------
    // Name: Process
    // Desc: The main Process method converts an intermediate format content 
    //       pipeline NodeContent tree to a ModelContent object with embedded 
    //       animation data.
    // ------------------------------------------------------------------------
    public override ModelContent Process(NodeContent input, ContentProcessorContext context)
    {
      ValidateMesh(input, context, null);

      // Find the skeleton.
      BoneContent skeleton = MeshHelper.FindSkeleton(input);

      if (skeleton == null)
      {
        throw new InvalidContentException("Input skeleton not found.");
      }

      // We don't want to have to worry about different parts of the model being
      // in different local coordinate systems, so let's just bake everything.
      FlattenTransforms(input, skeleton);

      // Read the bind pose and skeleton hierarchy data.
      IList<BoneContent> bones = MeshHelper.FlattenSkeleton(skeleton);

      // Ensure that the bone count is within the range for shader 2.0
      if (bones.Count > MaxBones)
      {
        throw new InvalidContentException(string.Format("Skeleton has {0} bones, but the maximum supported is {1}.", bones.Count, MaxBones));
      }

      // The skinned model data
      List<Matrix> bindPose = new List<Matrix>();
      List<Matrix> inverseBindPose = new List<Matrix>();
      List<int> skeletonHierarchy = new List<int>();

      // Assign the bone transforms and inverse transforms
      foreach (BoneContent bone in bones)
      {
        bindPose.Add(bone.Transform);
        inverseBindPose.Add(Matrix.Invert(bone.AbsoluteTransform));
        skeletonHierarchy.Add(bones.IndexOf(bone.Parent as BoneContent));
      }

      // Convert animation data to our runtime format.
      Dictionary<string, AnimationClip> animationClips;
      animationClips = ProcessAnimations(skeleton.Animations, bones, bindPose);

      // Chain to the base ModelProcessor class so it can convert the model data.
      ModelContent model = base.Process(input, context);

      // Store our custom animation data in the Tag property of the model.
      model.Tag = new SkinningData(animationClips, bindPose, inverseBindPose, skeletonHierarchy);
      return model;
    }


    // ------------------------------------------------------------------------
    // Name: ProcessAnimations
    // Desc: Converts an intermediate format content pipeline 
    //       AnimationContentDictionary object to our runtime AnimationClip 
    //       format.
    // ------------------------------------------------------------------------
    static Dictionary<string, AnimationClip> ProcessAnimations(AnimationContentDictionary animations, IList<BoneContent> bones, List<Matrix> bindPose)
    {
      // Build up a table mapping bone names to indices.
      Dictionary<string, int> boneMap = new Dictionary<string, int>();
      for (int i = 0; i < bones.Count; i++)
      {
        string boneName = bones[i].Name;
        if (!string.IsNullOrEmpty(boneName))
        {
          boneMap.Add(boneName, i);
        }
      }

      // All animation clips in the file
      Dictionary<string, AnimationClip> animationClips = new Dictionary<string, AnimationClip>();

      // Convert each animation in turn.
      foreach (KeyValuePair<string, AnimationContent> animation in animations)
      {
        AnimationClip processed = ProcessAnimation(animation.Value, boneMap, bindPose);
        animationClips.Add(animation.Key, processed);
      }

      // Ensure that there is some animation clips
      if (animationClips.Count == 0)
      {
        throw new InvalidContentException("Input file does not contain any animations.");
      }

      return animationClips;
    }


    // ------------------------------------------------------------------------
    // Name: ProcessAnimation
    // Desc: Converts an intermediate format content pipeline AnimationContent 
    //       object to our runtime AnimationClip format.
    // ------------------------------------------------------------------------
    static AnimationClip ProcessAnimation(AnimationContent animation, Dictionary<string, int> boneMap, List<Matrix> bindPose)
    {
      // List to hold all the keyframes for the animation
      List<Keyframe> keyframes = new List<Keyframe>();

      // For each input animation channel.
      foreach (KeyValuePair<string, AnimationChannel> channel in animation.Channels)
      {
        // Look up what bone this channel is controlling.
        int boneIndex;
        if (!boneMap.TryGetValue(channel.Key, out boneIndex))
        {
          throw new InvalidContentException(string.Format("Found animation for bone '{0}', " + "which is not part of the skeleton.", channel.Key));
        }

        // Convert the keyframe data.
        foreach (AnimationKeyframe keyframe in channel.Value)
        {
          // Decompose the transform into a translation and a rotation.
          Vector3 scale = new Vector3();
          Vector3 translation = new Vector3();
          Quaternion rotation = new Quaternion();
          keyframe.Transform.Decompose(out scale, out rotation, out translation);

          // Add the keyframe to the list
          keyframes.Add(new Keyframe(boneIndex, keyframe.Time, translation, rotation));
        }
      }

      // Sort the merged keyframes by time.
      keyframes.Sort(CompareKeyframeTimes);

      // Ensure that there are some keyframes
      if (keyframes.Count == 0)
      {
        throw new InvalidContentException("Animation has no keyframes.");
      }

      // Ensure that the animation has a duration
      if (animation.Duration <= TimeSpan.Zero)
      {
        throw new InvalidContentException("Animation has a zero duration.");
      }

      // Convert the flat list of keyframes into a list of animation frames
      IList<AnimationFrame> animationFrames = CreateAnimationFrames(keyframes);
      CreateMissingKeyFrames(animationFrames, bindPose);

      // Create an animation clip and return it.
      return new AnimationClip(animation.Duration, animationFrames);
    }


    // ------------------------------------------------------------------------
    // Name: CompareKeyframeTimes
    // Desc: Comparison function for sorting keyframes into ascending time order.
    // ------------------------------------------------------------------------
    static int CompareKeyframeTimes(Keyframe a, Keyframe b)
    {
      return a.Time.CompareTo(b.Time);
    }


    // ------------------------------------------------------------------------
    // Name: CreateAnimationFrames
    // Desc: Create animation frames from a flat list of keyframes
    // Parm: IList<Keyframe> keyframes - the list of keyframes
    // Retn: IList<AnimationFrame> - the list of animation frames
    // ------------------------------------------------------------------------
    static IList<AnimationFrame> CreateAnimationFrames(IList<Keyframe> keyframes)
    {
      // Create the list of frames
      IList<AnimationFrame> animationFrames = new List<AnimationFrame>();

      // Create temp storage for a set of keyframes that occur at the same time on different bones.
      IList<Keyframe> frames = new List<Keyframe>();
      TimeSpan time = new TimeSpan(0, 0, 0);

      // Test all keyframes
      foreach (Keyframe keyframe in keyframes)
      {
        // Put all keyframes into an animation frame
        if (keyframe.Time != time && keyframes.Count > 0)
        {
          AnimationFrame frame = new AnimationFrame(time, frames);
          animationFrames.Add(frame);
          frames = new List<Keyframe>();
          time = keyframe.Time;
        }

        // Add the keyframe to the list
        frames.Add(keyframe);
      }

      // Put all keyframes into an animation frame
      if (keyframes.Count > 0)
      {
        AnimationFrame frame = new AnimationFrame(time, frames);
        animationFrames.Add(frame);
      }

      // Return the list of animation frames
      return animationFrames;
    }


    // ------------------------------------------------------------------------
    // Name: CreateMissingKeyFrames
    // Desc: Fill out the missing keyframes in each animation frame
    // Parm: IList<AnimationFrame> animationFrames - the animation frames to 
    //       fillout
    // ------------------------------------------------------------------------
    static void CreateMissingKeyFrames(IList<AnimationFrame> animationFrames, List<Matrix> bindPose)
    {
      Vector3[] tData = new Vector3[bindPose.Count];
      Quaternion[] rData = new Quaternion[bindPose.Count];

      for (int i = 0; i < bindPose.Count; i++)
      {
        Vector3 scale = new Vector3();
        bindPose[i].Decompose(out scale, out rData[i], out tData[i]);
      }

      foreach (AnimationFrame frame in animationFrames)
      {
        // Update the tData and rData with this keyframe data
        foreach (Keyframe keyframe in frame.Keyframes)
        {
          tData[keyframe.Bone] = keyframe.Translation;
          rData[keyframe.Bone] = keyframe.Rotation;
        }

        // Rebuild the keyframe list
        frame.Keyframes.Clear();
        for (int i = 0; i < bindPose.Count; i++)
        {
          Keyframe key = new Keyframe(i, frame.Time, tData[i], rData[i]);
          frame.Keyframes.Add(key);
        }
      }
    }


    // ------------------------------------------------------------------------
    // Name: ValidateMesh
    // Desc: Makes sure this mesh contains the kind of data we know how to 
    //       animate.
    // ------------------------------------------------------------------------
    static void ValidateMesh(NodeContent node, ContentProcessorContext context, string parentBoneName)
    {
      // Cast the node to a MeshContent
      MeshContent mesh = node as MeshContent;
      if (mesh != null)
      {
        // Check that the parent bone is the root of the skeleton
        if (parentBoneName != null)
        {
          context.Logger.LogWarning(null, null, "Mesh {0} is a child of bone {1}. SkinnedModelProcessor " +
            "does not correctly handle meshes that are children of bones.", mesh.Name, parentBoneName);
        }

        // Check that the mesh has skinning data
        if (!MeshHasSkinning(mesh))
        {
          context.Logger.LogWarning(null, null, "Mesh {0} has no skinning information, so it has been deleted.", mesh.Name);
          mesh.Parent.Children.Remove(mesh);
          return;
        }
      }
      else if (node is BoneContent)
      {
        // If this is a bone, remember that we are now looking inside it.
        parentBoneName = node.Name;
      }

      // Recurse (iterating over a copy of the child collection,
      // because validating children may delete some of them).
      foreach (NodeContent child in new List<NodeContent>(node.Children))
      {
        ValidateMesh(child, context, parentBoneName);
      }
    }


    // ------------------------------------------------------------------------
    // Name: MeshHasSkinning
    // Desc: Checks whether a mesh contains skininng information.
    // ------------------------------------------------------------------------
    static bool MeshHasSkinning(MeshContent mesh)
    {
      foreach (GeometryContent geometry in mesh.Geometry)
      {
        if (!geometry.Vertices.Channels.Contains(VertexChannelNames.Weights()))
        {
          return false;
        }
      }

      return true;
    }


    // ------------------------------------------------------------------------
    // Name: FlattenTransforms
    // Desc: Bakes unwanted transforms into the model geometry, so everything 
    //       ends up in the same coordinate system.
    // ------------------------------------------------------------------------
    static void FlattenTransforms(NodeContent node, BoneContent skeleton)
    {
      foreach (NodeContent child in node.Children)
      {
        // Don't process the skeleton, because that is special.
        if (child == skeleton)
        {
          continue;
        }

        // Bake the local transform into the actual geometry.
        MeshHelper.TransformScene(child, child.Transform);

        // Having baked it, we can now set the local
        // coordinate system back to identity.
        child.Transform = Matrix.Identity;

        // Recurse.
        FlattenTransforms(child, skeleton);
      }
    }


    // ------------------------------------------------------------------------
    // Name: ConvertMaterial
    // Desc: Changes all the materials to use our skinned model effect.
    // ------------------------------------------------------------------------
    protected override MaterialContent ConvertMaterial(MaterialContent material, ContentProcessorContext context)
    {
      // Cast the material to a BasicMaterial
      BasicMaterialContent basicMaterial = material as BasicMaterialContent;

      // Esnure that the material is a BasicMaterial
      if (basicMaterial == null)
      {
        throw new InvalidContentException(string.Format("SkinnedModelProcessor only supports BasicMaterialContent, " +
            "but input mesh uses {0}.", material.GetType()));
      }

      // Create an effect material
      EffectMaterialContent effectMaterial = new EffectMaterialContent();

      // Store a reference to our skinned mesh effect.
      string effectPath = Path.GetFullPath("shaders\\SkinnedModel.fx");
      effectMaterial.Effect = new ExternalReference<EffectContent>(effectPath);

      // Copy texture settings from the input
      // BasicMaterialContent over to our new material.
      if (basicMaterial.Texture != null)
      {
        effectMaterial.Textures.Add("Texture", basicMaterial.Texture);
      }

      // Chain to the base ModelProcessor converter.
      return base.ConvertMaterial(effectMaterial, context);
    }
  }


  // --------------------------------------------------------------------------
  // Name: AnimationClipWriter
  // Desc: Writes the data to an XNB
  // --------------------------------------------------------------------------
  [ContentTypeWriter]
  public class AnimationClipWriter : ContentTypeWriter<AnimationClip>
  {
    protected override void Write(ContentWriter output, AnimationClip value)
    {
      output.WriteObject(value.Duration);
      output.WriteObject(value.AnimationFrames);
    }

    public override string GetRuntimeReader(TargetPlatform targetPlatform)
    {
      return typeof(AnimationClipReader).AssemblyQualifiedName;
    }
  }



  // --------------------------------------------------------------------------
  // Name: AnimationFrameWriter
  // Desc: Writes the data to an XNB
  // --------------------------------------------------------------------------
  [ContentTypeWriter]
  public class AnimationFrameWriter : ContentTypeWriter<AnimationFrame>
  {
    protected override void Write(ContentWriter output, AnimationFrame value)
    {
      output.WriteObject(value.Time);
      output.WriteObject(value.Keyframes);
    }

    public override string GetRuntimeReader(TargetPlatform targetPlatform)
    {
      return typeof(AnimationFrameReader).AssemblyQualifiedName;
    }
  }




  // --------------------------------------------------------------------------
  // Name: KeyframeWriter
  // Desc: Writes the data to an XNB
  // --------------------------------------------------------------------------
  [ContentTypeWriter]
  public class KeyframeWriter : ContentTypeWriter<Keyframe>
  {
    protected override void Write(ContentWriter output, Keyframe value)
    {
      output.WriteObject(value.Bone);
      output.WriteObject(value.Time);
      output.WriteObject(value.Translation);
      output.WriteObject(value.Rotation);
    }

    public override string GetRuntimeReader(TargetPlatform targetPlatform)
    {
      return typeof(KeyframeReader).AssemblyQualifiedName;
    }
  }



  // --------------------------------------------------------------------------
  // Name: SkinningDataWriter
  // Desc: Writes the data to an XNB
  // --------------------------------------------------------------------------
  [ContentTypeWriter]
  public class SkinningDataWriter : ContentTypeWriter<SkinningData>
  {
    protected override void Write(ContentWriter output, SkinningData value)
    {
      output.WriteObject(value.AnimationClips);
      output.WriteObject(value.BindPose);
      output.WriteObject(value.InverseBindPose);
      output.WriteObject(value.SkeletonHierarchy);
    }

    public override string GetRuntimeReader(TargetPlatform targetPlatform)
    {
      return typeof(SkinningDataReader).AssemblyQualifiedName;
    }
  }



















}


// -- EOF

