// ----------------------------------------------------------------------------
// File: Types.h
// Desc: General type definitions
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef __TYPES_H
#define __TYPES_H


// ----------------------------------------------------------------------------
// Build for MFC Compatability
// ----------------------------------------------------------------------------
#define __MFC_ENABLED


// ----------------------------------------------------------------------------
// The windows version
// ----------------------------------------------------------------------------
#ifdef  __MFC_ENABLED
#define WINVER 0x0501
#endif // __MFC_ENABLED


// ----------------------------------------------------------------------------
// We dont need all of windows whistles, bells, and overheads
// ----------------------------------------------------------------------------
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN


// ----------------------------------------------------------------------------
// We want to keep to the ISO standard
// ----------------------------------------------------------------------------
#ifndef STRICT
#define STRICT
#endif // STRICT


// ----------------------------------------------------------------------------
// Set the version and the CRT security
// ----------------------------------------------------------------------------
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif // _WIN32_WINNT


// ----------------------------------------------------------------------------
// Set the direct input version
// ----------------------------------------------------------------------------
#define DIRECTINPUT_VERSION  0x0800


// ----------------------------------------------------------------------------
// Inlcude the windows headers
// ----------------------------------------------------------------------------
#ifdef  __MFC_ENABLED

#define _AFX_ALL_WARNINGS

#include <afxwin.h>   // MFC core and standard components
#include <afxext.h>   // MFC extensions
#include <afxdisp.h>  // MFC Automation classes
#include <afxdtctl.h> // MFC support for Internet Explorer 4 Common Controls

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>		// MFC support for Windows Common Controls
#endif

#else  // !__MFC_ENABLED

#include <windows.h>

#endif // !__MFC_ENABLED


// ----------------------------------------------------------------------------
// Standard includes for directx and common useage
// ----------------------------------------------------------------------------
#include <mmsystem.h>
#include <process.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <d3d9types.h>
#include <D3dx9mesh.h>
#include <dinput.h>
#include <tchar.h>
#include <stdio.h>
#include <fcntl.h>
#include <new>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <conio.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <exception>
#include <algorithm>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string.h>
#include <wtypes.h>
#include <complex>
#include <queue>
#include <time.h>


// ----------------------------------------------------------------------------
// Import the libs
// ----------------------------------------------------------------------------
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------
const float HALF_PI = D3DX_PI / 2;
const float EPSILON = 0.001f;
const float FLOAT_MAX =  3.402823466e+38F;
const float FLOAT_MIN = -3.402823466e+38F;


// ----------------------------------------------------------------------------
// Unsigned type definitions
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
// STL typefeds
// ----------------------------------------------------------------------------
#define Array         std::vector
#define Map           std::map
#define SortedSet     std::set
#define MultiMap      std::multimap
#define List          std::list
#define InputStream   std::istream
#define OutputStream  std::ostream
#define MakePair      std::make_pair
#define Rect          RECT
#define StringArray   Array<String>
#define Max           std::max
#define Min           std::min


// ----------------------------------------------------------------------------
// String typedefs
// ----------------------------------------------------------------------------
typedef std::string       String;
typedef std::stringstream StringStream;


// ----------------------------------------------------------------------------
// Name: OffsetPtr (class)
// Desc: A smart pointer class that reads values that are segmented by a stride
//     through a block of data.
// ----------------------------------------------------------------------------
template <class T>
class OffsetPtr
{
public:
  // ------------------------------------------------------------------------
  // Constructors
  // ------------------------------------------------------------------------
  OffsetPtr() : m_pdata(0), m_stride(0) {}
  OffsetPtr(ubyte stride, ubyte offset, void *pdata) : m_pdata((ubyte *)pdata + offset), m_stride(stride) {}

  // ------------------------------------------------------------------------
  // Pointer operators to manipulate and read the m_pdata pointer using the
  // stride of the data.
  // ------------------------------------------------------------------------
     operator T ()          { return *((T*)(m_pdata)); }
  T &operator * ()          { return *((T*)(m_pdata)); }
  T *operator ->()          { return  ((T*)(m_pdata)); }
  T &operator [](uint idx)  { return *((T*)(m_pdata + (idx * m_stride)));   }
  const T &operator [](uint idx) const { return *((T*)(m_pdata + (idx * m_stride)));   }
  T &operator ++()          { m_pdata += m_stride; return *((T*)(m_pdata)); }
  T &operator --()          { m_pdata -= m_stride; return *((T*)(m_pdata)); }
     operator bool()        { return (m_pdata != 0); }

private:
  // ------------------------------------------------------------------------
  // Private members
  // ------------------------------------------------------------------------
  uchar   *m_pdata;
  ubyte    m_stride;
}; // class OffsetPtr


#endif //__TYPES_H

// -- EOF

