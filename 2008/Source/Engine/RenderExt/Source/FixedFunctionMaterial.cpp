
#include "FixedFunctionMaterial.h"
#include "Light.h"


FixedFunctionMaterial::FixedFunctionMaterial(DWORD fvf)
: Material  (),
  m_FVF     (fvf)
{  
  REF_COUNT_CTOR(FixedFunctionMaterial);
}


FixedFunctionMaterial::~FixedFunctionMaterial()
{
  REF_COUNT_DTOR(FixedFunctionMaterial);
}


bool FixedFunctionMaterial::Load()
{
  return true;
}


uint FixedFunctionMaterial::Begin() const
{
  Device->SetTransform(D3DTS_VIEW, &(Camera.GetView()));
  Device->SetTransform(D3DTS_PROJECTION, &(Camera.GetProj()));

  Device->SetFVF(m_FVF);

  return 1;
}


void FixedFunctionMaterial::BeginPass(uint pass) const
{
}


void FixedFunctionMaterial::Prepare(const Matrix &world_matrix, const D3DMATERIAL &material, 
    const TextureArray &textures, const LightArray &lights, ShadowCaster *pShadowCaster) const
{
  Device->SetTransform(D3DTS_WORLD, &world_matrix);
  Device->SetMaterial(&material);

  SetTexture(0, textures.GetTex0());
}


void FixedFunctionMaterial::EndPass() const
{
}


void FixedFunctionMaterial::End() const
{
}


bool FixedFunctionMaterial::AllocateDeviceMemory()
{
  
  return true;
}


bool FixedFunctionMaterial::ReleaseDeviceMemory()
{
  SetTexture(0, NULL);
  SetTexture(1, NULL);
  SetTexture(2, NULL);
  SetTexture(3, NULL);
  
  return true;
}


// -- EOF

