
#ifndef __OVERRIDE_RENDER_LIST_H_
#define __OVERRIDE_RENDER_LIST_H_


#include "libEngine.h"


// The material will be chosen bsaed on the rules:
//
// 1. If there is an override material for the vertex type, it is chosen
// 2. Otherwise if there is a global override material, it is chosen
// 3. Otherwise the mesh subset's material is chosen.
//
class OverrideRenderList : public RenderList
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  OverrideRenderList();
  virtual ~OverrideRenderList();

  // --------------------------------------------------------------------------
  // Set the override material for all vertex types
  // --------------------------------------------------------------------------
  void SetGlobalOverrideMaterial(const Material *pOverideMaterial);

  // --------------------------------------------------------------------------
  // Set the override material for a vertex type
  // --------------------------------------------------------------------------
  void SetOverrideMaterialForVertexType(const Material *pOverideMaterial, const VertexType *pVertexType);

  // --------------------------------------------------------------------------
  // Add a mesh to the render list
  // --------------------------------------------------------------------------
  virtual void Add(const Mesh *pMesh, const Matrix &matrix);

protected:
  // --------------------------------------------------------------------------
  // Mapping of a vertex type and a material
  // --------------------------------------------------------------------------
  typedef Map<const VertexType *, const Material *> OverrideMaterialMap;

  // --------------------------------------------------------------------------
  // The override materials
  // --------------------------------------------------------------------------
  const Material       *m_pGlobalOverride;    // Global material
  OverrideMaterialMap   m_OverrideMaterials;  // Per vertex type materials

};


#endif // __OVERRIDE_RENDER_LIST_H_

// -- EOF

