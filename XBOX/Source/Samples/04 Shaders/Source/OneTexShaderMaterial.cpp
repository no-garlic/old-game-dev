
#include "OneTexShaderMaterial.h"


OneTexShaderMaterial::OneTexShaderMaterial()
{
}


OneTexShaderMaterial::~OneTexShaderMaterial()
{
}


void OneTexShaderMaterial::Prepare(const Matrix &world_matrix, 
                                   const D3DMATERIAL &material, 
                                   const TextureArray &textures, 
                                   const LightArray &lights,
                                   ShadowCaster *pShadowCaster) const
{
  Matrix wvp = world_matrix * Camera.GetViewProj();
  wvp.Transpose();

  SetVSMatrix(0, wvp);
  SetTexture(0, textures.GetTex0());

  // Set a pixel shader constant to interpolate with the pixel color
  float t = fabs(sinf(Application.GetRunningTime() * 2.0f));
  SetPSVec4(0, Vec4(t, t, t, 1.0f));
}


bool OneTexShaderMaterial::CreateVertexDeclaration()
{
#if PC
  D3DVERTEXELEMENT9 decl[] = 
  {
    { 0, 0, D3DDECLTYPE_FLOAT3,  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
    { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
  };

  return (Device->CreateVertexDeclaration(decl, &m_VertexDeclaration) == S_OK);
#else

  DWORD vertexDecl[] = 
  {
    D3DVSD_STREAM( 0 ),
    D3DVSD_REG( 0, D3DVSDT_FLOAT3 ),  // position
    D3DVSD_REG( 1, D3DVSDT_FLOAT3 ),  // normal
    D3DVSD_REG( 2, D3DVSDT_FLOAT2 ),  // texture
    D3DVSD_END()
  };

  m_VertexDeclaration = new DWORD[5];
  memcpy(m_VertexDeclaration, vertexDecl, 5 * sizeof(DWORD));

#endif

  return true;
}


bool OneTexShaderMaterial::CreateVertexShader()
{
  FileHandle handle = Application.GetMaterialDatabase()->FindFileHandle("OneTexShaderMaterial.vsh");
  return LoadVertexShader(handle);
}


bool OneTexShaderMaterial::CreatePixelShader()
{
  FileHandle handle = Application.GetMaterialDatabase()->FindFileHandle("OneTexShaderMaterial.psh");
  return LoadPixelShader(handle);
}


// -- EOF

