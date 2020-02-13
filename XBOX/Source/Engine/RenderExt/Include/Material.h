// ----------------------------------------------------------------------------
// File: Material.h
// Desc: MAterial support
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MATERIAL_H_
#define __MATERIAL_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libMaths.h"
#include "libRenderCore.h"
#include "Texture.h"
#include "ShadowCaster.h"
#include "Light.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Material;


// ----------------------------------------------------------------------------
// Typedefs
// ----------------------------------------------------------------------------
typedef Array<Material *> MaterialArray;


// ----------------------------------------------------------------------------
// Name: Material  (class)
// Desc: Class to manage a material
// ----------------------------------------------------------------------------
class Material : public DeviceObject, private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Material();
  virtual ~Material();

  // --------------------------------------------------------------------------
  // Get the material name
  // --------------------------------------------------------------------------
  void SetName(const String &name)  { m_Name = name; }
  const String &GetName() const     { return m_Name; }

  // --------------------------------------------------------------------------
  // Load the material
  // --------------------------------------------------------------------------
  virtual bool Load() = 0;

  // --------------------------------------------------------------------------
  // Set all constants for the material before beginning the render
  // --------------------------------------------------------------------------
  virtual void Prepare(const Matrix &world_matrix, const D3DMATERIAL &material, 
    const TextureArray &textures, const LightArray &lights, 
    ShadowCaster *pShadowCaster = 0) const = 0;

  // --------------------------------------------------------------------------
  // Set a bone matrix
  // --------------------------------------------------------------------------
  virtual void SetBoneMatrix(uint boneId, const Matrix &matrix) const;

  // --------------------------------------------------------------------------
  // Use the material
  // --------------------------------------------------------------------------
  virtual uint Begin() const = 0;
  virtual void BeginPass(uint pass = 0) const = 0;
  virtual void EndPass() const = 0;
  virtual void End() const = 0;

protected:
  // --------------------------------------------------------------------------
  // Set a texture
  // --------------------------------------------------------------------------
  void SetTexture(uint stage, const Texture *pTexture) const;

  // --------------------------------------------------------------------------
  // Manage device memory
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory() = 0;
  virtual bool ReleaseDeviceMemory() = 0;

protected:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  String  m_Name;

}; // Material


// ----------------------------------------------------------------------------
// Name: MaterialLoader (class)
// Desc: Class to load Materials
// ----------------------------------------------------------------------------
class MaterialCache
{
public:
  // --------------------------------------------------------------------------
  // Get a material from the cache
  // --------------------------------------------------------------------------
  static const Material *GetMaterial(const String &name);
  static const Material *GetDefaultMaterial();

  // --------------------------------------------------------------------------
  // Register a material in the cache
  // --------------------------------------------------------------------------
  static void RegisterMaterial(const String &name, Material *pMaterial);
  static void SetDefaultMaterial(Material *pMaterial);
  static void UnRegisterMaterial(const String &name);
  
private:
  // --------------------------------------------------------------------------
  // Private static members
  // --------------------------------------------------------------------------
  static Map<String, Material *>  s_MaterialMap;
  static Material *               s_DefaultMaterial;

}; // class MaterialCache


template <class T>
struct MaterialCreationFunctor : public ApplicationCentral::CreationFunctor
{
  MaterialCreationFunctor(const String &name, bool isDefault)
    : ApplicationCentral::CreationFunctor  (name), 
      Default                              (isDefault),
      m_pMaterial                          (NULL)
  {}

  virtual bool Create()
  {
    m_pMaterial = new T;
    m_pMaterial->SetName(Name);
    
    if (!m_pMaterial->Load())
    {
      delete m_pMaterial;
      m_pMaterial = NULL;
      return false;
    }
    
    MaterialCache::RegisterMaterial(Name, m_pMaterial);
    
    if (Default)
      MaterialCache::SetDefaultMaterial(m_pMaterial);

    return true;
  }

  virtual bool Destroy()
  {
    if (m_pMaterial)
    {
      MaterialCache::UnRegisterMaterial(Name);
      delete m_pMaterial;
      m_pMaterial = NULL;
    }

    return true;
  }

  T *m_pMaterial;
  bool Default;
};


#define REGISTER_MATERIAL(x) ApplicationCentral::AddCreationFunctor(new MaterialCreationFunctor<x>(#x,false));
#define REGISTER_DEFAULT_MATERIAL(x) ApplicationCentral::AddCreationFunctor(new MaterialCreationFunctor<x>(#x,true));


#endif // __MATERIAL_H_


// -- EOF


