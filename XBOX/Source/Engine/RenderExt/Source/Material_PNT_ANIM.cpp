

#include "Material_PNT_ANIM.h"


Material_PNT_ANIM::Material_PNT_ANIM()
{
  REF_COUNT_CTOR(Material_PNT_ANIM);
}


Material_PNT_ANIM::~Material_PNT_ANIM()
{
  REF_COUNT_DTOR(Material_PNT_ANIM);
}


void Material_PNT_ANIM::Prepare(const Matrix &world_matrix, 
                                const D3DMATERIAL &material, 
                                const TextureArray &textures, 
                                const LightArray &lights, 
                                ShadowCaster *pShadowCaster) const
{
  Matrix wvp = world_matrix * Camera.GetViewProj();
  wvp.Transpose();

  // Set the wvp matrix
  SetVSMatrix(0, wvp);

  // Set the render states
  RenderState.Set(D3DRS_CULLMODE, D3DCULL_NONE);

  // Set the material and lights
  Device->SetMaterial(&material);
  Device->SetVertexShaderConstantF(5, (float *) &material.Diffuse, 1);

  // Set the lights
  if (lights.size() > 0)
  {
    D3DLIGHT &light = *lights[0];

    Vec3 lightDir = -((Vec3)light.Direction);

    Device->SetVertexShaderConstantF(4, (float *) &lightDir, 1);  
    Device->SetVertexShaderConstantF(6, (float *) &light.Ambient, 1);
  }

  // Set the texture
  if (textures.GetTex0())
  {
    SetTexture(0, textures.GetTex0());
  }
}


void Material_PNT_ANIM::SetBoneMatrix(uint boneId, const Matrix &matrix) const
{
  Device->SetVertexShaderConstantF(7 + boneId * 3, (float *)&matrix, 3);
}


bool Material_PNT_ANIM::CreateVertexDeclaration()
{
#if PC
  D3DVERTEXELEMENT9 decl[] = 
  {
    { 0, 0 ,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
    { 0, 28,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
    { 0, 44,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
    { 0, 56,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
  };

  return (Device->CreateVertexDeclaration(decl, &m_VertexDeclaration) == S_OK);
#else

  DWORD vertexDecl[] = 
  {
    D3DVSD_STREAM( 0 ),
    D3DVSD_REG( 0, D3DVSDT_FLOAT3 ),  // position
    D3DVSD_REG( 1, D3DVSDT_FLOAT4 ),  // blend weight
    D3DVSD_REG( 2, D3DVSDT_FLOAT4 ),  // bend indices
    D3DVSD_REG( 3, D3DVSDT_FLOAT3 ),  // normal
    D3DVSD_REG( 4, D3DVSDT_FLOAT2 ),  // texture
    D3DVSD_END()
  };

  m_VertexDeclaration = new DWORD[5];
  memcpy(m_VertexDeclaration, vertexDecl, 5 * sizeof(DWORD));

#endif

  return true;
}


bool Material_PNT_ANIM::CreateVertexShader()
{
  FileHandle handle = Application.GetMaterialDatabase()->FindFileHandle("Material_PNT_ANIM.vsh");
  return LoadVertexShader(handle);
}


bool Material_PNT_ANIM::CreatePixelShader()
{
  FileHandle handle = Application.GetMaterialDatabase()->FindFileHandle("Material_PNT_ANIM_NOTEX.psh");
  return LoadPixelShader(handle);
}



// -- EOF

