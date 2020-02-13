
#ifndef __LIB_ENGINE_H_
#define __LIB_ENGINE_H_


#include "libStandard.h"
#include "libMaths.h"
#include "libRenderCore.h"
#include "libRenderExt.h"
#include "libRender2D.h"
#include "libCal3D.h"


#if PC
#ifdef _DEBUG

#ifdef TOOLS
#pragma comment (lib, "Standard-Tools_d.lib")
#pragma comment (lib, "Maths-Tools_d.lib")
#pragma comment (lib, "RenderCore-Tools_d.lib")
#pragma comment (lib, "RenderExt-Tools_d.lib")
#pragma comment (lib, "Render2D-Tools_d.lib")
#pragma comment (lib, "Cal3D-Tools_d.lib")
#else // !TOOLS
#pragma comment (lib, "Standard_d.lib")
#pragma comment (lib, "Maths_d.lib")
#pragma comment (lib, "RenderCore_d.lib")
#pragma comment (lib, "RenderExt_d.lib")
#pragma comment (lib, "Render2D_d.lib")
#pragma comment (lib, "Cal3D_d.lib")
#endif // !TOOLS

#else // !_DEBUG

#ifdef TOOLS
#pragma comment (lib, "Standard-Tools.lib")
#pragma comment (lib, "Maths-Tools.lib")
#pragma comment (lib, "RenderCore-Tools.lib")
#pragma comment (lib, "RenderExt-Tools.lib")
#pragma comment (lib, "Render2D-Tools.lib")
#pragma comment (lib, "Cal3D-Tools.lib")
#else // !TOOLS

#ifdef FINAL_RELEASE
#pragma comment (lib, "Standard-Final.lib")
#pragma comment (lib, "Maths-Final.lib")
#pragma comment (lib, "RenderCore-Final.lib")
#pragma comment (lib, "RenderExt-Final.lib")
#pragma comment (lib, "Render2D-Final.lib")
#pragma comment (lib, "Cal3D-Final.lib")
#else // !FINAL_RELEASE
#pragma comment (lib, "Standard.lib")
#pragma comment (lib, "Maths.lib")
#pragma comment (lib, "RenderCore.lib")
#pragma comment (lib, "RenderExt.lib")
#pragma comment (lib, "Render2D.lib")
#pragma comment (lib, "Cal3D.lib")
#endif // !FINAL_RELEASE

#endif // !TOOLS

#endif // !_DEBUG


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "comctl32.lib")
#pragma comment (lib, "rpcrt4.lib")
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "odbc32.lib")
#else // !_DEBUG
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "comctl32.lib")
#pragma comment (lib, "rpcrt4.lib")
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "odbc32.lib")
#endif // !_DEBUG

#endif // PC


#endif // __LIB_ENGINE_H_

// -- EOF

