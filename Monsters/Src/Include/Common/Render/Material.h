// ----------------------------------------------------------------------------
// File: Material.h
// Desc: Effect file support
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MATERIAL_H_
#define __MATERIAL_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Maths/MathInc.h"
#include "Engine/EngineInc.h"
#include "Render/Texture.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Material;


// ----------------------------------------------------------------------------
// Typedefs
// ----------------------------------------------------------------------------
typedef Array<Material *> MaterialArray;


// ----------------------------------------------------------------------------
// The parameter types
// ----------------------------------------------------------------------------
enum MaterialParameters
{
  // Camera / Projection Matricies
  matrix_World,
  matrix_View,
  matrix_Proj,
  matrix_WorldView,
  matrix_ViewProj,
  matrix_WorldViewProj,
  matrix_InvView,
  matrix_InvProj,
  matrix_InvViewProj,

  // Camera Position and Vectors
  camera_Pos,
  camera_Look,
  camera_Up,
  camera_Right,

  // Global Ambient
  global_Ambient,

  // Material Properties
  material_Diffuse,
  material_Ambient,
  material_Specular,
  material_Emissive,
  material_Power,

  // Fog Properties
  fog_Color,
  fog_Start,
  fog_End,
  fog_Density,
  fog_Enabled,

  // Textures
  tex_Diffuse,
  tex_Alpha,
  tex_Normal,
  tex_0,
  tex_1,

  // Directional Light 0
  light0_Enabled,
  light0_Direction,
  light0_Diffuse,
  light0_Ambient,
  light0_Specular,
  light0_Power,

  /*
  // Directional Light 1
  light1_Enabled,
  light1_Direction,
  light1_Diffuse,
  light1_Ambient,
  light1_Specular,
  light1_Power,
  */

  // Omni Light 0
  omni0_Enabled,
  omni0_Position,
  omni0_Diffuse,
  omni0_Ambient,
  omni0_Specular,
  omni0_Power,
  omni0_Range,
  omni0_Atten0,
  omni0_Atten1,
  omni0_Atten2,

  // Omni Light 1
  omni1_Enabled,
  omni1_Position,
  omni1_Diffuse,
  omni1_Ambient,
  omni1_Specular,
  omni1_Power,
  omni1_Range,
  omni1_Atten0,
  omni1_Atten1,
  omni1_Atten2,

  // Omni Light 2
  omni2_Enabled,
  omni2_Position,
  omni2_Diffuse,
  omni2_Ambient,
  omni2_Specular,
  omni2_Power,
  omni2_Range,
  omni2_Atten0,
  omni2_Atten1,
  omni2_Atten2,

  // Omni Light 3
  omni3_Enabled,
  omni3_Position,
  omni3_Diffuse,
  omni3_Ambient,
  omni3_Specular,
  omni3_Power,
  omni3_Range,
  omni3_Atten0,
  omni3_Atten1,
  omni3_Atten2
}; // enum MaterialParameters


// ----------------------------------------------------------------------------
// Name: Material  (class)
// Desc: Class to manage a effect
// ----------------------------------------------------------------------------
class Material : public RefCounted
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Material();
  virtual ~Material();

  // --------------------------------------------------------------------------
  // Get the file handle
  // --------------------------------------------------------------------------
  FileHandle GetFileHandle() { return m_handle; }

  // --------------------------------------------------------------------------
  // Load the effect
  // --------------------------------------------------------------------------
  bool Load(FileHandle handle);

  // --------------------------------------------------------------------------
  // Get the d3d effect
  // --------------------------------------------------------------------------
  operator LPD3DXEFFECT()             { return m_effect; }
  operator const LPD3DXEFFECT() const { return m_effect; }

  // --------------------------------------------------------------------------
  // Use the effect
  // --------------------------------------------------------------------------
  inline uint Begin(ulong flags = 0) const;
  inline void BeginPass(uint pass = 0) const;
  inline void EndPass() const;
  inline void End() const;

  // --------------------------------------------------------------------------
  // Set all constants for the effect ebfore beginning the render
  // --------------------------------------------------------------------------
  void Prepare(const Matrix &world_matrix, const D3DMATERIAL9 &material, 
    const TextureArray &textures) const;

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  LPD3DXEFFECT            m_effect;
  Map<ulong, D3DXHANDLE>  m_params;
  FileHandle              m_handle;

  // --------------------------------------------------------------------------
  // Build the parameter map
  // --------------------------------------------------------------------------
  static void BuildParameterMap();

  // --------------------------------------------------------------------------
  // Private static members
  // --------------------------------------------------------------------------
  static Map<ulong, String>   s_parameter_map;    // All supported parameters
  
}; // Material


// ----------------------------------------------------------------------------
// Name: BaseEffectFunctor (struct)
// Desc: Base class effect functor allowing a effect to be loaded
// ----------------------------------------------------------------------------
struct BaseEffectFunctor
{
  virtual Material *operator()(FileHandle handle) const = 0;
}; // class BaseEffectFunctor


// ----------------------------------------------------------------------------
// Name: EffectFunctorTemplate  (struct)
// Desc: Templated scene effect functor that can create sceen effects of
//       a derived type (that is specified by the template argument).
// ----------------------------------------------------------------------------
template <class T>
struct EffectFunctorTemplate : public BaseEffectFunctor
{
  // --------------------------------------------------------------------------
  // Name: operator
  // Desc: Create a effect and load it from a file
  // Retn: Effect * - the created effect, or null if hte effect failed to 
  //       load
  // --------------------------------------------------------------------------
  virtual Material *operator()(FileHandle handle) const 
  { 
    T *peffect = new T();
    if (!peffect->Load(handle))
      SafeDelete(peffect);

    return peffect;
  } // operator()

}; // struct EffectFunctorTemplate


// ----------------------------------------------------------------------------
// Typedef of a effect functor to create Material instances
// ----------------------------------------------------------------------------
typedef EffectFunctorTemplate<Material> MaterialFunctor;


// ----------------------------------------------------------------------------
// Name: MaterialLoader (class)
// Desc: Class to load effects
// ----------------------------------------------------------------------------
class MaterialLoader
{
public:
  // --------------------------------------------------------------------------
  // Load the effect from disk
  // --------------------------------------------------------------------------
  static Material *LoadEffect(FileHandle handle);
  static Material *LoadEffect(FileHandle handle, const BaseEffectFunctor &type);
  
  // --------------------------------------------------------------------------
  // Release any effects with no external references
  // --------------------------------------------------------------------------
  static void GarbageCollect();

private:
  // --------------------------------------------------------------------------
  // Private static members
  // --------------------------------------------------------------------------
  static Map<String, Material *> s_effect_map;
  
}; // class MaterialLoader


// ----------------------------------------------------------------------------
// Name: Material::Begin
// Desc: Begin the effect
// Parm: ulong flags - the flags
// Retn: uint        - the number of passes
// ----------------------------------------------------------------------------
inline uint Material::Begin(ulong flags) const
{
  uint numPasses = 0;
  D3DCheck(m_effect->Begin(&numPasses, flags));
  return numPasses;
} // Begin


// ----------------------------------------------------------------------------
// Name: Material::BeginPass
// Desc: Begin a pass
// Parm: uint pass - the pass
// ----------------------------------------------------------------------------
inline void Material::BeginPass(uint pass) const
{
  D3DCheck(m_effect->BeginPass(pass));
} // BeginPass


// ----------------------------------------------------------------------------
// Name: Material::EndPass
// Desc: End a pass
// ----------------------------------------------------------------------------
inline void Material::EndPass() const
{
  D3DCheck(m_effect->EndPass());
} // EndPass


// ----------------------------------------------------------------------------
// Name: Material::End
// Desc: End the effect
// ----------------------------------------------------------------------------
inline void Material::End() const
{
  D3DCheck(m_effect->End());
} // End


#endif // __MATERIAL_H_


// -- EOF


