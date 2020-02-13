// ----------------------------------------------------------------------------
// File: RenderList.h
// Desc: A list of meshes to be rendered
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __RENDER_LIST_H_
#define __RENDER_LIST_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "libMaths.h"
#include "ShadowCaster.h"
#include "Mesh.h"


// ----------------------------------------------------------------------------
// Name: RenderList  (class)
// Desc: A list of meshes to be rendered
// ----------------------------------------------------------------------------
class RenderList : private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  RenderList();
  virtual ~RenderList();

  // --------------------------------------------------------------------------
  // Add a mesh to the render list
  // --------------------------------------------------------------------------
  virtual void Add(const Mesh *pMesh, const Matrix &matrix);

  // --------------------------------------------------------------------------
  // Render to the shadow buffer
  // --------------------------------------------------------------------------
  virtual uint RenderToShadowCaster(const LightArray &lights, ShadowCaster *pShadowCaster, const Material *pMaterial);
  
  // --------------------------------------------------------------------------
  // Render to the back buffer with / without shadows
  // --------------------------------------------------------------------------
  virtual uint Render(const LightArray &lights);
  virtual uint RenderWithShadows(const LightArray &lights, ShadowCaster *pShadowCaster);

  // --------------------------------------------------------------------------
  // Get the bounding sphere of all geometry contained in the render list
  // --------------------------------------------------------------------------
  const Sphere &GetBSphere() const { return m_Bounds; }
    
  // --------------------------------------------------------------------------
  // Get the number of render items contained in the render list
  // --------------------------------------------------------------------------
  uint GetRenderItemCount() const { return m_TotalCount; }

protected:
  // --------------------------------------------------------------------------
  // Internal render function that is called by Render() and RenderWithShadows()
  // --------------------------------------------------------------------------
  virtual uint RenderInternal(const LightArray &lights, ShadowCaster *pShadowCaster);

  // --------------------------------------------------------------------------
  // Name: RenderCall (struct)
  // Desc: Info for a single render call
  // --------------------------------------------------------------------------
  struct RenderCall
  {
    uint              subsetAddr;     // The address of the subset
    uint              subsetId;       // The subsetId
    const Material   *pMaterial;      // The material
    const Mesh       *pMesh;          // The mesh
    const MeshSubset *pSubset;        // The subset
    Array<Matrix>     matrixArray;    // The instances
  }; // struct RenderCall

  // --------------------------------------------------------------------------
  // A map of render calls indexed by the address of the subset
  // --------------------------------------------------------------------------
  typedef Map<uint, RenderCall> RenderCallMap;

  // --------------------------------------------------------------------------
  // Name: RenderItem (struct)
  // Desc: Info for a single material
  // --------------------------------------------------------------------------
  struct RenderItem
  {
    uint              materialAddr;   // The address of the material
    const Material   *pMaterial;      // The material
    RenderCallMap     renderCalls;    // The render calls
  }; // struct RenderItem

  // --------------------------------------------------------------------------
  // A map of render items indexed by the address of the material
  // --------------------------------------------------------------------------
  typedef Map<uint, RenderItem> RenderItemMap;

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  RenderItemMap   m_RenderItems;
  Sphere          m_Bounds;
  uint            m_TotalCount; // All render calls
  
}; // class RenderList


#endif // __RENDER_LIST_H_

// -- EOF

