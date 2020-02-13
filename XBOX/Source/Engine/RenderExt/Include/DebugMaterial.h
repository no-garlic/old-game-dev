
#ifndef __DEBUG_MATERIAL_H_
#define __DEBUG_MATERIAL_H_


#include "libRenderCore.h"
#include "ShaderMaterial.h"


class DebugMaterial : public ShaderMaterial
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  DebugMaterial();
  virtual ~DebugMaterial();

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
  virtual void End() const;

protected:
  // --------------------------------------------------------------------------
  // Create the vertex declaration and the shaders
  // --------------------------------------------------------------------------
  virtual bool CreateVertexDeclaration();
  virtual bool CreateVertexShader();
  virtual bool CreatePixelShader();

private:

};


#endif // __DEBUG_MATERIAL_H_

// -- EOF

