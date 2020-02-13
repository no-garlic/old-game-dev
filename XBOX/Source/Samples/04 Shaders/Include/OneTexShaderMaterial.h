
#ifndef __ONETEX_SHADER_MATERIAL_H_
#define __ONETEX_SHADER_MATERIAL_H_


#include "libEngine.h"


class OneTexShaderMaterial : public ShaderMaterial
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  OneTexShaderMaterial();
  virtual ~OneTexShaderMaterial();

  // --------------------------------------------------------------------------
  // Set all constants for the material before beginning the render
  // --------------------------------------------------------------------------
  virtual void Prepare(const Matrix &world_matrix, const D3DMATERIAL &material, 
    const TextureArray &textures, const LightArray &lights, 
    ShadowCaster *pShadowCaster = 0) const;

protected:
  // --------------------------------------------------------------------------
  // Create the vertex declaration and the shaders
  // --------------------------------------------------------------------------
  virtual bool CreateVertexDeclaration();
  virtual bool CreateVertexShader();
  virtual bool CreatePixelShader();

};


#endif // __ONETEX_SHADER_MATERIAL_H_

// -- EOF

