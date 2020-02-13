
#ifndef __MATERIAL_PNT_ANIM_H_
#define __MATERIAL_PNT_ANIM_H_


#include "libRenderCore.h"
#include "ShaderMaterial.h"


class Material_PNT_ANIM : public ShaderMaterial
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Material_PNT_ANIM();
  virtual ~Material_PNT_ANIM();

  // --------------------------------------------------------------------------
  // Set all constants for the material before beginning the render
  // --------------------------------------------------------------------------
  virtual void Prepare(const Matrix &world_matrix, const D3DMATERIAL &material, 
    const TextureArray &textures, const LightArray &lights, 
    ShadowCaster *pShadowCaster = 0) const;

  // --------------------------------------------------------------------------
  // Set a bone matrix
  // --------------------------------------------------------------------------
  virtual void SetBoneMatrix(uint boneId, const Matrix &matrix) const;

protected:
  // --------------------------------------------------------------------------
  // Create the vertex declaration and the shaders
  // --------------------------------------------------------------------------
  virtual bool CreateVertexDeclaration();
  virtual bool CreateVertexShader();
  virtual bool CreatePixelShader();

private:

};


#endif // __MATERIAL_PNT_ANIM_H_

// -- EOF

