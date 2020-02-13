// ----------------------------------------------------------------------------
// File: Material.cpp
// Desc: Effect file support
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Render/Material.h"
#include "Engine/ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Static initialisation
// ----------------------------------------------------------------------------
Map<String, Material *> MaterialLoader::s_effect_map;
Map<ulong, String>         Material::s_parameter_map;


// ----------------------------------------------------------------------------
// Name: Material::Material
// Desc: Constructor
// ----------------------------------------------------------------------------
Material::Material()
: m_effect   (NULL)
{
  REF_COUNT_CTOR(Material);

  // Install the garbage collector task at exit
  static bool gcInstalled = false;
  if (!gcInstalled)
  {
    atexit(&MaterialLoader::GarbageCollect);
    gcInstalled = true;
  } // if
} // Material


// ----------------------------------------------------------------------------
// Name: Material::~Material
// Desc: Destructor
// ----------------------------------------------------------------------------
Material::~Material()
{
  REF_COUNT_DTOR(Material);

  SafeRelease(m_effect);
} // ~Material


// ----------------------------------------------------------------------------
// Name: Material::Load
// Desc: Load the effect
// Parm: FileHandle handle - the file handle
// Retn: bool              - true if loaded
// ----------------------------------------------------------------------------
bool Material::Load(FileHandle handle)
{
#ifdef _DEBUG
  ulong flags = D3DXSHADER_DEBUG;
#else
  ulong flags = 0;
#endif

  m_handle = handle;

  LPD3DXBUFFER errors;
  if (FAILED(D3DXCreateEffectFromFile(ApplicationCentral.GetDevice(), handle.GetAbsoluteFilename().c_str(),
    NULL, NULL, flags, NULL, &m_effect, &errors)))
  {
    LOG_ERROR << "Failed to create the effect: " << handle.GetAbsoluteFilename() << ENDLOG;
    if (errors)
    {
      LOG_ERROR << (const char *) errors->GetBufferPointer() << ENDLOG;
      SafeRelease(errors);
    } // if

    return false;
  } // if

  // Make sure the parameter map is built
  if (s_parameter_map.empty())
    BuildParameterMap();

  // Determine which parameters we need to send
  Map<ulong, String>::iterator iter(s_parameter_map.begin()), end(s_parameter_map.end());
  for (; iter != end; ++iter)
  {
    D3DXHANDLE handle = m_effect->GetParameterByName(NULL, iter->second.c_str());
    if (!handle)
      continue;

    // Store the parameter
    m_params[iter->first] = handle;
  } // for

  return true;
} // Load


// ----------------------------------------------------------------------------
// Name: Material::Prepare
// Desc: Prepare the effect parameters
// Parm: const Matrix            &world_matrix - the world matrix
// Parm: const D3DMATERIAL9      &material     - the material
// Parm: const TextureArray &textures     - the texture array
// ----------------------------------------------------------------------------
void Material::Prepare(const Matrix           &world_matrix, 
                          const D3DMATERIAL9  &material, 
                          const TextureArray  &textures) const
{
  Application &ac = ApplicationCentral;
  const Camera &camera = ac.GetCamera();

  Map<ulong, D3DXHANDLE>::const_iterator iter(m_params.begin()), end(m_params.end());
  for (; iter != end; ++iter)
  {
    const D3DXHANDLE &h = iter->second;

    const LPDIRECT3DTEXTURE9 pDiffuseTex = ((textures.GetDiffuse()) ? (textures.GetDiffuse()->GetPtr()) : NULL);
    const LPDIRECT3DTEXTURE9 pAlphaTex   = ((textures.GetAlpha())   ? (textures.GetAlpha()->GetPtr())   : NULL);
    const LPDIRECT3DTEXTURE9 pNormalTex  = ((textures.GetNormal())  ? (textures.GetNormal()->GetPtr())  : NULL);
    const LPDIRECT3DTEXTURE9 pTex0       = ((textures.GetTex0())    ? (textures.GetTex0()->GetPtr())    : NULL);
    const LPDIRECT3DTEXTURE9 pTex1       = ((textures.GetTex1())    ? (textures.GetTex1()->GetPtr())    : NULL);

    switch (iter->first)
    {
      // ----------------------------------------------------------------------
      // World / View / Projection Matrices
      // ----------------------------------------------------------------------
      case matrix_World:          { m_effect->SetMatrix(h, &world_matrix);                 break;  }
      case matrix_View:           { m_effect->SetMatrix(h, &(camera.GetView()));           break;  }
      case matrix_Proj:           { m_effect->SetMatrix(h, &(camera.GetProj()));           break;  }
      case matrix_WorldView:      { Matrix world_view;
                                    D3DXMatrixMultiply(&world_view, &world_matrix, &(camera.GetView()));
                                    m_effect->SetMatrix(h, &world_view);                   break;  }
      case matrix_ViewProj:       { m_effect->SetMatrix(h, &(camera.GetViewProj()));       break;  }
      case matrix_WorldViewProj:  { Matrix world_view_proj;
                                    D3DXMatrixMultiply(&world_view_proj, &world_matrix, &(camera.GetViewProj()));
                                    m_effect->SetMatrix(h, &world_view_proj);              break;  }
      case matrix_InvView:        { m_effect->SetMatrix(h, &(camera.GetInvView()));        break;  }
      case matrix_InvProj:        { m_effect->SetMatrix(h, &(camera.GetInvProj()));        break;  }
      case matrix_InvViewProj:    { m_effect->SetMatrix(h, &(camera.GetInvViewProj()));    break;  }

      // ----------------------------------------------------------------------
      // Camera Vectors and Position
      // ----------------------------------------------------------------------

      case camera_Pos:    { m_effect->SetVector(h, &(Vec4(camera.GetPosition(), 1.0f)));   break;  }
      case camera_Look:   { m_effect->SetVector(h, &(Vec4(camera.GetLook(), 1.0f)));       break;  }
      case camera_Up:     { m_effect->SetVector(h, &(Vec4(camera.GetUp(), 1.0f)));         break;  }
      case camera_Right:  { m_effect->SetVector(h, &(Vec4(camera.GetRight(), 1.0f)));      break;  }

      // ----------------------------------------------------------------------
      // Material properties
      // ----------------------------------------------------------------------
      case material_Diffuse:  { m_effect->SetVector(h, (Vec4*) &(material.Diffuse));       break;  }
      case material_Ambient:  { m_effect->SetVector(h, (Vec4*) &(material.Ambient));       break;  }
      case material_Specular: { m_effect->SetVector(h, (Vec4*) &(material.Specular));      break;  }
      case material_Emissive: { m_effect->SetVector(h, (Vec4*) &(material.Emissive));      break;  }
      case material_Power:    { m_effect->SetFloat(h, material.Power);                     break;  }

      // ----------------------------------------------------------------------
      // Textures
      // ----------------------------------------------------------------------
      case tex_Diffuse:       { m_effect->SetTexture(h, pDiffuseTex);                      break;  }
      case tex_Alpha:         { m_effect->SetTexture(h, pAlphaTex);                        break;  }
      case tex_Normal:        { m_effect->SetTexture(h, pNormalTex);                       break;  }
      case tex_0:             { m_effect->SetTexture(h, pTex0);                            break;  }
      case tex_1:             { m_effect->SetTexture(h, pTex1);                            break;  }

      // ----------------------------------------------------------------------
      // Global lighting
      // ----------------------------------------------------------------------
      case global_Ambient:    { m_effect->SetVector(h, (Vec4*) &ac.GetGlobalAmbient());    break;  }

      // ----------------------------------------------------------------------
      // Directional Light 0
      // ----------------------------------------------------------------------
      case light0_Enabled:    { m_effect->SetBool(h, ac.GetDirectionalLight().enabled);                    break;  }
      case light0_Direction:  { m_effect->SetVector(h, &(Vec4(-ac.GetDirectionalLight().direction, 1)));   break;  }
      case light0_Diffuse:    { m_effect->SetVector(h, (Vec4*) &ac.GetDirectionalLight().diffuse);         break;  }
      case light0_Ambient:    { m_effect->SetVector(h, (Vec4*) &ac.GetDirectionalLight().ambient);         break;  }
      case light0_Specular:   { m_effect->SetVector(h, (Vec4*) &ac.GetDirectionalLight().specular);        break;  }
      case light0_Power:      { m_effect->SetVector(h, (Vec4*) &ac.GetDirectionalLight().power);           break;  }

      // ----------------------------------------------------------------------
      // Fog
      // ----------------------------------------------------------------------
      case fog_Enabled:       { m_effect->SetBool(h, ac.GetFog().enabled);            break;  }
      case fog_Color:         { m_effect->SetVector(h, (Vec4*) &ac.GetFog().color);   break;  }
      case fog_Start:         { m_effect->SetFloat(h, ac.GetFog().start);             break;  }
      case fog_End:           { m_effect->SetFloat(h, ac.GetFog().end);               break;  }
      case fog_Density:       { m_effect->SetFloat(h, ac.GetFog().density);           break;  }

      // ----------------------------------------------------------------------
      // Omni Light 0
      // ----------------------------------------------------------------------
      case omni0_Enabled:     { m_effect->SetBool(h, ac.GetOmniLight0().enabled);                   break;  }
      case omni0_Position:    { m_effect->SetVector(h, &(Vec4(ac.GetOmniLight0().position, 1)));    break;  }
      case omni0_Diffuse:     { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight0().diffuse);        break;  }
      case omni0_Ambient:     { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight0().ambient);        break;  }
      case omni0_Specular:    { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight0().specular);       break;  }
      case omni0_Power:       { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight0().power);          break;  }
      case omni0_Range:       { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight0().range);          break;  }
      case omni0_Atten0:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight0().atten0);         break;  }
      case omni0_Atten1:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight0().atten1);         break;  }
      case omni0_Atten2:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight0().atten2);         break;  }

      // ----------------------------------------------------------------------
      // Omni Light 1
      // ----------------------------------------------------------------------
      case omni1_Enabled:     { m_effect->SetBool(h, ac.GetOmniLight1().enabled);                   break;  }
      case omni1_Position:    { m_effect->SetVector(h, &(Vec4(ac.GetOmniLight1().position, 1)));    break;  }
      case omni1_Diffuse:     { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight1().diffuse);        break;  }
      case omni1_Ambient:     { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight1().ambient);        break;  }
      case omni1_Specular:    { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight1().specular);       break;  }
      case omni1_Power:       { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight1().power);          break;  }
      case omni1_Range:       { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight1().range);          break;  }
      case omni1_Atten0:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight1().atten0);         break;  }
      case omni1_Atten1:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight1().atten1);         break;  }
      case omni1_Atten2:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight1().atten2);         break;  }

      // ----------------------------------------------------------------------
      // Omni Light 2
      // ----------------------------------------------------------------------
      case omni2_Enabled:     { m_effect->SetBool(h, ac.GetOmniLight2().enabled);                   break;  }
      case omni2_Position:    { m_effect->SetVector(h, &(Vec4(ac.GetOmniLight2().position, 1)));    break;  }
      case omni2_Diffuse:     { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight2().diffuse);        break;  }
      case omni2_Ambient:     { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight2().ambient);        break;  }
      case omni2_Specular:    { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight2().specular);       break;  }
      case omni2_Power:       { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight2().power);          break;  }
      case omni2_Range:       { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight2().range);          break;  }
      case omni2_Atten0:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight2().atten0);         break;  }
      case omni2_Atten1:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight2().atten1);         break;  }
      case omni2_Atten2:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight2().atten2);         break;  }

      // ----------------------------------------------------------------------
      // Omni Light 3
      // ----------------------------------------------------------------------
      case omni3_Enabled:     { m_effect->SetBool(h, ac.GetOmniLight3().enabled);                   break;  }
      case omni3_Position:    { m_effect->SetVector(h, &(Vec4(ac.GetOmniLight3().position, 1)));    break;  }
      case omni3_Diffuse:     { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight3().diffuse);        break;  }
      case omni3_Ambient:     { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight3().ambient);        break;  }
      case omni3_Specular:    { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight3().specular);       break;  }
      case omni3_Power:       { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight3().power);          break;  }
      case omni3_Range:       { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight3().range);          break;  }
      case omni3_Atten0:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight3().atten0);         break;  }
      case omni3_Atten1:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight3().atten1);         break;  }
      case omni3_Atten2:      { m_effect->SetVector(h, (Vec4*) &ac.GetOmniLight3().atten2);         break;  }
    };
  } // for
} // Prepare


// ----------------------------------------------------------------------------
// Name: MaterialLoader::LoadEffect
// Desc: Load a effect or retrieve it from the cache
// Parm: FileHandle handle - the file handle
// Retn: Material *        - the effect
// ----------------------------------------------------------------------------
Material *MaterialLoader::LoadEffect(FileHandle handle)
{
  return LoadEffect(handle, MaterialFunctor());
} // LoadEffect


// ----------------------------------------------------------------------------
// Name: MaterialLoader::LoadEffect
// Desc: Load a effect or get it from the cache
// Parm: FileHandle handle - the file handle
// Parm: const BaseEffectFunctor &type  - the creation functor
// Retn: Material *                  - the effect
// ----------------------------------------------------------------------------
Material *MaterialLoader::LoadEffect(FileHandle handle, const BaseEffectFunctor &type)
{
  Map<String, Material *>::iterator iter = s_effect_map.find(handle.GetAbsoluteFilename());
  if (iter != s_effect_map.end())
    return iter->second;

  Material *peffect = type(handle);
  if (!peffect)
    return NULL;

  s_effect_map.insert(MakePair(handle.GetAbsoluteFilename(), peffect));
  SafeRef(peffect);

  return peffect;
} // LoadEffect


// ----------------------------------------------------------------------------
// Name: Material::BuildParameterMap
// Desc: Build the parameter map
// ----------------------------------------------------------------------------
void Material::BuildParameterMap()
{
  s_parameter_map[matrix_World] = "matrix_World";
  s_parameter_map[matrix_View] = "matrix_View";
  s_parameter_map[matrix_Proj] = "matrix_Proj";
  s_parameter_map[matrix_WorldView] = "matrix_WorldView";
  s_parameter_map[matrix_ViewProj] = "matrix_ViewProj";
  s_parameter_map[matrix_WorldViewProj] = "matrix_WorldViewProj";
  s_parameter_map[matrix_InvView] = "matrix_InvView";
  s_parameter_map[matrix_InvProj] = "matrix_InvProj";
  s_parameter_map[matrix_InvViewProj] = "matrix_InvViewProj";
  s_parameter_map[camera_Pos] = "camera_Pos";
  s_parameter_map[camera_Look] = "camera_Look";
  s_parameter_map[camera_Up] = "camera_Up";
  s_parameter_map[camera_Right] = "camera_Right";
  s_parameter_map[global_Ambient] = "global_Ambient";
  s_parameter_map[material_Diffuse] = "material_Diffuse";
  s_parameter_map[material_Ambient] = "material_Ambient";
  s_parameter_map[material_Specular] = "material_Specular";
  s_parameter_map[material_Power] = "material_Power";
  s_parameter_map[fog_Color] = "fog_Color";
  s_parameter_map[fog_Start] = "fog_Start";
  s_parameter_map[fog_End] = "fog_End";
  s_parameter_map[fog_Density] = "fog_Density";
  s_parameter_map[fog_Enabled] = "fog_Enabled";
  s_parameter_map[tex_Diffuse] = "tex_Diffuse";
  s_parameter_map[tex_Alpha] = "tex_Alpha";
  s_parameter_map[tex_0] = "tex_0";
  s_parameter_map[tex_1] = "tex_1";
  s_parameter_map[tex_Normal] = "tex_Normal";
  s_parameter_map[light0_Enabled] = "light0_Enabled";
  s_parameter_map[light0_Direction] = "light0_Direction";
  s_parameter_map[light0_Diffuse] = "light0_Diffuse";
  s_parameter_map[light0_Ambient] = "light0_Ambient";
  s_parameter_map[light0_Specular] = "light0_Specular";
  s_parameter_map[light0_Power] = "light0_Power";
  s_parameter_map[omni0_Enabled] = "omni0_Enabled";
  s_parameter_map[omni0_Position] = "omni0_Position";
  s_parameter_map[omni0_Diffuse] = "omni0_Diffuse";
  s_parameter_map[omni0_Ambient] = "omni0_Ambient";
  s_parameter_map[omni0_Specular] = "omni0_Specular";
  s_parameter_map[omni0_Power] = "omni0_Power";
  s_parameter_map[omni0_Range] = "omni0_Range";
  s_parameter_map[omni0_Atten0] = "omni0_Atten0";
  s_parameter_map[omni0_Atten1] = "omni0_Atten1";
  s_parameter_map[omni0_Atten2] = "omni0_Atten2";
  s_parameter_map[omni1_Enabled] = "omni1_Enabled";
  s_parameter_map[omni1_Position] = "omni1_Position";
  s_parameter_map[omni1_Diffuse] = "omni1_Diffuse";
  s_parameter_map[omni1_Ambient] = "omni1_Ambient";
  s_parameter_map[omni1_Specular] = "omni1_Specular";
  s_parameter_map[omni1_Power] = "omni1_Power";
  s_parameter_map[omni1_Range] = "omni1_Range";
  s_parameter_map[omni1_Atten0] = "omni1_Atten0";
  s_parameter_map[omni1_Atten1] = "omni1_Atten1";
  s_parameter_map[omni1_Atten2] = "omni1_Atten2";
  s_parameter_map[omni2_Enabled] = "omni2_Enabled";
  s_parameter_map[omni2_Position] = "omni2_Position";
  s_parameter_map[omni2_Diffuse] = "omni2_Diffuse";
  s_parameter_map[omni2_Ambient] = "omni2_Ambient";
  s_parameter_map[omni2_Specular] = "omni2_Specular";
  s_parameter_map[omni2_Power] = "omni2_Power";
  s_parameter_map[omni2_Range] = "omni2_Range";
  s_parameter_map[omni2_Atten0] = "omni2_Atten0";
  s_parameter_map[omni2_Atten1] = "omni2_Atten1";
  s_parameter_map[omni2_Atten2] = "omni2_Atten2";
  s_parameter_map[omni3_Enabled] = "omni3_Enabled";
  s_parameter_map[omni3_Position] = "omni3_Position";
  s_parameter_map[omni3_Diffuse] = "omni3_Diffuse";
  s_parameter_map[omni3_Ambient] = "omni3_Ambient";
  s_parameter_map[omni3_Specular] = "omni3_Specular";
  s_parameter_map[omni3_Power] = "omni3_Power";
  s_parameter_map[omni3_Range] = "omni3_Range";
  s_parameter_map[omni3_Atten0] = "omni3_Atten0";
  s_parameter_map[omni3_Atten1] = "omni3_Atten1";
  s_parameter_map[omni3_Atten2] = "omni3_Atten2";
} // BuildParameterMap


// ----------------------------------------------------------------------------
// Name: MaterialLoader::GarbageCollect
// Desc: Release any effects with no external references
// ----------------------------------------------------------------------------
void MaterialLoader::GarbageCollect()
{
  Map<String, Material *>::iterator iter(s_effect_map.begin()), end(s_effect_map.end());
  while (iter != end)
  {
    Material *peffect = iter->second;
    if (peffect->GetRefCount() == 1)
    {
      iter = s_effect_map.erase(iter);
      SafeUnRef(peffect);
    } // if
    else
    {
      ++iter;
    } // else
  } // if
} // GarbageCollect


// -- EOF


