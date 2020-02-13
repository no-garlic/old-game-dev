// ----------------------------------------------------------------------------
// File: Material.cpp
// Desc: Material file support
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "Material.h"


// ----------------------------------------------------------------------------
// Static initialisation
// ----------------------------------------------------------------------------
Map<String, Material *> MaterialCache::s_MaterialMap;
Material *MaterialCache::s_DefaultMaterial = NULL;


// ----------------------------------------------------------------------------
// Name: Material::Material
// Desc: Constructor
// ----------------------------------------------------------------------------
Material::Material()
{
} // Material


// ----------------------------------------------------------------------------
// Name: Material::~Material
// Desc: Destructor
// ----------------------------------------------------------------------------
Material::~Material()
{
} // ~Material


// ----------------------------------------------------------------------------
// Name: MaterialCache::SetTexture
// Desc: Set a texture
// ----------------------------------------------------------------------------
void Material::SetTexture(uint stage, const Texture *pTexture) const
{
  ASSERT(stage < 4, "Texture stage out of range");

  if (pTexture)
  {
    D3DCheck(Device->SetTexture(stage, pTexture->GetPtr()));
  }
  else
  {
    D3DCheck(Device->SetTexture(stage, NULL));
  }
}


// --------------------------------------------------------------------------
// Set a bone matrix
// --------------------------------------------------------------------------
void Material::SetBoneMatrix(uint boneId, const Matrix &matrix) const
{
}


// ----------------------------------------------------------------------------
// Name: MaterialCache::GetMaterial
// Desc: Get a material from the cache
// ----------------------------------------------------------------------------
const Material *MaterialCache::GetMaterial(const String &name)
{
  Map<String, Material *>::iterator iter = s_MaterialMap.find(name);
  if (iter != s_MaterialMap.end())
    return iter->second;

  return s_DefaultMaterial;
} // LoadMaterial


// --------------------------------------------------------------------------
// Register a material in the cache
// --------------------------------------------------------------------------
void MaterialCache::RegisterMaterial(const String &name, Material *pMaterial)
{
#if !FINAL_RELEASE
  Map<String, Material *>::iterator iter = s_MaterialMap.find(name);
  if (iter != s_MaterialMap.end())
    ASSERT(NULL, "Cannot register two materials with the same name");
#endif

  s_MaterialMap.insert(MakePair(name, pMaterial));
}


// --------------------------------------------------------------------------
// UnRegister a material in the cache
// --------------------------------------------------------------------------
void MaterialCache::UnRegisterMaterial(const String &name)
{
  s_MaterialMap.erase(name);
}


// --------------------------------------------------------------------------
// Set the default material
// --------------------------------------------------------------------------
void MaterialCache::SetDefaultMaterial(Material *pMaterial)
{
  s_DefaultMaterial = pMaterial;
}


// --------------------------------------------------------------------------
// Get the default material
// --------------------------------------------------------------------------
const Material *MaterialCache::GetDefaultMaterial()
{
  return s_DefaultMaterial;
}


// -- EOF


