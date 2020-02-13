

#include "SelectedMeshMaterial.h"


SelectedMeshMaterial::SelectedMeshMaterial()
{
  REF_COUNT_CTOR(SelectedMeshMaterial);
  m_Ambient   = Color(0.35f, 0.0f, 0.0f);
  m_Diffuse   = Color(0.35f, 0.15f, 0.15f);
  m_Lighting  = true;
}


SelectedMeshMaterial::~SelectedMeshMaterial()
{
  REF_COUNT_DTOR(SelectedMeshMaterial);
}


void SelectedMeshMaterial::Prepare(const Matrix &world_matrix, 
                                const D3DMATERIAL &material, 
                                const TextureArray &textures, 
                                const LightArray &lights, 
                                ShadowCaster *pShadowCaster) const
{
  D3DMATERIAL mat = material;

  mat.Ambient = m_Ambient;
  mat.Diffuse = m_Diffuse;

  if (!m_Lighting)
  {
    mat.Diffuse = Color::Black;
  }

  TextureArray tex;
  FixedFunctionMaterial_PN::Prepare(world_matrix, mat, tex, lights, pShadowCaster);
}


void SelectedMeshMaterial::ForceColor(const Color &ambient, const Color &diffuse)
{
  m_Ambient = ambient;
  m_Diffuse = diffuse;
}


// -- EOF

