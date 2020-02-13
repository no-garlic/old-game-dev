// ----------------------------------------------------------------------------
// File: EffectMaterial.h
// Desc: Material class that uses a vertex and pixel shader
// Auth: Michael Petrou
// (C) Copyright: 2007
// ----------------------------------------------------------------------------
#ifndef __EFFECT_MATERIAL_H_
#define __EFFECT_MATERIAL_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Material.h"


// ----------------------------------------------------------------------------
// Name: EffectMaterial (class)
// Desc: Material class that uses a vertex and pixel shader
// ----------------------------------------------------------------------------
class EffectMaterial : public Material
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  EffectMaterial();
  virtual ~EffectMaterial();

  // --------------------------------------------------------------------------
  // Load the material
  // --------------------------------------------------------------------------
  virtual bool Load();

  // --------------------------------------------------------------------------
  // Set all constants for the material before beginning the render
  // --------------------------------------------------------------------------
  virtual void Prepare(const Matrix &world_matrix, const D3DMATERIAL &material, 
    const TextureArray &textures, const LightArray &lights, 
    ShadowCaster *pShadowCaster = 0) const;

  // --------------------------------------------------------------------------
  // Use the material
  // --------------------------------------------------------------------------
  virtual uint Begin() const;
  virtual void BeginPass(uint pass = 0) const;
  virtual void EndPass() const;
  virtual void End() const;

protected:
  // --------------------------------------------------------------------------
  // Manage device memory
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory();
  virtual bool ReleaseDeviceMemory();

  // --------------------------------------------------------------------------
  // Create the vertex declaration and the effect
  // --------------------------------------------------------------------------
  virtual bool CreateVertexDeclaration() = 0;
  virtual bool CreateEffect() = 0;

  // --------------------------------------------------------------------------
  // Commit the changes of the effect (must be called at the end of prepare)
  // --------------------------------------------------------------------------
  virtual void CommitChanges() const;

  // --------------------------------------------------------------------------
  // Load the effect from a source file
  // --------------------------------------------------------------------------
  virtual bool LoadEffect(FileHandle handle);

protected:
  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  VERTEXDECLARATION m_VertexDeclaration;
  LPD3DXEFFECT      m_Effect;
  FileHandle        m_EffectHandle;

};


#endif // __EFFECT_MATERIAL_H_

// -- EOF

