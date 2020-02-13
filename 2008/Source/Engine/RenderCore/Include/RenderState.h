
#ifndef __RENDER_STATE_H_
#define __RENDER_STATE_H_


#include "libRenderCore.h"


#define FLOAT_TO_DWORD(x) (*((DWORD*)(&x)))
#define DWORD_TO_FLOAT(x) (*((float*)(&x)))


#define RenderState RenderStateManager::GetInstance()

#if XBOX
#define MAX_RENDERSTATE D3DRS_MAX
#else
#define MAX_RENDERSTATE 256
#define D3DCOLORWRITEENABLE_ALL D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_ALPHA
#endif


class RenderStateManager
{
public:
  static RenderStateManager &GetInstance();
  static void DestroyInstance();

public:
  RenderStateManager();

  bool ResetToDefault();

  bool Set(D3DRENDERSTATETYPE type, DWORD value);
  DWORD Get(D3DRENDERSTATETYPE type);
  bool SetDefault(D3DRENDERSTATETYPE type);
  bool GetDefault(D3DRENDERSTATETYPE type, DWORD &value);

private:
  static RenderStateManager *s_pInstance;

  DWORD   m_RenderStates[MAX_RENDERSTATE];



};


#endif // __RENDER_STATE_H_

// -- EOF

