// ----------------------------------------------------------------------------
// File: RenderManager.cs
// Desc: 
// Auth: Michael Petrou
// (C) Copyright: 2009
// ----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;




namespace WaveRace360
{
  public class RenderItem
  {
    public Material Material;
    public IRender  RenderInterface;
    public Matrix   Transform;
    public CullMode Cull;
  };


  public class RenderLayer
  {
    public int              Priority;
    public List<RenderItem> Items;
  };


  // --------------------------------------------------------------------------
  // Name: RenderManager
  // Desc: 
  // --------------------------------------------------------------------------
  public class RenderManager
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public static RenderManager Instance { get { return s_instance; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private static RenderManager s_instance = new RenderManager();
    private SortedList<int, RenderLayer> m_renderLayers;


    // ------------------------------------------------------------------------
    // Name: RenderManager
    // Desc: Constructor
    // ------------------------------------------------------------------------
    public RenderManager()
    {
      m_renderLayers = new SortedList<int,RenderLayer>();
    }


    public void Add(Material a_material, IRender a_renderInterface, int a_renderPriority, Matrix a_transform, CullMode a_cull)
    {
      RenderItem item = new RenderItem();
      item.Material = a_material;
      item.RenderInterface = a_renderInterface;
      item.Transform = a_transform;
      item.Cull = a_cull;

      RenderLayer layer;
      if (m_renderLayers.TryGetValue(a_renderPriority, out layer))
      {
        layer.Items.Add(item);
      }
      else
      {
        layer = new RenderLayer();
        layer.Priority = a_renderPriority;
        layer.Items = new List<RenderItem>();
        layer.Items.Add(item);
        m_renderLayers[a_renderPriority] = layer;
      }
    }


    public void Render()
    {
      foreach (RenderLayer layer in m_renderLayers.Values)
      {
        foreach (RenderItem item in layer.Items)
        {
          item.Material.Render(item.RenderInterface, item.Transform, item.Cull);
        }
      }

      Clear();
    }


    public void Clear()
    {
      m_renderLayers.Clear();
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

