// ----------------------------------------------------------------------------
// File: Material.cs
// Desc: Base class for all materials.
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: Material
  // Desc: Base class for all materials. The conept of a material, is a wrapper 
  //       around an effect (fx file). The material can render any object that 
  //       has inherits from the IRender interface.
  // --------------------------------------------------------------------------
  public abstract class Material
  {
    // ------------------------------------------------------------------------
    // Public Members
    // ------------------------------------------------------------------------
    public String Name { get { return m_name; } }


    // ------------------------------------------------------------------------
    // Private Members
    // ------------------------------------------------------------------------
    protected String m_name;
    protected Effect m_effect;


    // ------------------------------------------------------------------------
    // Name: Material
    // Desc: Constructor
    // Parm: String a_effectName - the name of the effect file to load
    // ------------------------------------------------------------------------
    public Material(String a_effectName)
    {
      m_name = a_effectName;
      m_effect = Systems.Content.Load<Effect>(Asset.Resolve(AssetType.AT_SHADER, a_effectName));
      CreateParameters();
    }


    // ------------------------------------------------------------------------
    // Name: CreateParameters
    // Desc: Create any effect file parameters - called after the effect is 
    //       loaded.
    // ------------------------------------------------------------------------
    protected abstract void CreateParameters();


    // ------------------------------------------------------------------------
    // Name: SetParameters
    // Desc: Set the effect parameters - called each time that the material is 
    //       about to render an IRender object.
    // Parm: Matrix a_worldMatrix - the world matrix that the IRender object is 
    //       to be rendered with.
    // ------------------------------------------------------------------------
    protected abstract void SetParameters();


    // ------------------------------------------------------------------------
    // Name: SetState
    // Desc: Called before the effect is started, allowing any changes in render
    //       state to be pushed.
    // ------------------------------------------------------------------------
    protected virtual void SetState()
    {
    }


    // ------------------------------------------------------------------------
    // Name: ResetState
    // Desc: Called after the effect has finished to return the render state to 
    //       it's default.
    // ------------------------------------------------------------------------
    protected virtual void ResetState()
    {
    }


    public void AddForRender(IRender a_renderInterface, int a_renderPriority, Matrix a_worldMatrix, CullMode a_cullMode)
    {
      RenderManager.Instance.Add(this, a_renderInterface, a_renderPriority, a_worldMatrix, a_cullMode);
    }

    
    public void AddForRender(IRender a_renderInterface, RenderPriority a_renderPriority, Matrix a_worldMatrix, CullMode a_cullMode)
    {
      RenderManager.Instance.Add(this, a_renderInterface, (int) a_renderPriority, a_worldMatrix, a_cullMode);
    }


    public abstract void SetTransforms(Matrix a_worldMatrix);


    public virtual void ApplyModelInfo(IRender a_renderInterface, CullMode a_cullMode, out CullMode a_outCullMode)
    {
      if (a_renderInterface.ModelInfo.AlphaBlend)
      {
        Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = true;
        Systems.Graphics.GraphicsDevice.RenderState.AlphaSourceBlend = Blend.SourceAlpha;
        Systems.Graphics.GraphicsDevice.RenderState.AlphaDestinationBlend = Blend.InverseSourceAlpha;

        Systems.Graphics.GraphicsDevice.RenderState.AlphaTestEnable = false;
      }
      else if (a_renderInterface.ModelInfo.AlphaMask)
      {
        Systems.Graphics.GraphicsDevice.RenderState.AlphaTestEnable = true;
        Systems.Graphics.GraphicsDevice.RenderState.ReferenceAlpha = a_renderInterface.ModelInfo.ReferenceAlpha;

        Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = false;
      }
      else      
      {
        Systems.Graphics.GraphicsDevice.RenderState.AlphaTestEnable = false;
        Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = false;
      }

      if (a_renderInterface.ModelInfo.TwoSided)
      {
        a_outCullMode = CullMode.None;
      }
      else
      {
        a_outCullMode = a_cullMode;
      }
    }

    
    // ------------------------------------------------------------------------
    // Name: Render
    // Desc: Render the supplied IRender object with this material.
    // Parm: IRender a_renderInterface - the object to render
    // Parm: Matrix a_worldMatrix  - the world matrix to render this object with
    //       (passed to SetParameters())
    // Parm: CullMode a_cullMode   - the cull mode to render this object with
    // ------------------------------------------------------------------------
    public void Render(IRender a_renderInterface, Matrix a_worldMatrix, CullMode a_cullMode)
    {
      // Set the effect parameters
      SetParameters();

      // Set the state
      SetState();

      // Apply the model info
      CullMode a_outCullMode;
      ApplyModelInfo(a_renderInterface, a_cullMode, out a_outCullMode);

      // Bind the effect
      m_effect.CommitChanges();      
      m_effect.Begin();

      // Render each pass
      foreach (EffectPass pass in m_effect.CurrentTechnique.Passes)
      {
        // Set the cull mode
        Systems.Graphics.GraphicsDevice.RenderState.CullMode = a_outCullMode;

        // Render the pass
        pass.Begin();
        a_renderInterface.Render(this, a_worldMatrix);
        pass.End();
      }

      // End the effect
      m_effect.End();

      // Reset the values set by the model info
      Systems.Graphics.GraphicsDevice.RenderState.AlphaTestEnable = false;
      Systems.Graphics.GraphicsDevice.RenderState.AlphaBlendEnable = false;
      Systems.Graphics.GraphicsDevice.RenderState.CullMode = CullMode.None;

      // Reset the state
      ResetState();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

