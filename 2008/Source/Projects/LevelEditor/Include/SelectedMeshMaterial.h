
#ifndef __SELECTED_MESH_MATERIAL_H_
#define __SELECTED_MESH_MATERIAL_H_


#include "libEngine.h"


class SelectedMeshMaterial : public FixedFunctionMaterial_PN
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  SelectedMeshMaterial();
  virtual ~SelectedMeshMaterial();

  // --------------------------------------------------------------------------
  // Set the color to force
  // --------------------------------------------------------------------------
  void ForceColor(const Color &ambient, const Color &diffuse);

  // --------------------------------------------------------------------------
  // Set the lighting mode to use for hte material. The material is always 
  // rendered with lighting on (because it uses fixed function), this should
  // impact the color material values used.
  // --------------------------------------------------------------------------
  inline void SetLightingMode(bool lightingOn) { m_Lighting = lightingOn; }

  // --------------------------------------------------------------------------
  // Set all constants for the material before beginning the render
  // --------------------------------------------------------------------------
  virtual void Prepare(const Matrix &world_matrix, const D3DMATERIAL &material, 
    const TextureArray &textures, const LightArray &lights, 
    ShadowCaster *pShadowCaster = 0) const;

private:
  Color   m_Ambient;
  Color   m_Diffuse;
  bool    m_Lighting;

};


#endif // __SELECTED_MESH_MATERIAL_H_

// -- EOF

