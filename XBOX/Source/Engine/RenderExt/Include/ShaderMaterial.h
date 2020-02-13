// ----------------------------------------------------------------------------
// File: ShaderMaterial.h
// Desc: Material class that uses a vertex and pixel shader
// Auth: Michael Petrou
// (C) Copyright: 2007
// ----------------------------------------------------------------------------
#ifndef __SHADER_MATERIAL_H_
#define __SHADER_MATERIAL_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Material.h"


// ----------------------------------------------------------------------------
// Name: ShaderMaterial (class)
// Desc: Material class that uses a vertex and pixel shader
// ----------------------------------------------------------------------------
class ShaderMaterial : public Material
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ShaderMaterial();
  virtual ~ShaderMaterial();

  // --------------------------------------------------------------------------
  // Load the material
  // --------------------------------------------------------------------------
  virtual bool Load();

  // --------------------------------------------------------------------------
  // Set all constants for the material before beginning the render
  // --------------------------------------------------------------------------
  virtual void Prepare(const Matrix &world_matrix, const D3DMATERIAL &material, 
    const TextureArray &textures, const LightArray &lights, 
    ShadowCaster *pShadowCaster = 0) const = 0;

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
  // Create the vertex declaration and the shaders
  // --------------------------------------------------------------------------
  virtual bool CreateVertexDeclaration() = 0;
  virtual bool CreateVertexShader() = 0;
  virtual bool CreatePixelShader() = 0;

  // --------------------------------------------------------------------------
  // Load the shaders from source files
  // --------------------------------------------------------------------------
  virtual bool LoadVertexShader(FileHandle handle);
  virtual bool LoadPixelShader(FileHandle handle);

  // --------------------------------------------------------------------------
  // Set the shader constants
  // --------------------------------------------------------------------------
  void SetVSFloat(uint reg, float data) const;
  void SetVSVec3(uint reg, const Vec3 &data) const;
  void SetVSVec4(uint reg, const Vec4 &data) const;
  void SetVSMatrix(uint reg, const Matrix &data) const;
  void SetPSFloat(uint reg, float data) const;
  void SetPSVec3(uint reg, const Vec3 &data) const;
  void SetPSVec4(uint reg, const Vec4 &data) const;
  void SetPSMatrix(uint reg, const Matrix &data) const;

protected:
  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  VERTEXDECLARATION m_VertexDeclaration;
  VERTEXSHADER      m_VertexShader;
  PIXELSHADER       m_PixelShader;
  FileHandle        m_VertexShaderHandle;
  FileHandle        m_PixelShaderHandle;

};


#endif // __SHADER_MATERIAL_H_

// -- EOF

