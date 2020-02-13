#ifndef __STD_TYPE_H_
#define __STD_TYPE_H_


// ----------------------------------------------------------------------------
// The platform defines
// ----------------------------------------------------------------------------
#define PLATFORM_PC     1
#define PLATFORM_XBOX   2

// ----------------------------------------------------------------------------
// Set the platform
// ----------------------------------------------------------------------------
#ifdef _XBOX
#define PC        0
#define XBOX      1
#define IS_PC     false
#define IS_XBOX   true
#define CONSOLE   1
#define PLATFORM  PLATFORM_XBOX
#else
#define PC        1
#define XBOX      0
#define IS_PC     true
#define IS_XBOX   false
#define CONSOLE   0
#define PLATFORM  PLATFORM_PC
#endif

// ----------------------------------------------------------------------------
// Dont run on windows 98 or below
// ----------------------------------------------------------------------------
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0400
#endif

// ----------------------------------------------------------------------------
// We need atleast windows XP to run
// ----------------------------------------------------------------------------
#ifndef WINVER 
#define WINVER 0x0501
#endif

// ----------------------------------------------------------------------------
// Use a minimal amount of windows includes
// ----------------------------------------------------------------------------
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// ----------------------------------------------------------------------------
// Adhere to teh c++ standard strictly
// ----------------------------------------------------------------------------
#ifndef STRICT
#define STRICT
#endif

// ----------------------------------------------------------------------------
// Use stats in all builds other than final release
// ----------------------------------------------------------------------------
#ifdef FINAL_RELEASE
#define STATS 0
#else
#define STATS 1
#endif

// ----------------------------------------------------------------------------
// We use direct input 8
// ----------------------------------------------------------------------------
#define DIRECTINPUT_VERSION 0x0800

// ----------------------------------------------------------------------------
// Windows includes
// ----------------------------------------------------------------------------
#if XBOX
#define DIRECT3D_VERSION 0x0800
#define D3DCOMPILE_PUREDEVICE 1
#include <xtl.h>
#else
#include <windows.h>
#endif

// ----------------------------------------------------------------------------
// Stl includes
// ----------------------------------------------------------------------------
#include <vector>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <istream>
#include <ostream>
#include <fstream>
#include <queue>

// ----------------------------------------------------------------------------
// DirectX includes
// ----------------------------------------------------------------------------
#if XBOX
#include <xgraphics.h>
#include <xfont.h>
#include <d3d8.h>
#include <d3d8types.h>
#include <d3dx8math.h>
#else
#include <d3d9.h>
#include <dinput.h>
#include <xinput.h>
#include <d3d9types.h>
#include <d3dx9math.h>
#endif

// ----------------------------------------------------------------------------
// Disable a few warnings
// ----------------------------------------------------------------------------
#if PC
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#endif

// ----------------------------------------------------------------------------
// Typedef the stl to simpler names
// ----------------------------------------------------------------------------
#define Array         std::vector
#define Map           std::map
#define SortedSet     std::set
#define MultiMap      std::multimap
#define List          std::list
#define Stack         std::stack
#define Queue         std::queue
#define InputStream   std::istream
#define OutputStream  std::ostream
#define FileStream    std::fstream
#define MakePair      std::make_pair
#define Max           std::max
#define Min           std::min

// ----------------------------------------------------------------------------
// Unsigned types
// ----------------------------------------------------------------------------
typedef unsigned char       ubyte;
typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned long       ulong;
typedef unsigned int        uint;
typedef unsigned int        uword;
typedef unsigned long       dword;
typedef unsigned long       udword;
typedef unsigned long long  uqword;


// ----------------------------------------------------------------------------
// A basic rect class
// ----------------------------------------------------------------------------
struct Rect
{
  Rect() : left(0), top(0), right(0), bottom(0) {}
  Rect(long l, long t, long r, long b) : left(l), top(t), right(r), bottom(b) {}
#if PC
  operator RECT() { return (RECT) (*this); }
#endif

  long left;
  long top;
  long right;
  long bottom;
};


// ----------------------------------------------------------------------------
// Add one array to another
// ----------------------------------------------------------------------------
template <typename T>
inline Array<T> &operator+=(Array<T> &copyTo, const Array<T> &copyFrom)
{
  for (uint i = 0; i < copyFrom.size(); i++)
    copyTo.push_back(copyFrom[i]);

  return copyTo;
}


// ----------------------------------------------------------------------------
// Clear a queue
// ----------------------------------------------------------------------------
template <typename T>
inline void ClearQueue(Queue<T> &q)
{
  while (!q.empty())
    q.pop();
}



#if XBOX

#define VIEWPORT            D3DVIEWPORT8
#define DEVICE              LPDIRECT3DDEVICE8
#define DIRECT3D            LPDIRECT3D8
#define DIRECT3DSURFACE     LPDIRECT3DSURFACE8
#define DIRECT3DTEXTURE     LPDIRECT3DTEXTURE8
#define D3DMATERIAL         D3DMATERIAL8
#define D3DLIGHT            D3DLIGHT8
#define VERTEXSHADER        DWORD
#define PIXELSHADER         DWORD
#define VERTEXDECLARATION   DWORD*
#define VERTEXBUFFER        LPDIRECT3DVERTEXBUFFER8
#define INDEXBUFFER         LPDIRECT3DINDEXBUFFER8
#define Direct3DCreate(x)   Direct3DCreate8(x)
#define SetFVF              SetVertexShader

#else

#define VIEWPORT            D3DVIEWPORT9
#define DEVICE              LPDIRECT3DDEVICE9
#define DIRECT3D            LPDIRECT3D9
#define DIRECT3DSURFACE     LPDIRECT3DSURFACE9
#define DIRECT3DTEXTURE     LPDIRECT3DTEXTURE9
#define D3DMATERIAL         D3DMATERIAL9
#define D3DLIGHT            D3DLIGHT9
#define VERTEXSHADER        LPDIRECT3DVERTEXSHADER9
#define PIXELSHADER         LPDIRECT3DPIXELSHADER9      
#define VERTEXDECLARATION   LPDIRECT3DVERTEXDECLARATION9
#define VERTEXBUFFER        LPDIRECT3DVERTEXBUFFER9
#define INDEXBUFFER         LPDIRECT3DINDEXBUFFER9
#define Direct3DCreate(x)   Direct3DCreate9(x)

#endif


#endif // __STD_TYPE_H_

// -- EOF

