
#include "RenderState.h"


RenderStateManager *RenderStateManager::s_pInstance = NULL;


RenderStateManager &RenderStateManager::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new RenderStateManager();
    atexit(RenderStateManager::DestroyInstance);
  }
  return *s_pInstance;
}


void RenderStateManager::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
}


RenderStateManager::RenderStateManager()
{
}


bool RenderStateManager::Set(D3DRENDERSTATETYPE type, DWORD value)
{
  ASSERT(type < MAX_RENDERSTATE, "Render state index is greater than MAX_RENDERSTATE");
  NULL_ASSERT(Device);

  if (m_RenderStates[type] != value)
  {
    m_RenderStates[type] = value;
    Device->SetRenderState(type, value);
  }
  return true;
}


DWORD RenderStateManager::Get(D3DRENDERSTATETYPE type)
{
  ASSERT(type < MAX_RENDERSTATE, "Render state index is greater than MAX_RENDERSTATE");
  return m_RenderStates[type];
}


bool RenderStateManager::SetDefault(D3DRENDERSTATETYPE type)
{
  DWORD value;
  if (GetDefault(type, value))
  {
    Set(type, value);
    return true;
  }

  return false;
}


bool RenderStateManager::GetDefault(D3DRENDERSTATETYPE type, DWORD &value)
{
  ASSERT(type < MAX_RENDERSTATE, "Render state index is greater than MAX_RENDERSTATE");

  float float0 = 0.0f;
  float float1 = 1.0f;
  float float2 = 2.0f;
  DWORD dword0 = FLOAT_TO_DWORD(float0);
  DWORD dword1 = FLOAT_TO_DWORD(float1);
  DWORD dword2 = FLOAT_TO_DWORD(float2);

  switch (type)
  {
    case D3DRS_ZENABLE:                     value = D3DZB_TRUE;               return true;
    case D3DRS_FILLMODE:                    value = D3DFILL_SOLID;            return true;
    case D3DRS_SHADEMODE:                   value = D3DSHADE_GOURAUD;         return true;
    case D3DRS_ZWRITEENABLE:                value = TRUE;                     return true;
    case D3DRS_ALPHATESTENABLE:             value = FALSE;                    return true;
    case D3DRS_SRCBLEND:                    value = D3DBLEND_ONE;             return true;
    case D3DRS_DESTBLEND:                   value = D3DBLEND_ZERO;            return true;
    case D3DRS_CULLMODE:                    value = D3DCULL_CCW;              return true;
    case D3DRS_ZFUNC:                       value = D3DCMP_LESSEQUAL;         return true;
    case D3DRS_ALPHAREF:                    value = 0x0;                      return true;
    case D3DRS_ALPHAFUNC:                   value = D3DCMP_ALWAYS;            return true;
    case D3DRS_DITHERENABLE:                value = FALSE;                    return true;
    case D3DRS_ALPHABLENDENABLE:            value = FALSE;                    return true;
    case D3DRS_FOGENABLE:                   value = FALSE;                    return true;
    case D3DRS_SPECULARENABLE:              value = FALSE;                    return true;
    case D3DRS_FOGCOLOR:                    value = 0;                        return true;
    case D3DRS_FOGTABLEMODE:                value = D3DFOG_NONE;              return true;
    case D3DRS_FOGSTART:                    value = dword0;                   return true;
    case D3DRS_FOGEND:                      value = dword1;                   return true;
    case D3DRS_FOGDENSITY:                  value = dword0;                   return true;
    case D3DRS_RANGEFOGENABLE:              value = FALSE;                    return true;
    case D3DRS_STENCILENABLE:               value = FALSE;                    return true;
    case D3DRS_STENCILFAIL:                 value = D3DSTENCILOP_KEEP;        return true;
    case D3DRS_STENCILZFAIL:                value = D3DSTENCILOP_KEEP;        return true;
    case D3DRS_STENCILPASS:                 value = D3DSTENCILOP_KEEP;        return true;
    case D3DRS_STENCILFUNC:                 value = D3DCMP_ALWAYS;            return true;
    case D3DRS_STENCILREF:                  value = 0;                        return true;
    case D3DRS_STENCILMASK:                 value = 0xFFFFFFFF;               return true;
    case D3DRS_STENCILWRITEMASK:            value = 0xFFFFFFFF;               return true;
    case D3DRS_TEXTUREFACTOR:               value = 0xFFFFFFFF;               return true;
    case D3DRS_WRAP0:                       value = 0;                        return true;
    case D3DRS_WRAP1:                       value = 0;                        return true;
    case D3DRS_WRAP2:                       value = 0;                        return true;
    case D3DRS_WRAP3:                       value = 0;                        return true;
    case D3DRS_LIGHTING:                    value = TRUE;                     return true;
    case D3DRS_AMBIENT:                     value = 0;                        return true;
    case D3DRS_COLORVERTEX:                 value = TRUE;                     return true;
    case D3DRS_LOCALVIEWER:                 value = TRUE;                     return true;
    case D3DRS_NORMALIZENORMALS:            value = FALSE;                    return true;
    case D3DRS_DIFFUSEMATERIALSOURCE:       value = D3DMCS_COLOR1;            return true;
    case D3DRS_SPECULARMATERIALSOURCE:      value = D3DMCS_COLOR2;            return true;
    case D3DRS_AMBIENTMATERIALSOURCE:       value = D3DMCS_COLOR2;            return true;
    case D3DRS_EMISSIVEMATERIALSOURCE:      value = D3DMCS_MATERIAL;          return true;
    case D3DRS_VERTEXBLEND:                 value = D3DVBF_DISABLE;           return true;
    case D3DRS_POINTSIZE:                   value = dword1;                   return true;
    case D3DRS_POINTSIZE_MIN:               value = dword1;                   return true;
    case D3DRS_POINTSPRITEENABLE:           value = FALSE;                    return true;
    case D3DRS_POINTSCALEENABLE:            value = FALSE;                    return true;
    case D3DRS_POINTSCALE_A:                value = dword1;                   return true;
    case D3DRS_POINTSCALE_B:                value = dword0;                   return true;
    case D3DRS_POINTSCALE_C:                value = dword0;                   return true;
    case D3DRS_MULTISAMPLEANTIALIAS:        value = TRUE;                     return true;
    case D3DRS_MULTISAMPLEMASK:             value = 0xFFFFFFFF;               return true;
    case D3DRS_PATCHEDGESTYLE:              value = D3DPATCHEDGE_DISCRETE;    return true;
    case D3DRS_POINTSIZE_MAX:               value = dword2;                   return true;
    case D3DRS_COLORWRITEENABLE:            value = D3DCOLORWRITEENABLE_ALL;  return true;
    case D3DRS_BLENDOP:                     value = D3DBLENDOP_ADD;           return true;

#if XBOX

    // XBOX Extensions
    case D3DRS_BLENDCOLOR:                  value = 0;                        return true;
    case D3DRS_SWATHWIDTH:                  value = D3DSWATH_128;             return true;
    case D3DRS_POLYGONOFFSETZSLOPESCALE:    value = dword0;                   return true;
    case D3DRS_POLYGONOFFSETZOFFSET:        value = dword0;                   return true;
    case D3DRS_POINTOFFSETENABLE:           value = FALSE;                    return true;
    case D3DRS_WIREFRAMEOFFSETENABLE:       value = FALSE;                    return true;
    case D3DRS_SOLIDOFFSETENABLE:           value = FALSE;                    return true;
    case D3DRS_DEPTHCLIPCONTROL:            value = D3DDCC_CULLPRIMITIVE;     return true;
    case D3DRS_STIPPLEENABLE:               value = FALSE;                    return true;

#else

    // DirectX 9 (Pc)
    case D3DRS_LASTPIXEL:                   value = 0;                        return true;
    case D3DRS_CLIPPING:                    value = TRUE;                     return true;
    case D3DRS_FOGVERTEXMODE:               value = D3DFOG_NONE;              return true;
    case D3DRS_CLIPPLANEENABLE:             value = 0;                        return true;
    case D3DRS_DEBUGMONITORTOKEN:           value = 0;                        return true;
    case D3DRS_INDEXEDVERTEXBLENDENABLE:    value = FALSE;                    return true;
    case D3DRS_TWEENFACTOR:                 value = dword0;                   return true;
    case D3DRS_POSITIONDEGREE:              value = D3DDEGREE_CUBIC;          return true;
    case D3DRS_NORMALDEGREE:                value = D3DDEGREE_LINEAR;         return true;
    case D3DRS_SCISSORTESTENABLE:           value = FALSE;                    return true;
    case D3DRS_SLOPESCALEDEPTHBIAS:         value = 0;                        return true;
    case D3DRS_ANTIALIASEDLINEENABLE:       value = FALSE;                    return true;
    case D3DRS_MINTESSELLATIONLEVEL:        value = dword1;                   return true;
    case D3DRS_MAXTESSELLATIONLEVEL:        value = dword1;                   return true;
    case D3DRS_ADAPTIVETESS_X:              value = dword0;                   return true;
    case D3DRS_ADAPTIVETESS_Y:              value = dword0;                   return true;
    case D3DRS_ADAPTIVETESS_Z:              value = dword1;                   return true;
    case D3DRS_ADAPTIVETESS_W:              value = dword0;                   return true;
    case D3DRS_ENABLEADAPTIVETESSELLATION:  value = FALSE;                    return true;
    case D3DRS_TWOSIDEDSTENCILMODE:         value = FALSE;                    return true;
    case D3DRS_CCW_STENCILFAIL:             value = D3DSTENCILOP_KEEP;        return true;
    case D3DRS_CCW_STENCILZFAIL:            value = D3DSTENCILOP_KEEP;        return true;
    case D3DRS_CCW_STENCILPASS:             value = D3DSTENCILOP_KEEP;        return true;
    case D3DRS_CCW_STENCILFUNC:             value = D3DCMP_ALWAYS;            return true;
    case D3DRS_COLORWRITEENABLE1:           value = 0x0000000f;               return true;
    case D3DRS_COLORWRITEENABLE2:           value = 0x0000000f;               return true;
    case D3DRS_COLORWRITEENABLE3:           value = 0x0000000f;               return true;
    case D3DRS_BLENDFACTOR:                 value = 0xffffffff;               return true;
    case D3DRS_SRGBWRITEENABLE:             value = 0;                        return true;
    case D3DRS_DEPTHBIAS:                   value = 0;                        return true;
    case D3DRS_WRAP4:                       value = 0;                        return true;
    case D3DRS_WRAP5:                       value = 0;                        return true;
    case D3DRS_WRAP6:                       value = 0;                        return true;
    case D3DRS_WRAP7:                       value = 0;                        return true;
    case D3DRS_WRAP8:                       value = 0;                        return true;
    case D3DRS_WRAP9:                       value = 0;                        return true;
    case D3DRS_WRAP10:                      value = 0;                        return true;
    case D3DRS_WRAP11:                      value = 0;                        return true;
    case D3DRS_WRAP12:                      value = 0;                        return true;
    case D3DRS_WRAP13:                      value = 0;                        return true;
    case D3DRS_WRAP14:                      value = 0;                        return true;
    case D3DRS_WRAP15:                      value = 0;                        return true;
    case D3DRS_SEPARATEALPHABLENDENABLE:    value = FALSE;                    return true;
    case D3DRS_SRCBLENDALPHA:               value = D3DBLEND_ONE;             return true;
    case D3DRS_DESTBLENDALPHA:              value = D3DBLEND_ZERO;            return true;
    case D3DRS_BLENDOPALPHA:                value = D3DBLENDOP_ADD;           return true;

#endif
  }
  return false;
}


bool RenderStateManager::ResetToDefault()
{
  memset(m_RenderStates, 0, sizeof(DWORD) * MAX_RENDERSTATE);

  for (uint i = 0; i < MAX_RENDERSTATE; i++)
    SetDefault((D3DRENDERSTATETYPE) i);

  return true;
}


// -- EOF


