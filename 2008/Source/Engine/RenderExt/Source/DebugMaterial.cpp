

#include "DebugMaterial.h"


DebugMaterial::DebugMaterial()
{
  REF_COUNT_CTOR(DebugMaterial);
}


DebugMaterial::~DebugMaterial()
{
  REF_COUNT_DTOR(DebugMaterial);
}


uint DebugMaterial::Begin() const
{
  ShaderMaterial::Begin();

  // Set the render states
  RenderState.Set(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
  RenderState.Set(D3DRS_CULLMODE, D3DCULL_NONE);

  return 1;
}


void DebugMaterial::End() const
{
  ShaderMaterial::End();

  // Set the render states
  RenderState.SetDefault(D3DRS_FILLMODE);
  RenderState.SetDefault(D3DRS_CULLMODE);
}


void DebugMaterial::Prepare(const Matrix &world_matrix, 
                            const D3DMATERIAL &material, 
                            const TextureArray &textures, 
                            const LightArray &lights, 
                            ShadowCaster *pShadowCaster) const
{
  Matrix wvp = world_matrix * Camera.GetViewProj();
  wvp.Transpose();

  // Set the wvp matrix
  SetVSMatrix(0, wvp);

  // Set the constant color
  SetPSVec4(0, Vec4(material.Diffuse.r, material.Diffuse.g, material.Diffuse.b, material.Diffuse.a));
}


bool DebugMaterial::CreateVertexDeclaration()
{
#if PC
  D3DVERTEXELEMENT9 decl[] = 
  {
    { 0, 0 ,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
    D3DDECL_END()
  };

  return (Device->CreateVertexDeclaration(decl, &m_VertexDeclaration) == S_OK);
#else

  DWORD vertexDecl[] = 
  {
    D3DVSD_STREAM( 0 ),
    D3DVSD_REG( 0, D3DVSDT_FLOAT3 ),  // position
    D3DVSD_REG( 1, D3DVSDT_FLOAT3 ),  // normal
    D3DVSD_END()
  };

  m_VertexDeclaration = new DWORD[3];
  memcpy(m_VertexDeclaration, vertexDecl, 3 * sizeof(DWORD));

  $$ error -> Should this be 2 OR 3 ??

#endif

  return true;
}


bool DebugMaterial::CreateVertexShader()
{
  FileHandle handle = Application.GetMaterialDatabase()->FindFileHandle("DebugMaterial.vsh");
  return LoadVertexShader(handle);
}


bool DebugMaterial::CreatePixelShader()
{
  FileHandle handle = Application.GetMaterialDatabase()->FindFileHandle("DebugMaterial.psh");
  return LoadPixelShader(handle);
}



// -- EOF

