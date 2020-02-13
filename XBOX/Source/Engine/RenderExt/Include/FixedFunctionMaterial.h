
#ifndef __FIXEDFUNCTION_MATERIAL_H_
#define __FIXEDFUNCTION_MATERIAL_H_


#include "Material.h"


class FixedFunctionMaterial : public Material
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  FixedFunctionMaterial(DWORD fvf);
  virtual ~FixedFunctionMaterial();

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

protected:
  // --------------------------------------------------------------------------
  // The vertex format
  // --------------------------------------------------------------------------
  DWORD   m_FVF;

};


class FixedFunctionMaterial_P : public FixedFunctionMaterial
{
public:
  // --------------------------------------------------------------------------
  // Construct with the FVF for the material
  // --------------------------------------------------------------------------
  FixedFunctionMaterial_P() 
    : FixedFunctionMaterial(D3DFVF_XYZ) {}

};


class FixedFunctionMaterial_PC : public FixedFunctionMaterial
{
public:
  // --------------------------------------------------------------------------
  // Construct with the FVF for the material
  // --------------------------------------------------------------------------
  FixedFunctionMaterial_PC() 
    : FixedFunctionMaterial(D3DFVF_XYZ|D3DFVF_DIFFUSE) {}

};


class FixedFunctionMaterial_PT : public FixedFunctionMaterial
{
public:
  // --------------------------------------------------------------------------
  // Construct with the FVF for the material
  // --------------------------------------------------------------------------
  FixedFunctionMaterial_PT() 
    : FixedFunctionMaterial(D3DFVF_XYZ|D3DFVF_TEX1) {}

};


class FixedFunctionMaterial_PCT : public FixedFunctionMaterial
{
public:
  // --------------------------------------------------------------------------
  // Construct with the FVF for the material
  // --------------------------------------------------------------------------
  FixedFunctionMaterial_PCT() 
    : FixedFunctionMaterial(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1) {}

};


class FixedFunctionMaterial_PN : public FixedFunctionMaterial
{
public:
  // --------------------------------------------------------------------------
  // Construct with the FVF for the material
  // --------------------------------------------------------------------------
  FixedFunctionMaterial_PN()
    : FixedFunctionMaterial(D3DFVF_XYZ|D3DFVF_NORMAL) {}

};


class FixedFunctionMaterial_PNC : public FixedFunctionMaterial
{
public:
  // --------------------------------------------------------------------------
  // Construct with the FVF for the material
  // --------------------------------------------------------------------------
  FixedFunctionMaterial_PNC() 
    : FixedFunctionMaterial(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE) {}

};


class FixedFunctionMaterial_PNCT : public FixedFunctionMaterial
{
public:
  // --------------------------------------------------------------------------
  // Construct with the FVF for the material
  // --------------------------------------------------------------------------
  FixedFunctionMaterial_PNCT() 
    : FixedFunctionMaterial(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1) {}

};


class FixedFunctionMaterial_PNT : public FixedFunctionMaterial
{
public:
  // --------------------------------------------------------------------------
  // Construct with the FVF for the material
  // --------------------------------------------------------------------------
  FixedFunctionMaterial_PNT()
    : FixedFunctionMaterial(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1) {}

};


#endif // __FIXEDFUNCTION_MATERIAL_H_

// -- EOF

