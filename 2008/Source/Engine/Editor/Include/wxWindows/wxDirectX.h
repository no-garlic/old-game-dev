// ----------------------------------------------------------------------------
// File: wxDirectX.h
// Desc: Global handles to the WX components
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __WX_DIRECTX_H_
#define __WX_DIRECTX_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "wx/wx.h"
#include "wx/timer.h"
#include "wx/math.h"
#include "wx/module.h"


// ----------------------------------------------------------------------------
// Global constants
// ----------------------------------------------------------------------------
#define wxDirectXCanvasName _T("DirectXCanvas")
static const wxChar *wxDirectXCanvasClassName = wxT("wxDirectXCanvasClass");
static const wxChar *wxDirectXCanvasClassNameNoRedraw = wxT("wxDirectXCanvasClassNR");


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class wxDirectXContext;
class wxDirectXCanvas;
class wxDirectXModule;


// ----------------------------------------------------------------------------
// Define the create app function
// ----------------------------------------------------------------------------
wxAppConsole *wxCreateApp();


// ----------------------------------------------------------------------------
// Get the wx app
// ----------------------------------------------------------------------------
inline wxApp& wxGetApp()
{
  return *(wxApp *) wxTheApp;
}


// ----------------------------------------------------------------------------
// Wx Libs to link with
// ----------------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment (lib, "wxmsw26d_propgrid.lib")
#pragma comment (lib, "wxmsw26d_gl.lib")
#pragma comment (lib, "wxmsw26d_core.lib")
#pragma comment (lib, "wxmsw26d_adv.lib")
#pragma comment (lib, "wxmsw26d_dbgrid.lib")
#pragma comment (lib, "wxbase26d.lib")
#pragma comment (lib, "wxtiffd.lib")
#pragma comment (lib, "wxjpegd.lib")
#pragma comment (lib, "wxpngd.lib")
#pragma comment (lib, "wxzlibd.lib")
#pragma comment (lib, "wxregexd.lib")
#pragma comment (lib, "wxexpatd.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "comctl32.lib")
#pragma comment (lib, "rpcrt4.lib")
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "odbc32.lib")
#else // !_DEBUG
#pragma comment (lib, "wxmsw26_propgrid.lib")
#pragma comment (lib, "wxmsw26_gl.lib")
#pragma comment (lib, "wxmsw26_core.lib")
#pragma comment (lib, "wxmsw26_adv.lib")
#pragma comment (lib, "wxmsw26_dbgrid.lib")
#pragma comment (lib, "wxbase26.lib")
#pragma comment (lib, "wxtiff.lib")
#pragma comment (lib, "wxjpeg.lib")
#pragma comment (lib, "wxpng.lib")
#pragma comment (lib, "wxzlib.lib")
#pragma comment (lib, "wxregex.lib")
#pragma comment (lib, "wxexpat.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "comctl32.lib")
#pragma comment (lib, "rpcrt4.lib")
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "odbc32.lib")
#endif // !_DEBUG


#endif // __WX_DIRECTX_H_

// -- EOF

